#ifndef PRINTERUARTTHREAD_H
#define PRINTERUARTTHREAD_H

#include "QThread"
#include <QSerialPort>
#include <QSerialPortInfo>



class UartThread : public QThread
{
    Q_OBJECT


    //explicit UartThread(QWidget *parent = nullptr);


signals:
    void sendDataToWdiget(QString data);


public slots:
    void Uart_ready_read_slots();
    void Uart_sendData_slots(QByteArray data);
    void uart_search_com_slots();


public:
    explicit UartThread();
    void run();


private:
    QSerialPort *serialPort;    //float data;


};

#endif // PRINTERUARTTHREAD_H
