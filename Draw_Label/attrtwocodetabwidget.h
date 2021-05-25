#ifndef ATTRTWOCODETABWIDGET_H
#define ATTRTWOCODETABWIDGET_H

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


class AttrTwoCodeTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttrTwoCodeTabWidget(QWidget *parent = nullptr);
    void attr_twocode_init_show_meta(TwoCodeItemMeta meta);
    void attr_twocode_update_item_tabmeta_widget(TwoCodeItemMeta meta);
    void attr_twocode_init_signal_slot();


    QLabel *name_lab;
    QComboBox *cb_ecl_style;
    QComboBox *cb_mode;
    QComboBox *cb_uw;           //二维码码宽选择

    QPlainTextEdit *data_plain_text;
    QCheckBox *display_boundframe;

    QLineEdit *x_ledit;
    QLineEdit *y_ledit;
    QLineEdit *width_ledit;
    QLineEdit *height_ledit;


signals:

public slots:

    void attr_twocode_data_changed();
    void attr_twocode_x_y_changed();
    void attr_twocode_ecl_changed(int index);
    void attr_twocode_mode_changed(int index);
    void attr_twocode_display_bound_changed(int state);
    void attr_twocode_uintw_changed(int index);

};

#endif // ATTRTWOCODETABWIDGET_H
