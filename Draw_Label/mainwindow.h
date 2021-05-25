#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common_def.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <drawlabel.h>
#include <QLayout>
#include "drawtextitem.h"
#include <uarttabwidget.h>
#include "attrtexttabwidget.h"
#include "attronecodetabwidget.h"
#include "attrtwocodetabwidget.h"
#include "attronecodetabwidget.h"
#include "drawlineitem.h"
#include "attrlinetabwidget.h"
#include "drawrectitem.h"
#include "attrrecttabwidget.h"
#include "attrlabeltabwidget.h"


class DrawLabel;        //增加前置申明


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void attr_widget_tab_meta_update_show(QGraphicsItem *item);
    void attr_tabmeta_show_invalid();
    void tabmain_print_all();                                           //打印所有图元
    bool tabmain_creaet_uart_data_file(QFile *fp);
    bool tabmain_write_uart_data_file(QFile *fp, QByteArray qba, QString extra_str);

    DrawLabel *wal;
    QLabel *status_show_label;
    QLabel *mouse_coord_label;


    //工作区的三个控件指针
    QToolBar *central_tool_bar;              //central左边的toolbar
    QTabWidget *central_tab_main;            //central中间的tab画布区域(工作区域)
    QTabWidget *central_tab_meta;            //central右边的tab区域


    QWidget *tab_attr_manager;               //tab_main里的单个焦点控件属性展示
    AttrTextTabWidget * tab_text_attr_manager;
    AttrOneCodeTabWidget * tab_one_attr_manager;
    AttrTwoCodeTabWidget * tab_two_attr_manager;
    AttrLineTabWidget * tab_line_attr_manager;
    AttrRectTabWidget * tab_rect_attr_manager;
    AttrLabelTabWidget * tab_label_attr_manager;


    UartTabWidget *tab_uart_manager;         //tab_main里的控件管理器
    QWidget *tab_res_manager;                //tab_main里的控件管理器


    DrawTextItem    *text_item_select;                 //指向当前选中的txtitem的指针
    DrawOneCodeItem *onecode_item_select;
    DrawTwoCodeItem *twocode_item_select;
    DrawLineItem    *line_item_select;
    DrawRectItem    *rect_item_select;


signals:
    void printerUart_sendDataToPrinter(QByteArray data);

public slots:
    void widget_main_connect_init();        //信号槽初始化
    void widget_main_show_coord();

    //File 槽函数
    bool tabmain_file_new();
    bool tabmain_file_open();       //File save文件保存槽函数
    bool tabmain_file_save();       //File save文件保存槽函数

    //Edit 主菜单 的action槽函数
    bool tabmain_create_edit_text_item();
    bool tabmain_create_edit_onecode_item();
    bool tabmain_create_edit_twocode_item();
    bool tabmain_create_edit_pic_item();
    bool tabmain_create_edit_line_item();
    bool tabmain_create_edit_rect_item();
    void tabmain_uart_print_data();    //通过串口打印scene的所有items

    //EDIT槽函数
    void tabmain_remove_scene_item();
    void tabmain_remove_scene_all_item();

    //tabmain槽函数
    void tabmain_current_index_changed();
    void tabmain_remove_sub_tab(int index);

    //Language主菜单槽函数
    void tabmain_language_zh_clicked();
    void tabmain_language_en_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);               //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);                //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);             //鼠标释放事件
    //void keyPressEvent(QKeyEvent *event);                   //键盘按下事件
    void paintEvent(QPaintEvent *event);

private:
    bool widget_main_init(uint from);       //主界面初始化
    void widget_main_menu_bar_init();       //菜单栏初始化
    void widget_main_tool_bar_init();       //工具栏初始化
    void widget_main_status_bar_init();     //状态栏初始化
    void widget_main_work_area_init();      //主界面工作区域初始化（除标题栏，菜单栏，工具栏和状态栏的中心区域）
    void widget_main_work_area_toolbar_init();
    void widget_main_work_area_tabmain_init();
    void widget_main_work_area_tabmanger_init();
    void destroyLayoutWidget(QLayout* layout);


    Ui::MainWindow *ui;                     //当前界面的指针

    //菜单栏菜单项
    QMenu *FileMenu;                        //文件菜单项
    QMenu *EditMenu;                        //编辑菜单项
    QMenu *ToolMenu;                        //工具菜单项
    QMenu *HelpMenu;                        //帮助菜单项
    QMenu *LanguageMenu;                         //语言菜单项

    //1.File菜单action声明
    QAction *File_New;
    QAction *File_Open;
    QAction *File_Save;
    QAction *File_Save_As;

    //2.Edit菜单action 声明
    QAction *Edit_text;
    QAction *Edit_one_code;
    QAction *Edit_two_code;
    QAction *Edit_pic;
    QAction *Edit_line;
    QAction *Edit_rect;

    //3.Tool菜单action声明
    QAction *Tool_Print;
    QAction *Tool_Template_set;
    QAction *Tool_Repeal;
    QAction *Tool_Recover;
    QAction *Tool_Remove;
    QAction *Tool_RemoveAll;

    //Lanuage主菜单相关
    QAction *lang_zh;           //中文简体
    QAction *lang_en;           //英文

    //鼠标相关
    QPoint mainlastPos;                 //记录鼠标实时坐标
};
#endif // MAINWINDOW_H
