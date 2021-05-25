#include "drawrectitem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include "main.h"
#include <QGraphicsSceneMouseEvent>


RectItemMeta rect_item_init =
{
    QObject::tr("rect"),
    QPen(Qt::black, 0, Qt::SolidLine),     //线条/画笔宽度,黑色,10pix像素,实线
    QRectF(0,0,0,0),                              //显示范围
    QRectF(0,0,0,0),                              //坐标矩形
    true
};

/**
 * @brief DrawRectItem::DrawRectItem
 *构造函数
 * @param parent
 */
DrawRectItem::DrawRectItem(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    qDebug("[DrawRectItem--%s]:%s", __func__, "create a rect");
    this->setFlags(QGraphicsRectItem::ItemIsMovable|QGraphicsRectItem::ItemIsSelectable | QGraphicsRectItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);           //支持悬浮事件

    //初始化设置
    //名字
    rect_item_init.name = QObject::tr("rect");

    //笔宽
    rect_item_init.pen.setWidthF(MM2PIX_H(RECT_ITEM_PEN_WIDTH_MM));

    //坐标矩形
    rect_item_init.CoordRect.setX(MM2PIX_H(RECT_ITEM_BOUNDRECT_X_MM));
    rect_item_init.CoordRect.setY(MM2PIX_V(RECT_ITEM_BOUNDRECT_Y_MM));
    rect_item_init.CoordRect.setWidth(MM2PIX_H(RECT_ITEM_BOUNDRECT_W_MM));
    rect_item_init.CoordRect.setHeight(MM2PIX_V(RECT_ITEM_BOUNDRECT_H_MM));

    setRectMeta(rect_item_init);
    setFocus();
}

QRectF DrawRectItem::boundingRect() const
{
//   return QGraphicsRectItem::boundingRect();
    qreal adjusts;
    adjusts = (MM2PIX_H(ITEM_PULL_RECT_LEN_MM) > meta.pen.widthF()) ? MM2PIX_H(ITEM_PULL_RECT_LEN_MM) : meta.pen.widthF();

    QRectF rc = QGraphicsRectItem::boundingRect();
//    rc.adjust(-meta.pen.widthF(), -meta.pen.widthF(), meta.pen.widthF(), meta.pen.widthF());
    rc.adjust(-adjusts, -adjusts, adjusts, adjusts);
    return rc;      //注意不同的参数的区别
}

QPainterPath DrawRectItem::shape() const
{
    //return QGraphicsRectItem::shape();
    QPainterPath path;
    path.addRect(DrawRectItem::boundingRect());
    return path;
}

bool DrawRectItem::contains(const QPointF &point) const
{
    return QGraphicsRectItem:: contains(point);
}

void DrawRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(meta.display_boundframe)
    {
        if(hasFocus())
        {
            updatePullBoundRect(painter);                      //显示拉伸点
        }
    }

    //获取目前实际rect范围
    QRectF rf = this->rect();


    QGraphicsRectItem::paint(painter, option, widget);
}

