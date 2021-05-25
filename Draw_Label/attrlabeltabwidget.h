#ifndef ATTRLABELTABWIDGET_H
#define ATTRLABELTABWIDGET_H

#include <QWidget>
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


//初始化label,view和scene
extern LabelPanelMeta label_init_meta;


//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(LabelPanelMeta)


class AttrLabelTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttrLabelTabWidget(QWidget *parent = nullptr);
    void attr_label_init_show_meta(LabelPanelMeta meta);
    void attr_label_update_item_tabmeta_widget(LabelPanelMeta meta);
    void attr_label_init_signal_slot();

    QLabel *name_lab;
    QLineEdit *name_edit;


    //画板上下左右移动按钮
    QPushButton *up_bt;
    QPushButton *down_bt;
    QPushButton *left_bt;
    QPushButton *right_bt;


    //label
    QLineEdit *lx_ledit;
    QLineEdit *ly_ledit;
    QLineEdit *lwidth_ledit;
    QLineEdit *lheight_ledit;

    //view
    QLineEdit *vx_ledit;
    QLineEdit *vy_ledit;
    QLineEdit *vwidth_ledit;
    QLineEdit *vheight_ledit;

    //场景
    QLineEdit *sx_ledit;
    QLineEdit *sy_ledit;
    QLineEdit *swidth_ledit;
    QLineEdit *sheight_ledit;




signals:

public slots:
    void attr_label_x_y_changed();
    void attr_label_up_move_bt_clicked();
    void attr_label_down_move_bt_clicked();
    void attr_label_left_move_bt_clicked();
    void attr_label_right_move_bt_clicked();
    void attr_label_name_changed();

};

#endif // ATTRLABELTABWIDGET_H
