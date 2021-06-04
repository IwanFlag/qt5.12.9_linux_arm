#include "UartThread.h"
#include "qdebug.h"
//#include "main.h"
#include <QMessageBox>
#include <QString>
#include <QIODevice>
#include <QObject>


/**
 * @brief UartThread::UartThread
 */
UartThread::UartThread()
{
    qDebug("[UartThread--%s]:>>", __func__);
    //m_port = port;
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printeruart_ready_read_slots);
    serialPort = new QSerialPort;                                 //init one uart port
}

/**
 * @brief UartThread::run
 * 重写，初始化
 */
void UartThread::run()
{
    qDebug("[UartThread--%s]:>>", __func__);
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printeruart_ready_read_slots);
    //QObject::connect(&g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::errorOccurred, this, &printeruart_ready_read_slots);
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
        QString MSG_STR;
        MSG_STR += now_text+"/" + portName+"/" + bound;
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
        if(serialPort->open(QIODevice::ReadWrite))
        {
            uart_open_flag_signals(1);
            QMessageBox::about(NULL, tr("Uart Tip"), MSG_STR);
        }
        else
        {
            QMessageBox::about(NULL, tr("Uart Tip"), tr("warning:Can not open uart"));
            uart_open_flag_signals(0);
            return;
        }
        //isUartOpenFlag = true;
        //设置"控制管脚状态".网上说,不设置这个,可能无法接收到槽函数
        //printerSerialPort->setDataTerminalReady(false);
        serialPort->setDataTerminalReady(true);

        //qDebug("[UartTabWidget--%s]:>>11b:%d", __func__, b);
        //串口接收
        connect(serialPort, &QSerialPort::readyRead, this, &UartThread::uart_ready_read_slots, Qt::QueuedConnection);
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
        //QMessageBox::about(NULL, tr("UartThread"), tr("close"));
        uart_close_flag_signals(1);

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

/**
 * @brief UartThread::uart_ready_read_slots
 * recevie
 */
void UartThread::uart_ready_read_slots()
{
    qDebug("[UartThread--%s]:>>", __func__);


    //QMessageBox::about(NULL, tr("UartThread"), tr("printeruart_ready_read_slots"));

    //从接收缓冲区中读取数据
    QByteArray buffer = serialPort->readAll();


    //QByteArray转为大写QSting
    QString str(buffer.toHex().toUpper());//toUpper()大写

//    //从界面中读取以前收到的数据
//    QString recv = g_widget->tab_uart_manager->recv_plain_text->toPlainText();
//    QString recv;

//    recv += QString(str);
//    recv += "\n";           //加一个换行符
        str+= "\n";

    QMessageBox::about(NULL, tr("Uart recevie:"), str);
    emit sendDataToQml(str);
}

/**
 * @brief UartThread::uart_sendData_slots
 *                  app send data to
 * @param data
 */
void UartThread::uart_sendData_slots(QString data)
{
    qDebug("[UartThread--%s]:>>data:%s", __func__, qPrintable(data));
//    g_widget->tab_uart_manager->uart_send_HEX_byte(data);
    QMessageBox::about(NULL, tr("Uart send"), data);
    //serialPort->writeData(ch, ba.size());
    serialPort->write(data.toLatin1());
}

/**
 * @brief UartThread::uart_search_com_slots
 *      搜寻检测可用串口，并加载到下拉列表中
 */
void UartThread::uart_search_com_slots()
{
    qDebug("[UartThread--%s]:>>", __func__);
    QString str;

    //清除选项
    //this->uart_select_cb->clear();

    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
//        this->uart_select_cb->addItem(info.portName());
        qDebug("[UartThread--%s]:>>portName:%ss", __func__, qPrintable(info.portName()));
        m_ports.append(info.portName());
        str += info.portName() + "/";
        //info.description();         //描述符号
        //info.manufacturer();        //设备制造商
        emit uart_vaild_ports_to_qml(info.portName());
    }


    //QMessageBox::about(NULL, tr("UartThread"), str);

    if(!m_ports.isEmpty())
    {
        qDebug("[UartThread--%s]:>>vaild port", __func__);

        //QObject::connect(item, SIGNAL(qmlSignal(QString)),&myClass, SLOT(cppSlot(QString)));
//        emit uart_vaild_ports_to_qml(m_ports[0]);

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

