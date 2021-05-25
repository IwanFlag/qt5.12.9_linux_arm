#include "attronecodetabwidget.h"
#include "qdebug.h"
#include "main.h"
#include "common_fun.h"
#include <QCheckBox>




AttrOneCodeTabWidget::AttrOneCodeTabWidget(QWidget *parent)
    :QWidget(parent)
{
    qDebug("[AttrOneCodeTabWidget--%s]>>", __FUNCTION__);
    attr_onecode_init_show_meta(onecode_item_meta_init);
    attr_onecode_init_signal_slot();
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_init_show_meta
 *          显示一维码属性
 * @param onecode_meta
 */
void AttrOneCodeTabWidget::attr_onecode_init_show_meta(OneCodeItemMetaPS meta)
{
    qDebug("[AttrOneCodeTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();

    //2.加一个label标签，来显示item类别
    name_lab = new QLabel;
    name_lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);

    if(meta.name.trimmed().isEmpty() != false &&
            meta.name.trimmed().length() != 0)
    {
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_ONECODE));
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

    //一维码内容文本
    data_plain_text = new QPlainTextEdit;
    data_plain_text->setStyleSheet(BG_COLOR_STYLE_WHITE);
    content_gl->addWidget(data_plain_text, 1, 0, 2, 2); //占据1行1列
    content_gp->setLayout(content_gl);
    data_plain_text->setPlainText(meta.dataString);


    /*---------3.创建样式 group---------*/
    QGroupBox *style_gp = new QGroupBox;
    vb->addWidget(style_gp);

    style_gp->setTitle(tr("style"));

    //创建网络栅格布局
    QGridLayout *style_gl = new QGridLayout;
    style_gl->setSpacing(10);       //设置间距

    //编码类型下拉列表
    QLabel *cb_type_lab = new QLabel;
    cb_type_lab->setText(tr("code type:"));
    style_gl->addWidget(cb_type_lab, 0, 0, 1, 1); //占据1行1列

    cb_type_style = new QComboBox;

    cb_type_style->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_type_style->setView(new QListView());       //不知道干撒的


    //加载编码类型item,注意构造里面实现了几个字符串
    //GRAPHIC_SELECT_INDEX
    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_CODE128_INDEX], GRAPHIC_ONECODE_CODE128_INDEX);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_EAN128_INDEX], GRAPHIC_ONECODE_EAN128_INDEX);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_CODE11_INDEX], GRAPHIC_ONECODE_CODE11);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_CODE39_INDEX], GRAPHIC_ONECODE_CODE39);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_CODABAR_INDEX], GRAPHIC_ONECODE_CODABAR_INDEX);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_CODE93_INDEX], GRAPHIC_ONECODE_CODE93_INDEX);
//    cb_type_style->addItem(g_str_onecode_type[GRAPHIC_ONECODE_UPCA_INDEX], GRAPHIC_ONECODE_UPCA_INDEX);


//    cb_type_style->setItemText(GRAPHIC_ONECODE_CODE11_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_CODE11_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_CODE39_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_CODE39_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_EAN128_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_EAN128_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_CODABAR_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_CODABAR_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_CODE128_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_CODE128_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_CODE93_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_CODE93_INDEX]);
//    cb_type_style->setItemText(GRAPHIC_ONECODE_UPCA_INDEX, g_str_onecode_type[GRAPHIC_ONECODE_UPCA_INDEX]);

    //显示的当前编码类型
    //cb_type_style->setCurrentIndex(4);          //因为有些不能打印，这里先默认选择 CODE128
    //因为有些不能打印，这里先默认选择EAN128
    //cb_type_style->setCurrentText(g_str_onecode_type[GRAPHIC_ONECODE_EAN128_INDEX]);
    style_gl->addWidget(cb_type_style, 0, 1, 1, 1); //占据1行1列


    //再增加一个是否显示外边框的按钮
    //数据来源
    QLabel *display_boundframe_lab = new QLabel;
    display_boundframe_lab->setText(tr("display boundframe:"));
    //style_gl->addWidget(display_boundframe_lab, 1, 0, 1, 1); //占据1行1列

    display_boundframe = new QCheckBox;
    display_boundframe->setChecked(meta.display_boundframe);
    //style_gl->addWidget(display_boundframe, 1, 1, 1, 1); //占据1行1列


    //二维码 码宽 联合下拉列表
    QLabel *cb_uw_lab = new QLabel;
    cb_uw_lab->setText(tr("codeLine width:"));
    style_gl->addWidget(cb_uw_lab, 2, 0, 1, 1); //占据1行1列

    cb_uw = new QComboBox;

    cb_uw->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_uw->setView(new QListView());       //不知道干撒的

    //加载二维码码宽
    cb_uw->addItem(tr("1"), GRAPHIC_ONECODE_UINTW_1);
    cb_uw->addItem(tr("2"), GRAPHIC_ONECODE_UINTW_2);
    cb_uw->addItem(tr("3"), GRAPHIC_ONECODE_UINTW_3);
    cb_uw->addItem(tr("4"), GRAPHIC_ONECODE_UINTW_4);
    style_gl->addWidget(cb_uw, 2, 1, 1, 1); //占据1行1列
    cb_uw->setCurrentIndex(1);


    //实际的打印高度编辑框
