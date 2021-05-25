#include "drawlabel.h"
#include "main.h"
#include <QDebug>
#include <QHBoxLayout>
#include "common_fun.h"
#include <QMessageBox>
#include <common_def.h>
#include "drawtextitem.h"
#include "main.h"


//初始化label,view和scene
LabelPanelMeta label_init_meta =
{
    QObject::tr("label"),                                               //标签名字
    QRectF(0, 0, 0, 0),                                                 //label
    QRectF(0, 0, 0, 0),                                                 //view
    QRectF(0, 0, 0, 0),                                                 //scene
    1,                                                                  //放大缩小倍数(view和scene)
    QPointF(0, 0),                                                      //坐标系平移(view和scene)
    0,                                                                  //旋转角度(view和scene)
    0                                                                   //图元个数(scene)
};

DrawLabel::DrawLabel()
{

    this->setMouseTracking(true);               //设置鼠标为实时跟踪
    //setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);
    setStyleSheet(BG_COLOR_STYLE_WHITE);        //label设置为白色画板

    //label初始化
    int offset_x = (g_widget->centralWidget()->width() - this->width())/2;
    int offset_y = (g_widget->centralWidget()->height() - this->height())/2;
    label_init_meta.labelRect.setLeft(offset_x);
    label_init_meta.labelRect.setTop(offset_y);
    label_init_meta.labelRect.setWidth(MM2PIX_H(LABEL_LABEL_WIDTH_MM));
    label_init_meta.labelRect.setHeight(MM2PIX_V(LABEL_LABEL_HEIGHT_MM));

    //view
    label_init_meta.viewRect.setX(MM2PIX_H(ROD_OFFSET_LABEL_MM + VIEW_OFFSET_ROD_LEFT_MM));
    label_init_meta.viewRect.setY(MM2PIX_V(ROD_OFFSET_LABEL_MM+ VIEW_OFFSET_ROD_TOP_MM));
    label_init_meta.viewRect.setWidth(MM2PIX_H(VIEW_LABEL_WIDTH_MM));
    label_init_meta.viewRect.setHeight(MM2PIX_V(VIEW_LABEL_HEIGHT_MM));
    qDebug("[DrawLabel--%s]>>:222viewRect:%f,%d,%f", __FUNCTION__, label_init_meta.viewRect.width(), VIEW_LABEL_WIDTH_MM,MM2PIX_H(VIEW_LABEL_WIDTH_MM));

    //scene，scene是跟view重合的
    label_init_meta.sceneRect.setX(0);
    label_init_meta.sceneRect.setY(0);
    label_init_meta.sceneRect.setWidth(MM2PIX_H(SCENE_LABEL_WIDTH_MM));
    label_init_meta.sceneRect.setHeight(MM2PIX_V(SCENE_LABEL_HEIGHT_MM));

    //居中
    int w = label_init_meta.labelRect.width();
    int h = label_init_meta.labelRect.height();


    label_init_meta.labelRect.setX(MM2PIX_H(ROD_OFFSET_LABEL_MM));//随便填个数，居中不了就算了
    label_init_meta.labelRect.setY(MM2PIX_V(ROD_OFFSET_LABEL_MM));//随便填个数，居中不了就算了
    label_init_meta.labelRect.setWidth(w);
    label_init_meta.labelRect.setHeight(h);
    qDebug("[DrawLabel--%s]>>:viewRect:%f", __FUNCTION__, label_init_meta.viewRect.width());


    setLabelTabmeta(label_init_meta);
    qDebug("[DrawLabel--%s]>>labelRect:(%f,%f,%f,%f)",__func__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());

    wal_label_create_draw_view(); //一个label，一个视图，一个场景，初始化图形视图场景

    //每次新创建一个tab页后，先创建一个对应的画板属性框
    g_widget->tab_label_attr_manager = new AttrLabelTabWidget;
    g_widget->tab_label_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);


    if(QString::compare(g_widget->central_tab_meta->tabText(0), tr("Attribute"), Qt::CaseInsensitive) == 0)
    {
        //如果tabmeta属性框第一项是attribute,说明attr属性框已经存在,则先remove
        g_widget->central_tab_meta->removeTab(0);
    }

    g_widget->central_tab_meta->insertTab(0, g_widget->tab_label_attr_manager, tr("Attribute"));
    g_widget->central_tab_meta->setCurrentIndex(0);
    setSaveFlag(false);
    //g_widget->central_tab_meta->setTabText(g_widget->central_tab_meta->currentIndex(), this->meta.name);
}

void DrawLabel::mousePressEvent(QMouseEvent *event)
{
    qDebug("[DrawLabel:%s]",__func__);
    QLabel::mousePressEvent(event);
}

void DrawLabel::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug("[DrawLabel:%s]",__func__);
    workAreaMousePos = event->pos();
    QLabel::mouseMoveEvent(event);
}

void DrawLabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("[DrawLabel:%s]",__func__);
    QLabel::mouseReleaseEvent(event);
}

/**
 * @brief DrawLabel::paintEvent
 *      绘图事件处理函数
 * @param event
 */
void DrawLabel::paintEvent(QPaintEvent *event)
{
    drawOutRod();
    //drawInnerRod();
    //drawMouseCrossLine();
}

