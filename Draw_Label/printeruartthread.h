#ifndef PRINTERUARTTHREAD_H
#define PRINTERUARTTHREAD_H

#include "QThread"


class PrinterUartThread : public QThread
{
    Q_OBJECT

signals:
    void sendDataToWdiget(QString data);


public slots:
    void printerUart_ready_read_slots();
    void printerUart_sendDataToPrinter_slots(QByteArray data);


public:
    PrinterUartThread();
    void run();


private:
    QString m_port;
    //float data;


};

#endif // PRINTERUARTTHREAD_H
