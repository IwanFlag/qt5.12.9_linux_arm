#include "attrtwocodetabwidget.h"
#include "qdebug.h"
#include "main.h"
#include "common_fun.h"


AttrTwoCodeTabWidget::AttrTwoCodeTabWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>", __FUNCTION__);
    attr_twocode_init_show_meta(twocode_item_init);
    attr_twocode_init_signal_slot();
    this->cb_mode->setEnabled(false);       //暂时只支持8-bit
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_init_show_meta
 *              显示二维码item属性编辑框
 * @param index
 */
void AttrTwoCodeTabWidget::attr_twocode_init_show_meta(TwoCodeItemMeta meta)
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));

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

/*---------2.创建内容 group---------*/
    QGroupBox *content_gp = new QGroupBox;
    vb->addWidget(content_gp);

    content_gp->setTitle(tr("content"));

    //创建网络栅格布局
    QGridLayout *content_gl = new QGridLayout;
    content_gl->setSpacing(10);       //设置间距

//    //数据来源
//    QLabel *data_from_type = new QLabel;
//    data_from_type->setText(tr("data from:"));
//    content_gl->addWidget(data_from_type, 0, 0, 1, 1); //占据1行1列

//    //数据来源联合下拉列表
//    QComboBox *data_from_cb = new QComboBox;

//    data_from_cb->setStyleSheet("QComboBox{border:1px solid gray;}"
//         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
//         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
//         "QComboBox::drop-down{border:0px;}"); //下拉按钮
//    data_from_cb->setView(new QListView());       //不知道干撒的

//    //加载item
//    data_from_cb->addItem(tr("custom"), GRAPHIC_TEXT_FROM_CUSTOM);
//    data_from_cb->addItem(tr("other"), GRAPHIC_TEXT_FROM_OTHER);

//    data_from_cb->setItemText(0, tr("custom"));
//    data_from_cb->setItemText(1, tr("other"));

