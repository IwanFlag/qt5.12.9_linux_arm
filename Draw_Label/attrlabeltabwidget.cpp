#include "attrlabeltabwidget.h"
#include "qdebug.h"
#include "main.h"
#include "common_fun.h"





AttrLabelTabWidget::AttrLabelTabWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug("[AttrLabelTabWidget--%s]>>", __FUNCTION__);
    //label_init_meta.viewRect.setX(ROD_OFFSET_LABEL_MM + MM2PIX_H(4));     //商家说左右有4mm打印机无法打印到


    attr_label_init_show_meta(label_init_meta);
    attr_label_init_signal_slot();
}

/**
 * @brief AttrLabelTabWidget::attr_label_init_show_meta
 *              显示二维码item属性编辑框
 * @param index
 */
void AttrLabelTabWidget::attr_label_init_show_meta(LabelPanelMeta meta)
{
    qDebug("[AttrLabelTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();

    //2.加一个label标签，来显示item类别
    name_lab = new QLabel;
    name_lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);
    name_lab->setText(tr("fileName"));
    vb->addWidget(name_lab);

    name_edit = new QLineEdit();
    name_edit->setText(meta.name);
    name_edit->setStyleSheet(BG_COLOR_STYLE_WHITE);


    //设置字号
    QFont ft;
    ft.setPointSize(g_font_size[GRAPHIC_FONT_SIZE_HUGE]);
    name_edit->setFont(ft);
    name_lab->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    name_edit->setPalette(pa);
    name_lab->setPalette(pa);
    //对齐
    name_edit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    name_lab->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    vb->addWidget(name_edit);


    /*---------1.创建 移动按钮和放大缩小倍数控件---------*/
    QGroupBox *style_gp = new QGroupBox;
    vb->addWidget(style_gp);
    style_gp->setTitle(tr("action"));

    //创建网络栅格布局
    QGridLayout *style_gl = new QGridLayout;
    style_gl->setSpacing(10);       //设置间距

    //上下左右移动画板按钮
    //up
    up_bt = new QPushButton;
    up_bt->setText(tr("upMove"));
    style_gl->addWidget(up_bt, 0, 2, 1, 1); //占据1行1列

    //left
    left_bt = new QPushButton;
    left_bt->setText(tr("leftMove"));
    style_gl->addWidget(left_bt, 1, 0, 1, 1); //占据1行1列

    //down
    down_bt = new QPushButton;
    down_bt->setText(tr("downMove"));
    style_gl->addWidget(down_bt, 2, 2, 1, 1); //占据1行1列

    //right
    right_bt = new QPushButton;
    right_bt->setText(tr("rightMove"));
    style_gl->addWidget(right_bt, 1, 4, 1, 1); //占据1行1列

    //加载网络栅格布局
    style_gp->setLayout(style_gl);


    /*---------1.创建 label 位置 group---------*/
    QGroupBox *label_pos_gp = new QGroupBox;
    vb->addWidget(label_pos_gp);
    label_pos_gp->setTitle(tr("label position"));

    //创建网络栅格布局
    QGridLayout *label_pos_gl = new QGridLayout;
    label_pos_gl->setSpacing(10);       //设置间距

    //这里展示label的左上角坐标
    //x
    QLabel *lx_lab = new QLabel;
    lx_lab->setText(tr("top_left_x(mm):"));
    label_pos_gl->addWidget(lx_lab, 0, 0, 1, 1); //占据1行1列

    lx_ledit = new QLineEdit();
    label_pos_gl->addWidget(lx_ledit, 0, 1, 1, 1); //占据1行1列
    lx_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal lx_coord = meta.labelRect.left();
    lx_coord = pix2mm(lx_coord, ENUM_DIR_H);
    QString lstr_x = QString::number(lx_coord,'lx_coord', 1);
    lx_ledit->setText(lstr_x);
    //lx_ledit->setReadOnly(true);

    //y
    QLabel *ly_lab = new QLabel;
    ly_lab->setText(tr("top_left_y(mm):"));
    label_pos_gl->addWidget(ly_lab, 0, 2, 1, 1); //占据1行1列

    ly_ledit = new QLineEdit();
    label_pos_gl->addWidget(ly_ledit, 0, 3, 1, 1); //占据1行1列
    ly_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal y_coord = meta.labelRect.top();
    y_coord = pix2mm(y_coord, ENUM_DIR_V);
    QString str_y = QString::number(y_coord,'y_coord', 1);
    ly_ledit->setText(str_y);
    //ly_ledit->setReadOnly(true);


    //width
//    QLabel *width_lab = new QLabel;
//    width_lab->setText(tr("width(mm):"));
//    label_pos_gl->addWidget(width_lab, 1, 0, 1, 1); //占据1行1列

//    lwidth_ledit = new QLineEdit();
//    label_pos_gl->addWidget(lwidth_ledit, 1, 1, 1, 1); //占据1行1列
//    lwidth_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal w_coord = meta.labelRect.width();
//    w_coord = pix2mm(w_coord, ENUM_DIR_H);
//    QString str_w = QString::number(w_coord,'w_coord', 1);
//    lwidth_ledit->setText(str_w);

//    //height
//    QLabel *height_lab = new QLabel;
//    height_lab->setText(tr("height(mm):"));
//    label_pos_gl->addWidget(height_lab, 1, 2, 1, 1); //占据1行1列

//    lheight_ledit = new QLineEdit();
//    label_pos_gl->addWidget(lheight_ledit, 1, 3, 1, 1); //占据1行1列
//    lheight_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal h_coord = meta.labelRect.height();
//    h_coord = pix2mm(h_coord, ENUM_DIR_V);
//    QString str_h = QString::number(h_coord,'h_coord', 1);
//    lheight_ledit->setText(str_h);

    //这里展示view的宽和高
    //width
    QLabel *vwidth_lab = new QLabel;
    vwidth_lab->setText(tr("width(mm):"));
    label_pos_gl->addWidget(vwidth_lab, 1, 0, 1, 1); //占据1行1列

    vwidth_ledit = new QLineEdit();
    label_pos_gl->addWidget(vwidth_ledit, 1, 1, 1, 1); //占据1行1列
    vwidth_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);


    qDebug("[AttrLabelTabWidget--%s]>>1111vw_coord:%f,%f", __FUNCTION__, meta.viewRect.width(), meta.viewRect.height());


    qreal vw_coord = meta.viewRect.width();
    //vw_coord = pix2mm(vw_coord, ENUM_DIR_H);

            vw_coord = PIX2MM_H(vw_coord);
            qDebug("[AttrLabelTabWidget--%s]>>0000vw_coord:%f", __FUNCTION__, vw_coord);

    QString vstr_w = QString::number(vw_coord,'vw_coord', 1);
    vwidth_ledit->setText(vstr_w);

    //height
    QLabel *vheight_lab = new QLabel;
    vheight_lab->setText(tr("height(mm):"));
    label_pos_gl->addWidget(vheight_lab, 1, 2, 1, 1); //占据1行1列

    vheight_ledit = new QLineEdit();
    label_pos_gl->addWidget(vheight_ledit, 1, 3, 1, 1); //占据1行1列
    vheight_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal vh_coord = meta.viewRect.height();
    vh_coord = pix2mm(vh_coord, ENUM_DIR_V);
    QString vstr_h = QString::number(vh_coord,'vh_coord', 1);
    vheight_ledit->setText(vstr_h);

    //位置group加载 位置加载网络栅格布局
    label_pos_gp->setLayout(label_pos_gl);

