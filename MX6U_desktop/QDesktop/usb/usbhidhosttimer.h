#ifndef USBHIDHOSTTIMER_H
#define USBHIDHOSTTIMER_H

#include <QObject>
#include <unistd.h>
#include "hidapi.h"


using namespace std;
#define hidDataLength 64


class UsbHidHostTimer : public QObject
{
    Q_OBJECT


public:
    explicit UsbHidHostTimer(QObject *parent = nullptr);
    int hidApi_Write(unsigned char *data, unsigned char length);
    int hidApi_Close(void);
    int hidApi_ReadTimer_Over_Handle();
    virtual void timerEvent( QTimerEvent *event);


signals:
    void hidDataArrived(unsigned char *data, unsigned char length);

private:
    hid_device *handle;
    unsigned char isOpen;
    int m_readTimerID;

};

#endif // USBHIDHOSTTIMER_H
