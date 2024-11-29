#ifndef AG_POWER_DATA_TABLE_H
#define AG_POWER_DATA_TABLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>

class ag_power_data_table : public QObject
{
    Q_OBJECT
public:
    ag_power_data_table(QString name,QObject *parent = nullptr);
    ag_power_data_table(QObject *parent = nullptr);

    bool create_table(QSqlDatabase &m_database);
    bool delete_table(QSqlDatabase &m_database);

    void write_data(QSqlDatabase &m_database,QJsonObject &w_data);

    static const QString c_field_id;
    static const QString c_field_emu_cid;
    static const QString c_field_emu_time;
    static const QString c_field_mi_cid;
    static const QString c_field_mim_version;
    static const QString c_field_mis_version;
    static const QString c_field_hard_version;
    static const QString c_field_pv;
    static const QString c_field_pcur;
    static const QString c_field_power;
    static const QString c_field_energy;
    static const QString c_field_temperature;
    static const QString c_field_gridv;
    static const QString c_field_gridcur;
    static const QString c_field_gridf;
    static const QString c_field_mim_err;
    static const QString c_field_mis_err;
    static const QString c_field_pv_id;
    static const QString c_field_nominal_power;
    static const QString c_field_reissue_data;
    static const QString c_field_sys_time;

private:
    QString m_name = "";
};

#endif // AG_POWER_DATA_TABLE_H
