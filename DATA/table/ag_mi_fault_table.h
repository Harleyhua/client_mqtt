#ifndef AG_MI_FAULT_TABLE_H
#define AG_MI_FAULT_TABLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>
#include <QJsonObject>

class ag_mi_fault_table:public QObject
{
    Q_OBJECT
public:
    ag_mi_fault_table(QString name,QObject *parent = nullptr);
    ag_mi_fault_table(QObject *parent = nullptr);

    bool create_table(QSqlDatabase &m_database);
    bool delete_table(QSqlDatabase &m_database);
    void write_data(QSqlDatabase &m_database,QJsonObject &w_data);

    static const QString c_field_id;
    static const QString c_field_emu_cid;
    static const QString c_field_mi_cid;
    static const QString c_field_pv_id;
    static const QString c_field_mim_err;
    static const QString c_field_mim2_err;
    static const QString c_field_mim3_err;
    static const QString c_field_mim4_err;
    static const QString c_field_mis_err;
    static const QString c_field_mis2_err;
    static const QString c_field_pv;
    static const QString c_field_pcur;
    static const QString c_field_power;
    static const QString c_field_energy;
    static const QString c_field_temperature;
    static const QString c_field_gridv;
    static const QString c_field_gridcur;
    static const QString c_field_gridf;
    static const QString c_field_sys_time;

private:
    QString m_name = "mi_fault";
};

#endif // AG_MI_FAULT_TABLE_H
