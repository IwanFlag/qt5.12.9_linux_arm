#include "drawlineitem.h"
#include <QCursor>
#include "main.h"
#include "qdebug.h"
#include "QString"
#include <QObject>
#include <QGraphicsSceneMouseEvent>


//默认初始化为在label中心的水平线
LineItemMetaPS line_item_meta_init =
{
    QObject::tr("line"),                            //名字
    true,
    QPointF(0.0, 0.0),                              //图元原点偏移
    0.0,                                            //旋转角度默认0
    QPen(Qt::black, 10, Qt::SolidLine),             //线条/画笔宽度,黑色,10pix像素,实线
    50,                                             //直线长度
    QPointF(50, 50),                                //起始坐标
    QPointF(100, 50),                               //结束坐标,但是实际会以设置的直线长度确定
    QRectF(0,0,0,0),                                //外接矩形暂时用不到
    QRectF(0,0,0,0)                                 //坐标矩形，宽和高暂时不用
};

DrawLineItem::DrawLineItem(QGraphicsItem *parent):
    QGraphicsLineItem(parent)
{
    qDebug("[DrawLineItem--%s]>>",__func__);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    m_bound_offset = 20;
    setAcceptHoverEvents(true);

    //初始化设置
    //名字
    line_item_meta_init.name = QObject::tr("line");

    //笔宽
    line_item_meta_init.pen.setWidthF(MM2PIX_V(LINE_ITEM_PEN_WIDTH_MM));

    //直线长度初始化,会在设置meta里面忽略终点
    line_item_meta_init.len = MM2PIX_H(LINE_ITEM_PEN_LEN_MM);


    setLineEditMeta(line_item_meta_init);
    setFocus();
}

/**
 * @brief DrawLineItem::setLineEditMeta
 * @param meta
 */
void DrawLineItem::setLineEditMeta(LineItemMetaPS meta)
{
    qDebug("[DrawLineItem--%s]>>",__func__);

    this->meta = meta;

    //设置meta后,更新meta到该item
    prepareGeometryChange();
    updateLineEditItemWidget();
}

/**
 * @brief DrawLineItem::getLineEditMeta
 * @return
 */
LineItemMetaPS DrawLineItem::getLineEditMeta()
{
    qDebug("[DrawLineItem--%s]>>",__func__);
    return this->meta;
}

/**
 * @brief DrawLineItem::updateLineEditItemWidget
 */
void DrawLineItem::updateLineEditItemWidget()
{
    LineItemMetaPS meta = this->getLineEditMeta();
    qDebug("[DrawLineItem--%s]>>name:%s",__func__, qPrintable(meta.name));
    this->setPen(meta.pen);
    QLineF linef = this->line();
    linef.setP1(mapFromScene(meta.start_point));
    linef.setP2(mapFromScene(meta.end_point));

    linef.setLength(meta.len);
    qDebug("[DrawLineItem--%s]>>meta.rotate:%d",__func__, meta.rotate);
    linef.setAngle(meta.rotate);            //设置线段基于现在的角度
    qDebug("[DrawLineItem--%s]>>angle:%d",__func__, linef.angle());

    qDebug("[DrawLineItem--%s]>>linef(%f,%f,%f,%f)",__func__, linef.p1().x(), linef.p1().y(), linef.p2().x(), linef.p2().y());
    this->setLine(linef);    //设置了长度,下面重新更新坐标
    //this->setRotation(meta.rotate);
}

/**
 * @brief DrawLineItem::updatePullBoundRect
 *      更新boundrect里面的拉伸区域,鼠标点击拉伸区域移动，可以拉伸
 * @param painter
 */
