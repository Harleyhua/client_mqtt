#ifndef COMMON_H
#define COMMON_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class common : public QObject
{
    Q_OBJECT
public:
    explicit common(QObject *parent = nullptr);

    static uint8_t qbtarray_to_u8(const QByteArray &ay,uint16_t index);
    static uint16_t qbtarray_to_u16(const QByteArray &ay,uint16_t index);
    static uint32_t qbtarray_to_u32(const QByteArray &ay,uint16_t index);
    static uint16_t get_system_yearmon_time();
    static QString get_system_detail_time();

};

#endif
