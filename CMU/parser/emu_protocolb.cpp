#include "common.h"
#include "emu_protocolb.h"
#include "ag_emu_status_table.h"
#include "ag_emu_property_table.h"
#include "ag_power_data_table.h"
#include "ag_mi_property_table.h"
#include "ag_mi_fault_table.h"

emu_protocolb::emu_protocolb(QObject *parent)
    : QObject{parent}
{

}


void emu_protocolb::to_emu_status_json(QString Emuid, const QByteArray &s_data,QJsonObject &rt_data)
{
    QString emu_cid = Emuid.toUpper();
    QString sign = QString("%1").arg(common::qbtarray_to_u8(s_data,0),2,16,QLatin1Char('0'));
    QString status = QString("%1").arg(common::qbtarray_to_u32(s_data,1),8,16,QLatin1Char('0'));
    QString status_reserve = QString("%1").arg(common::qbtarray_to_u8(s_data,5),2,16,QLatin1Char('0'));
    QString run_mode = QString("%1").arg(common::qbtarray_to_u8(s_data,6),2,16,QLatin1Char('0'));
    QString func = QString("%1").arg(common::qbtarray_to_u16(s_data,7),4,16,QLatin1Char('0'));
    QString sys_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    rt_data.insert(ag_emu_status_table::c_field_emu_cid,emu_cid);
    rt_data.insert(ag_emu_status_table::c_field_status,status);
    rt_data.insert(ag_emu_status_table::c_field_status_reserve,status_reserve);
    rt_data.insert(ag_emu_status_table::c_field_run_mode,run_mode);
    rt_data.insert(ag_emu_status_table::c_field_sign,sign);
    rt_data.insert(ag_emu_status_table::c_field_func,func);
    rt_data.insert(ag_emu_status_table::c_field_sys_time,sys_time);
}

void emu_protocolb::to_emu_property_json(QString Emuid, const QByteArray &s_data, QJsonObject &rt_data)
{
    QJsonObject js_datas;
    js_datas.insert(ag_emu_property_table::c_field_emu_cid,Emuid.toUpper());
    js_datas.insert(ag_emu_property_table::c_field_hard_version,
                    QString("%1").arg(common::qbtarray_to_u16(s_data,0),4,16,QLatin1Char('0')));
    js_datas.insert(ag_emu_property_table::c_field_soft_version,
                    QString("%1").arg(common::qbtarray_to_u16(s_data,2),4,16,QLatin1Char('0')));
    js_datas.insert(ag_emu_property_table::c_field_type,
                    QString("%1").arg(common::qbtarray_to_u32(s_data,4),7,16,QLatin1Char('0')));
    js_datas.insert(ag_emu_property_table::c_field_reserve,
                    QString("%1").arg(common::qbtarray_to_u8(s_data,36),2,16,QLatin1Char('0')));
    rt_data.insert("datas",js_datas);
}

void emu_protocolb::to_powerdata_json(QString Emuid,const QByteArray &s_data, QJsonObject &rt_data,uint16_t &date)
{
    QString t_emu_cid = Emuid.toUpper();
    QString t_cur_date = common::get_system_detail_time();
    uint8_t t_data_nums = s_data.size() / 23; //设备数  //每路数据固定23个字节
    uint32_t start_index = 0;
    QJsonArray mis_jsarray;

    date = common::get_system_yearmon_time();

    for(int i=0;i<t_data_nums;i++)
    {
        QJsonObject mi_json;
        start_index = 23 * i;
        mi_json.insert(ag_power_data_table::c_field_emu_cid,t_emu_cid);
        mi_json.insert(ag_power_data_table::c_field_mi_cid,QString::number(common::qbtarray_to_u32(s_data,start_index),16)); //index 18-22);
        mi_json.insert(ag_power_data_table::c_field_pv_id,((uint8_t)s_data[start_index+4]) & 0x0F);
        mi_json.insert(ag_power_data_table::c_field_pv,((float)(common::qbtarray_to_u16(s_data,start_index + 5)))/512);    //*64/32768);
        mi_json.insert(ag_power_data_table::c_field_pcur,((float)(common::qbtarray_to_u16(s_data,start_index + 7))));
        mi_json.insert(ag_power_data_table::c_field_power,((float)(common::qbtarray_to_u16(s_data,start_index + 9)))/32);       //*1024/32768;);
        mi_json.insert(ag_power_data_table::c_field_energy,((float)(common::qbtarray_to_u32(s_data,start_index + 11)))/8192);   //*4/32768;);
        mi_json.insert(ag_power_data_table::c_field_temperature,((float)(common::qbtarray_to_u16(s_data,start_index + 15)))/128-40);   //*256/32768 -40;);
        mi_json.insert(ag_power_data_table::c_field_gridv,((float)(common::qbtarray_to_u16(s_data,start_index + 17)))/64);   //512/32768;);
        mi_json.insert(ag_power_data_table::c_field_gridcur,((float)(common::qbtarray_to_u16(s_data,start_index + 19))));
        mi_json.insert(ag_power_data_table::c_field_gridf,((float)(common::qbtarray_to_u16(s_data,start_index + 21)))/256);  //*128/32768;);
        mi_json.insert(ag_power_data_table::c_field_nominal_power,0);
        mi_json.insert(ag_power_data_table::c_field_reissue_data,"NO");
        mi_json.insert(ag_power_data_table::c_field_sys_time,t_cur_date);

        mis_jsarray.append(mi_json);
    }

    rt_data .insert("datas",mis_jsarray);
}

