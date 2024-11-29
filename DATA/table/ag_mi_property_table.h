#ifndef AG_MI_PROPERTY_TABLE_H
#define AG_MI_PROPERTY_TABLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>
#include <QJsonObject>

class ag_mi_property_table : public QObject
{
    Q_OBJECT
public:
    explicit ag_mi_property_table(QObject *parent = nullptr);

    bool create_table(QSqlDatabase &m_database);
    bool delete_table(QSqlDatabase &m_database);

    void write_property(QSqlDatabase &m_database,QJsonObject &w_data);

    static const QString c_field_cid;
    static const QString c_field_pv_id;
    static const QString c_field_mi_type;
    static const QString c_field_nominal_power;
    static const QString c_field_mim_version;
    static const QString c_field_mim2_version;
    static const QString c_field_mim3_version;
    static const QString c_field_mim4_version;
    static const QString c_field_mis_version;
    static const QString c_field_mis2_version;
    static const QString c_field_hard_version;
    static const QString c_field_property_reserve;

private:
    QString m_name = "mi_m_table";

};

#endif // AG_MI_PROPERTY_TABLE_H
