#include "UartThread.h"
#include "qdebug.h"
//#include "main.h"
#include <QMessageBox>


/**
 * @brief UartThread::UartThread
 */
UartThread::UartThread()
{
    qDebug("[UartThread--%s]:>>", __func__);
    //m_port = port;
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printerUart_ready_read_slots);
    serialPort = new QSerialPort;                                 //init one uart port
}


/**
 * @brief UartThread::run
 * 重写，初始化
 */
void UartThread::run()
{
    qDebug("[UartThread--%s]:>>", __func__);
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printerUart_ready_read_slots);
    //QObject::connect(&g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::errorOccurred, this, &printerUart_ready_read_slots);
    QThread::exec();
}


void UartThread::Uart_ready_read_slots()
{
    qDebug("[UartThread--%s]:>>", __func__);


    //QMessageBox::about(NULL, tr("UartThread"), tr("printerUart_ready_read_slots"));

    //从接收缓冲区中读取数据
    QByteArray buffer = serialPort->readAll();

//    //遍历打印试试
//    for(int i = 0; i < buffer.size(); i++)
//    {
//        qDebug("[UartThread--%s]:>>recv data:\n%02x", __func__, buffer.at(i));
//    }

    //QByteArray转为大写QSting
    QString str(buffer.toHex().toUpper());//toUpper()大写

//    //从界面中读取以前收到的数据
//    QString recv = g_widget->tab_uart_manager->recv_plain_text->toPlainText();
    QString recv;

//    recv += QString(str);
    recv += "\n";           //加一个换行符

    //清空以前的显示
    //g_widget->tab_uart_manager->recv_plain_text->clear();

    //重新显示
    //g_widget->tab_uart_manager->recv_plain_text->setPlainText(recv);
//    emit sendDataToWdiget(recv);
}

/**
 * @brief UartThread::Uart_sendData_slots
 *                  app send data to
 * @param data
 */
void UartThread::Uart_sendData_slots(QByteArray data)
{
    qDebug("[UartThread--%s]:>>", __func__);
//    g_widget->tab_uart_manager->uart_send_HEX_byte(data);
}

/**
 * @brief UartThread::uart_search_com_slots
 *      搜寻检测可用串口，并加载到下拉列表中
 */
void UartThread::uart_search_com_slots()
{
    qDebug("[UartThread--%s]:>>", __func__);

    //清除选项
    //this->uart_select_cb->clear();

    //通过QSerialPortInfo查找可用串口
//    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
////        this->uart_select_cb->addItem(info.portName());
//        //info.description();         //描述符号
//        //info.manufacturer();        //设备制造商
//    }
}


