#include "attrtexttabwidget.h"
#include "qdebug.h"
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
#include "main.h"
#include "common_fun.h"


AttrTextTabWidget::AttrTextTabWidget(QWidget *parent) : QWidget(parent)
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);
    attr_text_item_tabmeta_widget_create(text_meta_init_val);
    attr_text_init_signal_slot();
    cb_font_height->setEnabled(false);          //发现打印机这个参数根本没用，暂时不用
}

/**
 * @brief AttrTextTabWidget::attr_text_item_tabmeta_widget_create
 *   右侧tab显示meta属性框(只能初始化调用一次，其他地方禁止再次调用，否则会再次创建这些控件)
 *              更新使用attr_text_update_item_tabmeta_widget
 * @param meta
 */
void AttrTextTabWidget::attr_text_item_tabmeta_widget_create(TextItemMetaPS meta)
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


    //内容富文本框
    data_plain_text = new QPlainTextEdit;
    data_plain_text->setStyleSheet(BG_COLOR_STYLE_WHITE);
    content_gl->addWidget(data_plain_text, 1, 0, 2, 2); //占据1行1列
    QString str_text = meta.dataString.trimmed();//去除字符串两侧的空白字符(空白字符包括空格、Tab以及换行符，而不仅仅是空格)
    qDebug("[AttrTextTabWidget--%s]>>[%d,%d]", __FUNCTION__,str_text.isEmpty(), str_text.length());

    //if((str_text.isEmpty() == false) && (str_text.length() != 0))
    {
        data_plain_text->setPlainText(meta.dataString);
        qDebug("[AttrTextTabWidget--%s]>>dataString:%s\n", __FUNCTION__,qPrintable(meta.dataString));
    }
    //else
    {
    //    data_plain_text->setPlainText(tr(STR_TEXT_EDIT_WRITE_HERE));
    }

    //字体
    QFont data_ft;
    //ft.setPointSize(g_text_font_height[meta.height]);
    data_ft.setPointSize(g_text_font_height[meta.height]);
    data_ft.setBold(meta.isbold);
    data_ft.setUnderline(meta.isunderline);
    //this->setFont(ft);

    data_plain_text->setFont(data_ft);
    data_plain_text->setReadOnly(false);            //默认就是false
    //加载网络栅格布局
    content_gp->setLayout(content_gl);

