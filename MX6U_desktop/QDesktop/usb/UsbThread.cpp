#include "UsbThread.h"
//#include "UsbThread.h"
#include "qdebug.h"
//#include "main.h"
#include <QMessageBox>
#include <QString>
#include <QIODevice>
#include <QObject>
#include "./common/common_fun.h"


UsbThread * UsbThread::g_static_this = nullptr;
/**
 * @brief UsbThread::UsbThread
 * @param parent
 */
UsbThread::UsbThread()
{
    qDebug("[UsbThread--%s]:>>", __func__);
    g_static_this = this;
    ctx = nullptr;
    usb_init();

//    //开启串口子线程
//    this->start();
    int pri = (int)this->priority();
    qDebug("[UsbThread--%s]:>>pri:%d,currentThreadId:%d", __func__, pri, currentThreadId());

}

UsbThread::~UsbThread()
{
    libusb_hotplug_deregister_callback(NULL, usb_arrived_handle);
    libusb_hotplug_deregister_callback(NULL, usb_left_handle);
}

/**
 * @brief UsbThread::run
 * 重写，初始化
 */
void UsbThread::run()
{
    while(1)
    {
        unsigned char rec_data[20];
        int actual_len;
        unsigned int timeout_MS = 100;
//        libusb_interrupt_read(handle, endpoint_in, rec_data, rec_len, &actual_len, timeout_MS);        //HID -> Host
        libusb_handle_events(ctx);     //event hand
//        libusb_clear_halt(handle, endpoint_in);

//        libusb_interrupt_transfer(handle, endpoint_in, rec_data, sizeof(rec_data), &actual_len, timeout_MS);
        //libusb_interrupt_transfer(handle, (endpoint_in | LIBUSB_ENDPOINT_IN), rec_data, sizeof(rec_data), &actual_len, timeout_MS);
        QString str = uncharToQstring(rec_data, sizeof(rec_data));

        qDebug("[UsbThread--%s]:>>str:%s", __func__, qPrintable(str));
        //msleep(10);
    }

    //QThread::exec();
}

int UsbThread::usb_init(void)
{
    int r;     //return value
    ssize_t cnt;
    //libusb_context *ctx = nullptr; //context 上下文
    qDebug("[UsbThread--%s]:>>", __func__);

    r = libusb_init(&ctx); //init 初始化libusb
    if(r<0 || ctx == Q_NULLPTR)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("failed to init libusb!"));
        return -1;
    }

    libusb_get_pollfds(ctx);

    void *user_data;
    r = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, LIBUSB_HOTPLUG_ENUMERATE,\
                                     HIL_USB_VID, HIL_USB_PID, LIBUSB_HOTPLUG_MATCH_ANY,
                                     libusb_hotplug_register_callback_arrived_handle,\
                                     NULL, &usb_arrived_handle);

    qDebug("[UsbThread--%s]:>>r :%d", __func__,r );


    r = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, LIBUSB_HOTPLUG_ENUMERATE,\
                                     HIL_USB_VID, HIL_USB_PID, LIBUSB_HOTPLUG_MATCH_ANY, libusb_hotplug_register_callback_left_handle,\
                                     NULL, &usb_left_handle);
    qDebug("[UsbThread--%s]:>>r :%d", __func__,r );
}

QString UsbThread::getPort()
{
    //return m_port;
}

/**
 * @brief UsbThread::usb_open_close
 *      open or close
 */
