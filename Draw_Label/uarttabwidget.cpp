#include "uarttabwidget.h"
#include <QDebug>
#include <QMessageBox>
#include "main.h"
#include <QListView>
#include "common_fun.h"


UartTabWidget::UartTabWidget(QWidget* parent)
    :QWidget(parent)
{
    qDebug("[UartTabWidget--%s]:>>%s", __func__, "create a uart widget");
    this->uart_create_widget_init();                    //必须放在开头

    //创建一个串口对象
    //printerSerialPort  = new QSerialPort;               //串口对象

    //创建一个串口子线程
    printerSerialThread = new PrinterUartThread;                   //打印机串口子线程

    //信号槽初始化
    uart_init_signal_slot();

    //初始化设置波特率 115200
    uart_bound_cb->setCurrentIndex(ENUM_UART_BOUND_115200);

    //发送按键失能
    send_byte_bt->setEnabled(false);
    cut_over_bt->setEnabled(false);
    cut_half_bt->setEnabled(false);
    init_reset_bt->setEnabled(false);
    testpage_bt->setEnabled(false);

    isUartOpenFlag = false;
}

void UartTabWidget::uart_create_widget_init()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();

    //2.加一个label标签，来显示item类别
    this->lab = new QLabel;
    this->lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);
    this->lab->setText(tr("UART"));

    //设置字号
    QFont ft;
    ft.setPointSize(g_font_size[GRAPHIC_FONT_SIZE_HUGE]);
    this->lab->setFont(ft);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    this->lab->setPalette(pa);

    //对齐
    this->lab->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    vb->addWidget(this->lab);

/*---------2.创建 setting group---------*/
    this->setting_gp = new QGroupBox;
    vb->addWidget(this->setting_gp);

    this->setting_gp->setTitle(tr("uart setting"));

    //创建网络栅格布局
    QGridLayout *content_gl = new QGridLayout;
    content_gl->setSpacing(50);       //设置间距

    //1.串口选择下拉列表
    this->uart_select_cb = new QComboBox;

    this->uart_select_cb->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    this->uart_select_cb->setView(new QListView());       //不知道干撒的

    //加载item
//    this->uart_select_cb->addItem(g_uart_name[ENUM_UART_SELECT_NO], ENUM_UART_SELECT_NO);
    this->uart_select_cb->addItem(g_uart_name[ENUM_UART_SELECT_0], ENUM_UART_SELECT_0);
    this->uart_select_cb->addItem(g_uart_name[ENUM_UART_SELECT_1], ENUM_UART_SELECT_1);
    this->uart_select_cb->addItem(g_uart_name[ENUM_UART_SELECT_2], ENUM_UART_SELECT_2);
    this->uart_select_cb->addItem(g_uart_name[ENUM_UART_SELECT_3], ENUM_UART_SELECT_3);

//    this->uart_select_cb->setItemText(ENUM_UART_SELECT_NO, g_uart_name[ENUM_UART_SELECT_NO]);
    this->uart_select_cb->setItemText(ENUM_UART_SELECT_0, g_uart_name[ENUM_UART_SELECT_0]);
    this->uart_select_cb->setItemText(ENUM_UART_SELECT_1, g_uart_name[ENUM_UART_SELECT_1]);
    this->uart_select_cb->setItemText(ENUM_UART_SELECT_2, g_uart_name[ENUM_UART_SELECT_2]);
    this->uart_select_cb->setItemText(ENUM_UART_SELECT_3, g_uart_name[ENUM_UART_SELECT_3]);

    content_gl->addWidget(this->uart_select_cb, 0, 0, 1, 1); //占据1行1列


    //2.波特率下拉列表选择
    this->uart_bound_cb = new QComboBox;

    this->uart_bound_cb->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    this->uart_bound_cb->setView(new QListView());       //不知道干撒的

    //加载item
    this->uart_bound_cb->addItem(QString::number(g_uart_bound_val[ENUM_UART_BOUND_4800]), ENUM_UART_BOUND_4800);
    this->uart_bound_cb->addItem(QString::number(g_uart_bound_val[ENUM_UART_BOUND_9600]), ENUM_UART_BOUND_9600);
    this->uart_bound_cb->addItem(QString::number(g_uart_bound_val[ENUM_UART_BOUND_115200]), ENUM_UART_BOUND_115200);
    this->uart_bound_cb->addItem(QString::number(g_uart_bound_val[ENUM_UART_BOUND_921600]), ENUM_UART_BOUND_921600);

    this->uart_bound_cb->setItemText(ENUM_UART_BOUND_4800, QString::number(g_uart_bound_val[ENUM_UART_BOUND_4800]));
    this->uart_bound_cb->setItemText(ENUM_UART_BOUND_9600, QString::number(g_uart_bound_val[ENUM_UART_BOUND_9600]));
    this->uart_bound_cb->setItemText(ENUM_UART_BOUND_115200, QString::number(g_uart_bound_val[ENUM_UART_BOUND_115200]));
    this->uart_bound_cb->setItemText(ENUM_UART_BOUND_921600, QString::number(g_uart_bound_val[ENUM_UART_BOUND_921600]));
    content_gl->addWidget(this->uart_bound_cb, 0, 1, 1, 1); //占据1行1列


    //检测串口按钮
    this->search_bt = new QPushButton;
    this->search_bt->setText(tr("Search"));
    content_gl->addWidget(this->search_bt, 1, 0, 1, 1); //占据1行1列

    //打开串口按钮
    this->open_close_bt = new QPushButton;
    this->open_close_bt->setText(tr("Open"));
    content_gl->addWidget(this->open_close_bt, 1, 1, 1, 1); //占据1行1列

    //加载网络栅格布局
    this->setting_gp->setLayout(content_gl);


    /*---------2.创建 recv group---------*/
    this->recv_gp = new QGroupBox;
    vb->addWidget(this->recv_gp);

    this->recv_gp->setTitle(tr("recv frame"));

    //创建网络栅格布局
    QGridLayout *recv_gl = new QGridLayout;
    recv_gl->setSpacing(10);       //设置间距

    //富文本框
    this->recv_plain_text = new QPlainTextEdit(this);
    this->recv_plain_text->setStyleSheet(BG_COLOR_STYLE_WHITE);
    recv_gl->addWidget(this->recv_plain_text, 0, 0, 1, 3); //占据1行1列
    //plain_text->setPlainText(tr(STR_TEXT_EDIT_WRITE_HERE));

    //加载网络栅格布局
    this->recv_gp->setLayout(recv_gl);

    /*---------3.创建 send group---------*/
    this->send_gp = new QGroupBox;
    vb->addWidget(this->send_gp);

    this->send_gp->setTitle(tr("send frame"));

    //创建网络栅格布局
    QGridLayout *send_gl = new QGridLayout;
    send_gl->setSpacing(10);       //设置间距

    //富文本框
    this->send_plain_text = new QPlainTextEdit;
    this->send_plain_text->setStyleSheet(BG_COLOR_STYLE_WHITE);
    send_gl->addWidget(this->send_plain_text, 0, 0, 1, 3); //占据1行1列
    //plain_text->setPlainText(tr(STR_TEXT_EDIT_WRITE_HERE));

    //加载网络栅格布局
    this->send_gp->setLayout(send_gl);