/*---------3.创建样式 group---------*/
    QGroupBox *style_gp = new QGroupBox;
    vb->addWidget(style_gp);

    style_gp->setTitle(tr("style"));

    //创建网络栅格布局
    QGridLayout *style_gl = new QGridLayout;
    style_gl->setSpacing(10);       //设置间距

    //字体类型label
    QLabel *cb_font_lab = new QLabel;
    cb_font_lab->setText(tr("font type:"));
    style_gl->addWidget(cb_font_lab, 0, 0, 1, 1); //占据1行1列

    //字体联合下拉列表（目前只做展示只用，此属性不可设置,disable）
    QComboBox *cb_font_style = new QComboBox;

    cb_font_style->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
         "QComboBox::drop-down{border:0px;}"); //下拉按钮
    cb_font_style->setView(new QListView());       //不知道干撒的

    //加载字体类型item
    cb_font_style->addItem(tr(STR_TEXT_EDIT_FONT_SONG), GRAPHIC_FONT_TYPE_SONG);
    cb_font_style->addItem(tr(STR_TEXT_EDIT_FONT_BLACK), GRAPHIC_FONT_TYPE_BLACK);

    cb_font_style->setItemText(GRAPHIC_FONT_TYPE_SONG - 1, tr(STR_TEXT_EDIT_FONT_SONG));   //0
    cb_font_style->setItemText(GRAPHIC_FONT_TYPE_BLACK - 1, tr(STR_TEXT_EDIT_FONT_BLACK));  //1

    //默认字体类型设置...宋体
    cb_font_style->setCurrentIndex(0);
    cb_font_style->setEnabled(false);           //打印机没有这个参数，暂时不用
    style_gl->addWidget(cb_font_style, 0, 1, 1, 1); //占据1行1列


    //字号类型label
    QLabel *cb_font_height_type = new QLabel;
    cb_font_height_type->setText(tr("font height:"));
    style_gl->addWidget(cb_font_height_type, 1, 0, 1, 1); //占据1行1列

    //字号大小 联合下拉列表 参考 g_text_font_height
    cb_font_height = new QComboBox;

    cb_font_height->setStyleSheet("QComboBox{border:1px solid gray;}"
         "QComboBox QAbstractItemView::item{height:20px;}" 		//下拉选项高度
         "QComboBox::down-arrow{image:url(:/icon/arrowdown);}"  //下拉箭头
         "QComboBox::drop-down{border:0px;}"); 					//下拉按钮
    cb_font_height->setView(new QListView());       				//不知道干撒的

    //加载字号大小item
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_8]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_8]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_10]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_10]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_12]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_12]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_14]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_14]);

    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_16]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_16]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_24]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_24]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_32]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_32]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_48]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_48]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_64]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_64]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_80]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_80]);
    cb_font_height->addItem(QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_86]), g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_86]);

    //可以整个枚举和字符串宏的对应关系全局变量..后面再说了
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_8, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_8]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_10, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_10]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_12, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_12]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_14, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_14]));

    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_16, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_16]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_24, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_24]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_32, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_32]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_48, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_48]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_64, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_64]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_80, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_80]));
    cb_font_height->setItemText(GRAPHIC_FONT_HEIGHT_INDEX_86, QString::number(g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_86]));

    //展示字体大小
    cb_font_height->setCurrentIndex(meta.height);
    style_gl->addWidget(cb_font_height, 1, 1, 1, 1); //占据1行1列

    //字体风格,加粗，斜体，下划线，删除线
    //粗体
    QLabel *bold_lab = new QLabel;
    bold_lab->setText(tr("bold:"));
    style_gl->addWidget(bold_lab, 2, 0, 1, 1); //占据1行1列

    bold_cb = new QCheckBox;
    style_gl->addWidget(bold_cb, 2, 1, 1, 1); //占据1行1列
    bold_cb->setChecked(meta.isbold);

    //下划线
    QLabel *underline_lab = new QLabel;
    underline_lab->setText(tr("underline:"));
    style_gl->addWidget(underline_lab, 3, 0, 1, 1); //占据1行1列

    underline_cb = new QCheckBox;
    style_gl->addWidget(underline_cb, 3, 1, 1, 1); //占据1行1列
    underline_cb->setChecked(meta.isunderline);


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
    x_coord = pix2mm(x_coord, ENUM_DIR_H);          //界面全部显示毫米
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
    y_coord = pix2mm(y_coord, ENUM_DIR_V);          //界面全部显示毫米
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
    w_coord = pix2mm(w_coord, ENUM_DIR_H);          //界面全部显示毫米
    QString str_w = QString::number(w_coord,'w_coord', 1);
    width_ledit->setText(str_w);
    width_ledit->setReadOnly(true);      //设置为用户只读

    //height
    QLabel *height_lab = new QLabel;
    height_lab->setText(tr("height(mm):"));
    pos_gl->addWidget(height_lab, 1, 2, 1, 1); //占据1行1列

    height_ledit = new QLineEdit();
    pos_gl->addWidget(height_ledit, 1, 3, 1, 1); //占据1行1列
    height_ledit->setStyleSheet(BG_COLOR_STYLE_WHITE);

    qreal h_coord = meta.CoordRect.height();
    h_coord = pix2mm(h_coord, ENUM_DIR_V);          //界面全部显示毫米
    QString str_h = QString::number(h_coord,'h_coord', 1);
    height_ledit->setText(str_h);
    height_ledit->setReadOnly(true);      //设置为用户只读

    //位置group加载 位置加载网络栅格布局
    pos_gp->setLayout(pos_gl);

    //5.控件加载布局
    this->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief AttrTextTabWidget::attr_text_update_item_tabmeta_widget
 *        根据meta 更新item的meta属性界面(mmp，差点搞混了,搞了好久)
 * @param meta
 */
