#include "mainwindow.h"

#include <QApplication>
#include "mysql.h"

#define VERSION "软件版本1.01"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle(VERSION);

    mysql *tmp_mysql = nullptr;
    //初始化数据库表
    // tmp_mysql = new mysql("main_sql");
    // tmp_mysql->table_init();
    // delete tmp_mysql;

    w.show();
    return a.exec();
}
