#ifndef PRINTERUARTTHREAD_H
#define PRINTERUARTTHREAD_H

#include "QThread"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQmlListProperty>


class UartThread : public QThread
{
    Q_OBJECT
    //Q_PROPERTY(QQmlListProperty<QString> vaildPorts READ getVaildPorts)


signals:
    void sendDataToWdiget(QString data);
    void uart_vaild_ports_to_qml(QString port);


public slots:
    void Uart_ready_read_slots();
    void Uart_sendData_slots(QByteArray data);
    void uart_search_com_slots();
    void uart_open_close_slots(QString now_text, QString portName, QString bound);


public:
    explicit UartThread();
    void run();
    QString getPort();
    void uart_open_close(QString now_text, QString portName, QString bound);


private:
    QSerialPort *serialPort;    //float data;
    QList<QString> m_ports;
    QString m_port;

};

#endif // PRINTERUARTTHREAD_H
