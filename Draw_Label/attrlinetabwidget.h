#ifndef ATTRLINETABWIDGET_H
#define ATTRLINETABWIDGET_H

#include <QWidget>
#include "common_def.h"
#include <drawtextitem.h>
#include <drawonecodeitem.h>
#include <drawtwocodeitem.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>


class AttrLineTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttrLineTabWidget(QWidget *parent = nullptr);
    void attr_line_item_tabmeta_widget_create(LineItemMetaPS meta);
    void attr_line_update_item_tabmeta_widget(LineItemMetaPS meta);
    void destroyLayoutWidget(QLayout* layout);
    void attr_line_init_signal_slot();


    //对应meta属性
    QLabel *name_lab;                       //名字标签
    //QPlainTextEdit *data_plain_text;        //文本内容编辑框
    //QComboBox *cb_font_height;              //字体高度下拉选择框
    //QCheckBox *bold_cb;                     //加粗复选框
    //QCheckBox *underline_cb;                //下划线复选框
    QCheckBox *display_boundframe;

    QPushButton *rotate_bt;                    //旋转按钮，每次旋转90度
    QLineEdit * rotate_display;                 //显示旋转角度,不可让用户编辑

    //QLineEdit *rotate_edit;
    QLineEdit *penwidth_lab_edit;
    QLineEdit *line_len_edit;

    //文本坐标属性
    QLineEdit *start_x_ledit;
    QLineEdit *start_y_ledit;
//    QLineEdit *width_ledit;
//    QLineEdit *height_ledit;
    QLineEdit *end_x_ledit;
    QLineEdit *end_y_ledit;


signals:

public slots:
//    void attr_text_data_changed();
//    void attr_text_x_y_changed();
//    void attr_text_font_height_changed(int);
//    void attr_text_font_bold_changed(int);
//    void attr_text_font_underline_changed(int);

    void attr_line_rotate_bt_clicked();
    void attr_line_penwidth_lab_edit_changed();
    void attr_line_line_len_edit_edit_changed();
    void attr_line_start_x_ledit_changed();
    void attr_line_start_y_ledit_changed();
    void attr_line_end_x_ledit_changed();
    void attr_line_end_y_ledit_changed();
    void attr_line_display_bound_changed(int state);

};

#endif // ATTRLINETABWIDGET_H
