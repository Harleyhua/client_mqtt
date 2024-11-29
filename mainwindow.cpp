#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDateTime>
//#include <QtMqtt/QMqttClient>
#include <Qtmqtt/qmqttclient.h>
#include <QtWidgets/QMessageBox>
#include <QJsonObject>
#include "mysql.h"
#include "emu_protocolb.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->EditLog->setReadOnly(true);
    ui->LineEditHost->setText("47.97.180.36");

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->LineEditHost->text());
    m_client->setPort(ui->SpinBoxPort->value());
    m_client->setClientId(ui->Client_id->text());
    m_client->setUsername(ui->Username->text());
    m_client->setPassword(ui->Password->text());
    m_client->setCleanSession(true);

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" Received Topic: ")
                                + topic.name()
                                + QLatin1String(" Message: ")
                                + message.toHex()
                                + QLatin1Char('\n');
        ui->EditLog->insertPlainText(content);
        topic_type(message,topic);
    });

    //确认客户端与代理服务器之间的连接是否保持活跃
    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" PingResponse")
                                + QLatin1Char('\n');
        ui->EditLog->insertPlainText(content);
    });

    connect(ui->LineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->SpinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    updateLogStateChange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonConnect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected)
    {
        ui->LineEditHost->setEnabled(false);
        ui->SpinBoxPort->setEnabled(false);
        ui->Client_id->setEnabled(false);
        ui->Username->setEnabled(false);
        ui->Password->setEnabled(false);
        ui->ButtonConnect->setText(tr("Disconnect"));
        m_client->connectToHost();
    }
    else
    {
        ui->LineEditHost->setEnabled(true);
        ui->SpinBoxPort->setEnabled(true);
        ui->Client_id->setEnabled(true);
        ui->Username->setEnabled(true);
        ui->Password->setEnabled(true);
        ui->ButtonConnect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_ButtonQuit_clicked()
{
    QApplication::quit();
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                            + QLatin1String(": State Change")
                            + QString::number(m_client->state())
                            + QLatin1Char('\n');
    ui->EditLog->insertPlainText(content);
}

void MainWindow::brokerDisconnected()
{
    ui->LineEditHost->setEnabled(true);
    ui->SpinBoxPort->setEnabled(true);
    ui->ButtonConnect->setText(tr("Connect"));
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(p);
}

void MainWindow::on_ButtonPublish_clicked()
{
    if (m_client->publish(ui->LineEditTopic->text(), ui->LineEditMessage->text().toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}

void MainWindow::on_ButtonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->LineEditTopic->text());
    if (!subscription)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}

void MainWindow::topic_type(const QByteArray &message,const QMqttTopicName &topic)
{
    QJsonObject js_obj;
    emu_protocolb tmp_pcol;
    mysql sql(m_name + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    QString type = topic.name();
    QString emuid = type.mid(4,8);
    QStringList parts = type.split('/');
    QString topic_type = parts.at(2);

    if(topic_type == "status")
    {
        tmp_pcol.to_emu_status_json(emuid,message,js_obj);
        sql.w_emu_status(js_obj);
    }
    else if (topic_type == "version")
    {
        tmp_pcol.to_emu_property_json(emuid,message,js_obj);
        sql.w_emu_property(js_obj);
    }
    else if (topic_type == "event")
    {
        uint16_t date = 0;
        tmp_pcol.to_powerdata_json(emuid,message,js_obj,date);
        sql.w_power(js_obj,date);
    }
    else if (topic_type == "fault")
    {
        uint16_t date = 0;
        tmp_pcol.to_faultdata_json(emuid,message,js_obj,date);
        sql.w_fault(js_obj,date);
    }
    else if (topic_type == "prisec")
    {
        tmp_pcol.to_mi_property_json(message,js_obj);
        sql.w_mi_property(js_obj);
    }
    else if (topic_type == "will")
    {
        // tmp_pcol.to_mi_property_json(emuid,message,js_obj);
        // sql.w_mi_property(js_obj);
    }
}

