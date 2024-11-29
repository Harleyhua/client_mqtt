#ifndef EMU_PROTOCOLB_H
#define EMU_PROTOCOLB_H

#include <QObject>

class emu_protocolb : public QObject
{
    Q_OBJECT
public:
    explicit emu_protocolb(QObject *parent = nullptr);

    void to_emu_property_json(QString Emuid, const QByteArray &s_data,QJsonObject &rt_data);
    void to_emu_status_json(QString Emuid, const QByteArray &s_data, QJsonObject &rt_data);
    void to_powerdata_json(QString Emuid,const QByteArray &s_data, QJsonObject &rt_data,uint16_t &date);
    void to_faultdata_json(QString Emuid,const QByteArray &s_data, QJsonObject &rt_data,uint16_t &date);
    void to_mi_property_json(const QByteArray &s_data, QJsonObject &rt_data);
};

#endif // EMU_PROTOCOLB_H