/*---------4.创建 cmd group---------*/
    this->cmd_gp = new QGroupBox;
    vb->addWidget(this->cmd_gp);
    this->cmd_gp->setTitle(tr("uart cmd"));

    //创建网络栅格布局
    QGridLayout *cmd_gl = new QGridLayout;
    cmd_gl->setSpacing(10);       //设置间距


    //清除按钮
    this->clearall_bt = new QPushButton(this);
    this->clearall_bt->setText(tr("ClearAll"));
    cmd_gl->addWidget(this->clearall_bt, 0, 0, 1, 1); //占据1行1列

//    //发送按钮(默认字符流)
//    this->send_bt = new QPushButton(this);
//    this->send_bt->setText("SendChar");
//    cmd_gl->addWidget(this->send_bt, 0, 1, 1, 1); //占据1行1列

    //发送按钮(默认字节流)
    this->send_byte_bt = new QPushButton(this);
    this->send_byte_bt->setText(tr("SendHexByte"));
    cmd_gl->addWidget(this->send_byte_bt, 0, 2, 1, 1); //占据1行1列

    //加载网络栅格布局
    this->cmd_gp->setLayout(cmd_gl);


    /*---------5.创建打印机按钮 printer group---------*/
    this->print_cmd_gp = new QGroupBox;
    vb->addWidget(this->print_cmd_gp);
    this->print_cmd_gp->setTitle(tr("print cmd"));

    //创建网络栅格布局
    QGridLayout *print_cmd_gl = new QGridLayout;
    print_cmd_gl->setSpacing(50);       //设置间距


    //全切 按钮
    this->cut_over_bt = new QPushButton(this);
    this->cut_over_bt->setText(tr("CutOver"));
    print_cmd_gl->addWidget(this->cut_over_bt, 0, 0, 1, 1); //占据1行1列

    //半切 按钮
    this->cut_half_bt = new QPushButton(this);
    this->cut_half_bt->setText(tr("CutHalf"));
    print_cmd_gl->addWidget(this->cut_half_bt, 0, 1, 1, 1); //占据1行1列

    //
    this->init_reset_bt = new QPushButton(this);
    this->init_reset_bt->setText(tr("Reset"));
    print_cmd_gl->addWidget(this->init_reset_bt, 1, 0, 1, 1); //占据1行1列

    // 按钮
    this->testpage_bt = new QPushButton(this);
    this->testpage_bt->setText(tr("testPrint"));
    print_cmd_gl->addWidget(this->testpage_bt, 1, 1, 1, 1); //占据1行1列

    //加载网络栅格布局
    this->print_cmd_gp->setLayout(print_cmd_gl);

    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief UartTabWidget::uart_init_signal_slot
 *          uart界面初始化信号和槽
 */
void UartTabWidget::uart_init_signal_slot()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    //连接寻找按钮 和对应的槽函数
//    QObject::connect(this->printerSerialPort, SIGNAL(readyRead()), this, SLOT(uart_ready_read_slots()));
    //QObject::connect(&printerSerialPort, &QSerialPort::readyRead, this, &UartTabWidget::uart_ready_read_slots);
    QObject::connect(this->search_bt, SIGNAL(clicked(bool)), this, SLOT(uart_search_com_slots()));
    QObject::connect(this->open_close_bt, SIGNAL(clicked(bool)), this, SLOT(uart_open_close_com_slots()));
    QObject::connect(this->clearall_bt, SIGNAL(clicked(bool)), this, SLOT(uart_clearall_data_slots()));
    //QObject::connect(this->send_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_char_stream_data_slots()));
    QObject::connect(this->send_byte_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_HEX_byte_stream_data_slots()));
    //特别注意这个，需要使用队列存储信号,注意第五个参数不同
    QObject::connect(printerSerialThread, SIGNAL(sendDataToWdiget(QString)), this, SLOT(uart_recv_data_handle(QString)), Qt::QueuedConnection);


    //打印机按钮槽函数
    QObject::connect(this->cut_over_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_cut_over_slots()));
    QObject::connect(this->cut_half_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_cut_half_slots()));
    QObject::connect(this->init_reset_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_reset_slots()));
    QObject::connect(this->testpage_bt, SIGNAL(clicked(bool)), this, SLOT(uart_send_cut_testPrint_slots()));
}

/**
 * @brief UartTabWidget::uart_send_HEX_byte
 *              串口发送数据(实际会把16进制的字符串转为16进制的数组)
 *              这里先不去除空白符
 * @param str:传入待发送的16进制的QString字符串
 */