void UsbThread::usb_open_close(QString now_text, QString usbName)
{
    qDebug("[UsbThread--%s]:>>", __func__);
    int r;
    struct libusb_device_descriptor dev_desc;

    if(QString::compare(now_text, tr("Open"), Qt::CaseInsensitive) == 0)
    {
        QString MSG_STR;
        MSG_STR += now_text + "/" + usbName;
        qDebug("[UsbThread--%s]:>>ready open usb", __func__);
        quint16 vid;
        quint16 pid;

        //QString str = "0,1,2,3,4,5,6,7,8,9";
        QStringList  usbNameInfos=  usbName.split("-");
        foreach (QString s, usbNameInfos)
        {
            qDebug("[UsbThread--%s]:>>s:%s\n", __func__, qPrintable(s));
        }

        bool ok;
        vid = usbNameInfos.at(2).toInt(&ok, 16);        //16 -> 10
        pid = usbNameInfos.at(3).toInt(&ok, 16);
        qDebug("[UsbThread--%s]:>>vid:%d,pid:%d\n", __func__,vid,pid);

        handle = libusb_open_device_with_vid_pid(ctx, vid, pid);
        if(handle == Q_NULLPTR)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("handle NULL!"));
            return;
        }


        if(libusb_kernel_driver_active(handle, USB_IFACE_NUM) == 1)//查看当前的接口是否被占用
        {
            //find out if kernel driver is attached
            qDebug("Kernel Driver Active\n");
            if(libusb_detach_kernel_driver(handle, USB_IFACE_NUM) == 0) //detach it,detach sys driver,use app,解除占用
            {
                qDebug("Kernel Driver Detached!\n");
            }
            else
            {
                QMessageBox::about(NULL, tr("usb:"), tr("Detached Failed!"));
                return;
            }
        }


        dev = libusb_get_device(handle);
        if(dev == Q_NULLPTR)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("dev NULL!"));
        }


        libusb_get_device_descriptor(dev, &dev_desc);
        qDebug("[UsbThread--%s]:>>bNumConfigurations:%d \n", __func__, dev_desc.bNumConfigurations);


        for(int n = 0; n < dev_desc.bNumConfigurations; ++n)    //1.config nums
        {
            r = libusb_get_config_descriptor(dev, n, &conf_desc);
            qDebug("[UsbThread--%s]:>>r:%d,bDeviceClass:%d \n", __func__, r, dev_desc.bDeviceClass);
            if(r < 0)
            {
                QMessageBox::about(NULL, tr("usb:"), tr("libusb_get_config_descriptor failed!"));
                return;
            }

            qDebug("[UsbThread--%s]:>>conf_desc->bNumInterfaces:%d \n", __func__, conf_desc->bNumInterfaces);
            for(int i=0; i<conf_desc->bNumInterfaces; i++)      //2.interface nums
            {
              for (int j=0; j<conf_desc->interface[i].num_altsetting; j++)  //3.altsettinhg nums
              {
                  for (int k=0; k<conf_desc->interface[i].altsetting[j].bNumEndpoints; k++)  //4.ep nums
                  {
                      // if is interface 0
                      if(conf_desc->interface[i].altsetting[j].bInterfaceNumber == USB_IFACE_NUM)
                      {
                          qDebug("[UsbThread--%s]:>>aaa \n", __func__);

                          const struct libusb_endpoint_descriptor *endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
                          if(endpoint->bmAttributes == LIBUSB_TRANSFER_TYPE_INTERRUPT)
                          {
                              qDebug("[UsbThread--%s]:>>bbb \n", __func__);

                              if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN)
                              {
                                  qDebug("[UsbThread--%s]:>>ccc \n", __func__);

                                  endpoint_in = endpoint->bEndpointAddress;
                              }
                              else
                              {
                                  qDebug("[UsbThread--%s]:>>dddd \n", __func__);

                                  endpoint_out = endpoint->bEndpointAddress;
                              }
                          }
                      }
                  }
              }
            }
            //must free
            libusb_free_config_descriptor(conf_desc);
        }


        r = libusb_set_configuration(handle, USB_CONFIG_NUM);
        qDebug("[UsbThread--%s]:>>libusb_strerror:%s \n", __func__, libusb_strerror((libusb_error)r));
        if(r < 0)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("configuer fail!"));
            return;
        }


        //libusb_get_config_descriptor(dev, 0, &conf_desc);

        r = libusb_claim_interface(handle, USB_IFACE_NUM);            //claim one interface
        if (r < 0)
        {
          //qDebug("设备申请接口失败 ！", r);
          QMessageBox::about(NULL, tr("usb:"), tr("libusb_claim_interface fail"));
          return;
        }

        usb_open_flag_signals(1);

//        //开启串口子线程
//        this->start();
    }
    else
    {

        usb_close();

        //终止串口子线程
        //this->terminate();
        quit();
    }
}

