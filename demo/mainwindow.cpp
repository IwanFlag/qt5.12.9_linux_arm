#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug("%s", __FUNCTION__);
    //设置主界面窗体大小(按道理是要根据每个设备的分辨率来设置的，目前先不管这个，随便定一个)
    //this->resize(QSize(WIDGET_MAIN_WIDE,  WIDGET_MAIN_HEGIHT));
    //QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    //QRect deskRect = desktopWidget->availableGeometry();
    //获取设备屏幕大小
    //QRect screenRect = desktopWidget->screenGeometry();
    //获取系统设置的屏幕个数（屏幕拷贝方式该值为1）
    //int g_nScreenCount = desktopWidget->screenCount();
    //qDebug("MainWindow--%s>>screenRect:(%d,%d)", __FUNCTION__,screenRect.width(),screenRect.height());

    //设置主界面的大小
    this->resize(200, 200);

    //主界面底色为浅灰色
    this->setStyleSheet("background-color: rgb(0, 0, 0)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