void DrawLabel::setLabelTabmeta(LabelPanelMeta meta)
{
    this->meta = meta;
    qDebug("[DrawLabel--%s]>>:333viewRect:%f,%d,%f", __FUNCTION__, meta.viewRect.width(), VIEW_LABEL_WIDTH_MM,MM2PIX_H(VIEW_LABEL_WIDTH_MM));

    updateLabelWidget();
}

LabelPanelMeta DrawLabel::getLabelTabmeta()
{
    return meta;
}

/**
 * @brief DrawLabel::updateLabelWidget
 * 更新主界面label画板
 */
void DrawLabel::updateLabelWidget()
{
    this->setGeometry(meta.labelRect.left(), meta.labelRect.top(),  meta.labelRect.width(), meta.labelRect.height());
}

/**
 * @brief DrawLabel::drawOutRod
 * 画外部标尺(page/页标尺)
 */
void DrawLabel::drawOutRod()
{
    QPainter painter(this);
    painter.begin(this);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    //font.setItalic(true);
    painter.setFont(font);

    qreal out_rod_offset_pix = MM2PIX_H(OUT_ROD_OFFSET_MM);
    //qreal out_rod_offset_pix = MM2PIX_H(out_rod_offset_pix);

    // 绘制文本
    QRect rect(0,0,out_rod_offset_pix,out_rod_offset_pix);
    painter.drawText(rect, Qt::AlignCenter, tr("(mm)"));

    //绘制外坐标y轴
    painter.drawLine(out_rod_offset_pix, out_rod_offset_pix, out_rod_offset_pix, this->height());
    //绘制外坐标x轴
    painter.drawLine(out_rod_offset_pix, out_rod_offset_pix, this->width(), out_rod_offset_pix);

    //x,y的像素长度转为毫米
    int w = pix2mm(width(), ENUM_DIR_H);
    int h = pix2mm(height(), ENUM_DIR_V);
    qDebug("[haa]:w:%d, h:%d",w, h);

    //纸张横坐标画刻度
    //if(!VIEW_OFFSET_ROD_LEFT_MM)             //如果这个左存在内标尺偏移，则不画外标尺横坐标
    {
        for(int x = 0; x < w; x++)
        {
            if(x%10 == 0)
            {
                //qDebug("[aa]:%d",x);
                //长刻度
                rect.setLeft(out_rod_offset_pix + (x*out_rod_offset_pix));
                QString str = "0";
                str.sprintf("%d", x);
                //painter.drawText(rect, Qt::AlignCenter, str);
                painter.drawLine(out_rod_offset_pix + mm2pix(x, ENUM_DIR_H), out_rod_offset_pix-10, out_rod_offset_pix + mm2pix(x, ENUM_DIR_H), out_rod_offset_pix);
            }
            else
            {
                //qDebug("[bb]:%d",x);
                painter.drawLine(out_rod_offset_pix + mm2pix(x, ENUM_DIR_H), out_rod_offset_pix-4, out_rod_offset_pix + mm2pix(x, ENUM_DIR_H), out_rod_offset_pix);
            }
        }
    }
    //纸张纵坐标画刻度(mm，偶数才画值)
    for(int x = 0; x < h; x++)
    {
        if(x%10 == 0)
        {
            //qDebug("[aa]:%d",x);
            painter.drawLine(out_rod_offset_pix-10, out_rod_offset_pix + mm2pix(x, ENUM_DIR_V), out_rod_offset_pix,out_rod_offset_pix + mm2pix(x, ENUM_DIR_V));
        }
        else
        {
            //qDebug("[bb]:%d",x);
            painter.drawLine(out_rod_offset_pix-4, out_rod_offset_pix + mm2pix(x, ENUM_DIR_V), out_rod_offset_pix, out_rod_offset_pix + mm2pix(x, ENUM_DIR_V));
        }
    }

    painter.end();
}

/**
 * @brief DrawLabel::drawInnerRod
 * 画内部标尺(view/绘图区域标尺)
 */