int UsbThread::usb_open()
{
    qDebug("[UsbThread--%s]:>>", __func__);
    struct libusb_device_descriptor dev_desc;
    int r;


    handle = libusb_open_device_with_vid_pid(ctx, HIL_USB_VID, HIL_USB_PID);
    qDebug("[UsbThread--%s]:>>HIL_USB_VID:%X,HIL_USB_PID:%X", __func__, HIL_USB_VID, HIL_USB_PID);

    if(handle == Q_NULLPTR)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("handle NULL!"));
        return - 1;
    }


    if(libusb_kernel_driver_active(handle, USB_IFACE_NUM) == 1)//查看当前的接口是否被占用
    {
        //find out if kernel driver is attached
        qDebug("Kernel Driver Active\n");
        if(libusb_detach_kernel_driver(handle, USB_IFACE_NUM) == 0) //detach it,detach sys driver,use app,解除占用
        {
            qDebug("Kernel Driver Detached!\n");
        }
        else
        {
            QMessageBox::about(NULL, tr("usb:"), tr("Detached Failed!"));
            return -2;
        }
    }


    dev = libusb_get_device(handle);
    if(dev == Q_NULLPTR)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("dev NULL!"));
    }


    libusb_get_device_descriptor(dev, &dev_desc);
    qDebug("[UsbThread--%s]:>>bNumConfigurations:%d \n", __func__, dev_desc.bNumConfigurations);


    for(int n = 0; n < dev_desc.bNumConfigurations; ++n)    //1.config nums
    {
        r = libusb_get_config_descriptor(dev, n, &conf_desc);
        qDebug("[UsbThread--%s]:>>r:%d,bDeviceClass:%d \n", __func__, r, dev_desc.bDeviceClass);
        if(r < 0)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("libusb_get_config_descriptor failed!"));
            return -3;
        }

        qDebug("[UsbThread--%s]:>>conf_desc->bNumInterfaces:%d \n", __func__, conf_desc->bNumInterfaces);
        for(int i=0; i<conf_desc->bNumInterfaces; i++)      //2.interface nums
        {
          for (int j=0; j<conf_desc->interface[i].num_altsetting; j++)  //3.altsettinhg nums
          {
              for (int k=0; k<conf_desc->interface[i].altsetting[j].bNumEndpoints; k++)  //4.ep nums
              {
                  // if is interface 0
                  if(conf_desc->interface[i].altsetting[j].bInterfaceNumber == USB_IFACE_NUM)
                  {
                      qDebug("[UsbThread--%s]:>>aaa \n", __func__);

                      const struct libusb_endpoint_descriptor *endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
                      if(endpoint->bmAttributes == LIBUSB_TRANSFER_TYPE_INTERRUPT)
                      {
                          qDebug("[UsbThread--%s]:>>bbb \n", __func__);

                          if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN)
                          {

                              endpoint_in = endpoint->bEndpointAddress;
                              qDebug("[UsbThread--%s]:>>ccc:%X \n", __func__,endpoint_in);

                          }
                          else
                          {

                              endpoint_out = endpoint->bEndpointAddress;
                              qDebug("[UsbThread--%s]:>>ddd:%X \n", __func__, endpoint_out);

                          }
                      }
                  }
              }
          }
        }
        //must free
        libusb_free_config_descriptor(conf_desc);
    }


//    r = libusb_set_configuration(handle, USB_CONFIG_NUM);
//    qDebug("[UsbThread--%s]:>>libusb_strerror:%s \n", __func__, libusb_strerror((libusb_error)r));
//    if(r < 0)
//    {
//        QMessageBox::about(NULL, tr("usb:"), tr("configuer fail!"));
//        return -4;
//    }


    //libusb_get_config_descriptor(dev, 0, &conf_desc);

    r = libusb_claim_interface(handle, USB_IFACE_NUM);            //claim one interface
    if (r < 0)
    {
      //qDebug("设备申请接口失败 ！", r);
      QMessageBox::about(NULL, tr("usb:"), tr("libusb_claim_interface fail"));
      return - 5;
    }

    usb_open_flag_signals(1);

    return r;
}

int UsbThread::usb_close()
{
    qDebug("[UsbThread--%s]:>>", __func__);

    //关闭usb
    if(handle)
    libusb_release_interface(handle, USB_IFACE_NUM);

    if(conf_desc)
    libusb_free_config_descriptor(conf_desc);

    if(handle)
    libusb_attach_kernel_driver(handle, USB_IFACE_NUM); //加载内核驱动，usb将重新出现在设备文件里

    if(handle)
    libusb_close(handle);


    if(ctx)
    libusb_exit(ctx);

    usb_close_flag_signals(1);

    return 0;
}

