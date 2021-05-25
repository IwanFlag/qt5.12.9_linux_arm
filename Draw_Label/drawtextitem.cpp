#include "drawtextitem.h"
#include <QFont>
#include <QPen>
#include <QPainter>
#include <main.h>
#include <QPlainTextEdit>
#include "common_def.h"


//初始化此item的属性框
TextItemMetaPS text_meta_init_val =
{
    QObject::tr("text"),                                //名字
    "hello soudian",                                //内容
    GRAPHIC_FONT_HEIGHT_INDEX_8,                //高度,打印机默认的是10号字体,mmp
    false,                                       //isbold
    false,                                       //isunderline
    false,                                       //inverse_white
    0,                                           //rotate,默认0不旋转
    MAG_INDEX_1,                                 //字符宽度放大系数
    MAG_INDEX_1,                                 //字符高度放大系数
    QRectF(0,0,0,0),              //显示范围
    QRectF(0,0,0,0)               //显示范围
};


/**
 * @brief DrawTextItem::DrawTextItem
 * 构造函数
 * @param parent
 */
DrawTextItem::DrawTextItem(QGraphicsTextItem *parent)
    :QGraphicsTextItem(parent)
{
    qDebug("[DrawTextItem:%s]",__func__);
    this->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    //setTextInteractionFlags(Qt::TextEditorInteraction); //设置为编辑框模式,等同QPlainTextEdit 的效果
    setAcceptDrops(true);                               //支持拖拽

    //初始化
    //名字
    text_meta_init_val.name = QObject::tr("text");

    //内容
    text_meta_init_val.dataString = QObject::tr("hello soudian");

    //坐标矩形
    text_meta_init_val.CoordRect.setX(MM2PIX_H(TEXT_ITEM_X_MM));
    text_meta_init_val.CoordRect.setY(MM2PIX_V(TEXT_ITEM_Y_MM));
    text_meta_init_val.CoordRect.setWidth(MM2PIX_H(TEXT_ITEM_W_MM));
    text_meta_init_val.CoordRect.setHeight(MM2PIX_V(TEXT_ITEM_H_MM));

    this->setTextEditMeta(text_meta_init_val);
    setFocus();
}

/**
 * @brief DrawTextItem::boundingRect
 *      重载外接矩形（绘图区域，刷新区域，如果图形超过这个区域，超出部分系统不自动刷新）
 * @return
 */
QRectF DrawTextItem::boundingRect() const
{
    //qDebug("[DrawTextItem:%s]",__func__);
    return QGraphicsTextItem::boundingRect();
}

/**
 * @brief DrawTextItem::paint
 * 绘画事件
 * @param painter
 * @param option
 * @param widget
 */
void DrawTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    qDebug("[DrawTextItem:%s]",__func__);
    QGraphicsTextItem::paint(painter,  option,widget);
}

/**
 * @brief DrawTextItem::shape
 *返回的图形如果有效，就是鼠标事件响应的区域，如果无效，则是外接矩形的区域
 *这里是text文本，有效区域返回的是一个矩形，拖动边框才有效
 * @return
 */
QPainterPath DrawTextItem::shape() const
{
    return QGraphicsTextItem::shape();
}

bool DrawTextItem::contains(const QPointF &point) const
{
    return QGraphicsTextItem::contains(point);
}

bool DrawTextItem::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsTextItem::isObscuredBy(item);
}

QPainterPath DrawTextItem::opaqueArea() const
{
    return QGraphicsTextItem::opaqueArea();
}

int DrawTextItem::type() const
{
    //return QGraphicsTextItem::type();
    return  Type;
}

/**
 * @brief DrawTextItem::setTextEditMeta
 * 设置图元的属性,一般是从属性框取值，往图元设置或者是初始化对象时设置一下
 * @param item      传入的item
 * @param meta
 */
void DrawTextItem::setTextEditMeta(TextItemMetaPS meta)
{
    //1.把属性同步
    this->meta = meta;
    qDebug("[DrawTextItem--%s]>>viewRect:(%f,%f,%f,%f)", __FUNCTION__,meta.viewRect.left(), meta.viewRect.top(), meta.viewRect.width(), meta.viewRect.height());


    updateTextEditItemWidget();
}

