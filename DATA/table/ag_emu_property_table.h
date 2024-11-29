#ifndef AG_EMU_PROPERTY_TABLE_H
#define AG_EMU_PROPERTY_TABLE_H

#include <QJsonObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class ag_emu_property_table : public QObject
{
    Q_OBJECT
public:
    explicit ag_emu_property_table(QObject *parent = nullptr);

    static const QString c_field_emu_cid;
    static const QString c_field_type;
    static const QString c_field_hard_version;
    static const QString c_field_soft_version;
    static const QString c_field_reserve;

    bool create_table(QSqlDatabase &m_database);
    bool delete_table(QSqlDatabase &m_database);

    void write_property(QSqlDatabase &m_database,QJsonObject &w_data);
    //void read_property(QSqlDatabase &m_database,QJsonObject &r_data,QJsonObject &data);
    //void read_property(QSqlDatabase &m_database,QString cid,QJsonObject &data);
private:
    QString m_name = "emu_property_m_table";

signals:

};

#endif // AG_EMU_PROPERTY_TABLE_H