//    /*---------2.创建 view 位置 group---------*/
//    QGroupBox *view_pos_gp = new QGroupBox;
//    vb->addWidget(view_pos_gp);
//    view_pos_gp->setTitle(tr("view position"));

//    //创建网络栅格布局
//    QGridLayout *view_pos_gl = new QGridLayout;
//    view_pos_gl->setSpacing(10);       //设置间距

//    //x
//    QLabel *view_x_lab = new QLabel;
//    view_x_lab->setText(tr("top_left_x(mm):"));
//    view_pos_gl->addWidget(view_x_lab, 0, 0, 1, 1); //占据1行1列

//    vx_ledit = new QLineEdit();
//    view_pos_gl->addWidget(vx_ledit, 0, 1, 1, 1); //占据1行1列
//    vx_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal vx_coord = meta.viewRect.left();
//    vx_coord = pix2mm(vx_coord, ENUM_DIR_H);
//    QString vstr_x = QString::number(vx_coord,'vx_coord', 1);
//    vx_ledit->setText(vstr_x);
//    //vx_ledit->setReadOnly(true);


//    //y
//    QLabel *view_y_lab = new QLabel;
//    view_y_lab->setText(tr("top_left_y(mm):"));
//    view_pos_gl->addWidget(view_y_lab, 0, 2, 1, 1); //占据1行1列