//    content_gl->addWidget(data_from_cb, 0, 1, 1, 1); //占据1行1列

    //文本编辑框（这个不要单行文本，等会换）
    //QLineEdit *data_from_le = new QLineEdit();
    //content_gl->addWidget(data_from_le, 1, 0, 2, 2); //占据1行1列
    data_plain_text = new QPlainTextEdit;
    data_plain_text->setStyleSheet(BG_COLOR_STYLE_WHITE);
    content_gl->addWidget(data_plain_text, 1, 0, 2, 2); //占据1行1列
    data_plain_text->setPlainText(meta.dataString);

    //加载网络栅格布局
    content_gp->setLayout(content_gl);

    /*---------3.创建样式 group---------*/
    QGroupBox *style_gp = new QGroupBox;
    vb->addWidget(style_gp);

    style_gp->setTitle(tr("style"));

    //创建网络栅格布局
    QGridLayout *style_gl = new QGridLayout;
    style_gl->setSpacing(10);       //设置间距


    //字号类型label
    QLabel *cb_ecl_lab = new QLabel;
    cb_ecl_lab->setText(tr("ecl:"));
    style_gl->addWidget(cb_ecl_lab, 0, 0, 1, 1); //占据1行1列

    //容错率 ecl 联合下拉列表
    cb_ecl_style = new QComboBox;

    cb_ecl_style->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_ecl_style->setView(new QListView());       //不知道干撒的

    //加载字体类型item
    cb_ecl_style->addItem(tr("low"), GRAPHIC_TWOCODE_ECLEVEL_L);
    cb_ecl_style->addItem(tr("medium"), GRAPHIC_TWOCODE_ECLEVEL_M);
    cb_ecl_style->addItem(tr("quality"), GRAPHIC_TWOCODE_ECLEVEL_Q);
    cb_ecl_style->addItem(tr("high"), GRAPHIC_TWOCODE_ECLEVEL_H);

    cb_ecl_style->setItemText(GRAPHIC_TWOCODE_ECLEVEL_L, tr(STR_TWOCODE_ECL_LOW));   //0
    cb_ecl_style->setItemText(GRAPHIC_TWOCODE_ECLEVEL_M, tr(STR_TWOCODE_ECL_MEDIUM));   //0
    cb_ecl_style->setItemText(GRAPHIC_TWOCODE_ECLEVEL_Q, tr(STR_TWOCODE_ECL_QUALITY));   //0
    cb_ecl_style->setItemText(GRAPHIC_TWOCODE_ECLEVEL_H, tr(STR_TWOCODE_ECL_HIGH));   //0

    //默认设置...
    cb_ecl_style->setCurrentIndex(meta.ecl);
    style_gl->addWidget(cb_ecl_style, 0, 1, 1, 1); //占据1行1列


    //编码模式label
    QLabel *cb_mode_lab = new QLabel;
    cb_mode_lab->setText(tr("mode:"));
    style_gl->addWidget(cb_mode_lab, 1, 0, 1, 1); //占据1行1列

    //编码模式 mode 联合下拉列表
    cb_mode = new QComboBox;

    cb_mode->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_mode->setView(new QListView());       //不知道干撒的

    //加载字号大小item
    cb_mode->addItem(tr(STR_TWOCODE_MODE_NUM), GRAPHIC_TWOCODE_MODE_NUM);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_AN), GRAPHIC_TWOCODE_MODE_AN);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_8), GRAPHIC_TWOCODE_MODE_8);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_KANJI), GRAPHIC_TWOCODE_MODE_KANJI);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_STRUCTURE), GRAPHIC_TWOCODE_MODE_STRUCTURE);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_ECI), GRAPHIC_TWOCODE_MODE_ECI);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_FNC1FIRST), GRAPHIC_TWOCODE_MODE_FNC1FIRST);
    cb_mode->addItem(tr(STR_TWOCODE_MODE_FNC1SECOND), GRAPHIC_TWOCODE_MODE_FNC1SECOND);

    //可以整个枚举和字符串宏的对应关系全局变量..后面再说了
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_NUM, tr(STR_TWOCODE_MODE_NUM));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_AN, tr(STR_TWOCODE_MODE_AN));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_8, tr(STR_TWOCODE_MODE_8));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_KANJI, tr(STR_TWOCODE_MODE_KANJI));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_STRUCTURE, tr(STR_TWOCODE_MODE_STRUCTURE));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_ECI, tr(STR_TWOCODE_MODE_ECI));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_FNC1FIRST, tr(STR_TWOCODE_MODE_FNC1FIRST));
    cb_mode->setItemText(GRAPHIC_TWOCODE_MODE_FNC1SECOND, tr(STR_TWOCODE_MODE_FNC1SECOND));

    //展示 mode
    cb_mode->setCurrentIndex(meta.mode);
    style_gl->addWidget(cb_mode, 1, 1, 1, 1); //占据1行1列

    //再增加一个是否显示外边框的按钮
    QLabel *display_boundframe_lab = new QLabel;
    display_boundframe_lab->setText(tr("display_boundframe:"));
    //style_gl->addWidget(display_boundframe_lab, 2, 0, 1, 1); //占据1行1列

    display_boundframe = new QCheckBox;
    display_boundframe->setChecked(meta.display_boundframe);
    //style_gl->addWidget(display_boundframe, 2, 1, 1, 1); //占据1行1列

    //编码模式label
    QLabel *cb_uw_lab = new QLabel;
    cb_uw_lab->setText(tr("codeLine width:"));
    style_gl->addWidget(cb_uw_lab, 3, 0, 1, 1); //占据1行1列

    //二维码 码宽 联合下拉列表
    cb_uw = new QComboBox;

    cb_uw->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_uw->setView(new QListView());       //不知道干撒的

    //加载二维码码宽
    cb_uw->addItem(tr("1->5mm"), GRAPHIC_TWOCODE_UINTW_1);
    cb_uw->addItem(tr("2->10mm"), GRAPHIC_TWOCODE_UINTW_2);
    cb_uw->addItem(tr("3->15mm"), GRAPHIC_TWOCODE_UINTW_3);
    cb_uw->addItem(tr("4->20mm"), GRAPHIC_TWOCODE_UINTW_4);
    style_gl->addWidget(cb_uw, 3, 1, 1, 1); //占据1行1列
    cb_uw->setCurrentIndex(1);

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
    width_ledit->setReadOnly(true);


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
    height_ledit->setReadOnly(true);

    //位置group加载 位置加载网络栅格布局
    pos_gp->setLayout(pos_gl);


    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_update_item_tabmeta_widget
 *              更新二维码item属性编辑框
 * @param index
 */