/**
 * @brief UsbThread::get_bcdUSBString
 * 	 * 0x0200 indicates USB 2.0, 0x0110 indicates USB 1.1, etc.
 * @param bcdUSB
 * @return
 */
QString UsbThread::get_bcdUSBString(quint8 bcdUSB)
{
    qDebug("[UsbThread--%s]:>>bcdUSB:%X", __func__, bcdUSB);
    if(bcdUSB == 0x0200)
    {
        return "USB 2.0";

    }
    else if(bcdUSB == 0x0110)
    {
        return "USB 1.1";
    }
    else
    {
        QString str = "USB x.x";
        str.append("(");
        str = str.append(QString::number(bcdUSB));
        str.append(")");

        return str;
    }
}

/**
 * @brief UsbThread::get_bDeviceClass
 * bDeviceClass
 * @param bDeviceClass
 * @return
 */
QString UsbThread::get_bDeviceClassString(quint16 bDeviceClass)
{
    qDebug("[UsbThread--%s]:>>bDeviceClass:%d", __func__, bDeviceClass);
    switch(bDeviceClass)
    {

        /** LIBUSB_CLASS_PER_INTERFACE */
        case LIBUSB_CLASS_PER_INTERFACE:
            {
                return "Per";
            }break;

        /** Audio class */
        case LIBUSB_CLASS_AUDIO:
            {
                return "Audio";
            }break;

        /** Communications class */
        case LIBUSB_CLASS_COMM:
    {
        return "Comm";
    }break;

        /** Human Interface Device class */
        case LIBUSB_CLASS_HID:
            {
                return "HID";
            }break;

        /** Physical */
        case LIBUSB_CLASS_PHYSICAL:
    {
        return "Phy";
    }break;

        /** Printer class */
        case LIBUSB_CLASS_PRINTER:
    {
        return "Printer";
    }break;

        /** Image class */
        case LIBUSB_CLASS_PTP: /* legacy name from libusb-0.1 usb.h */
    {
        return "Image";
    }break;

//        case LIBUSB_CLASS_IMAGE:
//            {}break;

        /** Mass storage class */
        case LIBUSB_CLASS_MASS_STORAGE:
            {
                return "Mass storage";
            }break;

        /** Hub class */
        case LIBUSB_CLASS_HUB:
            {
                return "Hub";
            }break;

        /** Data class */
        case LIBUSB_CLASS_DATA:
    {
        return "Data";
    }break;

        /** Smart Card */
        case LIBUSB_CLASS_SMART_CARD:
    {
        return "Smart";
    }break;

        /** Content Security */
        case LIBUSB_CLASS_CONTENT_SECURITY:
        {}break;

        /** Video */
        case LIBUSB_CLASS_VIDEO:
    {
        return "Video";
    }break;

        /** Personal Healthcare */
        case LIBUSB_CLASS_PERSONAL_HEALTHCARE:
            {}break;

        /** Diagnostic Device */
        case LIBUSB_CLASS_DIAGNOSTIC_DEVICE:
            {}break;

        /** Wireless class */
        case LIBUSB_CLASS_WIRELESS:
    {
        return "Wireless";
    }break;

        /** Application class */
        case LIBUSB_CLASS_APPLICATION:
    {
        return "Application";
    }break;

        /** Class is vendor-specific */
        case LIBUSB_CLASS_VENDOR_SPEC:
            {
                return "vendor";
            }break;

        default:
        {
            return QString::number(bDeviceClass);
        }break;
    }
}

int UsbThread::libusb_hotplug_register_callback_left_handle(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    qDebug("[UsbThread--%s]:>>!!!left", __func__);
//    if(handle)
//    {
//        handle = libusb_open_device_with_vid_pid(ctx, HIL_USB_VID, HIL_USB_PID);
//        if(handle == Q_NULLPTR)
//        {
//            QMessageBox::about(NULL, tr("usb:"), tr("handle NULL!"));
//            return;
//        }
//        libusb_set_auto_detach_kernel_driver(handle,1);
//        libusb_claim_interface(handle, USB_IFACE_NUM);  //请求接口之前先卸载内核驱动

//    }
    //g_static_this->usb_close();
}