//    vy_ledit = new QLineEdit();
//    view_pos_gl->addWidget(vy_ledit, 0, 3, 1, 1); //占据1行1列
//    vy_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal vy_coord = meta.viewRect.top();
//    vy_coord = pix2mm(vy_coord, ENUM_DIR_V);
//    QString vstr_y = QString::number(vy_coord,'vy_coord', 1);
//    vy_ledit->setText(vstr_y);
//    //vy_ledit->setReadOnly(true);


//    //width
//    QLabel *vwidth_lab = new QLabel;
//    vwidth_lab->setText(tr("width(mm):"));
//    view_pos_gl->addWidget(vwidth_lab, 1, 0, 1, 1); //占据1行1列

//    vwidth_ledit = new QLineEdit();
//    view_pos_gl->addWidget(vwidth_ledit, 1, 1, 1, 1); //占据1行1列
//    vwidth_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);


//    qreal vw_coord = meta.viewRect.width();
//    vw_coord = pix2mm(vw_coord, ENUM_DIR_H);
//    QString vstr_w = QString::number(vw_coord,'vw_coord', 1);
//    vwidth_ledit->setText(vstr_w);

//    //height
//    QLabel *vheight_lab = new QLabel;
//    vheight_lab->setText(tr("height(mm):"));
//    view_pos_gl->addWidget(vheight_lab, 1, 2, 1, 1); //占据1行1列

//    vheight_ledit = new QLineEdit();
//    view_pos_gl->addWidget(vheight_ledit, 1, 3, 1, 1); //占据1行1列
//    vheight_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal vh_coord = meta.viewRect.height();
//    vh_coord = pix2mm(vh_coord, ENUM_DIR_V);
//    QString vstr_h = QString::number(vh_coord,'vh_coord', 1);
//    vheight_ledit->setText(vstr_h);

//    //位置group加载 位置加载网络栅格布局
//    view_pos_gp->setLayout(view_pos_gl);


//    /*---------3.创建场景scene位置 group---------*/
//    QGroupBox *scene_pos_gp = new QGroupBox;
//    vb->addWidget(scene_pos_gp);
//    scene_pos_gp->setTitle(tr("scene position"));

//    //创建网络栅格布局
//    QGridLayout *scene_pos_gl = new QGridLayout;
//    scene_pos_gl->setSpacing(10);       //设置间距

//    //x
//    QLabel *scene_x_lab = new QLabel;
//    scene_x_lab->setText(tr("stop_left_x(mm):"));
//    scene_pos_gl->addWidget(scene_x_lab, 0, 0, 1, 1); //占据1行1列

//    sx_ledit = new QLineEdit();
//    scene_pos_gl->addWidget(sx_ledit, 0, 1, 1, 1); //占据1行1列
//    sx_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal sx_coord = meta.sceneRect.left();
//    sx_coord = pix2mm(sx_coord, ENUM_DIR_H);
//    QString sstr_x = QString::number(sx_coord,'sx_coord', 1);
//    sx_ledit->setText(sstr_x);
//    //sx_ledit->setReadOnly(true);


//    //y
//    QLabel *scene_y_lab = new QLabel;
//    scene_y_lab->setText(tr("stop_left_y(mm):"));
//    scene_pos_gl->addWidget(scene_y_lab, 0, 2, 1, 1); //占据1行1列

//    sy_ledit = new QLineEdit();
//    scene_pos_gl->addWidget(sy_ledit, 0, 3, 1, 1); //占据1行1列
//    sy_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal sy_coord = meta.sceneRect.top();
//    sy_coord = pix2mm(sy_coord, ENUM_DIR_V);
//    QString sstr_y = QString::number(sy_coord,'sy_coord', 1);
//    sy_ledit->setText(sstr_y);
//    //sy_ledit->setReadOnly(true);


