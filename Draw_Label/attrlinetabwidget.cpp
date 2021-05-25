#include "attrlinetabwidget.h"
#include "qdebug.h"
#include "main.h"
#include "common_fun.h"
#include <QCheckBox>
#include <QLineF>


AttrLineTabWidget::AttrLineTabWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    attr_line_item_tabmeta_widget_create(line_item_meta_init);
    attr_line_init_signal_slot();
}

/**
 * @brief AttrLineTabWidget::attr_line_item_tabmeta_widget_create
 *              创建和初始化line meta widget
 * @param meta
 */
void AttrLineTabWidget::attr_line_item_tabmeta_widget_create(LineItemMetaPS meta)
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();


    //2.加一个label标签，来显示item类别
    name_lab = new QLabel;
    name_lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);
    if((meta.name.isEmpty() == false) && (meta.name.length() != 0))
    {
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_TEXTEDIT));
    }

    //设置字号
    QFont ft;
    ft.setPointSize(g_font_size[GRAPHIC_FONT_SIZE_HUGE]);
    name_lab->setFont(ft);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    name_lab->setPalette(pa);

    //对齐
    name_lab->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    vb->addWidget(name_lab);


/*---------3.创建样式 group---------*/
    QGroupBox *style_gp = new QGroupBox;
    vb->addWidget(style_gp);

    style_gp->setTitle(tr("style"));

    //创建网络栅格布局
    QGridLayout *style_gl = new QGridLayout;
    style_gl->setSpacing(10);       //设置间距

    //再增加一个是否显示外边框的按钮
    QLabel *display_boundframe_lab = new QLabel;
    display_boundframe_lab->setText(tr("display_boundframe:"));
    style_gl->addWidget(display_boundframe_lab, 1, 0, 1, 1); //占据1行1列

    display_boundframe = new QCheckBox;
    display_boundframe->setChecked(meta.display_boundframe);
    style_gl->addWidget(display_boundframe, 1, 1, 1, 1); //占据1行1列

    //旋转角度按钮
    rotate_bt = new QPushButton;
    rotate_bt->setText(tr("rotate(-90')"));
    style_gl->addWidget(rotate_bt, 2, 0, 1, 1); //占据1行1列

    //旋转角度显示
    rotate_display = new QLineEdit;
    rotate_display->setText(QString::number(meta.rotate));
    rotate_display->setReadOnly(true);      //设置为用户只读
    //rotate_display->setStyleSheet(BG_COLOR_STYLE_WHITE);
    style_gl->addWidget(rotate_display, 2, 1, 1, 1); //占据1行1列

    //旋转角度编辑框
    //QLabel *rotate_lab = new QLabel;
    //rotate_lab->setText(tr("rotate:"));
    //style_gl->addWidget(rotate_lab, 2, 0, 1, 1); //占据1行1列

    //rotate_edit = new QLineEdit;
    //style_gl->addWidget(rotate_edit, 2, 1, 1, 1); //占据1行1列

    //画笔/线条宽度
    QLabel *penwidth_lab = new QLabel;
    penwidth_lab->setText(tr("penwidth(mm):"));
    style_gl->addWidget(penwidth_lab, 3, 0, 1, 1); //占据1行1列

    penwidth_lab_edit = new QLineEdit;
    style_gl->addWidget(penwidth_lab_edit, 3, 1, 1, 1); //占据1行1列
    penwidth_lab_edit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    //直线的长度
    QLabel *line_len_edit_lab = new QLabel;
    line_len_edit_lab->setText(tr("linelen(mm):"));
    style_gl->addWidget(line_len_edit_lab, 4, 0, 1, 1); //占据1行1列

    line_len_edit = new QLineEdit;
    style_gl->addWidget(line_len_edit, 4, 1, 1, 1); //占据1行1列
    line_len_edit->setStyleSheet(BG_COLOR_STYLE_WHITE);


    //加载网络栅格布局
    style_gp->setLayout(style_gl);