void UartTabWidget::uart_send_HEX_byte(QString str_text)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    //获取界面上的16进制字符串数据,注意，是16进制字符串,"a",而不是0xa
    //QString str_text = send_plain_text->toPlainText();

    //去掉字符串里面的空白符(两边没有去掉)
    //str_text = str_text.simplified();

    //去掉字符串两头的空白符
    //str = str.trimmed();

    qDebug("[UartTabWidget--%s]:>>[str_text]:%s\n", __func__, qPrintable(str_text));

    //把16进制字符串转为char* 纯16进制
    QByteArray byte_text;
    StringToHex(str_text, byte_text);
    qDebug("[UartTabWidget--%s]:>>size:%d", __func__, byte_text.size());

    //遍历打印试试
    for(int i = 0; i < byte_text.size(); i++)
    {
        qDebug("[UartTabWidget--%s]:>>[byte_text]%02x", __func__, byte_text.at(i));
    }

    printerSerialPort.write(byte_text);
}

/**
 * @brief UartTabWidget::uart_send_HEX_byte
 *      直接发送16进制字节流
 * @param b_data
 */
void UartTabWidget::uart_send_HEX_byte(QByteArray b_data)
{
    qDebug("[UartTabWidget--%s]:>>size:%d", __func__, b_data.size());
//    for(int i = 0; i < b_data.size(); i++)
//    {
//        qDebug("[UartTabWidget--%s]:>b_data:%02X\n", __func__, b_data.at(i));
//    }
    printerSerialPort.write(b_data);
}

void UartTabWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    QWidget::mousePressEvent(event);
}

//**
// * @brief UartTabWidget::uart_ready_read_slots
// */
//void UartTabWidget::uart_ready_read_slots()
//{
//    qDebug("[UartTabWidget--%s]:>>", __func__);

//    //QPlainTextEdit *recv = tab_uart_manager->findChild<QPlainTextEdit*>(recv_plain_text);
//    //QPushButton *button = parentWidget->findChild<QPushButton *>("button1");
//    //button->setText("start")
//    //recv->setPlainText("aaa");

//    //从接收缓冲区中读取数据
//    QByteArray buffer = printerSerialPort->readAll();
//    //遍历打印试试
//    for(int i = 0; i < buffer.size(); i++)
//    {
//        qDebug("[UartTabWidget--%s]:>>recv data:\n%02x", __func__, buffer.at(i));
//    }

//    //QByteArray转为大写QSting
//    QString str(buffer.toHex().toUpper());//toUpper()大写
//    //从界面中读取以前收到的数据
//    QString recv = this->recv_plain_text->toPlainText();
//    recv += QString(str);
//    recv += "\n";           //加一个换行符


//    //清空以前的显示
//    this->recv_plain_text->clear();

//    //重新显示
//    //this->recv_plain_text->append(recv);
//    //this->recv_plain_text->appendPlainText(recv);
//    this->recv_plain_text->setPlainText(recv);
//}

/**
 * @brief MainWindow::uart_search_com_slots
 *      搜寻检测可用串口，并加载到下拉列表中
 */
void UartTabWidget::uart_search_com_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    //清除选项
    this->uart_select_cb->clear();

    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        this->uart_select_cb->addItem(info.portName());
        //info.description();         //描述符号
        //info.manufacturer();        //设备制造商
    }
}

/**
 * @brief UartTabWidget::uart_open_close_com_slots
 *              打开串口
 */
void UartTabWidget::uart_open_close_com_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    if(QString::compare(this->open_close_bt->text(), tr("Open"), Qt::CaseInsensitive) == 0)
    {
        qDebug("[UartTabWidget--%s]:>>ready open uart", __func__);
        //设置串口名
        printerSerialPort.setPortName(uart_select_cb->currentText());
        lab->setText(uart_select_cb->currentText());

        int bound = uart_bound_cb->currentText().toInt();
        qDebug("[UartTabWidget--%s]:>>bound:(%d);", __func__,bound);

        //设置波特率
        printerSerialPort.setBaudRate(uart_bound_cb->currentText().toInt());

        //设置数据位数  默认Data8
        printerSerialPort.setDataBits(QSerialPort::Data8);


        //设置奇偶校验,默认无校验
        printerSerialPort.setParity(QSerialPort::NoParity);

        //设置停止位,默认 1bit 停止位
        printerSerialPort.setStopBits(QSerialPort::OneStop);

        //设置流控制
        printerSerialPort.setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!printerSerialPort.open(QIODevice::ReadWrite))
        {
            QMessageBox::about(NULL, tr("Uart Tip"), tr("Can not open uart"));
            return;
        }
        isUartOpenFlag = true;
        //设置"控制管脚状态".网上说,不设置这个,可能无法接收到槽函数
        //printerSerialPort->setDataTerminalReady(false);
        printerSerialPort.setDataTerminalReady(true);

        //qDebug("[UartTabWidget--%s]:>>11b:%d", __func__, b);
        //串口接收
        bool b = QObject::connect(&printerSerialPort, &QSerialPort::readyRead, printerSerialThread, &PrinterUartThread::printerUart_ready_read_slots);
        //串口发送
        connect(g_widget, SIGNAL(printerUart_sendDataToPrinter(QByteArray)), g_widget->tab_uart_manager->printerSerialThread, SLOT(printerUart_sendDataToPrinter_slots(QByteArray)), Qt::QueuedConnection);

        qDebug("[UartTabWidget--%s]:>>22b:%d", __func__, b);

        //开启串口子线程
        printerSerialThread->start();

        //控件失能
        uart_select_cb->setEnabled(false);
        uart_bound_cb->setEnabled(false);
        search_bt->setEnabled(false);
        open_close_bt->setText(QString(tr("Close")));

        //控件使能
        send_byte_bt->setEnabled(true);
        clearall_bt->setEnabled(true);
        cut_over_bt->setEnabled(true);
        cut_half_bt->setEnabled(true);
        init_reset_bt->setEnabled(true);
        testpage_bt->setEnabled(true);
    }
    else
    {
        //关闭串口
        printerSerialPort.close();
        //终止串口子线程
        printerSerialThread->terminate();
        //控件使能
        uart_select_cb->setEnabled(true);
        uart_bound_cb->setEnabled(true);
        search_bt->setEnabled(true);
        open_close_bt->setText(QString(tr("Open")));
        //控件失能
        send_byte_bt->setEnabled(false);
        //clearall_bt->setEnabled(false);
        cut_over_bt->setEnabled(false);
        cut_half_bt->setEnabled(false);
        init_reset_bt->setEnabled(false);
        testpage_bt->setEnabled(false);

        isUartOpenFlag = false;
    }
}