//    //width
//    QLabel *swidth_lab = new QLabel;
//    swidth_lab->setText(tr("swidth(mm):"));
//    scene_pos_gl->addWidget(swidth_lab, 1, 0, 1, 1); //占据1行1列

//    swidth_ledit = new QLineEdit();
//    scene_pos_gl->addWidget(swidth_ledit, 1, 1, 1, 1); //占据1行1列
//    swidth_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);


//    qreal sw_coord = meta.sceneRect.width();
//    sw_coord = pix2mm(sw_coord, ENUM_DIR_H);
//    QString sstr_w = QString::number(sw_coord,'sw_coord', 1);
//    swidth_ledit->setText(sstr_w);

//    //height
//    QLabel *sheight_lab = new QLabel;
//    sheight_lab->setText(tr("sheight(mm):"));
//    scene_pos_gl->addWidget(sheight_lab, 1, 2, 1, 1); //占据1行1列

//    sheight_ledit = new QLineEdit();
//    scene_pos_gl->addWidget(sheight_ledit, 1, 3, 1, 1); //占据1行1列
//    sheight_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal sh_coord = meta.sceneRect.height();
//    sh_coord = pix2mm(sh_coord, ENUM_DIR_V);
//    QString sstr_h = QString::number(sh_coord,'sh_coord', 1);
//    sheight_ledit->setText(sstr_h);

//    //位置group加载 位置加载网络栅格布局
//    scene_pos_gp->setLayout(scene_pos_gl);


    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrLabelTabWidget::attr_label_update_item_tabmeta_widget
 *              更新item属性编辑框
 * @param index
 */
void AttrLabelTabWidget::attr_label_update_item_tabmeta_widget(LabelPanelMeta meta)
{
    qDebug("[AttrLabelTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));


    //item 标签名字
    if(meta.name.trimmed().isEmpty() == false && meta.name.trimmed().length() != 0)
    {
//        name_lab->setText(meta.name);
        name_edit->setText(meta.name);
    }


    //label坐标
    //3.label的左上角坐标
    //x
    qreal lx_coord = meta.labelRect.left();
    lx_coord = pix2mm(lx_coord, ENUM_DIR_H);
    QString lstr_x = QString::number(lx_coord,'lx_coord', 1);
    lx_ledit->setText(lstr_x);

    //y
    qreal ly_coord = meta.labelRect.top();
    ly_coord = pix2mm(ly_coord, ENUM_DIR_V);
    QString lstr_y = QString::number(ly_coord,'ly_coord', 1);
    ly_ledit->setText(lstr_y);

//    //width
//    qreal lw_coord = meta.sceneRect.width();
//    lw_coord = pix2mm(lw_coord, ENUM_DIR_H);
//    QString lstr_w = QString::number(lw_coord,'lw_coord', 1);
//    swidth_ledit->setText(lstr_w);

//    //height
//    qreal lh_coord = meta.sceneRect.height();
//    lh_coord = pix2mm(lh_coord, ENUM_DIR_V);
//    QString lstr_h = QString::number(lh_coord,'lh_coord', 1);
//    sheight_ledit->setText(lstr_h);

    //view 宽和高
    //width
    qreal vw_coord = meta.viewRect.width();
    vw_coord = pix2mm(vw_coord, ENUM_DIR_H);
    QString vstr_w = QString::number(vw_coord,'vw_coord', 1);
    vwidth_ledit->setText(vstr_w);

    //height
    qreal vh_coord = meta.viewRect.height();
    vh_coord = pix2mm(vh_coord, ENUM_DIR_V);
    QString vstr_h = QString::number(vh_coord,'vh_coord', 1);
    vheight_ledit->setText(vstr_h);


    //切换tab
    g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_label_attr_manager,tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);

}
/**
 * @brief AttrLabelTabWidget::attr_label_init_signal_slot
 * 初始信号和槽函数
 */
