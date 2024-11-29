#include "sqlconnectpool.h"
#include "QsLog.h"

QMutex sqlconnectpool::mutex;
QWaitCondition sqlconnectpool::waitConnection;
sqlconnectpool* sqlconnectpool::instance = NULL;

extern QMutex sql_lock;
//mysql_login_stc login_param = {"127.0.0.1",3306,"jack_lin","zbeny001","bydas"};  //老化房 测试 本机
mysql_login_stc login_param = {"127.0.0.1",3306,"root","123456","bydas"};
//mysql_login_stc login_param = {"47.97.180.36",3306,"jack_lin","zbeny001","bydas"};

sqlconnectpool::sqlconnectpool()
{
    testOnBorrow = true;
    testOnBorrowSql = "SELECT 1";

    maxWaitTime  = 1000;
    waitInterval = 200;
    maxConnectionCount  = 300;
}

sqlconnectpool::~sqlconnectpool()
{
    // 销毁连接池的时候删除所有的连接
    foreach(QString connectionName, usedConnectionNames)
    {
        QSqlDatabase::removeDatabase(connectionName);
    }

    foreach(QString connectionName, unusedConnectionNames)
    {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

sqlconnectpool& sqlconnectpool::getInstance()
{
    if (NULL == instance)
    {
        QMutexLocker locker(&mutex);

        if (NULL == instance)
        {
            instance = new sqlconnectpool();
        }
    }

    return *instance;
}

void sqlconnectpool::release()
{
    QMutexLocker locker(&mutex);
    delete instance;
    instance = NULL;
}

QSqlDatabase sqlconnectpool::openConnection()
{
    sqlconnectpool& pool = sqlconnectpool::getInstance();
    QString connectionName;

    QMutexLocker locker(&mutex);

    int connectionCount = pool.unusedConnectionNames.size() + pool.usedConnectionNames.size();
    for (int i = 0;i < pool.maxWaitTime && pool.unusedConnectionNames.size() == 0
        && connectionCount == pool.maxConnectionCount; i += pool.waitInterval)
    {
        waitConnection.wait(&mutex, pool.waitInterval);

        connectionCount = pool.unusedConnectionNames.size() + pool.usedConnectionNames.size();
    }

    if (pool.unusedConnectionNames.size() > 0)
    {
        connectionName = pool.unusedConnectionNames.dequeue();
    }
    else if (connectionCount < pool.maxConnectionCount)
    {
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }
    else
    {
        QLOG_DEBUG() << "sql连接池已经达到最大连接数";
        return QSqlDatabase();
    }
    QSqlDatabase db = pool.createConnection(connectionName);

    if (db.isOpen())
    {
        QLOG_DEBUG() << "从连接池 connect sql db成功";
        pool.usedConnectionNames.enqueue(connectionName);
    }

    return db;
}

void sqlconnectpool::closeConnection(QSqlDatabase connection)
{
    sqlconnectpool& pool = sqlconnectpool::getInstance();
    QString connectionName = connection.connectionName();
    QSqlDatabase db1 = QSqlDatabase::database(connectionName);
    // 如果是我们创建的连接，从 used 里删除，放入 unused 里
    if (pool.usedConnectionNames.contains(connectionName))
    {
        QMutexLocker locker(&mutex);
        pool.usedConnectionNames.removeOne(connectionName);
        //pool.unusedConnectionNames.enqueue(connectionName);

        db1.close();
        db1 = QSqlDatabase();  //重置db
        db1.removeDatabase(connectionName);

        waitConnection.wakeOne();

        QLOG_DEBUG() << "关闭一个sql连接成功 连接名:" + connectionName;
    }
}

QSqlDatabase sqlconnectpool::openConnection(QString name)
{
    QSqlDatabase db;
    sql_lock.lock();
    db = QSqlDatabase::addDatabase("QMYSQL",name);
    db.setHostName(login_param.hostname);
    db.setPort(login_param.port);
    db.setUserName(login_param.username);
    db.setPassword(login_param.password);
    //m_db.setDatabaseName(login_param.database_name);
    db.open();

    sql_lock.unlock();
    //如果数据库未被建立  不能先setdatabasename
    db.setDatabaseName(login_param.database_name);
    QSqlQuery query(db);
    query.exec("USE " + login_param.database_name);
    return db;
}


void sqlconnectpool::closeConnection(QSqlDatabase db,QString name)
{
    sql_lock.lock();
    db.close();
    db = QSqlDatabase();  //重置db
    db.removeDatabase(name);
    sql_lock.unlock();
}

QSqlDatabase sqlconnectpool::createConnection(const QString &connectionName)
{

    // 连接已经创建过了，复用它，而不是重新创建
    if (QSqlDatabase::contains(connectionName))
    {
        QSqlDatabase db1 = QSqlDatabase::database(connectionName);

        if (testOnBorrow)
        {
            // 返回连接前访问数据库，如果连接断开，重新建立连接
            //qDebug() << "Test connection on borrow, execute:" << testOnBorrowSql << ", for" << connectionName;
            QSqlQuery query(testOnBorrowSql, db1);
            if (query.lastError().type() != QSqlError::NoError && !db1.open())
            {
                //qDebug() << "Open datatabase error:" << db1.lastError().text();
                return QSqlDatabase();
            }
        }

        return db1;
    }
    // 创建一个新的连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL",connectionName);
    QSqlQuery query(db);

    db.setHostName(login_param.hostname);
    db.setPort(login_param.port);
    db.setUserName(login_param.username);
    db.setPassword(login_param.password);

    if (!db.open())
    {
        return QSqlDatabase();
    }
    db.setDatabaseName(login_param.database_name);
    query.exec("USE " + login_param.database_name);
    return db;
}