int UsbThread::libusb_hotplug_register_callback_arrived_handle(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    qDebug("[UsbThread--%s]:>>!!!plug", __func__);
//    g_static_this->usb_close();
    g_static_this->usb_open();
}

/**
 * @brief UsbThread::usb_ready_read_slots
 * recevie
 */
void UsbThread::usb_ready_read_slots()
{
    qDebug("[UsbThread--%s]:>>", __func__);



//    //从接收缓冲区中读取数据
//    QByteArray buffer = serialPort->readAll();

//    //QByteArray转为大写QSting
//    QString str(buffer.toHex().toUpper());//toUpper()大写
//    str+= "\n";

//    QMessageBox::about(NULL, tr("usb recevie:"), str);
//    emit sendDataToQml(str);
}

/**
 * @brief UsbThread::usb_sendData_slots
 *                  app send data to
 * @param data
 */
void UsbThread::usb_sendData_slots(QString data)
{
    qDebug("[UsbThread--%s]:>>data:%s", __func__, qPrintable(data));
//    g_widget->tab_usb_manager->usb_send_HEX_byte(data);
    QMessageBox::about(NULL, tr("usb send"), data);
    //serialPort->writeData(ch, ba.size());
    //serialPort->write(data.toLatin1());
}

/**
 * @brief UsbThread::usb_search_com_slots
 *      搜寻检测可用串口，并加载到下拉列表中
 */
void UsbThread::usb_search_com_slots()
{
    qDebug("[UsbThread--%s]:>>", __func__);
    QString str;
//    libusb_device **dev_lists;           //devices
    int r;     //return value
    ssize_t cnt;
    //libusb_context *ctx = nullptr; //context 上下文


    r = libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG);
    qDebug("[UsbThread--%s]:>>LIBUSB_CAP_HAS_HOTPLUG:%d", __func__, r);

    r = libusb_has_capability(LIBUSB_CAP_HAS_HID_ACCESS );
    qDebug("[UsbThread--%s]:>>LIBUSB_CAP_HAS_HID_ACCESS:%d", __func__, r);

    r = libusb_has_capability(LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER );
    qDebug("[UsbThread--%s]:>>LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER :%d", __func__, r);


    cnt = libusb_get_device_list(ctx, &dev_lists); //获取设备列表
    qDebug("[UsbThread--%s]:>>cnt:%d", __func__, cnt);

    if (cnt <= 0)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("failed to get device list!"));
        return;
    }

    //遍历查找你要的设备
    int i = 0;
    QString useName;
    while ((dev = dev_lists[i++]) != nullptr)
    {
        struct libusb_device_descriptor desc;  //设备信息描述符
        r = libusb_get_device_descriptor(dev, &desc); //获取设备信息描述符
        if (r < 0)
        {
           qDebug()<<"failed to get device descriptor";  //fail to get device descriptor
           QMessageBox::about(NULL, tr("usb:"), tr("failed to get device descriptor!"));
           return;
        }

//        qDebug("==================i = [%d] desc=======\n",            i);
//        qDebug("bDescriptorType = %d\n",            desc.bDescriptorType);
//        qDebug("bcdUSB = %d\n",            desc.bcdUSB);
//        qDebug("bDeviceClass    = %d\n",            desc.bDeviceClass);
//        qDebug("bDeviceSubClass    = %d\n",            desc.bDeviceSubClass);
//        qDebug("bDeviceProtocol    = %d\n",            desc.bDeviceProtocol);

//        qDebug("device:          %04x:%04x\n",       desc.idVendor,desc.idProduct);
        useName = get_bcdUSBString(desc.bcdUSB);
        useName += "-";
        useName += get_bDeviceClassString(desc.bDeviceClass);
        useName += "-";
        useName += QString::number(desc.idVendor, 16);           //hex
        useName += "-";
        useName += QString::number(desc.idProduct, 16);          //hex
        qDebug("[UsbThread--%s]:>>useName:%s", __func__,qPrintable(useName));


        emit usb_vaild_ports_to_qml(useName);
    }
    libusb_free_device_list(dev_lists, 1);        //free the list, unref the devices in it
}

void UsbThread::usb_open_close_slots(QString now_text, QString usbName)
{
    qDebug("[UsbThread--%s]:>>now_text:%s,usbName:%s", __func__, qPrintable(now_text), qPrintable(usbName));
    usb_open_close(now_text, usbName);
}

