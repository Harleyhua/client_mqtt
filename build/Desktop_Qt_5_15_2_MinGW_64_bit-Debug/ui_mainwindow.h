/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QFormLayout *formLayout_3;
    QLabel *label_9;
    QLineEdit *LineEditHost;
    QLabel *label_10;
    QSpinBox *SpinBoxPort;
    QLabel *label_20;
    QLineEdit *Username;
    QLineEdit *Password;
    QLabel *label_13;
    QLabel *label_21;
    QLineEdit *Client_id;
    QPushButton *ButtonConnect;
    QGridLayout *gridLayout_3;
    QLineEdit *LineEditMessage;
    QLabel *label_11;
    QPushButton *ButtonSubscribe;
    QPushButton *ButtonPublish;
    QLineEdit *LineEditTopic;
    QLabel *label_12;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QPlainTextEdit *EditLog;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *HorizontalSpacer;
    QPushButton *ButtonQuit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(966, 781);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_9);

        LineEditHost = new QLineEdit(centralwidget);
        LineEditHost->setObjectName(QString::fromUtf8("LineEditHost"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, LineEditHost);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_10);

        SpinBoxPort = new QSpinBox(centralwidget);
        SpinBoxPort->setObjectName(QString::fromUtf8("SpinBoxPort"));
        SpinBoxPort->setMaximum(99999);
        SpinBoxPort->setValue(1883);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, SpinBoxPort);

        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_20);

        Username = new QLineEdit(centralwidget);
        Username->setObjectName(QString::fromUtf8("Username"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, Username);

        Password = new QLineEdit(centralwidget);
        Password->setObjectName(QString::fromUtf8("Password"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, Password);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_13);

        label_21 = new QLabel(centralwidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, label_21);

        Client_id = new QLineEdit(centralwidget);
        Client_id->setObjectName(QString::fromUtf8("Client_id"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, Client_id);


        horizontalLayout_7->addLayout(formLayout_3);

        ButtonConnect = new QPushButton(centralwidget);
        ButtonConnect->setObjectName(QString::fromUtf8("ButtonConnect"));

        horizontalLayout_7->addWidget(ButtonConnect);


        gridLayout_4->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        LineEditMessage = new QLineEdit(centralwidget);
        LineEditMessage->setObjectName(QString::fromUtf8("LineEditMessage"));

        gridLayout_3->addWidget(LineEditMessage, 1, 1, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 1, 0, 1, 1);

        ButtonSubscribe = new QPushButton(centralwidget);
        ButtonSubscribe->setObjectName(QString::fromUtf8("ButtonSubscribe"));

        gridLayout_3->addWidget(ButtonSubscribe, 0, 2, 1, 1);

        ButtonPublish = new QPushButton(centralwidget);
        ButtonPublish->setObjectName(QString::fromUtf8("ButtonPublish"));

        gridLayout_3->addWidget(ButtonPublish, 1, 2, 1, 1);

        LineEditTopic = new QLineEdit(centralwidget);
        LineEditTopic->setObjectName(QString::fromUtf8("LineEditTopic"));

        gridLayout_3->addWidget(LineEditTopic, 0, 1, 1, 1);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        EditLog = new QPlainTextEdit(groupBox);
        EditLog->setObjectName(QString::fromUtf8("EditLog"));

        horizontalLayout_8->addWidget(EditLog);


        gridLayout_4->addWidget(groupBox, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        HorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(HorizontalSpacer);

        ButtonQuit = new QPushButton(centralwidget);
        ButtonQuit->setObjectName(QString::fromUtf8("ButtonQuit"));

        horizontalLayout_9->addWidget(ButtonQuit);


        gridLayout_4->addLayout(horizontalLayout_9, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 966, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Host:", nullptr));
        LineEditHost->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        Username->setText(QString());
        Password->setText(QString());
        label_13->setText(QCoreApplication::translate("MainWindow", "Client_id:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        Client_id->setText(QString());
        ButtonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        LineEditMessage->setText(QCoreApplication::translate("MainWindow", "This is a test message", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Message:", nullptr));
        ButtonSubscribe->setText(QCoreApplication::translate("MainWindow", "Subscribe", nullptr));
        ButtonPublish->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        LineEditTopic->setText(QCoreApplication::translate("MainWindow", "BYM/+/+", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Topic:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Log Messages", nullptr));
        ButtonQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
