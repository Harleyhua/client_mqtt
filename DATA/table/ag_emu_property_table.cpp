#include "ag_emu_property_table.h"
#include "mysql_table.h"
#include "QsLog.h"

const QString ag_emu_property_table::c_field_emu_cid = "emu_cid";
const QString ag_emu_property_table::c_field_type = "type";
const QString ag_emu_property_table::c_field_hard_version = "hard_version";
const QString ag_emu_property_table::c_field_soft_version = "soft_version";
const QString ag_emu_property_table::c_field_reserve = "reserve";


ag_emu_property_table::ag_emu_property_table(QObject *parent)
    : QObject{parent}
{

}

void ag_emu_property_table::write_property(QSqlDatabase &m_database, QJsonObject &w_data)
{
    QSqlQuery query(m_database);
    QJsonObject property_data = w_data.value("datas").toObject();
    QString tmp_cmd = QString("INSERT INTO %1 (%2,%3,%4,%5,%6) values(?,?,?,?,?) ON DUPLICATE KEY UPDATE %7='%8',%9='%10',%11='%12'")
                          .arg(m_name,c_field_emu_cid,c_field_type,c_field_hard_version,c_field_soft_version,c_field_reserve,
                               c_field_type,property_data.value(c_field_type).toString(),
                               c_field_hard_version,property_data.value(c_field_hard_version).toString(),
                               c_field_soft_version,property_data.value(c_field_soft_version).toString());
    query.prepare(tmp_cmd);
    query.addBindValue(property_data.value(c_field_emu_cid).toString(""));
    query.addBindValue(property_data.value(c_field_type).toString(""));
    query.addBindValue(property_data.value(c_field_hard_version).toString(""));
    query.addBindValue(property_data.value(c_field_soft_version).toString(""));
    query.addBindValue(property_data.value(c_field_reserve).toString(""));

    if(query.exec())
    {

    }
    else
    {
        QLOG_WARN() << "写 网关属性表 失败";
    }

}
