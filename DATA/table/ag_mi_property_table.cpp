#include "ag_mi_property_table.h"
#include "mysql_table.h"
#include "QsLog.h"

const QString ag_mi_property_table::c_field_cid = "mi_cid";
const QString ag_mi_property_table::c_field_pv_id = "pv_id";
const QString ag_mi_property_table::c_field_mi_type = "mi_type";
const QString ag_mi_property_table::c_field_nominal_power = "nominal_power";
const QString ag_mi_property_table::c_field_mim_version = "mim_version";
const QString ag_mi_property_table::c_field_mim2_version = "mim2_version";
const QString ag_mi_property_table::c_field_mim3_version = "mim3_version";
const QString ag_mi_property_table::c_field_mim4_version = "mim4_version";
const QString ag_mi_property_table::c_field_mis_version = "mis_version";
const QString ag_mi_property_table::c_field_mis2_version = "mis2_version";
const QString ag_mi_property_table::c_field_hard_version = "hard_version";
const QString ag_mi_property_table::c_field_property_reserve = "property_reserve";


ag_mi_property_table::ag_mi_property_table(QObject *parent)
    : QObject{parent}
{

}


void ag_mi_property_table::write_property(QSqlDatabase &m_database, QJsonObject &w_data)
{
    QSqlQuery query(m_database);
    quint16 data_count = 0;

    data_count = w_data.value("datas").toArray().size();

    for(int i=0;i<data_count;i++)
    {
        QJsonObject tmp_property_data = w_data.value("datas").toArray()[i].toObject();
        QString tmp_cmd = QString("INSERT INTO %1 (%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13) values(?,?,?,?,?,?,?,?,?,?,?,?) ON DUPLICATE KEY UPDATE %14=%15,"
                                  "%16='%17',%18='%19',%20='%21',%22='%23',%24='%25',%26='%27'")
                                   .arg(m_name,c_field_cid,c_field_pv_id,c_field_mi_type,c_field_nominal_power,c_field_mim_version,c_field_mim2_version,
                                   c_field_mim3_version,c_field_mim4_version,c_field_mis_version,c_field_mis2_version,c_field_hard_version,
                                   c_field_property_reserve,c_field_nominal_power,QString::number(tmp_property_data.value(c_field_nominal_power).toInt(1000000)),
                                   c_field_mim_version,tmp_property_data.value(c_field_mim_version).toString(""),
                                   c_field_mim2_version,tmp_property_data.value(c_field_mim2_version).toString(""),
                                   c_field_mim3_version,tmp_property_data.value(c_field_mim3_version).toString(""),
                                   c_field_mim4_version,tmp_property_data.value(c_field_mim4_version).toString(""),
                                   c_field_mis_version,tmp_property_data.value(c_field_mis_version).toString(""),
                                   c_field_mis2_version,tmp_property_data.value(c_field_mis2_version).toString(""));

        query.prepare(tmp_cmd);
        query.addBindValue(tmp_property_data.value(c_field_cid).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_pv_id).toInt(0));
        query.addBindValue(tmp_property_data.value(c_field_mi_type).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_nominal_power).toInt(1000000));
        query.addBindValue(tmp_property_data.value(c_field_mim_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_mim2_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_mim3_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_mim4_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_mis_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_mis2_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_hard_version).toString(""));
        query.addBindValue(tmp_property_data.value(c_field_property_reserve).toString(""));

        if(query.exec())
        {
            QLOG_INFO() << QString("插入微逆对象属性成功 %1").arg(tmp_property_data.value("room_id").toString(""));
        }
        else
        {
            QLOG_WARN() << QString("插入微逆对象属性失败 %1,%2,%3,%4")
                               .arg(tmp_property_data.value(c_field_cid).toString(""),
                                    QString::number(tmp_property_data.value(c_field_nominal_power).toInt(1000000)),
                                    tmp_property_data.value(c_field_mim_version).toString(""),
                                    tmp_property_data.value(c_field_mis_version).toString(""));
        }
    }
}
