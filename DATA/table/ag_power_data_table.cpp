#include "ag_power_data_table.h"
#include "mysql_table.h"
#include "QsLog.h"

const QString ag_power_data_table::c_field_id = "id";
const QString ag_power_data_table::c_field_emu_cid = "emu_cid";
const QString ag_power_data_table::c_field_emu_time = "emu_time";
const QString ag_power_data_table::c_field_mi_cid = "mi_cid";
const QString ag_power_data_table::c_field_mim_version = "mim_version";
const QString ag_power_data_table::c_field_mis_version = "mis_version";
const QString ag_power_data_table::c_field_hard_version = "hard_version";
const QString ag_power_data_table::c_field_pv = "pv";
const QString ag_power_data_table::c_field_pcur = "pcur";
const QString ag_power_data_table::c_field_power = "power";
const QString ag_power_data_table::c_field_energy = "energy";
const QString ag_power_data_table::c_field_temperature = "temperature";
const QString ag_power_data_table::c_field_gridv = "gridv";
const QString ag_power_data_table::c_field_gridcur = "gridcur";
const QString ag_power_data_table::c_field_gridf = "gridf";
const QString ag_power_data_table::c_field_mim_err = "mim_err";
const QString ag_power_data_table::c_field_mis_err = "mis_err";
const QString ag_power_data_table::c_field_pv_id = "pv_id";
const QString ag_power_data_table::c_field_nominal_power = "nominal_power";
const QString ag_power_data_table::c_field_reissue_data = "reissue_data";
const QString ag_power_data_table::c_field_sys_time = "sys_time";

ag_power_data_table::ag_power_data_table(QString name, QObject *parent)
    : QObject{parent}
{
    m_name = name;
}

ag_power_data_table::ag_power_data_table(QObject *parent)
    : QObject{parent}
{

}

void ag_power_data_table::write_data(QSqlDatabase &m_database, QJsonObject &w_data)
{
    QSqlQuery query(m_database);
    QJsonArray tmp_datas = w_data.value("datas").toArray();

    QString head = QString("INSERT INTO %1 ").arg(m_name);
    QString cmd = QString("(%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)")
                      .arg(c_field_emu_cid,c_field_mi_cid,c_field_pv_id,c_field_pv,c_field_pcur,c_field_power,c_field_energy,
                           c_field_temperature,c_field_gridv,c_field_gridf,c_field_gridcur,c_field_reissue_data,c_field_sys_time);
    QVariantList records[13];
    for(int i=0;i<tmp_datas.size();i++)
    {
        QJsonObject mi_pw_obj = tmp_datas[i].toObject();
        records[0] << mi_pw_obj.value(c_field_emu_cid).toString();
        records[1] << mi_pw_obj.value(c_field_mi_cid).toString();
        records[2] << mi_pw_obj.value(c_field_pv_id).toInt();
        records[3] << mi_pw_obj.value(c_field_pv).toDouble();
        records[4] << mi_pw_obj.value(c_field_pcur).toDouble();
        records[5] << mi_pw_obj.value(c_field_power).toDouble();
        records[6] << mi_pw_obj.value(c_field_energy).toDouble();
        records[7] << mi_pw_obj.value(c_field_temperature).toDouble();
        records[8] << mi_pw_obj.value(c_field_gridv).toDouble();
        records[9] << mi_pw_obj.value(c_field_gridf).toDouble();
        records[10] << mi_pw_obj.value(c_field_gridcur).toDouble();
        records[11] << mi_pw_obj.value(c_field_reissue_data).toString();
        records[12] << mi_pw_obj.value(c_field_sys_time).toString();
    }

    query.prepare(head + cmd);
    query.addBindValue(records[0]);
    query.addBindValue(records[1]);
    query.addBindValue(records[2]);
    query.addBindValue(records[3]);
    query.addBindValue(records[4]);
    query.addBindValue(records[5]);
    query.addBindValue(records[6]);
    query.addBindValue(records[7]);
    query.addBindValue(records[8]);
    query.addBindValue(records[9]);
    query.addBindValue(records[10]);
    query.addBindValue(records[11]);
    query.addBindValue(records[12]);

    if(query.execBatch())
    {
        QLOG_INFO() << QString("微逆:%1 写入发电数据表成功");
    }
    else
    {
        QLOG_WARN() << QString("微逆:%1 写入发电数据表失败");
    }
}