/**
 * @brief UartTabWidget::uart_send_char_stream_data_slots
 *          发送数据按钮槽函数
 *          发送的是"ab102f"这种（字符流）
 */
void UartTabWidget::uart_send_char_stream_data_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
        //获取界面上的字符数据并转换成utf8格式的字节流
        QString str_text = send_plain_text->toPlainText();
        qDebug("[UartTabWidget--%s]:>>[str_text]:\n%s", __func__, qPrintable(str_text));

        //转为ascii
        QByteArray byte_text = str_text.toUtf8();

        //遍历打印试试
        for(int i = 0; i < str_text.size(); i++)
        {
            //qDebug("[UartTabWidget--%s]:>>[HEX]%02d", __func__, byte_text.at(i));
            //qDebug("[UartTabWidget--%s]:>>[TEN]%02x", __func__, byte_text.at(i));
        }

        printerSerialPort.write(byte_text);
    }
}

/**
 * @brief UartTabWidget::uart_send_HEX_byte_stream_data_slots
 *          发送数据按钮槽函数
 *          发送的是16进制的字节流
 *   ！！！发现如果在两条语句间有空白符或者换行符，会导致乱码
 *   ！！！分析发现是16进制字符流 转为 16进制字节流 出问题了，会导致有01变为FFFFFF01
 *      上面问题已经解决
 */
void UartTabWidget::uart_send_HEX_byte_stream_data_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
    //获取界面上的16进制字符串数据,注意，是16进制字符串,"a",而不是0xa
    QString str_text = send_plain_text->toPlainText();

    //去掉字符串里面的空白符(两边没有去掉)
    str_text = str_text.simplified();

    //去掉字符串两头的空白符
    //str = str.trimmed();

    qDebug("[UartTabWidget--%s]:>>[str_text]:%s\n", __func__, qPrintable(str_text));

    //把16进制字符串转为char* 纯16进制
    QByteArray byte_text;
    StringToHex(str_text, byte_text);
    qDebug("[UartTabWidget--%s]:>>size:%d", __func__, byte_text.size());

    //遍历打印试试
    for(int i = 0; i < byte_text.size(); i++)
    {
        qDebug("[UartTabWidget--%s]:>>[byte_text]%02x", __func__, byte_text.at(i));
    }

    printerSerialPort.write(byte_text);
    }
}

/**
 * @brief UartTabWidget::uart_clearall_data_slots
 *          清空接收和发送编辑框槽函数
 */
void UartTabWidget::uart_clearall_data_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    recv_plain_text->clear();
    send_plain_text->clear();
}

/**
 * @brief UartTabWidget::uart_recv_data_handle
 */
void UartTabWidget::uart_recv_data_handle(QString data)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    //从界面中读取以前收到的数据
    QString recv = this->recv_plain_text->toPlainText();
    recv += data;
    recv += "\n";                                       //加一个换行符

    //清空以前的显示
    this->recv_plain_text->clear();

    //重新显示
    this->recv_plain_text->setPlainText(recv);
}

/**
 * @brief UartTabWidget::uart_send_cut_over_slots
 * 全切
 */
void UartTabWidget::uart_send_cut_over_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
        printer_CutDownPaper_A25();
    }
}

/**
 * @brief UartTabWidget::uart_send_cut_half_slots
 * 半切
 */
void UartTabWidget::uart_send_cut_half_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
        printer_CutHalfDownPaper_A26();
    }
}

/**
 * @brief UartTabWidget::uart_send_reset_slots
 * 恢复打印机默认参数/清除缓存
 */
void UartTabWidget::uart_send_reset_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
        printer_InitFactoryReset_A27();
    }
}

/**
 * @brief UartTabWidget::uart_send_cut_testPrint_slots
 * 打印自测试纸
 */
void UartTabWidget::uart_send_cut_testPrint_slots()
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    if(this->isUartOpenFlag)
    {
        printer_OutTestInfo_A28();
    }
}

/**
 * @brief UartTabWidget::uart_create_widget_init
 *              右侧tab显示uart框
 * @param meta
 */
/**
 * @brief UartTabWidget::printer_PageSet_B02
 * 指示一个Page页面的开始，并设置Page页的大小，参考点坐标和页面旋转角度。
 * 1A 5B 01 x_L x_H y_L y_H Width_L width_H Height_L Height_H Rotate
 *
    x
        Page页面参考原点相对标签纸当前位置左上角的x轴偏移量。
    y
        Page页面参考原点相对标签纸当前位置左上角的y轴偏移量。
    Width
        Page页面页宽， x+Width的取值范围为：[1,576/384]。-》》[1,576]。
    Height
        Page页面页高，Heigth的取值范围为：[1, 1200]。-》》[1, 384]
    Rotate
        Page页面旋转角度，Rotate的取值范围为：{0,3}。
        当Rotate为0时，页面不旋转。
        当Rotate为1时，页面旋转90°打印。
        当Rotate为2时，页面旋转180°打印。
        当Rotate为3时，页面旋转270°打印。
 * @return
 */