void DrawLineItem::updatePullBoundRect(QPainter *painter)
{
    QLineF lf = this->line();
    qreal adjusts;
    adjusts = (MM2PIX_H(ITEM_PULL_RECT_LEN_MM) > meta.pen.widthF()) ? MM2PIX_H(ITEM_PULL_RECT_LEN_MM) : meta.pen.widthF();


    //offset = lf.length()/4;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter->setPen(pen);


    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

//    QRectF rf = boundingRect();
//    QPointF tl_p = rf.topLeft();
//    QPointF tr_p = rf.topRight();


    QPointF lp1 = lf.p1();
    QPointF lp2 = lf.p2();

    //qDebug("[DrawLineItem--%s]>>00(%f,%f,%f,%f)",__func__, rf.x(), rf.y(), rf.width(), rf.height());
//    tl_p = mapToScene(rf.topLeft());
//    tr_p = mapToScene(rf.topRight());

    //起始区域
    m_start_rf.setLeft(lp1.x() - adjusts);
    m_start_rf.setTop(lp1.y()- adjusts);
    m_start_rf.setWidth(adjusts*2);
    m_start_rf.setHeight(adjusts*2);
    painter->drawRect(m_start_rf);
    qDebug("[DrawLineItem--%s]>>m_start_rf(%f,%f,%f,%f)",__func__, m_start_rf.x(), m_start_rf.y(), m_start_rf.bottomRight().x(), m_start_rf.bottomRight().y());

    //终点伸缩点位矩形区域
    m_end_rf.setLeft(lp2.x() - adjusts);
    m_end_rf.setTop(lp2.y()- adjusts);
    m_end_rf.setWidth(adjusts*2);
    m_end_rf.setHeight(adjusts*2);
    painter->drawRect(m_end_rf);
    qDebug("[DrawLineItem--%s]>>m_end_rf(%f,%f,%f,%f)",__func__, m_end_rf.x(), m_end_rf.y(), m_end_rf.bottomRight().x(), m_end_rf.bottomRight().y());
}

/**
 * @brief DrawLineItem::updateLineItemNowCoord
 * 因为线条移动的原因，需要在某些情景前，先获取目前的实时位置坐标，
 * 一定要映射item坐标到场景去啊maptoscene!!!这该死的温柔..
 */
void DrawLineItem::updateLineItemNowCoord()
{
    //QPointF item_pos = this->pos();
    QLineF line = this->line();
    QPointF line_p1 = line.p1();
    QPointF line_p2 = line.p2();


    //qDebug("[DrawLineItem--%s]>>item_pos(%f,%f)",__func__, item_pos.x(), item_pos.y());
    qDebug("[DrawLineItem--%s]>>line_p1(%f,%f)",__func__, line_p1.x(), line_p1.y());
    qDebug("[DrawLineItem--%s]>>line_p2(%f,%f)",__func__, line_p2.x(), line_p2.y());


    //这才是真实的item在scene的起始和终点坐标
    //item_pos = mapToScene(item_pos);
    line_p1 = mapToScene(line_p1);
    line_p2 = mapToScene(line_p2);

    meta.start_point.setX(line_p1.x());
    meta.start_point.setY(line_p1.y());

    meta.end_point.setX(line_p2.x());
    meta.end_point.setY(line_p2.y());

    meta.CoordRect.setLeft(meta.start_point.x());
    meta.CoordRect.setTop(meta.start_point.y());

    //qDebug("[DrawLineItem--%s]>>mapToScene-item_pos(%f,%f)",__func__, item_pos.x(), item_pos.y());
    qDebug("[DrawLineItem--%s]>>mapToScene-line_p1(%f,%f)",__func__, line_p1.x(), line_p1.y());
    qDebug("[DrawLineItem--%s]>>mapToScene-line_p2(%f,%f)",__func__, line_p2.x(), line_p2.y());
}

/**
 * @brief DrawLineItem::itemChangedUpdateMetaAndTabWidget
 *              鼠标释放事件处理函数
 * @param event
 */
void DrawLineItem::itemChangedUpdateMetaAndTabWidget()
{
    updateLineItemNowCoord();                        //因为场景是释放事件才显示
    g_widget->line_item_select = this;
    g_widget->tab_line_attr_manager->attr_line_update_item_tabmeta_widget(this->meta);
}

QRectF DrawLineItem::boundingRect() const
{
    //qDebug("[DrawLineItem--%s]>>",__func__);

    QRectF rc = QGraphicsLineItem::boundingRect();
    qreal adjusts;
    adjusts = (MM2PIX_H(ITEM_PULL_RECT_LEN_MM) > meta.pen.widthF()) ? MM2PIX_H(ITEM_PULL_RECT_LEN_MM) : meta.pen.widthF();
    //qDebug("[DrawLineItem--%s]>>adjusts:%f",__func__, adjusts);

    //    rc.adjust(-meta.pen.widthF(), -meta.pen.widthF(), meta.pen.widthF(), meta.pen.widthF());
    rc.adjust(-adjusts, -adjusts, adjusts, adjusts);
    return rc;      //注意不同的参数的区别
//    return QGraphicsLineItem::boundingRect();
}