bool DrawRectItem::isObscuredBy(const QGraphicsItem *item) const
{
    qDebug("[DrawRectItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::isObscuredBy(item);

}

QPainterPath DrawRectItem::opaqueArea() const
{
    qDebug("[DrawRectItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::opaqueArea();
}

/**
 * @brief DrawRectItem::type
 * 自定义的一定要改写这里
 * @return
 */
int DrawRectItem::type() const
{
    //return QGraphicsRectItem::type();
    return  Type;
}

void DrawRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug("[DrawRectItem--%s]:", __FUNCTION__);
    if(m_top_left_flag)
    {
        qDebug("[DrawLineItem--%s]>>左上角正在伸缩", __func__);
        if(event->pos().x() < m_press_rect.bottomRight().x()
                && event->pos().y() < m_press_rect.bottomRight().y())
        {
            this->meta.CoordRect.setTopLeft(event->pos());
            this->meta.CoordRect.setBottomRight(m_press_rect.bottomRight());
            this->setRect(meta.CoordRect.x(), meta.CoordRect.y(), meta.CoordRect.width(), meta.CoordRect.height());
        }
    }
    else if(m_bottom_right_flag)
    {
        qDebug("[DrawLineItem--%s]>>右下角正在伸缩", __func__);
        if(event->pos().x() > m_press_rect.x()
                && event->pos().y() > m_press_rect.y())
        {
            this->meta.CoordRect.setBottomRight(event->pos());
            this->meta.CoordRect.setTopLeft(m_press_rect.topLeft());
            this->setRect(meta.CoordRect.x(), meta.CoordRect.y(), meta.CoordRect.width(), meta.CoordRect.height());
        }
        }
    else
    {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void DrawRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pf = event->pos();      //这他么的是item坐标

    qDebug("[DrawRectItem--%s]>>鼠标点击,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_top_left.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>鼠标点击在了 m_top_left 范围内",__func__);
        m_top_left_flag = true;
        m_press_rect = this->rect();
    }
    else if(m_bottom_right.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>鼠标点击在了 m_bottom_right 范围内",__func__);
        m_bottom_right_flag = true;
        m_press_rect = this->rect();

    }
    else
    {
        setCursor(Qt::SizeAllCursor);
        QGraphicsRectItem::mousePressEvent(event);
    }
}

void DrawRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawRectItem--%s]:", __FUNCTION__);
    //setCursor(QCursor(Qt::OpenHandCursor));
    m_top_left_flag = false;
    m_bottom_right_flag = false;
    itemChangedUpdateMetaAndTabWidget();
    setCursor(Qt::ArrowCursor);
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void DrawRectItem::keyPressEvent(QKeyEvent *event)
{
    int offset = 10;            //默认是10pix


    if (event->modifiers() & Qt::ControlModifier)
    {
        //如果是ctrl组合键,移动1pix
        offset = 1;
    }

    if (event->key() == Qt::Key_Up)
    {
        this->moveBy(0, -offset);
        event->setAccepted(true);
    }
    else if (event->key() == Qt::Key_Down)
    {
        this->moveBy(0, offset);
        event->setAccepted(true);
    }
    else if (event->key() == Qt::Key_Left)
    {
        this->moveBy(-offset, 0);
        event->setAccepted(true);
    }
    else if (event->key() == Qt::Key_Right)
    {
        this->moveBy(offset, 0);
        event->setAccepted(true);
    }

    //delete,删除图元
    if (event->key() == Qt::Key_Delete)
    {
        this->scene()->removeItem(this);
//        delete this;
    }


    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::keyPressEvent(event);
}

void DrawRectItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsRectItem::keyReleaseEvent(event);
}

void DrawRectItem::focusInEvent(QFocusEvent *event)
{
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::focusInEvent(event);
}

void DrawRectItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsRectItem::focusOutEvent(event);
}

void DrawRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pf = event->pos();
    //QPointF pf = QGraphicsItem::mapFromScene(event->pos());

    qDebug("[DrawRectItem--%s]>>悬浮进来,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_top_left.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>悬浮在了 m_top_left 范围内",__func__);
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(m_bottom_right.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>悬浮在了 m_bottom_right 范围内",__func__);
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
    }
}

void DrawRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pf = event->pos();      //这他么的是item坐标

    qDebug("[DrawRectItem--%s]>>悬浮移动,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_top_left.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>悬浮移动在了 m_top_left 范围内",__func__);
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(m_bottom_right.contains(pf))
    {
        qDebug("[DrawRectItem--%s]>>悬浮移动在了 m_bottom_right 范围内",__func__);
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
    }
}

void DrawRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("[DrawRectItem--%s]>>悬浮离开",__func__);

}

bool DrawRectItem::supportsExtension(QGraphicsRectItem::Extension extension) const
{
    return QGraphicsRectItem::supportsExtension(extension);
}

void DrawRectItem::setExtension(QGraphicsRectItem::Extension extension, const QVariant &variant)
{
    QGraphicsRectItem::setExtension(extension, variant);
}

QVariant DrawRectItem::extension(const QVariant &variant) const
{
    return QGraphicsRectItem::extension(variant);
}

/**
 * @brief DrawRectItem::showDrawRect
 *      画外接矩形框
 * @param painter
 */
void DrawRectItem::showDrawRect(QPainter *painter)
{
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
}

/**
 * @brief DrawRectItem::setRectMeta
 *              设置属性
 * @param item
 * @param meta
 */
void DrawRectItem::setRectMeta(RectItemMeta meta)
{
    this->meta = meta;

    updateRectItemWdiget();
}

/**
 * @brief DrawRectItem::getRectMeta
 * @return
 */
RectItemMeta DrawRectItem::getRectMeta()
{
    qDebug("[DrawRectItem--%s]>>", __func__);
    return this->meta;
}

/**
 * @brief DrawRectItem::updateRectItemWdiget
 *              根据目前的meta，更新item在主界面的显示
 * @param item
 * @return
 */
