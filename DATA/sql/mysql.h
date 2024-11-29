#ifndef MYSQL_H
#define MYSQL_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMutex>

extern QMutex emu_act_cache_lock;

enum sql_type {MYSQL};


class mysql : public QObject
{
    Q_OBJECT
public:
    explicit mysql(QString db_name,QObject *parent = nullptr);
    ~mysql();
    QString dbName()
    {
        return db_name;
    };
    QSqlDatabase& db()
    {
        return m_db;
    };

    bool create_database(QString database_name);
    bool delete_database(QString database_name);

    bool table_init();

    void w_emu_status(QJsonObject &s_data);
    void w_emu_property(QJsonObject &s_data);
    void write_power_index(QSqlDatabase &m_database,QJsonObject &w_data);
    void w_power(QJsonObject &s_data, uint16_t date);
    void w_fault(QJsonObject &s_data, uint16_t date);
    void w_mi_property(QJsonObject &s_data);


    QSqlDatabase getQSqlDatabaseFromMysql();
    static QHash<QString,QString> m_emucid_hand_lastTime;
private:
    QString db_name; //用什么链接名称
    QSqlDatabase m_db; //数据库
};

#endif // MYSQL_H
