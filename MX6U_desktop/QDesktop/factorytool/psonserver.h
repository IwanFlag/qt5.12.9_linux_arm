#ifndef PSONSERVER_H
#define PSONSERVER_H

#include <QObject>
#include    "common_factoryTool.h"

class PsOnServer: public QObject
{
    Q_OBJECT

public:


    PsOnServer(QWidget* parent = Q_NULLPTR);

    qint32 getMsgid(void);
    void setMSgid(qint32 msg_id);


    //DATA packet
    QByteArray PsOnServer_DataPacket(ENUM_DEVICE_TYPE device_type);
    QByteArray PsOnServer_BindPacket(ENUM_DEVICE_TYPE device_type);
    QByteArray PsOnServer_QueryNumPacket(ENUM_DEVICE_TYPE device_type);


    //

private:
    qint32 m_msg_id;

};

#endif // PSONSERVER_H
