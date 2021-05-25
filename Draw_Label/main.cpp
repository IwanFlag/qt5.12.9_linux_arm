#include "mainwindow.h"
#include <QApplication>
#include "common_def.h"
#include "drawtextitem.h"
#include <QTextCodec>
#include <QTranslator>
#include <QDomDocument>


//定义全局的变量
MainWindow *g_widget;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    //QTextCodec::setCodecForLocale(codec);

    QTranslator translator;
    translator.load(":/language/draw_label_zh.qm");
    a.installTranslator(&translator);


//    //新建QDomDocument类对象,它代表一个XML文档
//    QDomDocument doc("mydoc");

//    //建立指向*.xml文件的QFile对象
//    QFile file("my.xml");
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        qDebug("[main--%s]>>open failed!");
//        return 0;
//    }

//    QString errorStr;
//    int errorLine;
//    int errorCol;

//    if(!doc.setContent(&file, true, &errorStr, &errorLine, &errorCol))
//    {
//        qDebug("[main]>>(errorStr:%s, --%d, %d)", qPrintable(errorStr), errorLine, errorCol);
//        file.close();
//        return 0;
//    }


//    //关闭文件
//    file.close();
//    //获得doc的第一个节点,即XML说明
//    QDomNode firstNode = doc.firstChild();
//    //输出XML说明
//    qDebug("[main--%s]>>(%s,%s)", qPrintable(firstNode.nodeName()), qPrintable(firstNode.nodeValue()));


    g_widget = new MainWindow;
    g_widget->setWindowIcon(QIcon(MAIN_TEMPLATE_TWOCODE_PNG));
    g_widget->show();

    return a.exec();
}
