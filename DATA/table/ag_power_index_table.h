#ifndef AG_POWER_INDEX_TABLE_H
#define AG_POWER_INDEX_TABLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>

class ag_power_index_table : public QObject
{
    Q_OBJECT
public:
    explicit ag_power_index_table(QObject *parent = nullptr);

    bool create_table(QSqlDatabase &m_database);
    bool delete_table(QSqlDatabase &m_database);
    void write_power_index(QSqlDatabase &m_database, QJsonObject &w_data);
    void read_power_index(QSqlDatabase &m_database,QJsonObject &r_data,QJsonObject &data);

    static const QString c_field_cid;
    static const QString c_field_date;
    static const QString c_field_pwtable_name;
private:
    QString m_name = "power_index_m_table";
};

#endif // AG_POWER_INDEX_TABLE_H
