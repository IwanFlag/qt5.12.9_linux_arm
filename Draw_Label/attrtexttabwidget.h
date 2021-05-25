#ifndef ATTRTEXTTABWIDGET_H
#define ATTRTEXTTABWIDGET_H

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


class AttrTextTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttrTextTabWidget(QWidget *parent = nullptr);
    void attr_text_item_tabmeta_widget_create(TextItemMetaPS meta);
    void attr_text_update_item_tabmeta_widget(TextItemMetaPS meta);
    void destroyLayoutWidget(QLayout* layout);
    void attr_text_init_signal_slot();


    //对应meta属性
    QLabel *name_lab;                       //名字标签
    QPlainTextEdit *data_plain_text;        //文本内容编辑框
    QComboBox *cb_font_height;              //字体高度下拉选择框
    QCheckBox *bold_cb;                     //加粗复选框
    QCheckBox *underline_cb;                //下划线复选框

    //文本坐标属性
    QLineEdit *x_ledit;
    QLineEdit *y_ledit;
    QLineEdit *width_ledit;
    QLineEdit *height_ledit;


signals:

public slots:
    void attr_text_data_changed();
    void attr_text_x_y_changed();
    void attr_text_font_height_changed(int);
    void attr_text_font_bold_changed(int);
    void attr_text_font_underline_changed(int);

    //void attr_text_width_changed();
    //void attr_text_height_changed();
};

#endif // ATTRTEXTTABWIDGET_H