void DrawLabel::drawInnerRod()
{
    QPainter painter(this);
    painter.begin(this);
    QPen pen;

    //画标尺
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    //font.setItalic(true);
    painter.setFont(font);


//    // 绘制文本
//    QRect rect(0,0,INNER_ROD_OFFSET_MM, INNER_ROD_OFFSET_MM);
//    painter.drawText(rect, Qt::AlignCenter, "page");


    //绘制坐标线条
    qreal left_offset_pix = MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM);
    qreal top_offset_pix = MM2PIX_V(INNER_ROD_OFFSET_TOP_MM);
    qDebug("[DrawLabel--%s]>>111:%d,%d,",__func__, INNER_ROD_OFFSET_LEFT_MM, INNER_ROD_OFFSET_TOP_MM);
    qDebug("[DrawLabel--%s]>>222:%f,%f",__func__, MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM), MM2PIX_V(INNER_ROD_OFFSET_TOP_MM));
    qDebug("[DrawLabel--%s]>>333:%f,%f,",__func__, left_offset_pix, top_offset_pix);

    qDebug("[DrawLabel--%s]>>444:%f,%f,",__func__, this->meta.viewRect.width(), this->meta.viewRect.height());

    //作图区域画标尺
    //x,y的像素长度转为毫米
    qreal w = pix2mm(this->meta.viewRect.width(), ENUM_DIR_H);
    qreal h = pix2mm(this->meta.viewRect.height(), ENUM_DIR_V);

    qDebug("[DrawLabel--%s]>>555:w:%f, h:%f",__func__, w, h);

    //减去偏移等,算出实际画布
    w = w - (VIEW_OFFSET_ROD_LEFT_MM * 2);
    h = h - (VIEW_OFFSET_ROD_TOP_MM * 2);


    //y
    //painter.drawLine(left_offset_pix, top_offset_pix, left_offset_pix, h);
    //x
    //painter.drawLine(left_offset_pix, top_offset_pix, w, top_offset_pix);

    qDebug("[DrawLabel--%s]>>left_offset_pix:%f,top_offset_pix:%f,w:%f, h:%f",__func__, left_offset_pix, top_offset_pix, w, h);


    //画布横坐标画刻度
    for(int x = 0; x < w; x++)
    {
        if(x%10 == 0)
        {
            qDebug("[画布横坐标长刻度]:%d,%f",x,w);
            //长刻度
            //rect.setLeft(INNER_ROD_OFFSET_LEFT_MM + (x*INNER_ROD_OFFSET_LEFT_MM));
            QString str = "0";
            str.sprintf("%d", x);
            //painter.drawText(rect, Qt::AlignCenter, str);
            painter.drawLine(mm2pix(x + INNER_ROD_OFFSET_LEFT_MM, ENUM_DIR_H), MM2PIX_V(INNER_ROD_OFFSET_TOP_MM + LONG_ROD_LEN_MM), mm2pix(x + INNER_ROD_OFFSET_LEFT_MM, ENUM_DIR_H), MM2PIX_V(INNER_ROD_OFFSET_TOP_MM));
        }
        else
        {
            qDebug("[画布横坐标短刻度]:%d,%f",x,w);
            painter.drawLine(mm2pix(x + INNER_ROD_OFFSET_LEFT_MM, ENUM_DIR_H), MM2PIX_V(INNER_ROD_OFFSET_TOP_MM + SHORT_ROD_LEN_MM), mm2pix(x + INNER_ROD_OFFSET_LEFT_MM, ENUM_DIR_H), MM2PIX_V(INNER_ROD_OFFSET_TOP_MM));
        }
    }
    //画布纵坐标画刻度(mm，偶数才画值)
    for(int x = 0; x < h; x++)
    {
        if(x%10 == 0)
        {
            qDebug("[画布纵坐标aa]:%d",x);
            painter.drawLine(MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM + LONG_ROD_LEN_MM), mm2pix(x + INNER_ROD_OFFSET_TOP_MM, ENUM_DIR_V), MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM), mm2pix(x + INNER_ROD_OFFSET_TOP_MM, ENUM_DIR_V));
        }
        else
        {
            qDebug("[画布纵坐标bb]:%d",x);
            painter.drawLine(MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM + SHORT_ROD_LEN_MM), mm2pix(x + INNER_ROD_OFFSET_TOP_MM, ENUM_DIR_V), MM2PIX_H(INNER_ROD_OFFSET_LEFT_MM), mm2pix(x + INNER_ROD_OFFSET_TOP_MM, ENUM_DIR_V));
        }
    }

    painter.end();
}

/**
 * @brief DrawLabel::drawMouseCrossLine
 *              画鼠标十字线
 */
void DrawLabel::drawMouseCrossLine()
{
    QPainter painter(this);
    painter.begin(this);


    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    //绘制横向线
    painter.drawLine(0, workAreaMousePos.y(), width(), workAreaMousePos.y());
    //绘制纵向线
    painter.drawLine(workAreaMousePos.x(), 0, workAreaMousePos.x(), height());

    painter.end();
}

/**
 * @brief DrawLabel::toXML
 *          把worklabel和图元转为xml, 数值 必须存为 属性，否则解析不出来......！！！！！！
 */
