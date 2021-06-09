#include "UsbThread.h"
//#include "UsbThread.h"
#include "qdebug.h"
//#include "main.h"
#include <QMessageBox>
#include <QString>
#include <QIODevice>
#include <QObject>
#include "./common/common_fun.h"


/**
 * @brief UsbThread::UsbThread
 * @param parent
 */
UsbThread::UsbThread()
{
    qDebug("[UsbThread--%s]:>>", __func__);
    //开启串口子线程
    //this->start();

}

/**
 * @brief UsbThread::run
 * 重写，初始化
 */
void UsbThread::run()
{
    qDebug("[UsbThread--%s]:>>", __func__);
//    QObject::connect(g_widget->tab_usb_manager->printerSerialPort, &QSerialPort::readyRead, this, &printerusb_ready_read_slots);
    //QObject::connect(&g_widget->tab_usb_manager->printerSerialPort, &QSerialPort::errorOccurred, this, &printerusb_ready_read_slots);
    unsigned char rec_data[200];
    int rec_len = 10;
    int actual_len;
    unsigned int timeout_MS = 5000;
    libusb_bulk_transfer(handle, endpoint_in, rec_data, rec_len, &actual_len, timeout_MS);        //HID -> Host
    QString str = uncharToQstring(rec_data, 200);
    qDebug("[UsbThread--%s]:>>str:%s", __func__, qPrintable(str));
    QThread::exec();
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
    struct libusb_device_descriptor t_desc;

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


        libusb_context *ctx;
        handle = libusb_open_device_with_vid_pid(NULL, vid, pid);
        if(handle == Q_NULLPTR)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("handle NULL!"));
        }


        if(libusb_kernel_driver_active(handle, 0) == 1)//查看当前的接口是否被占用
        {
            //find out if kernel driver is attached
            qDebug("Kernel Driver Active\n");
            if(libusb_detach_kernel_driver(handle, 0) == 0) //detach it,detach sys driver,use app,解除占用
            {
                qDebug("Kernel Driver Detached!\n");
            }
        }


        dev = libusb_get_device(handle);
        if(dev == Q_NULLPTR)
        {
            QMessageBox::about(NULL, tr("usb:"), tr("dev NULL!"));
        }


        libusb_get_device_descriptor(dev, &t_desc);
        for(int n = 0; n < t_desc.bNumConfigurations; ++n)
        {
            r = libusb_get_config_descriptor(dev, n, &conf_desc);
            qDebug("[UsbThread--%s]:>>r:%d \n", __func__, r);
            if(r < 0)
            {
                QMessageBox::about(NULL, tr("usb:"), tr("libusb_get_config_descriptor failed!"));
                return;
            }

            qDebug("[UsbThread--%s]:>>conf_desc->bNumInterfaces:%d \n", __func__, conf_desc->bNumInterfaces);

            for(int i=0; i<conf_desc->bNumInterfaces; i++)
            {
              for (int j=0; j<conf_desc->interface[i].num_altsetting; j++)
              {
                  for (int k=0; k<conf_desc->interface[i].altsetting[j].bNumEndpoints; k++)
                  {
                      const struct libusb_endpoint_descriptor *endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
                      if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN)
                      {
                          endpoint_in = endpoint->bEndpointAddress;
                      }
                      else
                      {
                          endpoint_out = endpoint->bEndpointAddress;
                      }
                  }
              }
            }
    }
          r = libusb_set_configuration(handle, 1);
//          char err_log[200];
//          err_log = libusb_strerror((libusb_error)r);
          //libusb_set_debug();
          qDebug("[UsbThread--%s]:>>libusb_strerror:%s \n", __func__, libusb_strerror((libusb_error)r));
          if (r < 0)
          {
                QMessageBox::about(NULL, tr("usb:"), tr("configuer fail!"));
                return;
          }


          //libusb_get_config_descriptor(dev, 0, &conf_desc);

          r = libusb_claim_interface(handle, 0);
          if (r < 0)
          {
              //qDebug("设备申请接口失败 ！", r);
              QMessageBox::about(NULL, tr("usb:"), tr("libusb_claim_interface fail"));
              return;
          }

          usb_open_flag_signals(1);

        //开启串口子线程
        this->start();
    }
    else
    {
        //关闭串口
        libusb_free_config_descriptor(conf_desc);
        libusb_close(handle);
        libusb_exit(NULL);


        //QMessageBox::about(NULL, tr("UsbThread"), tr("close"));
        usb_close_flag_signals(1);


        //终止串口子线程
        this->terminate();
    }
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
    libusb_device **devs;           //devices
    int r;     //return value
    ssize_t cnt;
    libusb_context *ctx=nullptr; //context 上下文

    r=libusb_init(&ctx); //init 初始化libusb
    if(r<0)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("failed to init libusb!"));
        return;
    }

    cnt = libusb_get_device_list(nullptr, &devs); //获取设备列表
    qDebug("[UsbThread--%s]:>>cnt:%d", __func__, cnt);

    if (cnt < 0)
    {
        QMessageBox::about(NULL, tr("usb:"), tr("failed to get device list!"));
        return;
    }

    //遍历查找你要的设备
    int i = 0;
    QString useName;
   while ((dev = devs[i++]) != nullptr)
   {
           struct libusb_device_descriptor desc;  //设备信息描述符

           r = libusb_get_device_descriptor(dev, &desc); //获取设备信息描述符
           if (r < 0)
           {
               qDebug()<<"failed to get device descriptor";  //fail to get device descriptor
               QMessageBox::about(NULL, tr("usb:"), tr("failed to get device descriptor!"));
               return;
           }


           qDebug("bcdUSB = %5u\n",            desc.bcdUSB);
           qDebug("bDeviceClass    = %5u\n",            desc.bDeviceClass);
           qDebug("device:          %04x:%04x\n",       desc.idVendor,desc.idProduct);
           useName = get_bcdUSBString(desc.bcdUSB);
           useName += "-";
           useName += get_bDeviceClassString(desc.bDeviceClass);
           useName += "-";
           useName += QString::number(desc.idVendor, 16);           //hex
           useName += "-";
           useName += QString::number(desc.idProduct, 16);          //hex
           qDebug("[UsbThread--%s]:>>useName:%s", __func__,qPrintable(useName));

            emit usb_vaild_ports_to_qml(useName);
//           {
//               r=libusb_open(dev,&udev); //打开设备，获取设备操作符
//               if(r<0)
//               {
//                   qDebug()<<"failed to open device";  //fail to open device
//                   QMessageBox::about(NULL, tr("usb:"), tr("failed to open device!"));
//                   qDebug()<<libusb_error_name(r)<<" "<<r;
//                   qDebug()<<"udev:"<<udev;
//                   return;
//               }
//               else
//               {
//                   qDebug()<<"open device successfully";  //success to open device
//                   qDebug()<<"udev:"<<udev;
//               }
//               break;
//           }
       }

   libusb_free_device_list(devs, 1);        //free the list, unref the devices in it
}

void UsbThread::usb_open_close_slots(QString now_text, QString usbName)
{
    qDebug("[UsbThread--%s]:>>now_text:%s,usbName:%s", __func__, qPrintable(now_text), qPrintable(usbName));
    usb_open_close(now_text, usbName);
}