//    QLabel *print_heigt_lab = new QLabel;
//    print_heigt_lab->setText(tr("display height(mm):"));
//    style_gl->addWidget(print_heigt_lab, 3, 0, 1, 1); //占据1行1列

//    print_heigt_ledit = new QLineEdit();
//    style_gl->addWidget(print_heigt_ledit, 3, 1, 1, 1); //占据1行1列
//    print_heigt_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

//    qreal hx_coord = meta.CoordRect.left();
//    hx_coord = pix2mm(hx_coord, ENUM_DIR_H);
//    QString hstr_x = QString::number(hx_coord,'hx_coord', 1);
//    print_heigt_ledit->setText(hstr_x);

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
    //height_ledit->setReadOnly(true);


    //位置group加载 位置加载网络栅格布局
    pos_gp->setLayout(pos_gl);


    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_update_item_tabmeta_widget
 *          更新一维码属性界面
 * @param onecode_meta
 */
void AttrOneCodeTabWidget::attr_onecode_update_item_tabmeta_widget(OneCodeItemMetaPS meta)
{
    qDebug("[AttrOneCodeTabWidget--%s]>>name:%s", __FUNCTION__, qPrintable(meta.name));


    //1.name名字更新
    if((meta.name.isEmpty() == false) && (meta.name.length() != 0))
    {
        name_lab->setText(meta.name);
    }
    else
    {
        name_lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_TEXTEDIT));
    }


    //2.富文本框内容更新
    QString str_text = meta.dataString.trimmed();//去除字符串两侧的空白字符(空白字符包括空格、Tab以及换行符，而不仅仅是空格)
    qDebug("[AttrOneCodeTabWidget--%s]>>[%d,%d]", __FUNCTION__,str_text.isEmpty(), str_text.length());
    data_plain_text->setPlainText(meta.dataString);


    //码宽-二维码宽度
    cb_uw->setCurrentIndex(meta.uintw - 1);


    //打印高度
//    qreal print_heigt_coord = meta.display_height;
//    print_heigt_coord = pix2mm(print_heigt_coord, ENUM_DIR_V);
//    QString pstr_y = QString::number(print_heigt_coord, 'print_heigt_coord', 1);
//    print_heigt_ledit->setText(pstr_y);


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

    //
    g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_one_attr_manager,tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_init_signal_slot
 *                  初始信号和槽函数
 */
void AttrOneCodeTabWidget::attr_onecode_init_signal_slot()
{
    qDebug("[AttrOneCodeTabWidget--%s]>>", __FUNCTION__);
    QObject::connect(this->data_plain_text, SIGNAL(textChanged()), this, SLOT(attr_onecode_data_changed()));
    QObject::connect(this->x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_onecode_x_y_changed()));
    QObject::connect(this->y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_onecode_x_y_changed()));
    QObject::connect(this->width_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_onecode_x_y_changed()));
    QObject::connect(this->height_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_onecode_x_y_changed()));
    QObject::connect(this->cb_type_style, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_onecode_type_changed(int)));
    QObject::connect(this->display_boundframe, SIGNAL(stateChanged(int)), this, SLOT(attr_onecode_display_bound_changed(int)));
    QObject::connect(this->cb_uw, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_onecode_uintw_changed(int)));
    //QObject::connect(this->print_heigt_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_onecode_disheight_changed()));
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_data_changed
 * 把改变的内容复制到 textitem去
 */