bool DrawLabel::toXML()
{
    //创建目录操作示例
    QDir *dir = new QDir;
    QString dir_pathname;


    dir_pathname = dir_pathname.append(SAVE_DIR_PATH);
    dir_pathname = dir_pathname.append(SAVE_DIR_NAME);


    if(dir->exists(dir_pathname))
    {
        qDebug("[DrawLabel--%s]>>目录已经存在,%s", __func__, qPrintable(dir_pathname));
    }
    else
    {
        bool ret = dir->mkdir(dir_pathname);
        if(ret)
        {
            qDebug("[DrawLabel--%s]>>目录创建成功,%s", __func__, qPrintable(dir_pathname));
        }
        else
        {
            qDebug("[DrawLabel--%s]>>目录创建失败,%s", __func__, qPrintable(dir_pathname));
            QMessageBox::warning(NULL, tr("dir"), tr("create dir fail!"));
            return false;
        }
    }


    //文件操作
    QFile fp;
    QString filename = dir_pathname.append(meta.name);
    fp.setFileName(filename);

    if(fp.exists())
    {
        //QMessageBox::warning(NULL, tr("file"), tr("file exist,pls change file name or delete exist file!"));
        QMessageBox::warning(NULL, tr("file"), tr("file exist!"));
        return false;
    }


    if(!fp.open(QIODevice::ReadWrite))
    {
        qDebug("[DrawLabel--%s]>>open failed! %s", __func__, qPrintable(filename));
        return false;
    }


    //创建xml声明
    QDomDocument doc;
    QDomProcessingInstruction instruction;  //添加处理指令
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    //创建根元素 label
    QDomElement root = doc.createElement(STR_DRAW_LABEL);    //类名，即元素名字 STR_DRAW_LABEL
    doc.appendChild(root); //添加根元素

    //创建第一个元素, label_meta 元素
    QDomElement label_meta = doc.createElement(STR_DRAW_LABEL_META);       //结构体即元素名字
    root.appendChild(label_meta);

    //name 子元素
    QDomElement name = doc.createElement(STR_DRAW_LABEL_META_NAME);           //即文件名,页tabbar name
    QDomText text = doc.createTextNode(meta.name);
    name.appendChild(text);
    label_meta.appendChild(name);

    //labelRect 子元素
    QDomElement labelRect = doc.createElement(STR_DRAW_LABEL_META_RECT);
    label_meta.appendChild(labelRect);
    labelRect.setAttribute("labelRect_l", meta.labelRect.left());
    labelRect.setAttribute("labelRect_t", meta.labelRect.top());
    labelRect.setAttribute("labelRect_w", meta.labelRect.width());
    labelRect.setAttribute("labelRect_h", meta.labelRect.height());


    //viewRect 子元素
    QDomElement viewRect = doc.createElement(STR_DRAW_LABEL_META_V);
    label_meta.appendChild(viewRect);
    viewRect.setAttribute("viewRect_l", meta.viewRect.left());
    viewRect.setAttribute("viewRect_t", meta.viewRect.top());
    viewRect.setAttribute("viewRect_w", meta.viewRect.width());
    viewRect.setAttribute("viewRect_h", meta.viewRect.height());


    //sceneRect 子元素
    QDomElement sceneRect = doc.createElement(STR_DRAW_LABEL_META_S);
    label_meta.appendChild(sceneRect);
    sceneRect.setAttribute("sceneRect_l", meta.sceneRect.left());
    sceneRect.setAttribute("sceneRect_t", meta.sceneRect.top());
    sceneRect.setAttribute("sceneRect_w", meta.sceneRect.width());
    sceneRect.setAttribute("sceneRect_h", meta.sceneRect.height());


    //获取item数据
    //先获取scene上的所有Item
    QList<QGraphicsItem *> list_items = this->wal_view->wal_scene->items();

    //根据类型来加载显示,定义一个枚举来区分此item是什么类型, 且是哪个item
    for(int i = 0; i < list_items.size(); i++)
    {
        int item_type = list_items[i]->type() - 65536;//UserType==65536,不知道UserType为什么引用不了
        switch(item_type)
        {
            case ENUM_TEXT_EDIT:
                {
                    DrawTextItem* text_item = qgraphicsitem_cast<DrawTextItem*>(list_items[i]);

                    //创建元素 item_e
                    //QDomElement item_obj = doc.createElement(tr("DrawTextItem"));    //类名，即元素名字
                    //root.appendChild(item_obj); //添加根元素

                    //创建 meta 元素
                    QDomElement item_meta = doc.createElement(STR_TEXT_ITEM_META);       //结构体即元素名字
                    root.appendChild(item_meta);


                    //创建 TextItemMetaPS 的子元素 name
                    QDomElement name = doc.createElement(STR_TEXT_ITEM_META_NAME);                           //结构体即元素名字
                    QDomElement dataString = doc.createElement(STR_TEXT_ITEM_DATA);               //结构体即元素名字
                    QDomElement height = doc.createElement(STR_TEXT_ITEM_HEIGHT);                       //结构体即元素名字
                    QDomElement isbold = doc.createElement(STR_TEXT_ITEM_BOLD);                       //结构体即元素名字
                    QDomElement isunderline = doc.createElement(STR_TEXT_ITEM_UNDERLINE);             //结构体即元素名字
                    QDomElement rotate = doc.createElement(STR_TEXT_ITEM_ROTATE);                       //结构体即元素名字
                    QDomElement mag_w = doc.createElement(STR_TEXT_ITEM_MAGW);                         //结构体即元素名字
                    QDomElement mag_h = doc.createElement(STR_TEXT_ITEM_MAGH);                         //结构体即元素名字
                    QDomElement viewRect = doc.createElement(STR_TEXT_ITEM_VR);                   //结构体即元素名字
                    QDomElement CoordRect = doc.createElement(STR_TEXT_ITEM_CR);                 //结构体即元素名字

                    //添加子项 name 子元素
                    item_meta.appendChild(name);
                    QDomText text = doc.createTextNode(text_item->meta.name);
                    name.appendChild(text);

                    //添加子项 dataString 子元素
                    item_meta.appendChild(dataString);
                    text = doc.createTextNode(text_item->meta.dataString);
                    dataString.appendChild(text);

                    //添加子项 height 子元素
                    item_meta.appendChild(height);
                    height.setAttribute(STR_TEXT_ITEM_HEIGHT, text_item->meta.height);
//                    item_meta.appendChild(height);
//                    qreal val = text_item->meta.height;
//                    QString qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    //book.setAttribute("id",1); //方式一：创建属性  其中键值对的值可以是各种类型
//                    height.appendChild(text);

                    //添加子项 isbold 子元素
                    item_meta.appendChild(isbold);
                    isbold.setAttribute(STR_TEXT_ITEM_BOLD, text_item->meta.isbold);

//                    item_meta.appendChild(isbold);
//                    val = text_item->meta.isbold;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    isbold.appendChild(text);

                    //添加子项 isunderline 子元素
                    item_meta.appendChild(isunderline);
                    isunderline.setAttribute(STR_TEXT_ITEM_UNDERLINE, text_item->meta.isunderline);

//                    item_meta.appendChild(isunderline);
//                    val = text_item->meta.isunderline;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    isunderline.appendChild(text);

                    //添加子项 rotate 子元素
                    item_meta.appendChild(rotate);
                    rotate.setAttribute(STR_TEXT_ITEM_ROTATE, text_item->meta.rotate);

//                    item_meta.appendChild(rotate);
//                    val = text_item->meta.rotate;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    rotate.appendChild(text);

                    //添加子项 mag_w 子元素
                    item_meta.appendChild(mag_w);
                    mag_w.setAttribute(STR_TEXT_ITEM_MAGW, text_item->meta.mag_w);

//                    item_meta.appendChild(mag_w);
//                    val = text_item->meta.mag_w;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    mag_w.appendChild(text);

                    //添加子项 mag_h 子元素
                    item_meta.appendChild(mag_h);
                    mag_h.setAttribute(STR_TEXT_ITEM_MAGH, text_item->meta.mag_h);

//                    item_meta.appendChild(mag_h);
//                    val = text_item->meta.mag_h;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    mag_h.appendChild(text);


                    //添加子项 viewRect 子元素
                    //viewRect 子元素
                    item_meta.appendChild(viewRect);
                    viewRect.setAttribute("viewRect_l", text_item->meta.viewRect.left());
                    viewRect.setAttribute("viewRect_t", text_item->meta.viewRect.top());
                    viewRect.setAttribute("viewRect_w", text_item->meta.viewRect.width());
                    viewRect.setAttribute("viewRect_h", text_item->meta.viewRect.height());

                    //CoordRect 子元素
                    item_meta.appendChild(CoordRect);
                    CoordRect.setAttribute("CoordRect_l", text_item->meta.CoordRect.left());
                    CoordRect.setAttribute("CoordRect_t", text_item->meta.CoordRect.top());
                    CoordRect.setAttribute("CoordRect_w", text_item->meta.CoordRect.width());
                    CoordRect.setAttribute("CoordRect_h", text_item->meta.CoordRect.height());
                }
                break;

            case ENUM_ONECODE_EDIT:
                {
                    DrawOneCodeItem* text_item = qgraphicsitem_cast<DrawOneCodeItem*>(list_items[i]);

                    //创建元素 item_e
//                    QDomElement item_obj = doc.createElement(tr("DrawOneCodeItem"));    //类名，即元素名字
//                    root.appendChild(item_obj); //添加根元素

                    //创建 meta 元素
                    QDomElement item_meta = doc.createElement(STR_OC_ITEM_META);       //结构体即元素名字
                    root.appendChild(item_meta);


                    //创建 TextItemMetaPS 的子元素 name
                    QDomElement name = doc.createElement(STR_OC_ITEM_META_NAME);                                   //结构体即元素名字
                    QDomElement dataString = doc.createElement(STR_OC_ITEM_DATA);                       //结构体即元素名字
                    QDomElement type = doc.createElement(STR_OC_ITEM_TYPE);                                   //结构体即元素名字
                    QDomElement frame_type = doc.createElement(STR_OC_ITEM_FRAME_TYPE);                       //结构体即元素名字
                    QDomElement display_boundframe = doc.createElement(STR_OC_ITEM_DBF);             //结构体即元素名字
                    QDomElement display_height = doc.createElement(STR_OC_ITEM_DHEIGHT);               //结构体即元素名字
                    QDomElement uintw = doc.createElement(STR_OC_ITEM_UINTW);                                 //结构体即元素名字
                    QDomElement rotate = doc.createElement(STR_OC_ITEM_ROTATE);                               //结构体即元素名字
                    QDomElement sec_level = doc.createElement(STR_OC_ITEM_SEC_LEVEL);                         //结构体即元素名字
                    QDomElement viewRect = doc.createElement(STR_OC_ITEM_VR);                           //结构体即元素名字
                    QDomElement CoordRect = doc.createElement(STR_OC_ITEM_CR);                         //结构体即元素名字

                    //添加子项 name 子元素
                    item_meta.appendChild(name);
                    QDomText text = doc.createTextNode(text_item->meta.name);
                    name.appendChild(text);

                    //添加子项 dataString 子元素
                    item_meta.appendChild(dataString);
                    text = doc.createTextNode(text_item->meta.dataString);
                    dataString.appendChild(text);

                    //添加子项 type 子元素
                    item_meta.appendChild(type);
                    type.setAttribute(STR_OC_ITEM_TYPE, text_item->meta.type);
//                    qreal val = text_item->meta.type;
//                    QString qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    type.appendChild(text);

                    //添加子项 frame_type 子元素
                    item_meta.appendChild(frame_type);
                    frame_type.setAttribute(STR_OC_ITEM_FRAME_TYPE, text_item->meta.frame_type);

//                    val = text_item->meta.frame_type;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    frame_type.appendChild(text);

                    //添加子项 display_boundframe 子元素
                    item_meta.appendChild(display_boundframe);
                    display_boundframe.setAttribute(STR_OC_ITEM_DBF, text_item->meta.display_boundframe);

//                    val = text_item->meta.display_boundframe;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    display_boundframe.appendChild(text);

                    //添加子项 display_height 子元素
                    item_meta.appendChild(display_height);
                    display_height.setAttribute(STR_OC_ITEM_DHEIGHT, text_item->meta.display_height);

//                    val = text_item->meta.display_height;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    display_height.appendChild(text);

                    //添加子项 uintw 子元素
                    item_meta.appendChild(uintw);
                    uintw.setAttribute(STR_OC_ITEM_UINTW, text_item->meta.uintw);

//                    val = text_item->meta.uintw;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    uintw.appendChild(text);

                    //添加子项 rotate 子元素
                    item_meta.appendChild(rotate);
                    rotate.setAttribute(STR_OC_ITEM_ROTATE, text_item->meta.rotate);

//                    val = text_item->meta.rotate;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    rotate.appendChild(text);

                    //添加子项 sec_level 子元素
                    item_meta.appendChild(sec_level);
                    sec_level.setAttribute(STR_OC_ITEM_SEC_LEVEL, text_item->meta.sec_level);

//                    val = text_item->meta.sec_level;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    sec_level.appendChild(text);

                    //添加子项 viewRect 子元素
                    //viewRect 子元素
                    item_meta.appendChild(viewRect);
                    viewRect.setAttribute("viewRect_l", text_item->meta.viewRect.left());
                    viewRect.setAttribute("viewRect_t", text_item->meta.viewRect.top());
                    viewRect.setAttribute("viewRect_w", text_item->meta.viewRect.width());
                    viewRect.setAttribute("viewRect_h", text_item->meta.viewRect.height());


                    //CoordRect 子元素
                    item_meta.appendChild(CoordRect);
                    CoordRect.setAttribute("CoordRect_l", text_item->meta.CoordRect.left());
                    CoordRect.setAttribute("CoordRect_t", text_item->meta.CoordRect.top());
                    CoordRect.setAttribute("CoordRect_w", text_item->meta.CoordRect.width());
                    CoordRect.setAttribute("CoordRect_h", text_item->meta.CoordRect.height());
                }
                break;

            case ENUM_TWOCODE_EDIT:
                {
                    DrawTwoCodeItem* text_item = qgraphicsitem_cast<DrawTwoCodeItem*>(list_items[i]);

                    //创建元素 item_e
        //                    QDomElement item_obj = doc.createElement(tr("DrawTwoCodeItem"));    //类名，即元素名字
        //                    root.appendChild(item_obj); //添加根元素

                    //创建 meta 元素
                    QDomElement item_meta = doc.createElement(STR_TC_ITEM_META);       //结构体即元素名字
                    root.appendChild(item_meta);


                    //创建 TextItemMetaPS 的子元素 name
                    QDomElement name = doc.createElement(STR_TC_ITEM_META_NAME);                                   //结构体即元素名字
                    QDomElement dataString = doc.createElement(STR_TC_ITEM_DATA);                       //结构体即元素名字
                    QDomElement ecl = doc.createElement(STR_TC_ITEM_ECL);                                   //结构体即元素名字
                    QDomElement mode = doc.createElement(STR_TC_ITEM_MODE);                       //结构体即元素名字
                    QDomElement uintw = doc.createElement(STR_TC_ITEM_UINTW);                                 //结构体即元素名字
                    QDomElement display_boundframe = doc.createElement(STR_TC_ITEM_DBF);                                 //结构体即元素名字
                    QDomElement viewRect = doc.createElement(STR_TC_ITEM_VR);                           //结构体即元素名字
                    QDomElement CoordRect = doc.createElement(STR_TC_ITEM_CR);                         //结构体即元素名字

                    //添加子项 name 子元素
                    item_meta.appendChild(name);
                    QDomText text = doc.createTextNode(text_item->meta.name);
                    name.appendChild(text);

                    //添加子项 dataString 子元素
                    item_meta.appendChild(dataString);
                    text = doc.createTextNode(text_item->meta.dataString);
                    dataString.appendChild(text);

                    //添加子项 ecl 子元素
                    item_meta.appendChild(ecl);
                    ecl.setAttribute(STR_TC_ITEM_ECL, text_item->meta.ecl);

//                    qreal val = text_item->meta.ecl;
//                    QString qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    ecl.appendChild(text);

                    //添加子项 mode 子元素
                    item_meta.appendChild(mode);
                    mode.setAttribute(STR_TC_ITEM_MODE, text_item->meta.mode);

//                    val = text_item->meta.mode;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    mode.appendChild(text);

                    //添加子项 uintw 子元素
                    item_meta.appendChild(uintw);
                    uintw.setAttribute(STR_TC_ITEM_UINTW, text_item->meta.uintw);

//                    val = text_item->meta.uintw;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    uintw.appendChild(text);

                    //添加子项 uintw 子元素
                    item_meta.appendChild(display_boundframe);
                    display_boundframe.setAttribute(STR_TC_ITEM_DBF, text_item->meta.display_boundframe);

                    //添加子项 viewRect 子元素
                    //viewRect 子元素
                    item_meta.appendChild(viewRect);
                    viewRect.setAttribute("viewRect_l", text_item->meta.viewRect.left());
                    viewRect.setAttribute("viewRect_t", text_item->meta.viewRect.top());
                    viewRect.setAttribute("viewRect_w", text_item->meta.viewRect.width());
                    viewRect.setAttribute("viewRect_h", text_item->meta.viewRect.height());


                    //CoordRect 子元素
                    item_meta.appendChild(CoordRect);
                    CoordRect.setAttribute("CoordRect_l", text_item->meta.CoordRect.left());
                    CoordRect.setAttribute("CoordRect_t", text_item->meta.CoordRect.top());
                    CoordRect.setAttribute("CoordRect_w", text_item->meta.CoordRect.width());
                    CoordRect.setAttribute("CoordRect_h", text_item->meta.CoordRect.height());

                }
                break;

            case ENUM_LINE_EDIT:
                {
                    DrawLineItem* text_item = qgraphicsitem_cast<DrawLineItem*>(list_items[i]);

                    //创建元素 item_e
        //                    QDomElement item_obj = doc.createElement(tr("DrawLineItem"));    //类名，即元素名字
        //                    root.appendChild(item_obj); //添加根元素

                    //创建 meta 元素
                    QDomElement item_meta = doc.createElement(STR_LINE_ITEM_META);       //结构体即元素名字
                    root.appendChild(item_meta);


                    //创建 TextItemMetaPS 的子元素 name
                    QDomElement name = doc.createElement(STR_LINE_ITEM_META_NAME);                                   //结构体即元素名字
                    QDomElement display_boundframe = doc.createElement(STR_LINE_ITEM_META_NAME);                       //结构体即元素名字
                    QDomElement xy_offset = doc.createElement(STR_LINE_ITEM_META_XYOFFSET);                                   //结构体即元素名字
                    QDomElement rotate = doc.createElement(STR_LINE_ITEM_META_ROTATE);                       //结构体即元素名字
                    QDomElement pen = doc.createElement(STR_LINE_ITEM_META_PEN);             //结构体即元素名字
                    QDomElement len = doc.createElement(STR_LINE_ITEM_META_LEN);               //结构体即元素名字
                    QDomElement start_point = doc.createElement(STR_LINE_ITEM_META_SP);                                 //结构体即元素名字
                    QDomElement end_point = doc.createElement(STR_LINE_ITEM_META_EP);                               //结构体即元素名字
                    QDomElement viewRect = doc.createElement(STR_LINE_ITEM_VR);                           //结构体即元素名字
                    QDomElement CoordRect = doc.createElement(STR_LINE_ITEM_CR);                         //结构体即元素名字

                    //添加子项 name 子元素
                    item_meta.appendChild(name);
                    QDomText text = doc.createTextNode(text_item->meta.name);
                    name.appendChild(text);

                    //添加子项 display_boundframe 子元素
                    item_meta.appendChild(display_boundframe);
                    display_boundframe.setAttribute(STR_LINE_ITEM_META_DBF, text_item->meta.display_boundframe);

//                    qreal val = text_item->meta.display_boundframe;
//                    QString qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    display_boundframe.appendChild(text);

                    //添加子项 xy_offset 子元素
                    item_meta.appendChild(xy_offset);
//                    qreal val = text_item->meta.xy_offset;
//                    QString qstr = QString::number(val,'val', 1);
                    xy_offset.setAttribute("xy_offset_x", text_item->meta.xy_offset.x());
                    xy_offset.setAttribute("xy_offset_y", text_item->meta.xy_offset.y());
//                    text = doc.createTextNode(qstr);
//                    xy_offset.appendChild(text);

                    //添加子项 rotate 子元素
                    item_meta.appendChild(rotate);
                    rotate.setAttribute(STR_LINE_ITEM_META_ROTATE, text_item->meta.rotate);

//                    val = text_item->meta.rotate;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    rotate.appendChild(text);

                    //添加子项 pen 子元素
                    item_meta.appendChild(pen);
//                    val = text_item->meta.pen;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
                    pen.setAttribute("pen_w", text_item->meta.pen.widthF());
                    //pen.setAttribute("pen_c", text_item->meta.pen.color());
                    pen.setAttribute("pen_l", text_item->meta.pen.style());

                    //pen.appendChild(text);

                    //添加子项 len 子元素
                    item_meta.appendChild(len);
                    len.setAttribute(STR_LINE_ITEM_META_LEN, text_item->meta.len);

//                    val = text_item->meta.len;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    len.appendChild(text);

                    //添加子项 start_point 子元素
                    item_meta.appendChild(start_point);
//                    val = text_item->meta.start_point;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    start_point.appendChild(text);
                    start_point.setAttribute("start_point_x", text_item->meta.start_point.x());
                    start_point.setAttribute("start_point_y", text_item->meta.start_point.y());

                    //添加子项 end_point 子元素
                    item_meta.appendChild(end_point);
//                    val = text_item->meta.end_point;
//                    qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    end_point.appendChild(text);
                    end_point.setAttribute("end_point_x", text_item->meta.end_point.x());
                    end_point.setAttribute("end_point_y", text_item->meta.end_point.y());


                    //添加子项 viewRect 子元素
                    //viewRect 子元素
                    item_meta.appendChild(viewRect);
                    viewRect.setAttribute("viewRect_l", text_item->meta.viewRect.left());
                    viewRect.setAttribute("viewRect_t", text_item->meta.viewRect.top());
                    viewRect.setAttribute("viewRect_w", text_item->meta.viewRect.width());
                    viewRect.setAttribute("viewRect_h", text_item->meta.viewRect.height());


                    //CoordRect 子元素
                    item_meta.appendChild(CoordRect);
                    CoordRect.setAttribute("CoordRect_l", text_item->meta.CoordRect.left());
                    CoordRect.setAttribute("CoordRect_t", text_item->meta.CoordRect.top());
                    CoordRect.setAttribute("CoordRect_w", text_item->meta.CoordRect.width());
                    CoordRect.setAttribute("CoordRect_h", text_item->meta.CoordRect.height());

                }
                break;

            case ENUM_RECT_EDIT:
                {
                    DrawRectItem* text_item = qgraphicsitem_cast<DrawRectItem*>(list_items[i]);

                    //创建元素 item_e
        //                    QDomElement item_obj = doc.createElement(tr("DrawRectItem"));    //类名，即元素名字
        //                    root.appendChild(item_obj); //添加根元素

                    //创建 meta 元素
                    QDomElement item_meta = doc.createElement(STR_RECT_ITEM_META);       //结构体即元素名字
                    root.appendChild(item_meta);


                    //创建 TextItemMetaPS 的子元素 name
                    QDomElement name = doc.createElement(STR_RECT_ITEM_META_NAME);                                   //结构体即元素名字
                    QDomElement pen = doc.createElement(STR_RECT_ITEM_META_PEN);                       //结构体即元素名字
                    QDomElement display_boundframe = doc.createElement(STR_RECT_ITEM_META_DBF);             //结构体即元素名字
                    QDomElement viewRect = doc.createElement(STR_RECT_ITEM_META_VR);                           //结构体即元素名字
                    QDomElement CoordRect = doc.createElement(STR_RECT_ITEM_META_CR);                         //结构体即元素名字

                    //添加子项 name 子元素
                    item_meta.appendChild(name);
                    QDomText text = doc.createTextNode(text_item->meta.name);
                    name.appendChild(text);

                    //添加子项 pen 子元素
                    item_meta.appendChild(pen);
//                    text = doc.createTextNode(text_item->meta.pen);
//                    pen.appendChild(text);
                    pen.setAttribute("pen_w", text_item->meta.pen.widthF());

                    //添加子项 display_boundframe 子元素
                    item_meta.appendChild(display_boundframe);
                    display_boundframe.setAttribute(STR_RECT_ITEM_META_DBF, text_item->meta.display_boundframe);

//                    qreal val = text_item->meta.display_boundframe;
//                    QString qstr = QString::number(val,'val', 1);
//                    text = doc.createTextNode(qstr);
//                    display_boundframe.appendChild(text);


                    //添加子项 viewRect 子元素
                    //viewRect 子元素
                    item_meta.appendChild(viewRect);
                    viewRect.setAttribute("viewRect_l", text_item->meta.viewRect.left());
                    viewRect.setAttribute("viewRect_t", text_item->meta.viewRect.top());
                    viewRect.setAttribute("viewRect_w", text_item->meta.viewRect.width());
                    viewRect.setAttribute("viewRect_h", text_item->meta.viewRect.height());


                    //CoordRect 子元素
                    item_meta.appendChild(CoordRect);
                    CoordRect.setAttribute("CoordRect_l", text_item->meta.CoordRect.left());
                    CoordRect.setAttribute("CoordRect_t", text_item->meta.CoordRect.top());
                    CoordRect.setAttribute("CoordRect_w", text_item->meta.CoordRect.width());
                    CoordRect.setAttribute("CoordRect_h", text_item->meta.CoordRect.height());
                }
                break;

            default:
                {

                }
                break;
        }
    }

    //文件操作
    QTextStream out(&fp);
    doc.save(out,4);            // 将文档保存到文件，4为子元素缩进字符数
    fp.close();
}