/**
 * @brief DrawTextItem::getTextEditMeta
 * 返回某个item的meta属性值
 * @param item
 * @return
 */
TextItemMetaPS DrawTextItem::getTextEditMeta()
{
    return this->meta;
}

/**
 * @brief DrawTextItem::updateTextEditMeta
 *          根据meta，更新item在画布界面的图形显示（区别tab）
 * @param item
 * @return
 */
void DrawTextItem::updateTextEditItemWidget()
{
    //初始化item
    TextItemMetaPS meta = this->getTextEditMeta();
    qDebug("[DrawTextItem--%s]>>name:%s, dataString:%s", __func__, qPrintable(meta.name), qPrintable(meta.dataString));

    //更新item的内容
    this->setPlainText(meta.dataString);

    //字体
    QFont ft;
    //ft.setPointSize(g_text_font_height[meta.height]);
    ft.setPointSize(g_text_font_height[meta.height]);
    ft.setBold(meta.isbold);
    ft.setUnderline(meta.isunderline);
    this->setFont(ft);

    //更新显示的位置
    this->setPos(meta.CoordRect.left(), meta.CoordRect.top());

}

/**
 * @brief DrawTextItem::getTextItemFontType
 *   获取协议所需要的FONTTYPE
     * FontType位	定义
            [0]	字体加粗
            [1]	下划线
            [2]	反白标志位，置 1 位图反白打印，清零正常打印。
            [3]	保留
            [4]	旋转标志位： 0 旋转 0° ； 1 旋转 90°；
            [7:5]	保留。
            [11:8]	位图宽度放大倍数。
            [15:12]	位图高度放大倍数。
 * @return
 */
qint16 DrawTextItem::getTextItemFontType()
{
    qint16 ft = 0x0000;
    TextItemMetaPS meta = this->getTextEditMeta();
    qDebug("[DrawTextItem--%s]>>name:%s", __func__, qPrintable(meta.name));

    if(meta.isbold)
    {
        //b0置位为1
        ft |= 0x0001;
        qDebug("[DrawTextItem--%s]>>isbold,ft:%02x", __func__, ft);
    }

    if(meta.isunderline)
    {
        //b1置位为1

        ft |= 0x0002;
        qDebug("[DrawTextItem--%s]>>isunderline,ft:%02x", __func__, ft);

    }

    if(meta.inverse_white)
    {
        //b2置位为1

        ft |= 0x0004;
        qDebug("[DrawTextItem--%s]>>inverse_white,ft:%02x", __func__, ft);

    }

    if(meta.rotate)
    {
        //b4置位为1
        ft |= 0x0010;
        qDebug("[DrawTextItem--%s]>>rotate,ft:%02x", __func__, ft);

    }
    qDebug("[DrawTextItem--%s]>>all,ft:%02x", __func__, ft);

    return ft;
}

/**
 * @brief DrawTextItem::itemChangedUpdateMetaAndTabWidget
 * 在item在画板变换后，例如鼠标或者按键位移后,及时更新目前的meta和tab框
 */
void DrawTextItem::itemChangedUpdateMetaAndTabWidget()
{
    qDebug("[DrawTextItem--%s]>>", __func__);
    updateTextItemNowCoord();
    g_widget->text_item_select = this;
    g_widget->tab_text_attr_manager->attr_text_update_item_tabmeta_widget(this->meta);
}

void DrawTextItem::updateTextItemNowCoord()
{
    //2.同步坐标,先获取在main的实际坐标,同步到meta变量中,这样meta才会更新
    QPointF item_pos = this->pos();
    this->meta.CoordRect.setLeft(item_pos.x());
    this->meta.CoordRect.setTop(item_pos.y());
    qDebug("[AttrTextTabWidget--%s]>>item_pos:(%f,%f)", __FUNCTION__,item_pos.x(),item_pos.y());


    //宽和高一直在变化,脑壳大,可以获取boundrect试试
    QRectF br = this->boundingRect();
    qDebug("[AttrTextTabWidget--%s]>>br:(%f,%f,%f,%f)", __FUNCTION__,br.left(), br.top(), br.width(), br.height());
    this->meta.CoordRect.setWidth(br.width());
    this->meta.CoordRect.setHeight(br.height());
    qDebug("[DrawTextItem--%s]>>22viewRect:(%f,%f,%f,%f)", __FUNCTION__,this->meta.viewRect.left(), meta.viewRect.top(), this->meta.viewRect.width(), this->meta.viewRect.height());
}