/*---------4.创建位置 group---------*/
    QGroupBox *pos_gp = new QGroupBox;
    vb->addWidget(pos_gp);
    pos_gp->setTitle(tr("position"));

    //创建网络栅格布局
    QGridLayout *pos_gl = new QGridLayout;
    pos_gl->setSpacing(10);       //设置间距

    //start_x
    QLabel *start_x_lab = new QLabel;
    start_x_lab->setText(tr("start_x(mm):"));
    pos_gl->addWidget(start_x_lab, 0, 0, 1, 1); //占据1行1列

    start_x_ledit = new QLineEdit();
    pos_gl->addWidget(start_x_ledit, 0, 1, 1, 1); //占据1行1列
    //start_x_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal start_point_x = meta.start_point.x();
    start_point_x = pix2mm(start_point_x, ENUM_DIR_H);          //界面全部显示毫米
    QString str_x = QString::number(start_point_x,'start_point_x', 1);
    start_x_ledit->setText(str_x);
    start_x_ledit->setReadOnly(true);      //设置为用户只读

    //start_y
    QLabel *y_lab = new QLabel;
    y_lab->setText(tr("start_y(mm):"));
    pos_gl->addWidget(y_lab, 0, 2, 1, 1); //占据1行1列

    start_y_ledit = new QLineEdit();
    pos_gl->addWidget(start_y_ledit, 0, 3, 1, 1); //占据1行1列
    //start_y_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal start_point_y = meta.start_point.y();
    start_point_y = pix2mm(start_point_y, ENUM_DIR_V);          //界面全部显示毫米
    QString str_y = QString::number(start_point_y,'start_point_y', 1);
    start_y_ledit->setText(str_y);
    start_y_ledit->setReadOnly(true);      //设置为用户只读

    //end_x
    QLabel *width_lab = new QLabel;
    width_lab->setText(tr("end_x(mm):"));
    pos_gl->addWidget(width_lab, 1, 0, 1, 1); //占据1行1列

    end_x_ledit = new QLineEdit();
    pos_gl->addWidget(end_x_ledit, 1, 1, 1, 1); //占据1行1列
    //end_x_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal end_point_x = meta.end_point.x();
    end_point_x = pix2mm(end_point_x, ENUM_DIR_H);          //界面全部显示毫米
    QString str_w = QString::number(end_point_x,'end_point_x', 1);
    end_x_ledit->setText(str_w);
    end_x_ledit->setReadOnly(true);      //设置为用户只读

    //end_y
    QLabel *height_lab = new QLabel;
    height_lab->setText(tr("end_y(mm):"));
    pos_gl->addWidget(height_lab, 1, 2, 1, 1); //占据1行1列

    end_y_ledit = new QLineEdit();
    pos_gl->addWidget(end_y_ledit, 1, 3, 1, 1); //占据1行1列
    //end_y_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal end_point_y = meta.end_point.y();
    end_point_y = pix2mm(end_point_y, ENUM_DIR_V);                  //界面全部显示毫米
    QString str_h = QString::number(end_point_y,'end_point_y', 1);
    end_y_ledit->setText(str_h);
    end_y_ledit->setReadOnly(true);      //设置为用户只读


    //位置group加载 位置加载网络栅格布局
    pos_gp->setLayout(pos_gl);

    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrLineTabWidget::attr_line_update_item_tabmeta_widget
 *          更新linew tabmeta界面
 * @param meta
 */
void AttrLineTabWidget::attr_line_update_item_tabmeta_widget(LineItemMetaPS meta)
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);

    //更新旋转角度的编辑框数值
    rotate_display->setText(QString::number(meta.rotate));

    //更新线宽度/画笔宽度 的编辑框数值
    penwidth_lab_edit->setText(QString::number(pix2mm(meta.pen.width(), ENUM_DIR_H)));

    //编辑长度
    line_len_edit->setText(QString::number(pix2mm(meta.len, ENUM_DIR_H)));


    //更新meta获取目前的位置
    //g_widget->line_item_select->getUpdateLineNowCoord();

    //start-end坐标
    //start_x
    qreal start_point_x = meta.start_point.x();
    qDebug("[AttrLineTabWidget--%s]>>11start_point_x:%f", __FUNCTION__, start_point_x);

    start_point_x = pix2mm(start_point_x, ENUM_DIR_H);          //界面全部显示毫米
    qDebug("[AttrLineTabWidget--%s]>>22start_point_x:%f", __FUNCTION__, start_point_x);

    QString str_x = QString::number(start_point_x,'start_point_x', 1);
    start_x_ledit->setText(str_x);

    //start_y
    qreal start_point_y = meta.start_point.y();
    start_point_y = pix2mm(start_point_y, ENUM_DIR_V);          //界面全部显示毫米
    QString str_y = QString::number(start_point_y,'start_point_y', 1);
    start_y_ledit->setText(str_y);

    //end_x
    qreal end_point_x = meta.end_point.x();
    end_point_x = pix2mm(end_point_x, ENUM_DIR_H);          //界面全部显示毫米
    QString str_w = QString::number(end_point_x,'end_point_x', 1);
    end_x_ledit->setText(str_w);

    //end_y
    qreal end_point_y = meta.end_point.y();
    end_point_y = pix2mm(end_point_y, ENUM_DIR_V);                  //界面全部显示毫米
    QString str_h = QString::number(end_point_y,'end_point_y', 1);
    end_y_ledit->setText(str_h);

    g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_line_attr_manager, QObject::tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);
}

