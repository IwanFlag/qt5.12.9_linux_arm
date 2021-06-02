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

QString UartThread::getPort()
{
    return m_port;
}

/**
 * @brief UartThread::uart_open_close
 *      open or close
 */
void UartThread::uart_open_close(QString now_text, QString portName, QString bound)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    if(QString::compare(now_text, tr("Open"), Qt::CaseInsensitive) == 0)
    {
        qDebug("[UartTabWidget--%s]:>>ready open uart", __func__);
        //设置串口名
        serialPort->setPortName(portName);
        //lab->setText(uart_select_cb->currentText());

        //int bound = uart_bound_cb->currentText().toInt();
        //qDebug("[UartTabWidget--%s]:>>bound:(%d);", __func__,bound);

        //设置波特率
        serialPort->setBaudRate(bound.toInt());

        //设置数据位数  默认Data8
        serialPort->setDataBits(QSerialPort::Data8);


        //设置奇偶校验,默认无校验
        serialPort->setParity(QSerialPort::NoParity);

        //设置停止位,默认 1bit 停止位
        serialPort->setStopBits(QSerialPort::OneStop);

        //设置流控制
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!serialPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::about(NULL, tr("Uart Tip"), tr("Can not open uart"));
            return;
        }
        //isUartOpenFlag = true;
        //设置"控制管脚状态".网上说,不设置这个,可能无法接收到槽函数
        //printerSerialPort->setDataTerminalReady(false);
        serialPort->setDataTerminalReady(true);

        //qDebug("[UartTabWidget--%s]:>>11b:%d", __func__, b);
        //串口接收
        //bool b = QObject::connect(serialPort, &QSerialPort::readyRead, printerSerialThread, &PrinterUartThread::printerUart_ready_read_slots);
        //串口发送
        //connect(g_widget, SIGNAL(printerUart_sendDataToPrinter(QByteArray)), g_widget->tab_uart_manager->printerSerialThread, SLOT(printerUart_sendDataToPrinter_slots(QByteArray)), Qt::QueuedConnection);

        //qDebug("[UartTabWidget--%s]:>>22b:%d", __func__, b);

        //开启串口子线程
        //printerSerialThread->start();
        this->start();
//        //控件失能
//        uart_select_cb->setEnabled(false);
//        uart_bound_cb->setEnabled(false);
//        search_bt->setEnabled(false);
//        open_close_bt->setText(QString(tr("Close")));

//        //控件使能
//        send_byte_bt->setEnabled(true);
//        clearall_bt->setEnabled(true);
//        cut_over_bt->setEnabled(true);
//        cut_half_bt->setEnabled(true);
//        init_reset_bt->setEnabled(true);
//        testpage_bt->setEnabled(true);
    }
    else
    {
        //关闭串口
        serialPort->close();

        //终止串口子线程
        //printerSerialThread->terminate();
        this->terminate();

//        //控件使能
//        uart_select_cb->setEnabled(true);
//        uart_bound_cb->setEnabled(true);
//        search_bt->setEnabled(true);
//        open_close_bt->setText(QString(tr("Open")));
//        //控件失能
//        send_byte_bt->setEnabled(false);
//        //clearall_bt->setEnabled(false);
//        cut_over_bt->setEnabled(false);
//        cut_half_bt->setEnabled(false);
//        init_reset_bt->setEnabled(false);
//        testpage_bt->setEnabled(false);

//        isUartOpenFlag = false;
    }
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
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
//        this->uart_select_cb->addItem(info.portName());
        qDebug("[UartThread--%s]:>>portName:%ss", __func__, qPrintable(info.portName()));
        m_ports.append(info.portName());
        //info.description();         //描述符号
        //info.manufacturer();        //设备制造商
    }

    if(!m_ports.isEmpty())
    {
        qDebug("[UartThread--%s]:>>vaild port", __func__);

        //QObject::connect(item, SIGNAL(qmlSignal(QString)),&myClass, SLOT(cppSlot(QString)));
        emit uart_vaild_ports_to_qml(m_ports[0]);
        //m_port = m_ports[0];

//        QObject *rect = object->findChild<QObject*>("combobox_bound_select");
//        if (rect)
//            {
//                qDebug("[UartThread--%s]:>>vvvvvvvvvvvvvvcccccccccccccccc", __func__);

//            }
    }
    else
    {
        qDebug("[UartThread--%s]:>>not vaild port", __func__);
    }
}

void UartThread::uart_open_close_slots(QString now_text, QString portName, QString bound)
{
    qDebug("[UartThread--%s]:>>now_text:%s,portName:%s,bound:%s", __func__, qPrintable(now_text), qPrintable(portName), qPrintable(bound));
    uart_open_close(now_text, portName, bound);
}