bool DrawTextItem::sceneEvent(QEvent *event)
{
    return QGraphicsTextItem::sceneEvent(event);
}

void DrawTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF ps = this->scenePos();          //获取此item在场景中的坐标
    qDebug("[DrawTextItem--%s]:ps(%0.2f,%0.2f)",__func__,ps.x(),ps.y());
    setCursor(Qt::SizeAllCursor);
    QGraphicsTextItem::mousePressEvent(event);
}

void DrawTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("[DrawTextItem--%s]>>", __func__);
    setCursor(Qt::SizeAllCursor);
    QGraphicsTextItem::mouseMoveEvent(event);
}

void DrawTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawTextItem--%s]>>", __func__);
    setCursor(Qt::ArrowCursor);
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsTextItem::mouseReleaseEvent(event);
}

void DrawTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void DrawTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsTextItem::contextMenuEvent(event);
}

void DrawTextItem::keyPressEvent(QKeyEvent *event)
{
    int offset = 10;            //默认是10pix


    if (event->modifiers() & Qt::ControlModifier)
    {
        //如果是ctrl组合键,移动1pix
        offset = 1;
    }

    if (event->key() == Qt::Key_Up)
    {
        meta.CoordRect.setY(meta.CoordRect.y() - offset);
        this->setPos(meta.CoordRect.x(), meta.CoordRect.y());
    }
    else if (event->key() == Qt::Key_Down)
    {
        meta.CoordRect.setY(meta.CoordRect.y() + offset);
        this->setPos(meta.CoordRect.x(), meta.CoordRect.y());

    }
    else if (event->key() == Qt::Key_Left)
    {
        meta.CoordRect.setX(meta.CoordRect.x() - offset);
        this->setPos(meta.CoordRect.x(), meta.CoordRect.y());
    }
    else if (event->key() == Qt::Key_Right)
    {
        meta.CoordRect.setX(meta.CoordRect.x() + offset);
        this->setPos(meta.CoordRect.x(), meta.CoordRect.y());
    }

    //delete,删除图元
    if (event->key() == Qt::Key_Delete)
    {
        this->scene()->removeItem(this);
//        delete this;
    }


    itemChangedUpdateMetaAndTabWidget();
    QGraphicsTextItem::keyPressEvent(event);
}

void DrawTextItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyReleaseEvent(event);
}

void DrawTextItem::focusInEvent(QFocusEvent *event)
{
    g_widget->text_item_select = this;
    g_widget->tab_text_attr_manager->attr_text_update_item_tabmeta_widget(this->meta);
    QGraphicsTextItem::focusInEvent(event);
}

void DrawTextItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusOutEvent(event);
}

void DrawTextItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsTextItem::dragEnterEvent(event);
}

void DrawTextItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsTextItem::dragLeaveEvent(event);
}

void DrawTextItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsTextItem::dragMoveEvent(event);
}

void DrawTextItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsTextItem::dropEvent(event);
}

void DrawTextItem::inputMethodEvent(QInputMethodEvent *event)
{
    QGraphicsTextItem::inputMethodEvent(event);
}

void DrawTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsTextItem::hoverEnterEvent(event);
}

void DrawTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsTextItem::hoverMoveEvent(event);
}

void DrawTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsTextItem::hoverLeaveEvent(event);
}

QVariant DrawTextItem::inputMethodQuery(Qt::InputMethodQuery query) const
{
    return QGraphicsTextItem::inputMethodQuery(query);
}

bool DrawTextItem::supportsExtension(QGraphicsItem::Extension extension) const
{
    return QGraphicsTextItem::supportsExtension(extension);
}

void DrawTextItem::setExtension(QGraphicsItem::Extension extension, const QVariant &variant)
{
    QGraphicsTextItem::setExtension(extension, variant);
}

QVariant DrawTextItem::extension(const QVariant &variant) const
{
    return QGraphicsTextItem::extension(variant);
}


