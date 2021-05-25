#ifndef UARTTABWIDGET_H
#define UARTTABWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <printeruartthread.h>


class PrinterUartThread;
class UartTabWidget : public QWidget
{
    Q_OBJECT

public:
    bool isUartOpenFlag;                //串口是否打开


    UartTabWidget(QWidget* parent = Q_NULLPTR);


    void uart_create_widget_init();
    void uart_init_signal_slot();
    void uart_send_HEX_byte(QString str_text);        //发送16进制字节流数据
    void uart_send_HEX_byte(QByteArray ba);

    //----串口协议部分,根据设置返回协议字符串,再传给uart发出
    //Bxx代表是标签部分协议，非小票协议
    QByteArray printer_PageSet_B02(qint16 x, qint16 y, qint16 Width, qint16 Height, qint8 Rotate);
    QByteArray printer_PageOver_B03();
    QByteArray printer_PagePrint_B04(qint8 PrintNum);
    QString printer_PageRun_B05(qint8 StopPosition, qint16 Offset);
    QByteArray printer_TextEditSetPrint_B06(qint16 x_offset, qint16 y_offset, qint16 FontHeight, qint16 FontType, QString data, qint16 data_len);

    QByteArray printer_LineEditSetPrint_B07(qint16 start_x, qint16 start_y, qint16 end_x, qint16 end_y, qint16 width, qint8 color);
    QByteArray printer_RectFrameEditSetPrint_B08(qint16 left, qint16 top, qint16 right, qint16 bottom, qint16 width, qint8 color);
    QString printer_RectBlockEditSetPrint_B09();
    QByteArray printer_OneBarCodeEditSetPrint_B10(qint16 x, qint16 y, qint8 BarcodeType, qint8 BarcodeHeight, qint8 UnitWidth, qint8 Rotate, QString data, qint16 data_len);

    QByteArray printer_QRCodeEditSetPrint_B11(qint8 version, qint8 ECC, qint16 x, qint16 y, qint8 UnitWidth, qint8 Rotate, QString data, qint16 data_len);
    QString printer_PixMapEditSetPrint_B12(qint16 x, qint16 y, qint16 Width, qint16 Height, qint16 ShowType, char* data, qint16 data_len);

    //打印机参数设置
    bool printer_Modeset_C01();
    bool printer_PageCheckUnderLabelMode_C02();
    bool printer_BoundSet_D01();

    //打印机额外功能
    void printer_InvokePic_E01();
    bool printer_PaperHaveStatus_E02();
    bool printer_PaperHaveQuery_E02_Ex();

    //
    QByteArray printer_CutDownPaper_A25();
    QByteArray printer_CutHalfDownPaper_A26();
    QByteArray printer_InitFactoryReset_A27();
    QByteArray printer_OutTestInfo_A28();
    QByteArray printer_FrontThenBack_A30();


    //重写事件
    void mousePressEvent(QMouseEvent *);

    //自定义函数

    //成员对象
    QSerialPort printerSerialPort;             //打印机串口对象指针
    PrinterUartThread * printerSerialThread;               //打印机串口子线程

    QLabel *lab;
    QGroupBox *setting_gp;
    QComboBox *uart_select_cb;
    QComboBox *uart_bound_cb;
    QGroupBox *recv_gp;
    QPlainTextEdit *recv_plain_text;
    QGroupBox *send_gp;
    QPlainTextEdit *send_plain_text;
    QGroupBox *cmd_gp ;

    QPushButton *clearall_bt;
    QPushButton *send_bt;                   //默认发送字符流
    QPushButton *send_byte_bt;              //发送字节流
    QPushButton *search_bt;                 //搜寻检测串口按钮
    QPushButton *open_close_bt;             //打开串口按钮

    QGroupBox *print_cmd_gp ;
    QPushButton *cut_over_bt;                 //全切
    QPushButton *cut_half_bt;                //半切
    QPushButton *init_reset_bt;              //初始化，恢复出厂，清空
    QPushButton *testpage_bt;                //打印测试纸


public slots:
//    void uart_ready_read_slots();           //当PC收到串口数据,会自动触发此槽函数
    void uart_search_com_slots();           //寻找检测串口按钮
    void uart_open_close_com_slots();       //打开/关闭串口按钮
    void uart_send_char_stream_data_slots();            //发送字符流数据
    void uart_send_HEX_byte_stream_data_slots();        //发送16进制字节流数据
    void uart_clearall_data_slots();                //清除接收和发送数据
    void uart_recv_data_handle(QString data);

    //打印机槽函数
    void uart_send_cut_over_slots();
    void uart_send_cut_half_slots();
    void uart_send_reset_slots();
    void uart_send_cut_testPrint_slots();



};
#endif // UARTTABWIDGET_H
