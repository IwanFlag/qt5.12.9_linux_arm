#ifndef UsbThread_H
#define UsbThread_H

#include <QObject>
#include "libusb.h"
#include "QThread"


class UsbThread : public QThread
{
    Q_OBJECT

public:
    //explicit UsbThread(QObject *parent = nullptr);
    explicit UsbThread();
    void run();
    QString getPort();
    void usb_open_close(QString now_text, QString usbName);
    QString get_bcdUSBString(quint8 bcdUSB);
    QString get_bDeviceClassString(quint16 bDeviceClass);


private:
    struct libusb_config_descriptor *conf_desc;
    quint8 endpoint_in, endpoint_out;
    libusb_device *dev;
    int OutSize;
    libusb_device_handle *handle;
    libusb_device **dev_lists;           //devices

    void print_devs(libusb_device **devs);


signals:
    void sendDataToQml(QString data);
    void usb_vaild_ports_to_qml(QString port);
    void usb_open_flag_signals(int flag);              //0:fail 1:sucess
    void usb_close_flag_signals(int flag);             //0:fail 1:sucess

public slots:
    void usb_ready_read_slots();
    void usb_sendData_slots(QString data);
    void usb_search_com_slots();
    void usb_open_close_slots(QString now_text, QString usbName);





};

#endif // UsbThread_H
