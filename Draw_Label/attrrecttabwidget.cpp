#include "attrrecttabwidget.h"
#include "qdebug.h"
#include "main.h"
#include "common_fun.h"


AttrRectTabWidget::AttrRectTabWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug("[AttrRectTabWidget--%s]>>", __FUNCTION__);
    attr_rect_init_show_meta(rect_item_init);
    attr_rect_init_signal_slot();
}

/**
 * @brief AttrRectTabWidget::attr_rect_init_show_meta
 *              显示二维码item属性编辑框
 * @param index
 */
void AttrRectTabWidget::attr_rect_init_show_meta(RectItemMeta meta)
{
    qDebug("[AttrRectTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();

    //2.加一个label标签，来显示item类别
    name_lab = new QLabel;
    name_lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);

    if(meta.name.trimmed().isEmpty() == false &&
            meta.name.trimmed().length() != 0)
    {
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_TWOCODE));
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

    //是否显示外接矩形
    QLabel *display_boundframe_lab = new QLabel;
    display_boundframe_lab->setText(tr("display_boundframe:"));
    style_gl->addWidget(display_boundframe_lab, 2, 0, 1, 1); //占据1行1列

    display_boundframe = new QCheckBox;
    display_boundframe->setChecked(meta.display_boundframe);
    style_gl->addWidget(display_boundframe, 2, 1, 1, 1); //占据1行1列

    //画笔/线条宽度设置
    QLabel *penwidth_lab = new QLabel;
    penwidth_lab->setText(tr("penwidth(mm):"));
    style_gl->addWidget(penwidth_lab, 3, 0, 1, 1); //占据1行1列

    penwidth_lab_edit = new QLineEdit;
    style_gl->addWidget(penwidth_lab_edit, 3, 1, 1, 1); //占据1行1列
    penwidth_lab_edit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    //加载网络栅格布局
    style_gp->setLayout(style_gl);

    /*---------4.创建位置 group---------*/
    QGroupBox *pos_gp = new QGroupBox;
    vb->addWidget(pos_gp);
    pos_gp->setTitle(tr("position"));

    //创建网络栅格布局
    QGridLayout *pos_gl = new QGridLayout;
    pos_gl->setSpacing(10);       //设置间距

    //x
    QLabel *x_lab = new QLabel;
    x_lab->setText(tr("x(mm):"));
    pos_gl->addWidget(x_lab, 0, 0, 1, 1); //占据1行1列

    x_ledit = new QLineEdit();
    pos_gl->addWidget(x_ledit, 0, 1, 1, 1); //占据1行1列
    x_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal x_coord = meta.CoordRect.left();
    x_coord = pix2mm(x_coord, ENUM_DIR_H);
    QString str_x = QString::number(x_coord,'x_coord', 1);
    x_ledit->setText(str_x);

    //y
    QLabel *y_lab = new QLabel;
    y_lab->setText(tr("y(mm):"));
    pos_gl->addWidget(y_lab, 0, 2, 1, 1); //占据1行1列

    y_ledit = new QLineEdit();
    pos_gl->addWidget(y_ledit, 0, 3, 1, 1); //占据1行1列
    y_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal y_coord = meta.CoordRect.top();
    y_coord = pix2mm(y_coord, ENUM_DIR_V);
    QString str_y = QString::number(y_coord,'y_coord', 1);
    y_ledit->setText(str_y);


    //width
    QLabel *width_lab = new QLabel;
    width_lab->setText(tr("width(mm):"));
    pos_gl->addWidget(width_lab, 1, 0, 1, 1); //占据1行1列

    width_ledit = new QLineEdit();
    pos_gl->addWidget(width_ledit, 1, 1, 1, 1); //占据1行1列
    width_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);


    qreal w_coord = meta.CoordRect.width();
    w_coord = pix2mm(w_coord, ENUM_DIR_H);
    QString str_w = QString::number(w_coord,'w_coord', 1);
    width_ledit->setText(str_w);

    //height
    QLabel *height_lab = new QLabel;
    height_lab->setText(tr("height(mm):"));
    pos_gl->addWidget(height_lab, 1, 2, 1, 1); //占据1行1列

    height_ledit = new QLineEdit();
    pos_gl->addWidget(height_ledit, 1, 3, 1, 1); //占据1行1列
    height_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal h_coord = meta.CoordRect.height();
    h_coord = pix2mm(h_coord, ENUM_DIR_V);
    QString str_h = QString::number(h_coord,'h_coord', 1);
    height_ledit->setText(str_h);

    //位置group加载 位置加载网络栅格布局
    pos_gp->setLayout(pos_gl);


    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrRectTabWidget::attr_rect_update_item_tabmeta_widget
 *              更新item属性编辑框
 * @param index
 */
