#include "mysql.h"
#include "QsLog.h"
#include "sqlconnectpool.h"
#include "ag_emu_status_table.h"
#include "ag_emu_property_table.h"
#include "ag_power_data_table.h"
#include "ag_power_index_table.h"
#include "ag_mi_property_table.h"
#include "ag_mi_fault_table.h"

extern mysql_login_stc login_param;


QMutex sql_lock;   //数据库建立连接锁，避免多线程是同时连接的异常
QMutex emu_act_cache_lock;
//mysql_login_stc login_param = {"127.0.0.1",3306,"jack_lin","zbeny001","bydas2"};   //本机
//mysql_login_stc login_param = {"1.117.152.46",3306,"root","zjbeny001","bydas"};

QHash<QString,QString> mysql::m_emucid_hand_lastTime{};

mysql::mysql(QString db_name, QObject *parent)
    : QObject{parent}
{
    //this->db_name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + db_name +common::rand_str();
    this->db_name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + db_name ;

    m_db = sqlconnectpool::openConnection(db_name);
}

QSqlDatabase mysql::getQSqlDatabaseFromMysql()
{
    return m_db;
}

mysql::~mysql()
{
    sqlconnectpool::closeConnection(m_db,db_name);
}

// bool mysql::create_database(QString database_name)
// {
//     QSqlQuery query = QSqlQuery(m_db);
//     if(query.exec("CREATE DATABASE IF NOT EXISTS "+ database_name +" CHARACTER SET utf8mb4"))
//     {
//         QLOG_INFO() << QString("创建数据库:%1 成功").arg(database_name);
//     }
//     else
//     {
//         QLOG_WARN() << QString("创建数据库: %1 失败").arg(database_name);
//         return false;
//     }
//     return true;
// }

// bool mysql::delete_database(QString database_name)
// {
//     QSqlQuery query = QSqlQuery(m_db);
//     if(query.exec("DROP DATABASE IF EXISTS " + database_name))
//     {
//         QLOG_INFO() << QString("删除数据库:%1 成功").arg(database_name);
//     }
//     else
//     {
//         QLOG_WARN() << QString("删除数据库: %1 失败").arg(database_name);
//         return false;
//     }
//     return true;
// }

// bool mysql::table_init()
// {
//     bool ret = true;

//     ag_emu_property_table tmp_emu_pro_tb;
//     ag_emu_status_table tmp_emu_status_tb;
//     ag_mi_fault_table tmp_mi_fault_tb;
//     ag_mi_property_table tmp_mi_pro_tb;
//     ag_power_index_table tmp_pw_idx_tb;

//     ret &= create_database(m_db.databaseName());
//     ret &= tmp_emu_pro_tb.create_table(m_db);
//     ret &= tmp_emu_status_tb.create_table(m_db);
//     ret &= tmp_mi_fault_tb.create_table(m_db);
//     ret &= tmp_mi_pro_tb.create_table(m_db);
//     ret &= tmp_pw_idx_tb.create_table(m_db);

//     for(int i=1;i<=12;i++)
//     {
//         QString year = QDateTime::currentDateTime().toString("yy");
//         QString name = "power_data_" + year + QString::number(i).rightJustified(2, '0')+ "_1";
//         ag_power_data_table tmp_pw_dt_tb(name);
//         ret &= tmp_pw_dt_tb.create_table(m_db);
//     }
//     return ret;
// }

void mysql::w_emu_status(QJsonObject &s_data)
{
    ag_emu_status_table tb;
    tb.w_data(m_db,s_data);
}

void mysql::w_emu_property(QJsonObject &s_data)
{
    ag_emu_property_table tmp_emu_property_tb;
    tmp_emu_property_tb.write_property(m_db,s_data);
}

void mysql::w_mi_property(QJsonObject &s_data)
{
    ag_mi_property_table tmp_mi_pty_tb;
    tmp_mi_pty_tb.write_property(m_db,s_data);
}

void mysql::w_power(QJsonObject &s_data, uint16_t date)
{
    QString table_name;
    //uint16_t date = common::get_system_yearmon_time();
    QJsonArray power_datas = s_data.value("datas").toArray();

    for(int i=0;i<power_datas.size();i++)
    {
        ag_power_index_table tmp_pw_idx_tb;
        QJsonArray table_list;
        QJsonObject idx_r_data;
        QJsonObject idx_datas;
        QJsonObject rt_data;
        idx_datas.insert("mi_cid",power_datas[i].toObject().value("mi_cid").toString());
        idx_datas.insert("date",date);
        idx_r_data.insert("params",idx_datas);

        tmp_pw_idx_tb.read_power_index(m_db,idx_r_data,rt_data);

        table_list = rt_data.value("datas").toObject().value("datatable_name").toArray();

        if(table_list.size() >0)
        {
            table_name = table_list[0].toString();
        }
        else
        {
            table_name = "power_data_m_" + QString::number(date) + "_1";
            idx_r_data.insert("datatable_name",table_name);
            QJsonObject w_data;
            QJsonObject w_datas;
            w_datas.insert("mi_cid",power_datas[i].toObject().value("mi_cid").toString());
            w_datas.insert("date",date);
            w_datas.insert("datatable_name",table_name);
            w_data.insert("datas",w_datas);
            tmp_pw_idx_tb.write_power_index(m_db,w_data);
        }
    }
    ag_power_data_table tmp_pw_data_tb(table_name);
    //写发电数据
    tmp_pw_data_tb.write_data(m_db,s_data);
}

void mysql::w_fault(QJsonObject &s_data, uint16_t date)
{
    ag_mi_fault_table tmp_mi_fault_tb;
    tmp_mi_fault_tb.write_data(m_db,s_data);
}
