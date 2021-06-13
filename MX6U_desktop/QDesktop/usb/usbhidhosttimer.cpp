#include "usbhidhosttimer.h"
//#include "hidinterface.h"
#include <QMessageBox>
#include "./common/common_fun.h"
#include "./common/common_def.h"
#include <QTimerEvent>


#define TIME_DELAY_MS 50

UsbHidHostTimer::UsbHidHostTimer(QObject *parent) : QObject(parent)
{
    qDebug("[UsbHidHostTimer--%s]:>>", __func__);

    // Open the device using the VID, PID,
    // and optionally the Serial number.
    //handle = hid_open(HID_USB_VID, HID_USB_PID, L"12345");
    handle = hid_open(HID_USB_VID, HID_USB_PID, NULL);
    if (!handle)
    {
        QMessageBox::about(NULL, tr("UsbHidHostTimer"),"unable to open device\n");
        isOpen = 0;
        return;
    }

    QMessageBox::about(NULL, tr("UsbHidHostTimer"),"open device success\n");
    isOpen = 1;
    m_readTimerID = this->startTimer(TIME_DELAY_MS);

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    emit hidDataArrived(NULL,0);
}

int UsbHidHostTimer::hidApi_ReadTimer_Over_Handle()
{
    unsigned char recData[hidDataLength];

    int res;
    if(isOpen==1)
    {
        qDebug("[UsbHidHostTimer--%s]:>>read", __func__);

        res = hid_read(handle, recData, hidDataLength);
        if (res == 0)
        {
            //QMessageBox::about(NULL, tr("UsbHidHostTimer"),"waiting...\n");
            //qDebug("[UsbHidHostTimer--%s]:>>no recv data", __func__);
        }
        else if (res < 0)
        {
            QMessageBox::about(NULL, tr("UsbHidHostTimer"),"Unable to read()\n");
            return - 1;
        }
        else
        {
//            int i;

//            unsigned char length = recData[0];

//            unsigned char datas[length];
//            for(i=0;i<length;i++)
//            {
//                datas[i]=recData[i+1];
//                qDebug("[UsbHidHostTimer--%s]:>>datas[%d]:%02hhx", __func__, i, datas[i]);
//            }

            int i;

            unsigned char length = 64;

            unsigned char datas[length];
            for(i=0;i<length;i++)
            {
                datas[i]=recData[i];
                qDebug("[UsbHidHostTimer--%s]:>>datas[%d]:%02hhx", __func__, i, datas[i]);
            }

            //QString recv_str = uncharToQstring(datas, sizeof(datas));
            //qDebug("[UsbHidHostTimer--%s]:>>recv_str:%s", __func__, qPrintable(recv_str));
            emit hidDataArrived(datas,length);
        }
    }
}


void UsbHidHostTimer::timerEvent(QTimerEvent *event)
{
    //qDebug("[UsbHidHostTimer--%s]:>>", __func__);

    if(event->timerId() == m_readTimerID)
    {
        hidApi_ReadTimer_Over_Handle();
//        killTimer(m_readTimerID);
//        m_readTimerID = this->startTimer(TIME_DELAY_MS);
    }
}


int UsbHidHostTimer::hidApi_Write(unsigned char *data, unsigned char length)
{
    qDebug("[UsbHidHostTimer--%s]:>>", __func__);

    int res;
    unsigned char realData[length+1];

    realData[0]=length;
    int i;
    for(i=0;i<length;i++)
    {
        realData[i+1]=data[i];
    }

    res = hid_write(handle, realData, length+1);
    if (res < 0)
    {
        QMessageBox::about(NULL, tr("UsbHidHostTimer"),"Unable to write()\n");
        qDebug("Error: %ls\n",hid_error(handle));
        return -1;
    }

    QMessageBox::about(NULL, tr("UsbHidHostTimer"),"write success\n");
    return 0;
}


int UsbHidHostTimer::hidApi_Close(void)
{
    qDebug("[UsbHidHostTimer--%s]:>>", __func__);

    killTimer(m_readTimerID);
    hid_close(handle);
    isOpen = 0;
    /* Free static HIDAPI objects. */
    hid_exit();
    delete handle;
    return 0;
}