void AttrRectTabWidget::attr_rect_update_item_tabmeta_widget(RectItemMeta meta)
{
    qDebug("[AttrRectTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));


    //item 标签名字
    if(meta.name.trimmed().isEmpty() == false && meta.name.trimmed().length() != 0)
    {
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_TWOCODE));
    }

    //更新线宽度/画笔宽度 的编辑框数值
    penwidth_lab_edit->setText(QString::number(pix2mm(meta.pen.width(), ENUM_DIR_H)));

    //坐标
    //3.文本坐标更新
    //x
    qreal x_coord = meta.CoordRect.left();
    x_coord = pix2mm(x_coord, ENUM_DIR_H);
    QString str_x = QString::number(x_coord,'x_coord', 1);
    x_ledit->setText(str_x);

    //y
    qreal y_coord = meta.CoordRect.top();
    y_coord = pix2mm(y_coord, ENUM_DIR_V);
    QString str_y = QString::number(y_coord,'y_coord', 1);
    y_ledit->setText(str_y);

    //width
    qreal w_coord = meta.CoordRect.width();
    w_coord = pix2mm(w_coord, ENUM_DIR_H);
    QString str_w = QString::number(w_coord,'w_coord', 1);
    width_ledit->setText(str_w);

    //height
    qreal h_coord = meta.CoordRect.height();
    h_coord = pix2mm(h_coord, ENUM_DIR_V);
    QString str_h = QString::number(h_coord,'h_coord', 1);
    height_ledit->setText(str_h);


    //切换tab
    g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_rect_attr_manager,tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);

}
/**
 * @brief AttrRectTabWidget::attr_rect_init_signal_slot
 * 初始信号和槽函数
 */
void AttrRectTabWidget::attr_rect_init_signal_slot()
{
    qDebug("[AttrRectTabWidget--%s]>>", __FUNCTION__);
    QObject::connect(this->penwidth_lab_edit, SIGNAL(textEdited(QString)), this, SLOT(attr_rect_penwidth_lab_edit_changed()));
    QObject::connect(this->x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_rect_x_y_changed()));
    QObject::connect(this->y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_rect_x_y_changed()));
    QObject::connect(this->width_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_rect_x_y_changed()));
    QObject::connect(this->height_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_rect_x_y_changed()));
    QObject::connect(this->display_boundframe, SIGNAL(stateChanged(int)), this, SLOT(attr_rect_display_bound_changed(int)));
}

void AttrRectTabWidget::attr_rect_penwidth_lab_edit_changed()
{
    qDebug("[AttrRectTabWidget--%s]>>", __FUNCTION__);
    RectItemMeta meta = g_widget->rect_item_select->getRectMeta();
    qreal pw = this->penwidth_lab_edit->text().toFloat();       //这是mm
    meta.pen.setWidthF(mm2pix(pw, ENUM_DIR_H));
    g_widget->rect_item_select->setRectMeta(meta);
}

/**
 * @brief AttrRectTabWidget::attr_rect_x_y_changed
 */
void AttrRectTabWidget::attr_rect_x_y_changed()
{
    qDebug("[AttrRectTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->rect_item_select && this->x_ledit && this->y_ledit)
    {
        //取出编写的文本
        QString x_str = this->x_ledit->text();
        QString y_str = this->y_ledit->text();
        QString width_ledit_str = this->width_ledit->text();
        QString height_ledit_str = this->height_ledit->text();

        //qDebug("[AttrRectTabWidget--%s]>>str(%s, %s)", __FUNCTION__, qPrintable(x_str), qPrintable(y_str));

        float x_mm = x_str.toFloat();
        float y_mm = y_str.toFloat();
        float width_ledit_mm = width_ledit_str.toFloat();
        float height_ledit_mm = height_ledit_str.toFloat();

        qDebug("[AttrRectTabWidget--%s]>>mm(%f, %f, %f, %f)", __FUNCTION__, x_mm, y_mm, width_ledit_mm, height_ledit_mm);

        float x_pix = mm2pix(x_mm, ENUM_DIR_H);
        float y_pix = mm2pix(y_mm, ENUM_DIR_V);
        float width_ledit_pix = mm2pix(width_ledit_mm, ENUM_DIR_H);
        float height_ledit_pix = mm2pix(height_ledit_mm, ENUM_DIR_V);

        qDebug("[AttrRectTabWidget--%s]>>pix(%f, %f, %f, %f)", __FUNCTION__, x_pix, y_pix, width_ledit_pix, height_ledit_pix);

        //把属性框编辑的文本发送到item上显示
        if(g_widget->rect_item_select)
        {
            RectItemMeta meta = g_widget->rect_item_select->getRectMeta();

            meta.CoordRect.setLeft(x_pix);
            meta.CoordRect.setTop(y_pix);
            meta.CoordRect.setWidth(width_ledit_pix);
            meta.CoordRect.setHeight(height_ledit_pix);

            g_widget->rect_item_select->setRectMeta(meta);
        }
    }
}

/**
 * @brief AttrRectTabWidget::attr_rect_display_bound_changed
 * 是否显示一维码外边框复选框
 * @param state
 */
void AttrRectTabWidget::attr_rect_display_bound_changed(int state)
{
    qDebug("[AttrRectTabWidget--%s]>>state:%d", __FUNCTION__,state);
    if(g_widget->rect_item_select)
    {
        g_widget->rect_item_select->meta.display_boundframe = state;
    }
    else
    {
        qDebug("[AttrRectTabWidget--%s]>>ERROR:-1", __FUNCTION__);
    }
}
