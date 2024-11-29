QT       += core gui network mqtt sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(./DATA/DATA.pri)
include(./CMU/CMU.pri)
include(./COMMON/COMMON.pri)
include(./OPEN_LIB/OPEN_LIB.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

RC_ICONS = client.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/log_doc/httpserver_log.log \
    ../build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/log_doc/sys_config/http_server.ini