void AttrTwoCodeTabWidget::attr_twocode_update_item_tabmeta_widget(TwoCodeItemMeta meta)
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));


    //item 标签名字
    if(meta.name.trimmed().isEmpty() == false && meta.name.trimmed().length() != 0)
    {
        qDebug("[DrawTwoCodeItem--%s]>>aaabbb,%s", __FUNCTION__,qPrintable(meta.name));
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_TWOCODE));
    }

    //更新属性框内容
    data_plain_text->setPlainText(meta.dataString);

    //容错率
    cb_ecl_style->setCurrentIndex(meta.ecl);

    //展示 mode
    cb_mode->setCurrentIndex(meta.mode);

    //码宽-二维码宽度
    cb_uw->setCurrentIndex(meta.uintw - 1);

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
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_two_attr_manager,tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);

}
/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_init_signal_slot
 * 初始信号和槽函数
 */
void AttrTwoCodeTabWidget::attr_twocode_init_signal_slot()
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>", __FUNCTION__);
    QObject::connect(this->data_plain_text, SIGNAL(textChanged()), this, SLOT(attr_twocode_data_changed()));
    QObject::connect(this->x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_twocode_x_y_changed()));
    QObject::connect(this->y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_twocode_x_y_changed()));
    QObject::connect(this->width_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_twocode_x_y_changed()));
    QObject::connect(this->height_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_twocode_x_y_changed()));
    QObject::connect(this->cb_ecl_style, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_twocode_ecl_changed(int)));
    QObject::connect(this->cb_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_twocode_mode_changed(int)));
    QObject::connect(this->display_boundframe, SIGNAL(stateChanged(int)), this, SLOT(attr_twocode_display_bound_changed(int)));
    QObject::connect(this->cb_uw, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_twocode_uintw_changed(int)));
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_data_changed
 * 把改变的内容复制到 textitem去
 */
void AttrTwoCodeTabWidget::attr_twocode_data_changed()
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>", __FUNCTION__);

    //取出编写的文本
    QString w_str = this->data_plain_text->toPlainText();
    qDebug("[AttrTwoCodeTabWidget--%s]>>w_str:\n%s", __FUNCTION__, qPrintable(w_str));

    //meta.dataString = w_str;
    //bool ret = isChineseString(meta.dataString);        //是否存在中文字符
    //w_str = utf8ToGb2312(w_str.toUtf8().data());//编码,先转为utf8,再搞成char*

    //获取目前的ecl，不做改变
    int ecl_index = this->cb_ecl_style->currentIndex();

    //获取目前的Mode，不做改变
    int mode_index = this->cb_mode->currentIndex();

    if(g_widget->twocode_item_select)
    {
        g_widget->twocode_item_select->setString(w_str, (GRAPHIC_TWOCODE_ECLEVEL)ecl_index, (GRAPHIC_TWOCODE_MODE)mode_index);
    }
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_x_y_changed
 */