QByteArray UartTabWidget::printer_PageSet_B02(qint16 x, qint16 y, qint16 Width, qint16 Height, qint8 Rotate)
{
    qDebug("[UartTabWidget--%s]:>>111PageSet OK!:(%d,%d,%d,%d,%d)", __func__, x, y, Width, Height, Rotate);
    qint16 p_x;
    qint16 p_y;
    qint16 p_Width;
    qint16 p_Height;
    QByteArray b_data;


    p_x = x;
    p_y = y;
    p_Width = Width;
    p_Height = Height;


    qDebug("[UartTabWidget--%s]:>>222PageSet OK!:(%d,%d,%d,%d,%d)", __func__, p_x, p_y, p_Width, p_Height, Rotate);


    p_Width = (qint16)pix2dot(p_Width, ENUM_DIR_H);
    p_Height = (qint16)pix2dot(p_Height, ENUM_DIR_V);
    qDebug("[UartTabWidget--%s]:>>22(%d,%d)", __func__, p_Width, p_Height);

    if(p_Width > PRINTER_SUPPORT_WIDTH_DOT_MAX)
    {
        //如果宽度过大,则提示,继续打印
        //QMessageBox::about(NULL, tr("Uart Tip"), "pageSeting width too big,continue print");
        //p_Width = PRINTER_SUPPORT_WIDTH_DOT_MAX;
    }
    else
    {
        //如果画板小于实际的标签宽度,则想办法居中,x
        //x = (576 - Width) / 2;
    }

    if(p_Height > PRINTER_SUPPORT_HEIGHT_DOT_MAX)
    {
        //如果宽度过大,则提示,继续打印
        //QMessageBox::about(NULL, tr("Uart Tip"), "pageSeting height too big,continue print");
        //p_Height = PRINTER_SUPPORT_HEIGHT_DOT_MAX;
    }
    else
    {
        //y = (384 - Height) / 2;
    }

//    Width = Width > (576) ? (576) : Width;
//    Height = Height > 384 ? 384 : Height;

    qDebug("[UartTabWidget--%s]:>>333PageSet OK!:(%d,%d,%d,%d,%d)", __func__, p_x, p_y, p_Width, p_Height, Rotate);


    //包头
    b_data.append(0X1A);
    b_data.append(0X5B);
    b_data.append(0X01);

    //x
    b_data.append(ShortInt2CharEX(p_x, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(p_x, ENUM_HIGH_BYTE));

    //y
    b_data.append(ShortInt2CharEX(p_y, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(p_y, ENUM_HIGH_BYTE));

    //width
    b_data.append(ShortInt2CharEX(p_Width, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(p_Width, ENUM_HIGH_BYTE));

    //Height
    b_data.append(ShortInt2CharEX(p_Height, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(p_Height, ENUM_HIGH_BYTE));

    //Rotate
    b_data.append(Rotate);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_PageOver_B03
 * Page页结束指令
 * 标识一个Page页面数据的结束。
 * 1A 5D 00
 * @return
 */
QByteArray UartTabWidget::printer_PageOver_B03()
{
    QByteArray b_data;
    b_data.append(0X1A);
    b_data.append(0X5D);
    b_data.append((char)0x00);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_PagePrint_B04
 * Page页打印指令
 * 将Page页上的内容打印到标签纸上
 * 该指令只会将页面内容打印1遍。
 * b：1A 4F 01 PrintNum

 * 输入参数： PrintNum
    Page页面内容将打印PrintNum次。
 * @return
 */
QByteArray UartTabWidget::printer_PagePrint_B04(qint8 PrintNum)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    QByteArray b_data;
    b_data.append(0X1A);
    b_data.append(0X4F);
    b_data.append(0X01);

    b_data.append(PrintNum);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_PageRun_B05
 * 走纸指令:
 * b: 1A 0C 01 StopPosition Offset_L Offset_H
 *      1A 0C 01 00 00 01\1A 0C 01 00 00 00
 * 输入参数：StopPosition
    标识走纸停止位置标示，取值范围: {0, 3}。
        StopType = 0，切纸口与标签缝平齐处停止走纸；
        StopType = 1，光标与标签头平齐处停止走纸；
    Offset
        标识停止位置偏移。当打印机检测到标签头或标签尾后，继续走纸Offset个点的长度。
 * @return
 */
QString UartTabWidget::printer_PageRun_B05(qint8 StopPosition, qint16 Offset)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);

    QByteArray s_data;

    char send_data[6] = {0x00};
    int index = 0;

    send_data[index++] = 0X1A;
    send_data[index++] = 0X4F;
    send_data[index++] = 0X00;

    //StopPosition
    send_data[index++] = StopPosition;

    //Offset
    send_data[index++] = ShortInt2CharEX(Offset, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(Offset, ENUM_HIGH_BYTE);


    qDebug("[UartTabWidget--%s]:>>%s,index：%d", __func__, send_data, index);

    s_data= QByteArray(send_data, index);

    return s_data;
}

/**
 * @brief UartTabWidget::printer_TextEditSetPrint_B06
 * 文本绘制指令
 * b :1A 54 01 x_L x_H y_L y_H FontHeight_L FontHeight_H FontType_L FontType_H String00
 * b.
    输入参数：
    X
        定义文本起始位置x坐标，取值范围：[0, Page_Width-1]；
    y
        定义文本起始位置y坐标，取值范围：[0, Page_Height-1]；
    FontHeight(这是字体的高度)
        文本字符字体高度，有效值范围为{16, 24, 32, 48, 64, 80, 96}。
    FontType
        文本字符特效，各位定义如下：
        FontType位	定义
        [0]	字体加粗
        [1]	下划线
        [2]	反白标志位，置 1 位图反白打印，清零正常打印。
        [3]	保留
        [4]	旋转标志位： 0 旋转 0° ； 1 旋转 90°；
        [7:5]	保留。
    下面的高字节取值范围-字体大小范围（11、22、33、44、55、66），分别表示字体基于现在的倍数，11表示正常大小，22表示放大两倍
        [11:8]	位图宽度放大倍数。
        [15:12]	位图高度放大倍数。
    要打印的，以0x00终止的文本字符串数据流。
    B:
    1B 40 1a 5B 01 00 00 00 00 80 01 40 01 00
    1A 54 01
    00 00  //X偏移量
    00 00  //Y偏移量
    18 00  //固定
    01 33
    C4E3BAC3 00
    1a 5d 00
    1a 4f 00
    备    注:
        字体大小范围（11、22、33、44、55、66）
        当文本宽度与文本起始坐标x的和大于页面宽度时,文本被截断打印。
 * @return
 */
QByteArray UartTabWidget::printer_TextEditSetPrint_B06(qint16 x_offset, qint16 y_offset, qint16 FontHeight, qint16 FontType, QString data, qint16 data_len)
{
    qDebug("[UartTabWidget--%s]:>>(%d,%d,%d,%d)", __func__,x_offset, y_offset, FontHeight, FontType);


    QByteArray b_data;

    //包头
    b_data.append(0X1A);
    b_data.append(0X54);
    b_data.append(0X01);

    //x_offset
    x_offset = pix2dot(x_offset, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(x_offset, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(x_offset, ENUM_HIGH_BYTE));

    //y_offset
    y_offset = pix2dot(y_offset, ENUM_DIR_V);
    b_data.append(ShortInt2CharEX(y_offset, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(y_offset, ENUM_HIGH_BYTE));

    //FontHeight
    //FontHeight = pix2dot(FontHeight, ENUM_DIR_V);     //这里不需要转换
    b_data.append(ShortInt2CharEX(FontHeight, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(FontHeight, ENUM_HIGH_BYTE));

    //FontType
    b_data.append(ShortInt2CharEX(FontType, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(FontType, ENUM_HIGH_BYTE));


    //data，因为这里是真实的字符串，所以需要转为8bit数组，其实就是QByte
//    QByteArray data_ba = utf8ToGb2312(data.toUtf8().data()).toLocal8Bit();
//    for(int i = 0; i < data_ba.size(); i++)
//    {
//        char a = (char)data_ba.at(i);
//        //qDebug("[UartTabWidget--%s]:>>[abc]%d,%d", __func__,data_ba.at(i), a);
//        b_data.append(a);
//    }
    b_data.append(utf8ToGb2312(data.toUtf8().data()).toLocal8Bit());
    b_data.append((char)0X00);                              //必须要加的数据内容结尾


    return b_data;
}

/**
 * @brief UartTabWidget::printer_LineEditSetPrint_B07
 * 线段绘制指令
 * b.
    1A 5C 01 StartX_L StartX_H EndY_L EndY_H Width_L Width_H Color

输入参数：
    StartX
        直线段起始点x坐标值，取值范围：[0, Page_Width-1]。
    StartY
        直线段起始点y坐标值，取值范围：[0，Page_Height-1]。
    EndX
    直线段终止点x坐标值，取值范围：[0, Page_Width-1]。
    EndY
        直线段终止点y坐标值，取值范围：[0,Page_Height-1]。
    Width
        直线段线宽，取值范围：[1，Page_Height-1]。
    Color
        直线段颜色，取值范围：{0, 1}。当Color为1时，线段为黑色。当Color为0时，线段为白色。
 * @return
 */
QByteArray UartTabWidget::printer_LineEditSetPrint_B07(qint16 start_x, qint16 start_y, qint16 end_x, qint16 end_y, qint16 width, qint8 color)
{
    qDebug("[UartTabWidget--%s]:>>start_x:%d,start_y:%d,end_x:%d,end_y:%d,width:%d,color:%d", __func__,start_x, start_y, end_x, end_y, width, color);
    QByteArray b_data;

    //包头
    b_data.append(0X1A);
    b_data.append(0X5C);
    b_data.append(0X01);

    //start_x
    start_x = pix2dot(start_x, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(start_x, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(start_x, ENUM_HIGH_BYTE));

    //start_y
    start_y = pix2dot(start_y, ENUM_DIR_V);
    b_data.append(ShortInt2CharEX(start_y, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(start_y, ENUM_HIGH_BYTE));

    //end_x
    end_x = pix2dot(end_x, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(end_x, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(end_x, ENUM_HIGH_BYTE));

    //end_y
    end_y = pix2dot(end_y, ENUM_DIR_V);
    b_data.append(ShortInt2CharEX(end_y, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(end_y, ENUM_HIGH_BYTE));

    //width
    //b_data.append(width);
    width = pix2dot(width, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(width, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(width, ENUM_HIGH_BYTE));

    //color
    b_data.append(color);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_RectFrameEditSetPrint_B08
 * 在Page页指定位置绘制指定大小的矩形框。
 * 输入参数：
    Left
        矩形框左上角x 坐标值，取值范围：[0, Page_Width-1]。
    Top
        矩形框左上角y坐标值。取值范围：[0, Page_Height-1]。
    Right
        矩形框右下角x坐标值。取值范围：[0, Page_Width-1]。
    Bottom
        矩形框右下角y坐标值。取值范围：[0, Page_Height-1]。
    Width
        矩形框线宽。
    Color
        矩形框线颜色，曲直范围{0，1}。当Color = 1时，绘制黑色矩形宽，Color = 0 时，绘制白色矩形框。
    返回参数：无
 *  1A 26 01 Left_L Left_H Top_L Top_H Right_L Right_H Bottom_L Bottom_H Width_L Width_H Color
 * @return
 */
QByteArray UartTabWidget::printer_RectFrameEditSetPrint_B08(qint16 left, qint16 top, qint16 right, qint16 bottom, qint16 width, qint8 color)
{
    qDebug("[UartTabWidget--%s]:>>left:%d,top:%d,right:%d,bottom:%d,width:%d,color:%d", __func__,left, top, right, bottom, width, color);
    QByteArray b_data;

    //包头
    b_data.append(0X1A);
    b_data.append(0X26);
    b_data.append(0X01);

    //left
    left = pix2dot(left, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(left, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(left, ENUM_HIGH_BYTE));

    //top
    top = pix2dot(top, ENUM_DIR_V);
    b_data.append(ShortInt2CharEX(top, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(top, ENUM_HIGH_BYTE));

    //right
    right = pix2dot(right, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(right, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(right, ENUM_HIGH_BYTE));

    //bottom
    bottom = pix2dot(bottom, ENUM_DIR_V);
    b_data.append(ShortInt2CharEX(bottom, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(bottom, ENUM_HIGH_BYTE));

    //width
    width = pix2dot(width, ENUM_DIR_H);
    b_data.append(ShortInt2CharEX(width, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(width, ENUM_HIGH_BYTE));

    //color
    b_data.append(color);


    return b_data;
}

QString UartTabWidget::printer_RectBlockEditSetPrint_B09()
{

}
/**
 * @brief UartTabWidget::printer_OneBarCodeEditSetPrint_B10
 * 一维条码指令
 *  1A 30 00 x_L x_H y_L y_H BarcodeType BarcodeHeight UnitWidth Rotate String00
    输入参数：
    x
        条码左上角x坐标值，取值范围：[0, Page_Width-1]。
    y
        条码左上角y坐标值，取值范围：[0, Page_Height-1]。
    BarcodeType
        标识条码类型，取值范围：[0,29]。各值定义如下：
    BarcodeHeight :
        定义条码高度。
    UnitWidth :
        定义条码码宽。取值范围：[1, 4]。各值定义如下：
    Rotate:
        表示条码旋转角度。取值范围：[0, 3]。各值定义如下：
    String00:
        以0x00结尾的文本字符数据流。
* @return
 */
QByteArray UartTabWidget::printer_OneBarCodeEditSetPrint_B10(qint16 x, qint16 y, qint8 BarcodeType, qint8 BarcodeHeight, qint8 UnitWidth, qint8 Rotate, QString data, qint16 data_len)
{
    qDebug("[UartTabWidget--%s]:>>x:%d,y:%d,BarcodeType:%d,BarcodeHeight:%d,%d,%d", __func__,x,y,BarcodeType,BarcodeHeight, UnitWidth, Rotate);
    QByteArray b_data;

    //包头
    b_data.append(0X1A);
    b_data.append(0X30);
    b_data.append((char)0X00);

    //x
    x = pix2dot(x, ENUM_DIR_H);
    qDebug("[UartTabWidget--%s]:>>[aaa]x:%d,y:%d,(%d，%d)", __func__,x,y,ShortInt2CharEX(x, ENUM_LOW_BYTE),ShortInt2CharEX(x, ENUM_HIGH_BYTE));

    b_data.append(ShortInt2CharEX(x, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(x, ENUM_HIGH_BYTE));

    //y
    y = pix2dot(y, ENUM_DIR_H);
    qDebug("[UartTabWidget--%s]:>>[zzz]x:%d,y:%d,%d", __func__,x,y,ShortInt2CharEX(y, ENUM_LOW_BYTE));

    b_data.append(ShortInt2CharEX(y, ENUM_LOW_BYTE));
    b_data.append(ShortInt2CharEX(y, ENUM_HIGH_BYTE));

    //BarcodeType
    b_data.append(BarcodeType);

    //BarcodeHeight
    BarcodeHeight = pix2dot(BarcodeHeight, ENUM_DIR_H);
    b_data.append(BarcodeHeight);

    //UnitWidth
    b_data.append(UnitWidth);

    //Rotate
    b_data.append(Rotate);

    //data
    b_data.append(data.toUtf8());
    b_data.append((char)0x00);      //必须00结尾，才能打出来


    //qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    //uart_send_HEX_byte(b_data);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_QRCodeEditSetPrint_B11
 *          QRCode条码(二维码)指令
 * 1A 31 00 version ECC x_L x_H y_L y_H UnitWidth Rotate String00
 * 输入参数：
    version
        指定字符版本。取值范围：[0,20]。当version为0时，打印机根据字符串长度自动计算版本号。
    ECC
        指定纠错等级。取值范围：[1, 4]。各值定义如下：
        ECC	纠错等级
        1	L：7%，低纠错，数据多。
        2	M：15%，中纠错
        3	Q：优化纠错
        4	H：30%，最高纠错，数据少。
    x
        QRCode码左上角x坐标值，取值范围：[0，Page_Width-1]。
    y
        QRCode码左上角y坐标值，取值范围：[0, Page_Height-1]。
    UnitWidth
        QRCode码码块，取值范围：[1, 4]。各值定义与指令输入参数UniWidth相同。
    Rotate
        QRCode码旋转角度，取值范围：[0, 3]。各值定义与指令输入参数Rotate相同。
    String00
        以0x00终止的QRCode文本字符数据流。
    返 回 值：无。

 * @return
 */
QByteArray UartTabWidget::printer_QRCodeEditSetPrint_B11(qint8 version, qint8 ECC, qint16 x, qint16 y, qint8 UnitWidth, qint8 Rotate, QString data, qint16 data_len)
{
    qDebug("[UartTabWidget--%s]:>>(version:%d,ECC:%d,x:%d,y:%d,UnitWidth:%d,Rotate:%d,data_len:%d)", __func__,version, ECC, x, y, UnitWidth, Rotate, data_len);
    QByteArray b_data;


    b_data.append(0X1A);
    b_data.append(0X31);
    b_data.append((char)0x00);      //必须强转下

    //version
    b_data.append(version);

    //ECC
    b_data.append(ECC);

    //x
    x = (pix2mm(x, ENUM_DIR_H));
    x = mm2dot(x);
    qint8 x_l = ShortInt2CharEX(x, ENUM_LOW_BYTE);
    qint8 x_h = ShortInt2CharEX(x, ENUM_HIGH_BYTE);

    b_data.append(x_l);
    b_data.append(x_h);

    //y
    y = (pix2mm(y, ENUM_DIR_V));
    y = mm2dot(y);
    qint8 y_l = ShortInt2CharEX(y, ENUM_LOW_BYTE);
    qint8 y_h = ShortInt2CharEX(y, ENUM_HIGH_BYTE);
    b_data.append((char)y_l);
    b_data.append((char)y_h);

    //UnitWidth
    b_data.append(UnitWidth);

    //Rotate
    b_data.append(Rotate);

    //data，因为这里是真实的字符串，所以需要转为utf-8
    //b_data.append(data.toUtf8());
    b_data.append(utf8ToGb2312(data.toUtf8().data()).toLocal8Bit());
    b_data.append((char)0x00);       //必须要加的数据内容结尾

    //qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    //uart_send_HEX_byte(b_data);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_PixMapEditSetPrint_B12
 * 位图指令
 * b：
    1A 21 01 x_L x_H y_L y_H Width_L Width_H Height_L Height_L ShowType Data
    b :
    输入参数：
    x
        位图左上角x坐标值，取值范围：[0, Page_Width]。
    y
        位图左上角y坐标值，取值范围：[0, Page_Height]。
    Width
        位图的像素宽度。
    Height
        位图的像素高度。
    ShowType（16bit）
        位图打印特效，ShowType 值各位定义如下：
    Data
        位图的点阵数据。
 * @return
 */
QString UartTabWidget::printer_PixMapEditSetPrint_B12(qint16 x, qint16 y, qint16 Width, qint16 Height, qint16 ShowType, char* data, qint16 data_len)
{
    qDebug("[UartTabWidget--%s]:>>", __func__);
    QByteArray s_data;
    int count = 13 + data_len;          //长度
    char send_data[count] = {0x00};
    int index = 0;

    send_data[index++] = 0X1A;
    send_data[index++] = 0X21;
    send_data[index++] = 0X01;

    //x
    send_data[index++] = ShortInt2CharEX(x, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(x, ENUM_HIGH_BYTE);

    //y
    send_data[index++] = ShortInt2CharEX(y, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(y, ENUM_HIGH_BYTE);

    //Width
    send_data[index++] = ShortInt2CharEX(Width, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(Width, ENUM_HIGH_BYTE);

    //Height
    send_data[index++] = ShortInt2CharEX(Height, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(Height, ENUM_HIGH_BYTE);

    //ShowType
    send_data[index++] = ShortInt2CharEX(ShowType, ENUM_LOW_BYTE);
    send_data[index++] = ShortInt2CharEX(ShowType, ENUM_HIGH_BYTE);

    //data
    memcpy(send_data + index, data, data_len);
    index += data_len;

    qDebug("[UartTabWidget--%s]:>>%s,index：%d", __func__, send_data, index);
    s_data= QByteArray(send_data, index);

    return s_data;
}

bool UartTabWidget::printer_Modeset_C01()
{

}

bool UartTabWidget::printer_PageCheckUnderLabelMode_C02()
{

}

bool UartTabWidget::printer_BoundSet_D01()
{

}

void UartTabWidget::printer_InvokePic_E01()
{

}

bool UartTabWidget::printer_PaperHaveStatus_E02()
{

}

bool UartTabWidget::printer_PaperHaveQuery_E02_Ex()
{

}

/**
 * @brief UartTabWidget::printer_CutDownPaper_A25
 * 全切纸（会把纸张切断,一次可能会切不断，可以多尝试几次发送该指令）
 * 选择切刀模式并全切
 *  1B 40
    30 30 30 0D 0A
    1B 69
 */
QByteArray UartTabWidget::printer_CutDownPaper_A25()
{
    QByteArray b_data;

    b_data.append(0X1B);
    b_data.append(0X69);

    //qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    //uart_send_HEX_byte(b_data);

    return b_data;
}

/**
 * @brief UartTabWidget::printer_CutHalfDownPaper_A26
 * 选择切刀模式并半切
    1B 40
    30 30 30 0D 0A
    1B 6D
 */
QByteArray UartTabWidget::printer_CutHalfDownPaper_A26()
{
    QByteArray b_data;

    b_data.append(0X1B);
    b_data.append(0X6D);

    qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    uart_send_HEX_byte(b_data);

    return b_data;
}

/**
 * @brief UartTabWidget::printer_InitFactoryReset_A27
        指令名称	初始化打印机
        十六进制 ：1B 40
        功能描述	初始化打印机下列内容：
            清除打印缓存
            各参数恢复默认值
 * @return
 */
QByteArray UartTabWidget::printer_InitFactoryReset_A27()
{
    qDebug("[AttrTabWidget--%s]>>printer init ok!", __FUNCTION__);
    QByteArray b_data;

    b_data.append(0X1B);
    b_data.append(0X40);


    return b_data;
}

/**
 * @brief UartTabWidget::printer_OutTestInfo_A28
 * 打印自测页
    十六进制 ：12 54
    打印机打印一张自测页，上面包含打印机的程序版本，通讯接口类型，代码页和其他一些数据
    1B 40 12 54
 * @return
 */
QByteArray UartTabWidget::printer_OutTestInfo_A28()
{
    QByteArray b_data;

    b_data.append(0X12);
    b_data.append(0X54);

    qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    uart_send_HEX_byte(b_data);

    return b_data;
}

/**
 * @brief UartTabWidget::printer_FrontThenBack_A30
 *  自动步进和回退相同长度
    十六进制 ：1F  2D   61  01  00
    自动步进和回退相同长度，用于长时间打印机不工作时，软件下发该指令使打印机步进一小段距离和回退相同距离，不至于打印机卡纸
    下发指令：1F  2D   61  01  00
    返回数据：不返回数据
 * @return
 */
QByteArray UartTabWidget::printer_FrontThenBack_A30()
{
    QByteArray b_data;

    b_data.append(0X1F);
    b_data.append(0X2D);
    b_data.append(0X61);
    b_data.append(0X01);
    b_data.append((char)0X00);
    qDebug("[UartTabWidget--%s]:>b_data:%s\n", __func__, b_data.data());
    uart_send_HEX_byte(b_data);

    return b_data;
}
