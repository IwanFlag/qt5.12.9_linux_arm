#include "printeruartthread.h"
#include "qdebug.h"
#include "main.h"
#include <QMessageBox>


PrinterUartThread::PrinterUartThread()
{
    qDebug("[PrinterUartThread--%s]:>>", __func__);
    //m_port = port;
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printerUart_ready_read_slots);

}

/**
 * @brief PrinterUartThread::run
 * 重写，初始化
 */
void PrinterUartThread::run()
{
    qDebug("[PrinterUartThread--%s]:>>", __func__);
//    QObject::connect(g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::readyRead, this, &printerUart_ready_read_slots);
    //QObject::connect(&g_widget->tab_uart_manager->printerSerialPort, &QSerialPort::errorOccurred, this, &printerUart_ready_read_slots);
    QThread::exec();
}

/**
 * @brief PrinterUartThread::printerUart_ready_read_slots
 */
void PrinterUartThread::printerUart_ready_read_slots()
{
    qDebug("[PrinterUartThread--%s]:>>", __func__);


    //QMessageBox::about(NULL, tr("PrinterUartThread"), tr("printerUart_ready_read_slots"));

    //从接收缓冲区中读取数据
    QByteArray buffer = g_widget->tab_uart_manager->printerSerialPort.readAll();

    //遍历打印试试
    for(int i = 0; i < buffer.size(); i++)
    {
        qDebug("[PrinterUartThread--%s]:>>recv data:\n%02x", __func__, buffer.at(i));
    }

    //QByteArray转为大写QSting
    QString str(buffer.toHex().toUpper());//toUpper()大写

    //从界面中读取以前收到的数据
    QString recv = g_widget->tab_uart_manager->recv_plain_text->toPlainText();
    recv += QString(str);
    //recv += "\n";           //加一个换行符

    //清空以前的显示
    //g_widget->tab_uart_manager->recv_plain_text->clear();

    //重新显示
    //g_widget->tab_uart_manager->recv_plain_text->setPlainText(recv);
    emit sendDataToWdiget(recv);
}

void PrinterUartThread::printerUart_sendDataToPrinter_slots(QByteArray data)
{
    qDebug("[PrinterUartThread--%s]:>>", __func__);
    g_widget->tab_uart_manager->uart_send_HEX_byte(data);
}
