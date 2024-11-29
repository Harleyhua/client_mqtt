INCLUDEPATH += \
    $$PWD/sql \
    $$PWD/table

DEPENDPATH += \
    $$PWD/sql \
    $$PWD/table

HEADERS += \
    $$PWD/sql/mysql.h \
    $$PWD/sql/mysql_table.h \
    $$PWD/sql/sqlconnectpool.h \
    $$PWD/table/ag_emu_property_table.h \
    $$PWD/table/ag_emu_status_table.h \
    $$PWD/table/ag_mi_fault_table.h \
    $$PWD/table/ag_mi_property_table.h \
    $$PWD/table/ag_power_data_table.h \
    $$PWD/table/ag_power_index_table.h

SOURCES += \
    $$PWD/sql/mysql.cpp \
    $$PWD/sql/mysql_table.cpp \
    $$PWD/sql/sqlconnectpool.cpp \
    $$PWD/table/ag_emu_property_table.cpp \
    $$PWD/table/ag_emu_status_table.cpp \
    $$PWD/table/ag_mi_fault_table.cpp \
    $$PWD/table/ag_mi_property_table.cpp \
    $$PWD/table/ag_power_data_table.cpp \
    $$PWD/table/ag_power_index_table.cpp
