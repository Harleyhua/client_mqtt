#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtMqtt/QMqttClient>
#include <Qtmqtt/qmqttclient.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setClientPort(int p);

private slots:
    void updateLogStateChange();

    void brokerDisconnected();

    void on_ButtonConnect_clicked();

    void on_ButtonSubscribe_clicked();

    void on_ButtonPublish_clicked();

    void on_ButtonQuit_clicked();

    void topic_type(const QByteArray &message,const QMqttTopicName &topic);

protected:
    QString m_name = "";

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;
};

#endif // MAINWINDOW_H
