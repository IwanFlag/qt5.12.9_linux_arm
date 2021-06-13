#include "usbhidhost.h"
//#include "hidinterface.h"
#include <QMessageBox>
#include "./common/common_fun.h"


UsbHidHost::UsbHidHost()
{
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    //handle = hid_open(HID_USB_VID, HID_USB_PID, L"12345");
    handle = hid_open(HID_USB_VID, HID_USB_PID, NULL);
    if (!handle)
    {
        QMessageBox::about(NULL, tr("UsbHidHost"),"unable to open device\n");
        isOpen = 0;
        return;
    }

    QMessageBox::about(NULL, tr("UsbHidHost"),"open device success\n");
    isOpen = 1;

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    emit hidDataArrived(NULL,0);
}


int UsbHidHost::hidApi_Write(unsigned char *data, unsigned char length)
{
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
        QMessageBox::about(NULL, tr("UsbHidHost"),"Unable to write()\n");
        qDebug("Error: %ls\n",hid_error(handle));
        return -1;
    }

    QMessageBox::about(NULL, tr("UsbHidHost"),"write success\n");
    return 0;
}


void UsbHidHost::run()
{
    qDebug("[UsbThread--%s]:>>run", __func__);
    unsigned char buf_cache[BUF_RECV_LEN_MAX];
    int j = 0, real_len = 0;
    int res;
    int real_data;


    while (isOpen==1)
    {
        unsigned char recData[hidDataLength];
        res = hid_read(handle, recData, hidDataLength);
        if (res == 0)
        {
            //QMessageBox::about(NULL, tr("UsbHidHost"),"waiting...\n");
            //qDebug("[UsbThread--%s]:>>no recv data", __func__);
        }
        else if (res < 0)
        {
            QMessageBox::about(NULL, tr("UsbHidHost"),"Unable to read()\n");
            return;
        }
        else
        {
            int i;

            //this data is map usb key val ,not ascii,/ref: https://blog.csdn.net/u012388993/article/details/116395497
            //example:
            // val :0x01, but if you enter keyborad key "1", then in hid is 0X1E.
            // my hid device,ths Usage ID is data...
            if(res >= 3)
            {
                if(recData[2] != 0X00 && recData[2] != 0X28)
                {
                    buf_cache[i] = recData[2];          //get index=3 number
                    //qDebug("[UsbThread--%s]:>>buf_cache[%d]:%02hhx", __func__, i, buf_cache[i]);
                    real_data = hidApi_Convert_UsageID_to_Data(buf_cache[i]);
                    if(real_data >= 0 && real_data <= 9)
                    {
                        qDebug("[UsbThread--%s]:>>real_data[%d]:%d", __func__, i, real_data);   //print num
                    }
                    else
                    {
                        qDebug("[UsbThread--%s]:>>real_data[%d]:%c", __func__, i, real_data);   //ptint charater
                    }
                    i++;
                }
            }
        }

        usleep(1000);
    }
}


int UsbHidHost::hidApi_Close(void)
{
    hid_close(handle);
    isOpen = 0;
    /* Free static HIDAPI objects. */
    hid_exit();

    delete handle;
    return 0;
}

/**
 * @brief UsbHidHost::hidApi_Convert_UsageID_to_Data
 * @param UsageID
 * @return
 */
int UsbHidHost::hidApi_Convert_UsageID_to_Data(int UsageID)
{
    int ret = 0;        //return val


    switch (UsageID)
    {

    //------------- (0X1E - 0X27) ->(a/A -> b/B)
        case 0X04:
            {
                ret = 'a';
            }
            break;

    case 0X05:
        {
            ret = 'b';
        }
        break;

    case 0X06:
        {
            ret = 'c';
        }
        break;

    case 0X07:
        {
            ret = 'd';
        }
        break;

    case 0X08:
        {
            ret = 'e';
        }
        break;

    case 0X09:
        {
            ret = 'f';
        }
        break;

    case 0X0A:
        {
            ret = 'g';
        }
        break;

    case 0X0B:
        {
            ret = 'h';
        }
        break;

    case 0X0C:
        {
            ret = 'i';
        }
        break;

    case 0X0D:
        {
            ret = 'j';
        }
        break;

    case 0X0E:
        {
            ret = 'k';
        }
        break;

    case 0X0F:
        {
            ret = 'l';
        }
        break;

    case 0X10:
        {
            ret = 'm';
        }
        break;

    case 0X11:
        {
            ret = 'n';
        }
        break;

    case 0X12:
        {
            ret = 'o';
        }
        break;

    case 0X13:
        {
            ret = 'p';
        }
        break;

    case 0X14:
        {
            ret = 'q';
        }
        break;
    case 0X15:
        {
            ret = 'r';
        }
        break;
    case 0X16:
        {
            ret = 's';
        }
        break;
    case 0X17:
        {
            ret = 't';
        }
        break;
    case 0X18:
        {
            ret = 'u';
        }
        break;
    case 0X19:
        {
            ret = 'v';
        }
        break;
    case 0X1A:
        {
            ret = 'w';
        }
        break;
    case 0X1B:
        {
            ret = 'x';
        }
        break;
    case 0X1C:
        {
            ret = 'y';
        }
        break;
    case 0X1D:
        {
            ret = 'z';
        }
        break;

    //------------- (0X1E - 0X27)
        case 0X1E:
            {
                ret = 1;
            }
            break;

        case 0X1F:
            {
                ret = 2;
            }
            break;

    case 0X20:
        {
            ret = 3;
        }
        break;
    case 0X21:
        {
            ret = 4;
        }
        break;
    case 0X22:
        {
            ret = 5;
        }
        break;
    case 0X23:
        {
            ret = 6;
        }
        break;
    case 0X24:
        {
            ret = 7;
        }
        break;

    case 0X25:
        {
            ret = 8;
        }
        break;

    case 0X26:
        {
            ret = 9;
        }
        break;

    case 0X27:
        {
            ret = 0;
        }
        break;

        case 0X28:          //key enter
            {
                ret = 108;
            }
            break;

    case 0X29:          //key esc
        {
            ret = 27;
        }
        break;

    case 0X2A:          //key DELETE
        {
            ret = 46;
        }
        break;
    case 0X2B:          //key TAB
        {
            ret = 9;
        }
        break;

    case 0X2C:          //key SPACE
        {
            ret = ' ';
        }
        break;

    case 0X2D:          //key - AND
        {
            ret = '_';
        }
        break;

    case 0X2E:          //key = AND  +
        {
            ret = '=';
        }
        break;

    case 0X2F:          //key [ AND  {
        {
            ret = '[';
        }
        break;

    case 0X30:          //key ] AND  }
        {
            ret = ']';
        }
        break;


    case 0X33:          //key ; AND :
        {
            ret = ':';
        }
        break;

    case 0X36:          //key , AND <
        {
            ret = ',';
        }
        break;

    case 0X37:          //key . AND >
        {
            ret = '.';
        }
        break;

    case 0X38:          //key / AND ?
        {
            ret = '/';
        }
        break;

    case 0X55:          //key *
        {
            ret = '*';
        }
        break;

    case 0X56:          //key *
        {
            ret = '-';
        }
        break;


    case 0X57:          //key *
        {
            ret = '+';
        }
        break;

        default:
            {

            }
            break;
    }

    return ret;
}