void AttrLabelTabWidget::attr_label_init_signal_slot()
{
    qDebug("[AttrLabelTabWidget--%s]>>", __FUNCTION__);
//    QObject::connect(this->penwidth_lab_edit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_penwidth_lab_edit_changed()));
    QObject::connect(this->name_edit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_name_changed()));

    //上下左右移动按钮
    QObject::connect(this->up_bt, SIGNAL(clicked(bool)), this, SLOT(attr_label_up_move_bt_clicked()));
    QObject::connect(this->down_bt, SIGNAL(clicked(bool)), this, SLOT(attr_label_down_move_bt_clicked()));
    QObject::connect(this->left_bt, SIGNAL(clicked(bool)), this, SLOT(attr_label_left_move_bt_clicked()));
    QObject::connect(this->right_bt, SIGNAL(clicked(bool)), this, SLOT(attr_label_right_move_bt_clicked()));

    //label
    QObject::connect(this->lx_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_x_y_changed()));
    QObject::connect(this->ly_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_x_y_changed()));
    QObject::connect(this->vwidth_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_x_y_changed()));
    QObject::connect(this->vheight_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_label_x_y_changed()));

    //view
    //    QObject::connect(this->display_boundframe, SIGNAL(stateChanged(int)), this, SLOT(attr_label_display_bound_changed(int)));
}

/**
 * @brief AttrLabelTabWidget::attr_label_x_y_changed
 */