void AttrTextTabWidget::attr_text_update_item_tabmeta_widget(TextItemMetaPS meta)
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);


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
    //if((str_text.isEmpty() == false) && (str_text.length() != 0))
    {
        data_plain_text->setPlainText(meta.dataString);
    }

    //更新粗体勾选框
    bold_cb->setChecked(meta.isbold);

    //更新下划线勾选框
    underline_cb->setChecked(meta.isunderline);


    //3.字体更新
    QFont ft;
    ft.setPointSize(g_text_font_height[meta.height]);
    ft.setBold(meta.isbold);
    ft.setBold(meta.isunderline);
    this->setFont(ft);

    //坐标宽高
    //x
    qreal x_coord = meta.CoordRect.left();
    QString str_x = QString::number(pix2mm(x_coord, ENUM_DIR_H),'x_coord', 1);
    x_ledit->setText(str_x);

    //y
    qreal y_coord = meta.CoordRect.top();
    QString str_y = QString::number(pix2mm(y_coord, ENUM_DIR_V),'y_coord', 1);
    y_ledit->setText(str_y);

    //width
    qreal w_coord = meta.CoordRect.width();
    QString str_w = QString::number(pix2mm(w_coord, ENUM_DIR_H),'w_coord', 1);
    width_ledit->setText(str_w);

    //height
    qreal h_coord = meta.CoordRect.height();
    QString str_h = QString::number(pix2mm(h_coord, ENUM_DIR_V),'h_coord', 1);
    height_ledit->setText(str_h);

    //
    g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_text_attr_manager,tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);
}

/**
 * @brief AttrTextTabWidget::attr_text_init_signal_slot
 * 初始信号和槽函数
 */
void AttrTextTabWidget::attr_text_init_signal_slot()
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);
    QObject::connect(this->data_plain_text, SIGNAL(textChanged()), this, SLOT(attr_text_data_changed()));
    QObject::connect(this->x_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_text_x_y_changed()));
    QObject::connect(this->y_ledit, SIGNAL(textEdited(QString)), this, SLOT(attr_text_x_y_changed()));
    QObject::connect(this->cb_font_height, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_text_font_height_changed(int)));
    QObject::connect(this->bold_cb, SIGNAL(stateChanged(int)), this, SLOT(attr_text_font_bold_changed(int)));
    QObject::connect(this->underline_cb, SIGNAL(stateChanged(int)), this, SLOT(attr_text_font_underline_changed(int)));
}

/**
 * @brief AttrTextTabWidget::attr_text_data_changed
 * 把改变的内容复制到 textitem去
 */
void AttrTextTabWidget::attr_text_data_changed()
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->text_item_select && this->data_plain_text)
    {
        TextItemMetaPS meta = g_widget->text_item_select->getTextEditMeta();
        meta.dataString = data_plain_text->toPlainText();
        bool ret = isChineseString(meta.dataString);        //是否存在中文字符
        //meta.dataString = utf8ToGb2312(meta.dataString.toUtf8().data());//编码,先转为utf8,再搞成char*

        //QByteArray ba = meta.dataString.toLocal8Bit();//编码转换
//        qDebug("[DrawTextItem--%s]>>size:%d", __FUNCTION__, ba.size());

//        for(int i = 0; i < ba.size(); i++)
//        {
//            qDebug("[DrawTextItem--%s]>>[%d]:%02x", __FUNCTION__, i, ba.at(i));
//        }
//          qDebug("[DrawTextItem--%s]>>22meta.dataString:%s", __FUNCTION__, qPrintable(meta.dataString));
        g_widget->text_item_select->setTextEditMeta(meta);
    }
    else
    {
        qDebug("[AttrTextTabWidget--%s]>>WARN:-1", __FUNCTION__);
    }
}

