CONFIG += c++11

INCLUDEPATH += \
    $$PWD/QsLog

DEPENDPATH += \
    $$PWD/QsLog

DEFINES += QS_LOG_LINE_NUMBERS

HEADERS += \
    $$PWD/QsLog/QsLog.h \
    $$PWD/QsLog/QsLogDest.h \
    $$PWD/QsLog/QsLogDisableForThisFile.h \
    $$PWD/QsLog/QsLogLevel.h

LIBS += -L$$PWD/bin -lQsLog2