void emu_protocolb::to_faultdata_json(QString Emuid,const QByteArray &s_data, QJsonObject &rt_data,uint16_t &date)
{
    QString t_emu_cid = Emuid.toUpper();
    QString t_cur_date = common::get_system_detail_time();
    uint8_t t_data_nums = s_data.size() / 35;
    uint32_t start_index = 0;
    QJsonArray mis_jsarray;

    date = common::get_system_yearmon_time();

    for(int i=0;i<t_data_nums;i++)
    {
        QJsonObject mi_json;
        start_index = 35 * i;
        mi_json.insert(ag_mi_fault_table::c_field_emu_cid,t_emu_cid);
        mi_json.insert(ag_mi_fault_table::c_field_mi_cid,QString::number(common::qbtarray_to_u32(s_data,start_index),16)); //index 18-22);
        mi_json.insert(ag_mi_fault_table::c_field_pv_id,((uint8_t)s_data[start_index+4]) & 0x0F);
        mi_json.insert(ag_mi_fault_table::c_field_mim_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +5),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_mim2_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +7),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_mim3_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +9),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_mim4_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +11),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_mis_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +13),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_mis2_err,QString("%1").arg(common::qbtarray_to_u16(s_data,start_index +15),4,16,QLatin1Char('0')));
        mi_json.insert(ag_mi_fault_table::c_field_pv,((float)(common::qbtarray_to_u16(s_data,start_index + 17)))/512);    //*64/32768);
        mi_json.insert(ag_mi_fault_table::c_field_pcur,((float)(common::qbtarray_to_u16(s_data,start_index + 19))));
        mi_json.insert(ag_mi_fault_table::c_field_power,((float)(common::qbtarray_to_u16(s_data,start_index + 21)))/32);       //*1024/32768;);
        mi_json.insert(ag_mi_fault_table::c_field_energy,((float)(common::qbtarray_to_u32(s_data,start_index + 23)))/8192);   //*4/32768;);
        mi_json.insert(ag_mi_fault_table::c_field_temperature,((float)(common::qbtarray_to_u16(s_data,start_index + 27)))/128-40);   //*256/32768 -40;);
        mi_json.insert(ag_mi_fault_table::c_field_gridv,((float)(common::qbtarray_to_u16(s_data,start_index + 29)))/64);   //512/32768;);
        mi_json.insert(ag_mi_fault_table::c_field_gridcur,((float)(common::qbtarray_to_u16(s_data,start_index + 31))));
        mi_json.insert(ag_mi_fault_table::c_field_gridf,((float)(common::qbtarray_to_u16(s_data,start_index + 33)))/256);  //*128/32768;);
        mi_json.insert(ag_mi_fault_table::c_field_sys_time,t_cur_date);

        mis_jsarray.append(mi_json);
    }

    rt_data .insert("datas",mis_jsarray);
}

void emu_protocolb::to_mi_property_json(const QByteArray &s_data, QJsonObject &rt_data)
{
    uint8_t t_data_nums = s_data.size() / 37;
    uint32_t start_index = 0;

    QJsonArray mis_jsarray;
    for(int i=0;i<t_data_nums;i++)
    {
        QJsonObject mi_property_json;
        start_index = 37 * i;
        mi_property_json.insert(ag_mi_property_table::c_field_cid,QString::number(common::qbtarray_to_u32(s_data,start_index + 0),16));
        mi_property_json.insert(ag_mi_property_table::c_field_pv_id,((uint8_t)s_data[start_index + 4]) & 0x0F);
        mi_property_json.insert(ag_mi_property_table::c_field_mi_type,QString::number(common::qbtarray_to_u32(s_data,start_index + 5),16));
        mi_property_json.insert(ag_mi_property_table::c_field_nominal_power,(uint8_t)s_data[start_index + 21] *10);
        mi_property_json.insert(ag_mi_property_table::c_field_mim_version,QString::number(((uint8_t)s_data[start_index + 22]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 22]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_mim2_version,QString::number(((uint8_t)s_data[start_index + 24]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 24]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_mim3_version,QString::number(((uint8_t)s_data[start_index + 26]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 26]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_mim4_version,QString::number(((uint8_t)s_data[start_index + 28]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 28]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_mis_version,QString::number(((uint8_t)s_data[start_index + 30]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 30]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_mis2_version,QString::number(((uint8_t)s_data[start_index + 32]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 32]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_hard_version,QString::number(((uint8_t)s_data[start_index + 34]) >> 4) +
                                                                               "." + QString::number(((uint8_t)s_data[start_index + 34]) &0x0f));
        mi_property_json.insert(ag_mi_property_table::c_field_property_reserve,QString::number(common::qbtarray_to_u8(s_data,start_index + 36)));

        mis_jsarray.append(mi_property_json);
    }

    rt_data.insert("datas",mis_jsarray);
}

