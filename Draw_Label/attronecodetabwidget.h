#ifndef ATTRONECODETABWIDGET_H
#define ATTRONECODETABWIDGET_H

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


class AttrOneCodeTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttrOneCodeTabWidget(QWidget *parent = nullptr);
    void attr_onecode_init_show_meta(OneCodeItemMetaPS meta);
    void attr_onecode_update_item_tabmeta_widget(OneCodeItemMetaPS meta);
    void attr_onecode_init_signal_slot();


private:
    QLabel *name_lab;
    QPlainTextEdit *data_plain_text;
    QComboBox *cb_type_style;                   //一维码类型选择下拉框
    QCheckBox *display_boundframe;
    QComboBox *cb_uw;                           //一维码码宽选择下拉框
    QLineEdit *print_heigt_ledit;


    QLineEdit *x_ledit;
    QLineEdit *y_ledit;
    QLineEdit *width_ledit;
    QLineEdit *height_ledit;


signals:


public slots:
    void attr_onecode_data_changed();
    void attr_onecode_x_y_changed();
    void attr_onecode_type_changed(int index);
    void attr_onecode_display_bound_changed(int state);
    void attr_onecode_uintw_changed(int index);
    void attr_onecode_disheight_changed();
};
#endif // ATTRONECODETABWIDGET_H
