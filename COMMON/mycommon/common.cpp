#include "common.h"

#include <QRegExp>
#include <QHostInfo>
#include <QDateTime>
#include <QByteArray>
#include <QTextCodec>
#include <QTime>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>


common::common(QObject *parent)
    : QObject{parent}
{

}

uint8_t common::qbtarray_to_u8(const QByteArray &ay, uint16_t index)
{
    return (uint8_t)ay[index];
}

uint16_t common::qbtarray_to_u16(const QByteArray &ay, uint16_t index)
{
    return ((uint8_t)ay[index] << 8) + (uint8_t)ay[index +1];
}

uint32_t common::qbtarray_to_u32(const QByteArray &ay, uint16_t index)
{
    return ((uint8_t)ay[index] << 24) +((uint8_t)ay[index+1] << 16) + ((uint8_t)ay[index+2] << 8) + (uint8_t)ay[index+3];
}

uint16_t common::get_system_yearmon_time()
{
    QDateTime tmp_time = QDateTime::currentDateTime();
    return tmp_time.toString("yyMM").toUInt();
}

QString common::get_system_detail_time()
{
    QDateTime tmp_time = QDateTime::currentDateTime();
    return tmp_time.toString("yyyy-MM-dd hh:mm:ss");
}