void AttrOneCodeTabWidget::attr_onecode_data_changed()
{
    qDebug("[AttrOneCodeTabWidget--%s]>>", __FUNCTION__);
    //把属性框编辑的文本发送到item上显示
    if(g_widget->onecode_item_select && this->data_plain_text)
    {
        OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();
        meta.dataString = this->data_plain_text->toPlainText();
        g_widget->onecode_item_select->setOneCodeMetaPS(meta);
    }
    else
    {
        qDebug("[AttrOneCodeTabWidget--%s]>>ERROR:-2", __FUNCTION__);
    }
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_x_y_changed
 */
void AttrOneCodeTabWidget::attr_onecode_x_y_changed()
{
    qDebug("[AttrOneCodeTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->onecode_item_select && this->x_ledit && this->y_ledit)
    {
        //取出编写的文本
        QString x_str = this->x_ledit->text();
        QString y_str = this->y_ledit->text();
        QString width_ledit_str = this->width_ledit->text();
        QString height_ledit_str = this->height_ledit->text();

        //qDebug("[AttrOneCodeTabWidget--%s]>>str(%s, %s)", __FUNCTION__, qPrintable(x_str), qPrintable(y_str));

        float x_mm = x_str.toFloat();
        float y_mm = y_str.toFloat();
        float width_ledit_mm = width_ledit_str.toFloat();
        float height_ledit_mm = height_ledit_str.toFloat();

        qDebug("[AttrOneCodeTabWidget--%s]>>mm(%f, %f, %f, %f)", __FUNCTION__, x_mm, y_mm, width_ledit_mm, height_ledit_mm);

        float x_pix = mm2pix(x_mm, ENUM_DIR_H);
        float y_pix = mm2pix(y_mm, ENUM_DIR_V);
        float width_ledit_pix = mm2pix(width_ledit_mm, ENUM_DIR_H);
        float height_ledit_pix = mm2pix(height_ledit_mm, ENUM_DIR_V);

        qDebug("[AttrOneCodeTabWidget--%s]>>11pix(%f, %f, %f, %f)", __FUNCTION__, x_pix, y_pix, width_ledit_pix, height_ledit_pix);

        //把属性框编辑的文本发送到item上显示
        if(g_widget->onecode_item_select)
        {
            OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();

            meta.CoordRect.setLeft(x_pix);
            meta.CoordRect.setTop(y_pix);
            meta.CoordRect.setWidth(width_ledit_pix);
            meta.CoordRect.setHeight(height_ledit_pix);
            qDebug("[AttrOneCodeTabWidget--%s]>>22pix(%f, %f, %f, %f)", __FUNCTION__, x_pix, y_pix, width_ledit_pix, height_ledit_pix);

            g_widget->onecode_item_select->setOneCodeMetaPS(meta);
        }
    }
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_type_changed
 * 界面下拉选择改变时，改变item的一维码绘画类型
 */
void AttrOneCodeTabWidget::attr_onecode_type_changed(int index)
{
    qDebug("[AttrOneCodeTabWidget--%s]>>11-index:%d", __FUNCTION__,index);
    //g_widget->onecode_item_select->setBarcodeType(g_onecode_type_index[index]);
    //把属性框编辑的文本发送到item上显示
    if(g_widget->onecode_item_select && this->data_plain_text)
    {
        OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();
        int type_index = this->cb_type_style->currentData().toInt();
        qDebug("[AttrOneCodeTabWidget--%s]>>22-type_index:%d", __FUNCTION__,type_index);
        meta.type = (GRAPHIC_ONECODE_TYPE_INDEX)type_index;
        g_widget->onecode_item_select->setOneCodeMetaPS(meta);
    }
    else
    {
        qDebug("[AttrOneCodeTabWidget--%s]>>ERROR:-2", __FUNCTION__);
    }
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_display_bound_changed
 * 是否显示一维码外边框复选框
 * @param state
 */
void AttrOneCodeTabWidget::attr_onecode_display_bound_changed(int state)
{
    qDebug("[AttrOneCodeTabWidget--%s]>>state:%d", __FUNCTION__,state);
    if(g_widget->onecode_item_select)
    {
        OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();
        meta.display_boundframe = state;
        g_widget->onecode_item_select->setOneCodeMetaPS(meta);
    }
    else
    {
        qDebug("[AttrOneCodeTabWidget--%s]>>ERROR:-1", __FUNCTION__);
    }
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_uintw_changed
 *                  二维码码宽
 */
void AttrOneCodeTabWidget::attr_onecode_uintw_changed(int index)
{
    //获取目前的内容，不做改变
    OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();

    //获取目前的Mode，不做改变
    int uintw_index = this->cb_uw->currentIndex();
    meta.uintw = (GRAPHIC_ONECODE_UINTW)this->cb_uw->currentData().toInt();

    qDebug("[AttrOneCodeTabWidget--%s]>>index:%d, meta.uintw:%d", __FUNCTION__, index, meta.uintw);
    g_widget->onecode_item_select->setOneCodeMetaPS(meta);
}

/**
 * @brief AttrOneCodeTabWidget::attr_onecode_disheight_changed
 */
void AttrOneCodeTabWidget::attr_onecode_disheight_changed()
{
    qDebug("[AttrOneCodeTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->onecode_item_select && this->print_heigt_ledit)
    {
        //取出编写的文本
        QString heigt_str = this->print_heigt_ledit->text();
        float heigt_mm = heigt_str.toFloat();
        float heigt_pix = mm2pix(heigt_mm, ENUM_DIR_V);
        //把属性框编辑的文本发送到item上显示
        if(g_widget->onecode_item_select)
        {
            OneCodeItemMetaPS meta = g_widget->onecode_item_select->getOneCodeMetaPS();
            meta.display_height = heigt_pix;
            g_widget->onecode_item_select->setOneCodeMetaPS(meta);
        }
    }
}