void AttrLineTabWidget::destroyLayoutWidget(QLayout *layout)
{

}

void AttrLineTabWidget::attr_line_init_signal_slot()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    QObject::connect(this->rotate_bt, SIGNAL(clicked(bool)), this, SLOT(attr_line_rotate_bt_clicked()));
    QObject::connect(this->penwidth_lab_edit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_penwidth_lab_edit_changed()));
    QObject::connect(this->line_len_edit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_line_len_edit_edit_changed()));
    QObject::connect(this->start_x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_start_x_ledit_changed()));
    QObject::connect(this->start_y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_start_y_ledit_changed()));
    QObject::connect(this->end_x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_end_x_ledit_changed()));
    QObject::connect(this->end_y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_line_end_y_ledit_changed()));
    QObject::connect(this->display_boundframe, SIGNAL(stateChanged(int)), this, SLOT(attr_line_display_bound_changed(int)));
}

void AttrLineTabWidget::attr_line_rotate_bt_clicked()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    LineItemMetaPS meta = g_widget->line_item_select->getLineEditMeta();
    meta.rotate += 90.0;
    if(meta.rotate >= 360.0)
    {
       meta.rotate= 0;      //旋转360,则归零
    }
    //g_widget->line_item_select->updateLineItemNowCoord();                        //因为场景是释放事件才显示
    g_widget->line_item_select->setLineEditMeta(meta);
}

void AttrLineTabWidget::attr_line_penwidth_lab_edit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    LineItemMetaPS meta = g_widget->line_item_select->getLineEditMeta();
    qreal pw = this->penwidth_lab_edit->text().toFloat();       //这是mm
    meta.pen.setWidthF(mm2pix(pw, ENUM_DIR_H));
    g_widget->line_item_select->setLineEditMeta(meta);
}

void AttrLineTabWidget::attr_line_line_len_edit_edit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    LineItemMetaPS meta = g_widget->line_item_select->getLineEditMeta();
    qreal len = this->line_len_edit->text().toFloat();
    meta.len = mm2pix(len, ENUM_DIR_H);     //mm
    qDebug("[AttrLineTabWidget--%s]>>meta.len:%f", __FUNCTION__, meta.len);
    qreal len2 = g_widget->line_item_select->line().length();
    qDebug("[AttrLineTabWidget--%s]>>len2:%f", __FUNCTION__, len2);
    g_widget->line_item_select->setLineEditMeta(meta);
}

void AttrLineTabWidget::attr_line_start_x_ledit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);

}

void AttrLineTabWidget::attr_line_start_y_ledit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);

}

void AttrLineTabWidget::attr_line_end_x_ledit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);
    LineItemMetaPS meta = g_widget->line_item_select->getLineEditMeta();
    QString end_x_str = this->end_x_ledit->text();
    float end_x_mm = end_x_str.toFloat();
    qDebug("[AttrLineTabWidget--%s]>>end_x_mm:%f", __FUNCTION__, end_x_mm);
    float end_x_pix = mm2pix(end_x_mm, ENUM_DIR_H);
    qDebug("[AttrLineTabWidget--%s]>>end_x_pix:%f", __FUNCTION__, end_x_pix);
    meta.end_point.setX(end_x_pix);
    g_widget->line_item_select->setLineEditMeta(meta);
}

void AttrLineTabWidget::attr_line_end_y_ledit_changed()
{
    qDebug("[AttrLineTabWidget--%s]>>", __FUNCTION__);

}

/**
 * @brief AttrLineTabWidget::attr_line_display_bound_changed
 * 是否显示一维码外边框复选框
 * @param state
 */
void AttrLineTabWidget::attr_line_display_bound_changed(int state)
{
    qDebug("[AttrLineTabWidget--%s]>>state:%d", __FUNCTION__,state);
    if(g_widget->line_item_select)
    {
        LineItemMetaPS meta = g_widget->line_item_select->getLineEditMeta();
        meta.display_boundframe = state;
        g_widget->line_item_select->setLineEditMeta(meta);
    }
    else
    {
        qDebug("[AttrLineTabWidget--%s]>>ERROR:-1", __FUNCTION__);
    }
}