void AttrTwoCodeTabWidget::attr_twocode_x_y_changed()
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->twocode_item_select && this->x_ledit && this->y_ledit)
    {
        //取出编写的文本
        QString x_str = this->x_ledit->text();
        QString y_str = this->y_ledit->text();
        QString width_ledit_str = this->width_ledit->text();
        QString height_ledit_str = this->height_ledit->text();

        //qDebug("[AttrTwoCodeTabWidget--%s]>>str(%s, %s)", __FUNCTION__, qPrintable(x_str), qPrintable(y_str));

        float x_mm = x_str.toFloat();
        float y_mm = y_str.toFloat();
        float width_ledit_mm = width_ledit_str.toFloat();
        float height_ledit_mm = height_ledit_str.toFloat();

        qDebug("[AttrTwoCodeTabWidget--%s]>>mm(%f, %f, %f, %f)", __FUNCTION__, x_mm, y_mm, width_ledit_mm, height_ledit_mm);

        float x_pix = mm2pix(x_mm, ENUM_DIR_H);
        float y_pix = mm2pix(y_mm, ENUM_DIR_V);
        float width_ledit_pix = mm2pix(width_ledit_mm, ENUM_DIR_H);
        float height_ledit_pix = mm2pix(height_ledit_mm, ENUM_DIR_V);

        qDebug("[AttrTwoCodeTabWidget--%s]>>pix(%f, %f, %f, %f)", __FUNCTION__, x_pix, y_pix, width_ledit_pix, height_ledit_pix);

        //把属性框编辑的文本发送到item上显示
        if(g_widget->twocode_item_select)
        {
            TwoCodeItemMeta meta = g_widget->twocode_item_select->getTwoCodeMeta();

            meta.CoordRect.setLeft(x_pix);
            meta.CoordRect.setTop(y_pix);
            meta.CoordRect.setWidth(width_ledit_pix);
            meta.CoordRect.setHeight(height_ledit_pix);

            g_widget->twocode_item_select->setTwoCodeMeta(meta);
        }
    }
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_ecl_changed
 * 界面下拉选择改变时，改变item的二维码绘画模型
 */
void AttrTwoCodeTabWidget::attr_twocode_ecl_changed(int index)
{
    //获取目前的内容，不做改变
    QString data_str = g_widget->twocode_item_select->getString();

    //获取目前的Mode，不做改变
    int mode_index = this->cb_mode->currentIndex();

    qDebug("[AttrTwoCodeTabWidget--%s]>>index:%d", __FUNCTION__,index);
    g_widget->twocode_item_select->setString(data_str, (GRAPHIC_TWOCODE_ECLEVEL)index, (GRAPHIC_TWOCODE_MODE)mode_index);
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_ecl_changed
 * 二维码编码类型界面下拉选择改变时，改变item的二维码绘画mode
 * 暂时只支持8-bit,在构造函数里面失能了这个下拉
 */
void AttrTwoCodeTabWidget::attr_twocode_mode_changed(int index)
{
    //获取目前的内容，不做改变
    QString data_str = g_widget->twocode_item_select->getString();

    //获取目前的Mode，不做改变
    //int mode_index = this->cb_mode->currentIndex();
    int ecl_index = this->cb_ecl_style->currentIndex();

    qDebug("[AttrTwoCodeTabWidget--%s]>>index:%d", __FUNCTION__,index);
    g_widget->twocode_item_select->setString(data_str, (GRAPHIC_TWOCODE_ECLEVEL)ecl_index, (GRAPHIC_TWOCODE_MODE)index);
}

/**
 * @brief AttrTwoCodeTabWidget::attr_onecode_display_bound_changed
 * 是否显示一维码外边框复选框
 * @param state
 */
void AttrTwoCodeTabWidget::attr_twocode_display_bound_changed(int state)
{
    qDebug("[AttrTwoCodeTabWidget--%s]>>state:%d", __FUNCTION__,state);
    if(g_widget->twocode_item_select)
    {
        g_widget->twocode_item_select->meta.display_boundframe = state;
    }
    else
    {
        qDebug("[AttrTwoCodeTabWidget--%s]>>ERROR:-1", __FUNCTION__);
    }
}

/**
 * @brief AttrTwoCodeTabWidget::attr_twocode_uintw_changed
 *                  二维码码宽
 */
void AttrTwoCodeTabWidget::attr_twocode_uintw_changed(int index)
{
    //获取目前的内容，不做改变
    QString data_str = g_widget->twocode_item_select->getString();
    TwoCodeItemMeta meta = g_widget->twocode_item_select->getTwoCodeMeta();

    //获取目前的Mode，不做改变
    int uintw_index = this->cb_uw->currentIndex();
    meta.uintw = (GRAPHIC_TWOCODE_UINTW)this->cb_uw->currentData().toInt();

    qDebug("[AttrTwoCodeTabWidget--%s]>>index:%d, meta.uintw:%d", __FUNCTION__, index, meta.uintw);
    g_widget->twocode_item_select->setTwoCodeMeta(meta);
    attr_twocode_update_item_tabmeta_widget(g_widget->twocode_item_select->getTwoCodeMeta());
}