void DrawRectItem::updateRectItemWdiget()
{
    qDebug("[DrawRectItem--%s]>>", __func__);

    //1.根据实时坐标(可能是移动造成的实际坐标变化),先同步到meta，设置item位置
    this->setPen(meta.pen);
    QPointF tl_map = meta.CoordRect.topLeft();
    tl_map = mapFromScene(tl_map);

    this->setRect(tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());      //不需要设置其它的
    qDebug("[DrawRectItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __func__,
           tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());


    //主动更新界面一次
    update();
}

/**
 * @brief DrawRectItem::itemChangedUpdateMetaAndTabWidget
 *              鼠标释放事件处理函数
 * @param event
 */
void DrawRectItem::itemChangedUpdateMetaAndTabWidget()
{
    qDebug("[DrawRectItem--%s]>>", __func__);
    updateRectItemNowCoord();
    g_widget->rect_item_select = this;
    g_widget->tab_rect_attr_manager->attr_rect_update_item_tabmeta_widget(this->meta);
}

void DrawRectItem::updateRectItemNowCoord()
{
    qDebug("[DrawRectItem--%s]>>", __func__);
    QRectF rf = this->rect();       //获取目前rect的实际位置
    QPointF pf_tl = rf.topLeft();
    QPointF pf_br = rf.bottomRight();


    qDebug("[DrawRectItem--%s]>>pf_tl:(%f,%f)", __FUNCTION__,pf_tl.x(), pf_tl.y());
    QPointF pf_tl_map = mapToScene(pf_tl);
    QPointF pf_br_map = mapToScene(pf_br);


    meta.CoordRect.setTopLeft(pf_tl_map);       //设置左上角
    //meta.CoordRect.setWidth(rf.width());
    //meta.CoordRect.setHeight(rf.height());
    meta.CoordRect.setBottomRight(pf_br_map);

    qDebug("[DrawRectItem--%s]>>pf_tl_map:(%f,%f)", __FUNCTION__,pf_tl_map.x(), pf_tl_map.y());
    qDebug("[DrawRectItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __FUNCTION__,
                                                                   meta.CoordRect.x(),
                                                                   meta.CoordRect.y(),
                                                                   meta.CoordRect.width(),
                                                                   meta.CoordRect.height()
                                                                   );

   //this->scene()->update();         //刷新下场景,否则可能是之前画的区域在后面绘图变小后，没有把之前的擦除掉
}


/**
 * @brief DrawRectItem::updatePullBoundRect
 *      更新boundrect里面的拉伸区域,鼠标点击拉伸区域移动，可以拉伸
 * @param painter
 */
void DrawRectItem::updatePullBoundRect(QPainter *painter)
{
    QRectF rf = this->rect();
    qreal adjusts;
    adjusts = (MM2PIX_H(ITEM_PULL_RECT_LEN_MM) > meta.pen.widthF()) ? MM2PIX_H(ITEM_PULL_RECT_LEN_MM) : meta.pen.widthF();


    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter->setPen(pen);


    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);


    QPointF tlp = rf.topLeft();
    QPointF brp = rf.bottomRight();

    //qDebug("[DrawRectItem--%s]>>00(%f,%f,%f,%f)",__func__, rf.x(), rf.y(), rf.width(), rf.height());
//    tl_p = mapToScene(rf.topLeft());
//    tr_p = mapToScene(rf.topRight());

    //起始区域
    m_top_left.setLeft(tlp.x() - adjusts);
    m_top_left.setTop(tlp.y()- adjusts);
    m_top_left.setWidth(adjusts*2);
    m_top_left.setHeight(adjusts*2);
    painter->drawRect(m_top_left);
    qDebug("[DrawRectItem--%s]>>m_top_left(%f,%f,%f,%f)",__func__, m_top_left.x(), m_top_left.y(), m_top_left.bottomRight().x(), m_top_left.bottomRight().y());

    //终点伸缩点位矩形区域
    m_bottom_right.setLeft(brp.x() - adjusts);
    m_bottom_right.setTop(brp.y()- adjusts);
    m_bottom_right.setWidth(adjusts*2);
    m_bottom_right.setHeight(adjusts*2);
    painter->drawRect(m_bottom_right);
    qDebug("[DrawRectItem--%s]>>m_end_rf(%f,%f,%f,%f)",__func__, m_bottom_right.x(), m_bottom_right.y(), m_bottom_right.bottomRight().x(), m_bottom_right.bottomRight().y());
}
