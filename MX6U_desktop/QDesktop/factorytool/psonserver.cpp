#include "psonserver.h"
#include "QDebug"


/**
 * @brief PsOnServer::PsOnServer
 */
PsOnServer::PsOnServer(QWidget* parent)
{
    qDebug("[PsOnServer--%s]>>", __FUNCTION__);

}

/**
 * @brief PsOnServer::getMsgid
 * @return
 */
qint32 PsOnServer::getMsgid()
{
    return m_msg_id;
}

/**
 * @brief PsOnServer::setMSgid
 * @param msg_id
 */
void PsOnServer::setMSgid(qint32 msg_id)
{
    m_msg_id = msg_id;
}

/**
 * @brief PsOnServer::PsOnServer_Packet
 *      only data PACKET
 * @param device_type
 * @return
 */
QByteArray PsOnServer::PsOnServer_DataPacket(ENUM_DEVICE_TYPE device_type)
{
    qDebug("[PsOnServer--%s]>>device_type:%d", __FUNCTION__, device_type);


    switch (device_type)
    {
        case DEVICE_TYPE_COLORBAO_MASTER:
            {
                qDebug("[PsOnServer--%s]>>DEVICE_TYPE_COLORBAO_MASTER", __FUNCTION__);

            }
            break;

        case DEVICE_TYPE_COLORBAO_SLAVE:
            {

            }
            break;

        default:
            {

            }
            break;
    }
}

/**
 * @brief PsOnServer::PsOnServer_BindPacket
 * @param device_type
 * @return
 */
QByteArray PsOnServer::PsOnServer_BindPacket(ENUM_DEVICE_TYPE device_type)
{
    QByteArray send_ba;

    //1.head FBFB
    send_ba.append(0XFB);
    send_ba.append(0XFB);


    //2.cmd type
    send_ba.append(ENUM_DEVICE_CMD_BIND);


    //3.msgid
    send_ba.append(getMsgid());


    //4.len
    send_ba.append((char)0x00);
    send_ba.append((char)0X56);


    //5.IMEI
    send_ba.append(0X11);
    send_ba.append(0X22);
    send_ba.append(0X33);
    send_ba.append(0X44);
    send_ba.append(0X55);
    send_ba.append(0X66);
    send_ba.append(0X77);
    send_ba.append(0X88);


    //6.data
    send_ba.append(PsOnServer_DataPacket(device_type));


    //7.checksum
    send_ba.append(0XDD);
    send_ba.append(0XDD);


    //8.tail
    send_ba.append(0XAA);
    send_ba.append(0XAA);
}