bool DrawLabel::getSaveFlag()
{
    return isSave;
}

void DrawLabel::setSaveFlag(bool ret)
{
    isSave = ret;
}

//bool DrawLabel::eventFilter(QObject *watched, QEvent *event)
//{
//    if(watched == this->wal_view)
//    {
//        qDebug("[orkAreaLabel::eventFilter]:aaaa");
//    }
//    else
//    {
//        qDebug("[orkAreaLabel::eventFilter]:bbb");


//    }
//}



/**
 * @brief DrawLabel::wal_label_create_draw_view
 *          初始化工作区的QGraphicsview，作为tabmain(label)的子窗口
 */
void DrawLabel::wal_label_create_draw_view()
{
    //创建一个视图,设置label为视图的父窗口
    wal_view = new DrawView(this);
}

/**
 * @brief DrawLabel::resizeEvent
 * 实现work area label大小改变是，同样改变scene和view的范围
 * label是视图的父窗口
 * 视图是场景的父窗口
 * 视图的坐标原定要基础label偏移（应为在label上画了一个标尺，不能遮盖标尺）
 * @param event
 */
void DrawLabel::resizeEvent(QResizeEvent *event)
{
    qDebug("[DrawLabel--%s]>>labelRect:(%f,%f,%f,%f)",__func__, meta.labelRect.left(), meta.labelRect.top(), meta.labelRect.width(), meta.labelRect.height());
    //画板label的范围
    this->setGeometry(meta.labelRect.left(), meta.labelRect.top(),  meta.labelRect.width(), meta.labelRect.height());
    //g_widget->tab_label_attr_manager->attr_label_update_item_tabmeta_widget(meta);
    //无论label多大，view不变
    wal_view->setGeometry(meta.viewRect.left(), meta.viewRect.top(),  meta.viewRect.width(), meta.viewRect.height());
}
