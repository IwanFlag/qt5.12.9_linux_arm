#ifndef UsbThread_H
#define UsbThread_H

#include <QObject>
#include "libusb.h"
#include "QThread"


#define HIL_USB_VID     0x0483
#define HIL_USB_PID     0x5741
#define HIL_USB_OUT_EP  0x01
#define HIL_USB_IN_EP   0x81
#define HIL_PKT_LENGTH  64
#define HIL_PKT_TIMEOUT 100
#define USB_CONFIG_NUM  1
#define USB_IFACE_NUM   0



class UsbThread : public QThread
{
    Q_OBJECT

public:
    static UsbThread* g_static_this;


    //explicit UsbThread(QObject *parent = nullptr);
    explicit UsbThread();
    ~UsbThread();
    void run();
    int usb_init(void);
    QString getPort();
    void usb_open_close(QString now_text, QString usbName);
    int usb_open(void);
    int usb_close(void);

    QString get_bcdUSBString(quint8 bcdUSB);
    QString get_bDeviceClassString(quint16 bDeviceClass);

    static int  LIBUSB_CALL libusb_hotplug_register_callback_left_handle(libusb_context *ctx,
                                                 libusb_device *device,
                                                 libusb_hotplug_event event,
                                                 void *user_data);


    static int  LIBUSB_CALL libusb_hotplug_register_callback_arrived_handle(libusb_context *ctx,
                                                 libusb_device *device,
                                                 libusb_hotplug_event event,
                                                 void *user_data);

private:
    struct libusb_config_descriptor *conf_desc;
    quint8 endpoint_in, endpoint_out;
    libusb_device *dev;
    int OutSize;
    libusb_device_handle *handle;
    libusb_device **dev_lists;           //devices
    libusb_hotplug_callback_handle usb_arrived_handle;
    libusb_hotplug_callback_handle usb_left_handle;
    libusb_context *ctx;
    //void print_devs(libusb_device **devs);

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
