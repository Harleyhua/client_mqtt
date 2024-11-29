#include "ag_emu_status_table.h"
#include "mysql_table.h"

#include <QVariant>
#include <QSqlQuery>
#include <QDateTime>
#include <QJsonArray>

const QString ag_emu_status_table::c_field_emu_cid = "emu_cid";
const QString ag_emu_status_table::c_field_status = "status";
const QString ag_emu_status_table::c_field_status_reserve = "status_reserve";
const QString ag_emu_status_table::c_field_run_mode = "run_mode";
const QString ag_emu_status_table::c_field_sign = "sign";
const QString ag_emu_status_table::c_field_func = "func";
const QString ag_emu_status_table::c_field_sys_time = "sys_time";

ag_emu_status_table::ag_emu_status_table(QObject *parent)
    : QObject{parent}
{

}

void ag_emu_status_table::w_data(QSqlDatabase &m_database,QJsonObject data)
{
    QString tmp_cmd = QString("INSERT INTO %1 (%2,%3,%4,%5,%6,%7,%8) VALUES (?,?,?,?,?,?,?)")
                          .arg(m_name,c_field_emu_cid,c_field_status,c_field_status_reserve,
                               c_field_run_mode,c_field_sign,c_field_func,c_field_sys_time);
    QSqlQuery query(m_database);

    query.prepare(tmp_cmd);
    query.addBindValue(data.value(c_field_emu_cid));
    query.addBindValue(data.value(c_field_status));
    query.addBindValue(data.value(c_field_status_reserve));
    query.addBindValue(data.value(c_field_run_mode));
    query.addBindValue(data.value(c_field_sign));
    query.addBindValue(data.value(c_field_func));
    query.addBindValue(data.value(c_field_sys_time));
    if(query.exec())
    {

    }
}