QPainterPath DrawLineItem::shape() const
{
//    qDebug("[DrawLineItem--%s]>>",__func__);

    //return QGraphicsLineItem::shape();
//    QPainterPath path;
//    path.addRect(DrawLineItem::boundingRect());
//    return path;


    qreal w = meta.pen.widthF()*2;
    //w *= 1.414;                 //我也不知道维萨要乘以1.414
    QPainterPath path = QGraphicsLineItem::shape();
    QPainterPathStroker stroker;
    stroker.setWidth(w);
    path = stroker.createStroke(path);
    return path;
}

bool DrawLineItem::contains(const QPointF &point) const
{
    return QGraphicsLineItem::contains(point);
}

void DrawLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //qDebug("[DrawLineItem--%s]>>",__func__);
    //设置旋转中心为图元的中心,否则会item坐标原点
//    QPointF centerPos = this->boundingRect().center();
//    this->setTransformOriginPoint(centerPos);
    if(meta.display_boundframe)
    {
        if(hasFocus())
        {
            updatePullBoundRect(painter);                      //显示绘画的Boundrect
        }
    }

    //painter->drawPath(shape());


//    QStyleOptionGraphicsItem op;
//    op.initFrom(widget);
//    op.state = QStyle::State_None;
//    painter->drawLine();
    QGraphicsLineItem::paint(painter, option, widget);
}

bool DrawLineItem::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsLineItem::isObscuredBy(item);
}

QPainterPath DrawLineItem::opaqueArea() const
{
    return QGraphicsLineItem::opaqueArea();
}

int DrawLineItem::type() const
{
    //return QGraphicsLineItem::type();
    return Type;
}

QPen DrawLineItem::pen() const
{
    return QGraphicsLineItem::pen();
}

void DrawLineItem::setPen(const QPen &pen)
{
    return QGraphicsLineItem::setPen(pen);
}

QLineF DrawLineItem::line() const
{
    return QGraphicsLineItem::line();
}

void DrawLineItem::setLine(const QLineF &line)
{
    return QGraphicsLineItem::setLine(line);
}

void DrawLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("[DrawLineItem--%s]>>",__func__);
    if(m_e_pulling_flag)
    {
        qDebug("[DrawLineItem--%s]>>终点正在伸缩", __func__);
        this->meta.end_point = mapToScene(event->pos());
    }
    else if(m_s_pulling_flag)
    {
        qDebug("[DrawLineItem--%s]>>起点正在伸缩", __func__);
        this->meta.start_point = mapToScene(event->pos());
    }
    else
    {
        QGraphicsLineItem::mouseMoveEvent(event);
    }
}

void DrawLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pf = event->pos();

    qDebug("[DrawLineItem--%s]>>鼠标点击,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_start_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>鼠标点击在了 m_start_rf 范围内",__func__);
        m_s_pulling_flag = true;
    }
    else if(m_end_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>鼠标点击在了 m_end_rf 范围内",__func__);
        m_e_pulling_flag = true;
    }
    else
    {
        setCursor(Qt::SizeAllCursor);                      //恢复箭头
        QGraphicsLineItem::mousePressEvent(event);
    }
}

void DrawLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawLineItem--%s]>>",__func__);
    updateLineItemNowCoord();                        //因为场景是释放事件才显示


    setCursor(Qt::ArrowCursor);                      //恢复箭头


    if(m_e_pulling_flag || m_s_pulling_flag)
    {
        QPointF mouse_scene_p = mapToScene(event->pos());
        QLineF linef = this->line();
        qDebug("[DrawLineItem--%s]>>linef(%f,%f,%f,%f)",__func__, linef.p1().x(), linef.p1().y(), linef.p2().x(), linef.p2().y());

        QPointF linef_scene_p1 = mapToScene(linef.p1());
        QPointF linef_scene_p2 = mapToScene(linef.p2());


        qDebug("[DrawLineItem--%s]>>linef_scene_p1(%f,%f)",__func__, linef_scene_p1.x(), linef_scene_p1.y());
        qDebug("[DrawLineItem--%s]>>linef_scene_p2(%f,%f)",__func__, linef_scene_p2.x(), linef_scene_p2.y());


        //if(linef_scene_p1.x() == linef_scene_p2.x())
        qDebug("[DrawLineItem--%s]>>linef.angle:(%f,%d)",__func__, linef.angle(), linef_scene_p1.x() == linef_scene_p2.x());
        //qFuzzyCompare 浮点比较接口
        //if(linef.angle() == 90 || linef.angle() == 270)


        if(m_e_pulling_flag)
        {
            if(qFuzzyCompare(linef_scene_p1.x(), linef_scene_p2.x()))
            {
                //垂直线
                qDebug("[DrawLineItem--%s]>>垂直线",__func__);
                this->meta.end_point.setX(linef_scene_p1.x());           //只做垂直拉伸
                this->meta.end_point.setY(mouse_scene_p.y());           //只做垂直拉伸
            }
            else
            {
                //水平线
                qDebug("[DrawLineItem--%s]>>水平线",__func__);
                this->meta.end_point.setX(mouse_scene_p.x());           //只做水平拉伸
                this->meta.end_point.setY(linef_scene_p1.y());           //只做垂直拉伸
            }
            qDebug("[DrawLineItem--%s]>>this->meta.end_point(%f,%f)",__func__, this->meta.end_point.x(), this->meta.end_point.y());
            m_e_pulling_flag = false;
            linef.setP1(mapFromScene(linef_scene_p1));
            linef.setP2(mapFromScene(meta.end_point));
        }


        if(m_s_pulling_flag)
        {
            if(qFuzzyCompare(linef_scene_p1.x(), linef_scene_p2.x()))
            {
                //垂直线
                qDebug("[DrawLineItem--%s]>>垂直线",__func__);
                this->meta.start_point.setX(linef_scene_p2.x());           //只做垂直拉伸
                this->meta.start_point.setY(mouse_scene_p.y());           //只做垂直拉伸
            }
            else
            {
                //水平线
                qDebug("[DrawLineItem--%s]>>水平线",__func__);
                this->meta.start_point.setX(mouse_scene_p.x());           //只做水平拉伸
                this->meta.start_point.setY(linef_scene_p2.y());           //只做垂直拉伸
            }
            //qDebug("[DrawLineItem--%s]>>this->meta.end_point(%f,%f)",__func__, this->meta.end_point.x(), this->meta.end_point.y());
            m_s_pulling_flag = false;
            linef.setP1(mapFromScene(meta.start_point));
            linef.setP2(mapFromScene(linef_scene_p2));

        }
        meta.len = linef.length();
        this->setLine(linef);
    }

    itemChangedUpdateMetaAndTabWidget();
    QGraphicsLineItem::mouseReleaseEvent(event);
}

void DrawLineItem::keyPressEvent(QKeyEvent *event)
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
    QGraphicsLineItem::keyPressEvent(event);
}

void DrawLineItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsLineItem::keyReleaseEvent(event);
}

void DrawLineItem::focusInEvent(QFocusEvent *event)
{
    qDebug("[DrawLineItem--%s]焦点进入>>",__func__);
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsLineItem::focusInEvent(event);
}

void DrawLineItem::focusOutEvent(QFocusEvent *event)
{
    qDebug("[DrawLineItem--%s]>>焦点出去",__func__);

    QGraphicsLineItem::focusOutEvent(event);
}

void DrawLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pf = event->pos();
    //QPointF pf = QGraphicsItem::mapFromScene(event->pos());

    qDebug("[DrawLineItem--%s]>>悬浮进来,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_start_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>悬浮在了 m_start_rf 范围内",__func__);
        if(meta.rotate == 90 || meta.rotate == 270)
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::SizeHorCursor);
    }
    else if(m_end_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>悬浮在了 m_end_rf 范围内",__func__);
        if(meta.rotate == 90 || meta.rotate == 270)
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::SizeHorCursor);    }
    else
    {
        setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
    }
}

void DrawLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pf = event->pos();      //这他么的是item坐标
    //QPointF pf = QGraphicsItem::mapFromScene(event->pos());

    qDebug("[DrawLineItem--%s]>>悬浮移动,pf:(%f,%f)",__func__, pf.x(), pf.y());
    if(m_start_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>悬浮移动在了 m_start_rf 范围内",__func__);
        if(meta.rotate == 90 || meta.rotate == 270)
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::SizeHorCursor);    }
    else if(m_end_rf.contains(pf))
    {
        qDebug("[DrawLineItem--%s]>>悬浮移动在了 m_end_rf 范围内",__func__);
        if(meta.rotate == 90 || meta.rotate == 270)
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::SizeHorCursor);    }
    else
    {
        setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
    }
}

void DrawLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("[DrawLineItem--%s]>>悬浮离开",__func__);

}

bool DrawLineItem::supportsExtension(QGraphicsItem::Extension extension) const
{
    return QGraphicsLineItem::supportsExtension(extension);
}

void DrawLineItem::setExtension(QGraphicsItem::Extension extension, const QVariant &variant)
{
    QGraphicsLineItem::setExtension(extension, variant);
}

QVariant DrawLineItem::extension(const QVariant &variant) const
{
    return QGraphicsLineItem::extension(variant);
}