/**
 * @brief AttrTextTabWidget::attr_text_x_y_changed
 */
void AttrTextTabWidget::attr_text_x_y_changed()
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);

    if(g_widget->text_item_select && this->x_ledit && this->y_ledit)
    {
        //取出编写的文本
        QString x_str = this->x_ledit->text();
        QString y_str = this->y_ledit->text();
        qDebug("[AttrTextTabWidget--%s]>>str(%s, %s)", __FUNCTION__, qPrintable(x_str), qPrintable(y_str));

        float x_mm = x_str.toFloat();
        float y_mm = y_str.toFloat();
        qDebug("[AttrTextTabWidget--%s]>>mm(%f, %f)", __FUNCTION__, x_mm, y_mm);

        float x_pix = mm2pix(x_mm, ENUM_DIR_H);
        float y_pix = mm2pix(y_mm, ENUM_DIR_V);
        qDebug("[AttrTextTabWidget--%s]>>pix(%f, %f)", __FUNCTION__, x_pix, y_pix);

        //把属性框编辑的文本发送到item上显示
        if(g_widget->text_item_select)
        {
            TextItemMetaPS meta = g_widget->text_item_select->getTextEditMeta();
            g_widget->text_item_select->setPos((qreal)x_pix, (qreal)y_pix);
            g_widget->text_item_select->setTextEditMeta(meta);
        }
    }
}

/**
 * @brief AttrTextTabWidget::attr_text_font_height_changed
 * 字符高度下拉框选择项改变
 */
void AttrTextTabWidget::attr_text_font_height_changed(int index)
{
    qDebug("[AttrTextTabWidget--%s]>>index:%d", __FUNCTION__, index);
    if(g_widget->text_item_select)
    {
        TextItemMetaPS meta = g_widget->text_item_select->getTextEditMeta();
        int height = g_widget->tab_text_attr_manager->cb_font_height->currentIndex();
        qDebug("[AttrTextTabWidget--%s]>>index:%d,height:%d", __FUNCTION__, index, height);
        meta.height = (GRAPHIC_TEXT_FONT_HEIGHT_INDEX)index;
        g_widget->text_item_select->setTextEditMeta(meta);
    }
}

/**
 * @brief AttrTextTabWidget::attr_text_font_bold_changed
 *  * 加粗复选框状态改变槽函数
 */
void AttrTextTabWidget::attr_text_font_bold_changed(int state)
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->text_item_select)
    {
        TextItemMetaPS meta = g_widget->text_item_select->getTextEditMeta();
        qDebug("[AttrTextTabWidget--%s]>>state:%d", __FUNCTION__, state);

        meta.isbold = (bool)state;
        qDebug("[AttrTextTabWidget--%s]>>isbold:%d", __FUNCTION__, meta.isbold);

        g_widget->text_item_select->setTextEditMeta(meta);
    }

}

/**
 * @brief AttrTextTabWidget::attr_text_font_underline_changed
 * 下划线复选框状态改变槽函数
 * @param val
 */
void AttrTextTabWidget::attr_text_font_underline_changed(int state)
{
    qDebug("[AttrTextTabWidget--%s]>>", __FUNCTION__);
    if(g_widget->text_item_select)
    {
        TextItemMetaPS meta = g_widget->text_item_select->getTextEditMeta();
        qDebug("[AttrTextTabWidget--%s]>>state:%d", __FUNCTION__, state);

        meta.isunderline = (bool)state;
        qDebug("[AttrTextTabWidget--%s]>>isunderline:%d", __FUNCTION__, meta.isunderline);

        g_widget->text_item_select->setTextEditMeta(meta);
    }

}