void AttrLabelTabWidget::attr_label_x_y_changed()
{
    qDebug("[AttrLabelTabWidget--%s]>>", __FUNCTION__);
    if(this->lx_ledit && this->ly_ledit&&this->vwidth_ledit&&this->vheight_ledit)
    {
        //取出编写的文本
        QString lx_str = this->lx_ledit->text();
        QString ly_str = this->ly_ledit->text();
        QString lwidth_ledit_str = this->vwidth_ledit->text();
        QString lheight_ledit_str = this->vheight_ledit->text();

        //qDebug("[AttrLabelTabWidget--%s]>>str(%s, %s)", __FUNCTION__, qPrintable(x_str), qPrintable(y_str));
        float lx_mm = lx_str.toFloat();
        float ly_mm = ly_str.toFloat();
        float lwidth_ledit_mm = lwidth_ledit_str.toFloat();
        float lheight_ledit_mm = lheight_ledit_str.toFloat();
        qDebug("[AttrLabelTabWidget--%s]>>mm(%f, %f, %f, %f)", __FUNCTION__, lx_mm, ly_mm, lwidth_ledit_mm, lheight_ledit_mm);

        float lx_pix = mm2pix(lx_mm, ENUM_DIR_H);
        float ly_pix = mm2pix(ly_mm, ENUM_DIR_V);
        float lwidth_ledit_pix = mm2pix(lwidth_ledit_mm, ENUM_DIR_H);
        float lheight_ledit_pix = mm2pix(lheight_ledit_mm, ENUM_DIR_V);
        qDebug("[AttrLabelTabWidget--%s]>>pix(%f, %f, %f, %f)", __FUNCTION__, lx_pix, ly_pix, lwidth_ledit_pix, lheight_ledit_pix);
        qDebug("[AttrLabelTabWidget--%s]>>22mm(%f, %f, %f, %f)", __FUNCTION__, MM2PIX_H(lx_mm), MM2PIX_V(ly_mm), MM2PIX_H(lwidth_ledit_mm), MM2PIX_V(lheight_ledit_mm));


        LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
        meta.labelRect.setLeft(lx_pix);
        meta.labelRect.setTop(ly_pix);

        //meta.labelRect.setWidth(lwidth_ledit_pix);
        //meta.labelRect.setHeight(lheight_ledit_pix);
        //这里的宽和高，是视图的宽呵高，场景宽高加上标尺宽高才是label的宽高.而场景跟随视图变化，
        meta.viewRect.setWidth(lwidth_ledit_pix);
        meta.viewRect.setHeight(lheight_ledit_pix);

        meta.labelRect.setWidth(meta.viewRect.width() + MM2PIX_H(ROD_OFFSET_LABEL_MM));
        meta.labelRect.setHeight(meta.viewRect.height() + MM2PIX_V(ROD_OFFSET_LABEL_MM));

        qDebug("[AttrLabelTabWidget--%s]>>labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());
        g_widget->wal->setLabelTabmeta(meta);
    }
}

void AttrLabelTabWidget::attr_label_up_move_bt_clicked()
{
    int offset = -10;

    LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
//    qDebug("[AttrLabelTabWidget--%s]>>11labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());
    QPointF tl_p = meta.labelRect.topLeft();
    tl_p.setY(tl_p.y() + offset);
    meta.labelRect.setTopLeft(tl_p);

    QPointF br_p = meta.labelRect.bottomRight();
    br_p.setY(br_p.y() + offset);
    meta.labelRect.setBottomRight(br_p);
    g_widget->wal->setLabelTabmeta(meta);
//    qDebug("[AttrLabelTabWidget--%s]>>22labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());

//    g_widget->wal->move(meta.labelRect.left(), meta.labelRect.top());
//    meta = g_widget->wal->getLabelTabmeta();

//    qDebug("[AttrLabelTabWidget--%s]>>33labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());

    attr_label_update_item_tabmeta_widget(meta);
}

void AttrLabelTabWidget::attr_label_down_move_bt_clicked()
{
    int offset = 10;

    LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
//    qDebug("[AttrLabelTabWidget--%s]>>11labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());
    QPointF tl_p = meta.labelRect.topLeft();
    tl_p.setY(tl_p.y() + offset);
    meta.labelRect.setTopLeft(tl_p);

    QPointF br_p = meta.labelRect.bottomRight();
    br_p.setY(br_p.y() + offset);
    meta.labelRect.setBottomRight(br_p);
    g_widget->wal->setLabelTabmeta(meta);
//    qDebug("[AttrLabelTabWidget--%s]>>22labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());

//    g_widget->wal->move(meta.labelRect.left(), meta.labelRect.top());
//    meta = g_widget->wal->getLabelTabmeta();

//    qDebug("[AttrLabelTabWidget--%s]>>33labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());
    attr_label_update_item_tabmeta_widget(meta);

}

void AttrLabelTabWidget::attr_label_left_move_bt_clicked()
{
    int offset = -10;

    LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
//    qDebug("[AttrLabelTabWidget--%s]>>11labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);
    QPointF tl_p = meta.labelRect.topLeft();
    tl_p.setX(tl_p.x() + offset);

    meta.labelRect.setTopLeft(tl_p);

    QPointF br_p = meta.labelRect.bottomRight();
    br_p.setX(br_p.x() + offset);

    meta.labelRect.setBottomRight(br_p);
    g_widget->wal->setLabelTabmeta(meta);
//    qDebug("[AttrLabelTabWidget--%s]>>22labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);

//    g_widget->wal->move(meta.labelRect.left(), meta.labelRect.top());
//    meta = g_widget->wal->getLabelTabmeta();

//    qDebug("[AttrLabelTabWidget--%s]>>33labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);
    attr_label_update_item_tabmeta_widget(meta);

}

void AttrLabelTabWidget::attr_label_right_move_bt_clicked()
{
    int offset = 10;

    LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
//    qDebug("[AttrLabelTabWidget--%s]>>11labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);
    QPointF tl_p = meta.labelRect.topLeft();
    tl_p.setX(tl_p.x() + offset);

    meta.labelRect.setTopLeft(tl_p);

    QPointF br_p = meta.labelRect.bottomRight();
    br_p.setX(br_p.x() + offset);

    meta.labelRect.setBottomRight(br_p);
    g_widget->wal->setLabelTabmeta(meta);
//    qDebug("[AttrLabelTabWidget--%s]>>22labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);

//    g_widget->wal->move(meta.labelRect.left(), meta.labelRect.top());
//    meta = g_widget->wal->getLabelTabmeta();

//    qDebug("[AttrLabelTabWidget--%s]>>33labelRect(%f, %f, %f, %f)", __FUNCTION__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.bottomRight().x, meta.labelRect.bottomRight().y);
    attr_label_update_item_tabmeta_widget(meta);

}

void AttrLabelTabWidget::attr_label_name_changed()
{
    qDebug("[AttrLabelTabWidget--%s]>>", __FUNCTION__);
    QString name;

    LabelPanelMeta meta = g_widget->wal->getLabelTabmeta();
    meta.name = name_edit->text();
    g_widget->wal->setLabelTabmeta(meta);
    g_widget->wal->setSaveFlag(false);          //名字更改,则标记为未保存
    if(!g_widget->wal->getSaveFlag())
    {
        name = meta.name;
        name = name.append(STR_FILE_UNSAVE_FLAG);
    }
    g_widget->central_tab_main->setTabText(g_widget->central_tab_main->currentIndex(), name);
}

