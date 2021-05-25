#ifndef AttrRectTabWidget_H
#define AttrRectTabWidget_H

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


extern RectItemMeta rect_item_init;


class AttrRectTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttrRectTabWidget(QWidget *parent = nullptr);
    void attr_rect_init_show_meta(RectItemMeta meta);
    void attr_rect_update_item_tabmeta_widget(RectItemMeta meta);
    void attr_rect_init_signal_slot();


    QLabel *name_lab;
    QLineEdit *penwidth_lab_edit;
    QCheckBox *display_boundframe;

    QLineEdit *x_ledit;
    QLineEdit *y_ledit;
    QLineEdit *width_ledit;
    QLineEdit *height_ledit;


signals:

public slots:
    void attr_rect_penwidth_lab_edit_changed();
    void attr_rect_x_y_changed();
    void attr_rect_display_bound_changed(int state);
};

#endif // AttrRectTabWidget_H
