#include "drawtwocodeitem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include "main.h"
#include "common_fun.h"


TwoCodeItemMeta twocode_item_init =
{
    QObject::tr("twocode"),
    "hello soudian",
    GRAPHIC_TWOCODE_ECLEVEL_Q,              //容错等级
    GRAPHIC_TWOCODE_MODE_8,                 //编码模式
    QRectF(0, 0, 0, 0),                     //显示范围
    QRectF(0,0,0,0),                        //坐标矩形
    true,                                   //是否显示拉伸点
    GRAPHIC_TWOCODE_UINTW_2                 //如果码宽是2，则二维码宽为10mm
};

/**
 * @brief DrawTwoCodeItem::DrawTwoCodeItem
 *构造函数
 * @param parent
 */
DrawTwoCodeItem::DrawTwoCodeItem(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    qDebug("[DrawTwoCodeItem--%s]:%s", __func__, "create a rect");
    qr = NULL;
    //设置标签
    this->setFlags(QGraphicsRectItem::ItemIsMovable|QGraphicsRectItem::ItemIsSelectable | QGraphicsRectItem::ItemIsFocusable);

    //初始化
    //名字
    twocode_item_init.name = QObject::tr("twocode");

    //内容
    twocode_item_init.dataString = QObject::tr("hello soudian");


    setTwoCodeMeta(twocode_item_init);
    setFocus();
}

DrawTwoCodeItem::~DrawTwoCodeItem()
{
    if(qr != NULL)
    {
       QRcode_free(qr);
    }
}
QRectF DrawTwoCodeItem::boundingRect() const
{
//   return QGraphicsRectItem::boundingRect();
   qreal adjusts;
   adjusts = MM2PIX_H(ITEM_PULL_RECT_LEN_MM);
   QRectF rc = QGraphicsRectItem::boundingRect();
   rc.adjust(-adjusts, -adjusts, adjusts, adjusts);
   return rc;      //注意不同的参数的区别
}

QPainterPath DrawTwoCodeItem::shape() const
{
    return QGraphicsRectItem::shape();
//    QPainterPath p;
//    p.addRect(DrawTwoCodeItem::boundingRect());
//    return p;
}

bool DrawTwoCodeItem::contains(const QPointF &point) const
{
    return QGraphicsRectItem:: contains(point);
}

void DrawTwoCodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(meta.display_boundframe)
    {
        showDrawRect(painter);                      //显示绘画的Boundrect
    }

    //获取目前实际rect范围
    QRectF rf = this->rect();

    //这个一定要跟随rect的范围去绘画
    if(qr != NULL)
    {
        drawTwoCode(*painter, rf);
    }

    QGraphicsRectItem::paint(painter, option, widget);
}

bool DrawTwoCodeItem::isObscuredBy(const QGraphicsItem *item) const
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::isObscuredBy(item);

}

QPainterPath DrawTwoCodeItem::opaqueArea() const
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::opaqueArea();
}

/**
 * @brief DrawTwoCodeItem::type
 * 自定义的一定要改写这里
 * @return
 */
int DrawTwoCodeItem::type() const
{
    //return QGraphicsRectItem::type();
    return  Type;
}

void DrawTwoCodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    setCursor(Qt::SizeAllCursor);
    QGraphicsRectItem::mouseMoveEvent(event);
}

void DrawTwoCodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    setCursor(Qt::SizeAllCursor);
    QGraphicsRectItem::mousePressEvent(event);
}

void DrawTwoCodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    setCursor(Qt::ArrowCursor);
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void DrawTwoCodeItem::keyPressEvent(QKeyEvent *event)
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

void DrawTwoCodeItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsRectItem::keyReleaseEvent(event);
}

void DrawTwoCodeItem::focusInEvent(QFocusEvent *event)
{
    qDebug("[DrawTwoCodeItem--%s]:", __FUNCTION__);
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::focusInEvent(event);
}

void DrawTwoCodeItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsRectItem::focusOutEvent(event);
}

bool DrawTwoCodeItem::supportsExtension(QGraphicsRectItem::Extension extension) const
{
    return QGraphicsRectItem::supportsExtension(extension);
}

void DrawTwoCodeItem::setExtension(QGraphicsRectItem::Extension extension, const QVariant &variant)
{
    QGraphicsRectItem::setExtension(extension, variant);
}

QVariant DrawTwoCodeItem::extension(const QVariant &variant) const
{
    return QGraphicsRectItem::extension(variant);
}

void DrawTwoCodeItem::draw(QPainter &painter, int width, int height)
{
    QColor foreground(Qt::black);
    painter.setBrush(foreground);

    const int qr_width = qr->width > 0 ? qr->width : 1;
    double scale_x = width / qr_width;
    double scale_y = height / qr_width;
    qDebug("[DrawTwoCodeItem--%s]:[%d],[%d,%d],[%f,%f]", __FUNCTION__, qr->width, width, height, scale_x, scale_y);

    for( int y = 0; y < qr_width; y ++)
    {
        for(int x = 0; x < qr_width; x++)
        {
            unsigned char b = qr->data[y * qr_width + x];
            if(b & 0x01)
            {
                //这里是以界面为坐标
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
}

/**
 * @brief DrawTwoCodeItem::drawTwoCode
 *              画二维码(里面的参数都用浮点型，否则会有大误差)
 * @param painter
 * @param r
 */
void DrawTwoCodeItem::drawTwoCode(QPainter &painter, QRectF r)
{
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);


    qreal x_offset = r.topLeft().x();
    qreal y_offset = r.topLeft().y();

    qreal width = r.width();
    qreal height = r.width();


    const int qr_width = qr->width > 0 ? qr->width : 1;
    double scale_x = width / qr_width;
    double scale_y = height / qr_width;
    qDebug("[DrawTwoCodeItem--%s]:[%d],[%d,%d],[%f,%f]", __FUNCTION__, qr->width, width, height, scale_x, scale_y);

    for( int y = 0; y < qr_width; y ++)
    {
        for(int x = 0; x < qr_width; x++)
        {
            unsigned char b = qr->data[y * qr_width + x];
            if(b & 0x01)
            {
                //这里是画到界面的正中间，应该给x,y一个偏移，让其在给定的矩形绘画，而不是在界面为中心绘画
                QRectF r(x_offset + (x * scale_x), y_offset +(y * scale_y), scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
}

void DrawTwoCodeItem::setString(QString str)
{
    string = str;
    if(qr != NULL)
    {
        QRcode_free(qr);
    }
    qr = QRcode_encodeString(string.toStdString().c_str(),
                             1,
                             QR_ECLEVEL_L,
                             QR_MODE_8,
                             1);
    //update();
}

QString DrawTwoCodeItem::getString()
{
    return this->string;
}

/**
 * @brief DrawTwoCodeItem::setDrawRect
 *  设置绘图区域
 * @param r
 */
void DrawTwoCodeItem::setDrawRect(QRectF r)
{
    this->m_bound_rect = r;
}

/**
 * @brief DrawTwoCodeItem::getDrawRect
 * 获取绘图区域
 * @return
 */
QRectF DrawTwoCodeItem::getDrawRect()
{
    return this->m_bound_rect;
}

/**
 * @brief DrawTwoCodeItem::showDrawRect
 *      画外接矩形框
 * @param painter
 */
void DrawTwoCodeItem::showDrawRect(QPainter *painter)
{
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
}

/**
 * @brief DrawTwoCodeItem::setString
 * @param str:二维码内容
 * @param ecl:二维码容错等级
 * @param mode：二维码编码模式
 */
void DrawTwoCodeItem::setString(QString str, GRAPHIC_TWOCODE_ECLEVEL ecl, GRAPHIC_TWOCODE_MODE mode)
{
    string = str;
    if(qr != NULL)
    {
        QRcode_free(qr);
    }

    //同步更新meta的值
    this->meta.ecl = ecl;
    this->meta.dataString = str;
    this->meta.mode = mode;
    qr = QRcode_encodeString(string.toStdString().c_str(),
                             1,
                             (QRecLevel)ecl,
                             (QRencodeMode)mode,
                             1);
    update();       //改变内容，图元及时更新
}

/**
 * @brief DrawTwoCodeItem::setTwoCodeMeta
 *              设置属性
 * @param item
 * @param meta
 */
void DrawTwoCodeItem::setTwoCodeMeta(TwoCodeItemMeta meta)
{
    qDebug("[DrawTwoCodeItem--%s]>>", __func__);

    //先根据码宽，计算二维码高宽
    meta.CoordRect.setWidth(mm2pix(meta.uintw*5, ENUM_DIR_H));
    meta.CoordRect.setHeight(mm2pix(meta.uintw*5, ENUM_DIR_V));

    this->meta = meta;


    qDebug("[DrawTwoCodeItem--%s]>>this->meta.uintw:%d,dataString:%s", __func__, this->meta.uintw, qPrintable(meta.dataString));
    updateTwoCodeItemWdiget();
}

/**
 * @brief DrawTwoCodeItem::getTwoCodeMeta
 * @return
 */
TwoCodeItemMeta DrawTwoCodeItem::getTwoCodeMeta()
{
    qDebug("[DrawTwoCodeItem--%s]>>", __func__);
    return this->meta;
}

/**
 * @brief DrawTwoCodeItem::updateOneCodeMeta
 *              根据目前的meta，更新item在主界面的显示
 * @param item
 * @return
 */
void DrawTwoCodeItem::updateTwoCodeItemWdiget()
{
    qDebug("[DrawTwoCodeItem--%s]>>", __func__);

    //1.根据实时坐标(可能是移动造成的实际坐标变化),先同步到meta，设置item位置
    //this->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    QPointF tl_map = meta.CoordRect.topLeft();
    tl_map = mapFromScene(tl_map);

    this->setRect(tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());      //不需要设置其它的
    qDebug("[DrawTwoCodeItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __func__,
           tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());

    //主动设置一下内容，否则无法触发化内容
    //设置字符串
    qDebug("[DrawTwoCodeItem--%s]>>this->meta.uintw:%d,dataString:%s,ecl:%d,mode:%d", __func__, this->meta.uintw, qPrintable(meta.dataString),meta.ecl,meta.mode);
    this->setString(meta.dataString, meta.ecl, meta.mode);

    //设置绘画范围
    //setDrawRect(meta.viewRect);


    //主动更新界面一次
    update();
}

/**
 * @brief DrawTwoCodeItem::itemChangedUpdateMetaAndTabWidget
 *鼠标释放书剑处理函数
 * @param event
 */
void DrawTwoCodeItem::itemChangedUpdateMetaAndTabWidget()
{
    qDebug("[DrawTwoCodeItem--%s]>>", __func__);
    updateTwoItemNowCoord();
    g_widget->twocode_item_select = this;
    g_widget->tab_two_attr_manager->attr_twocode_update_item_tabmeta_widget(this->meta);
}

void DrawTwoCodeItem::updateTwoItemNowCoord()
{
    qDebug("[DrawTwoCodeItem--%s]>>", __func__);
    QRectF rf = this->rect();       //获取目前rect的实际位置
    QPointF pf_tl = rf.topLeft();
    QPointF pf_br = rf.bottomRight();


    qDebug("[DrawTwoCodeItem--%s]>>pf_tl:(%f,%f)", __FUNCTION__,pf_tl.x(), pf_tl.y());
    QPointF pf_tl_map = mapToScene(pf_tl);
    QPointF pf_br_map = mapToScene(pf_br);


    meta.CoordRect.setTopLeft(pf_tl_map);       //设置左上角
    //meta.CoordRect.setWidth(rf.width());
    //meta.CoordRect.setHeight(rf.height());
    meta.CoordRect.setBottomRight(pf_br_map);

    qDebug("[DrawTwoCodeItem--%s]>>pf_tl_map:(%f,%f)", __FUNCTION__,pf_tl_map.x(), pf_tl_map.y());
    qDebug("[DrawTwoCodeItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __FUNCTION__,
                                                                   meta.CoordRect.x(),
                                                                   meta.CoordRect.y(),
                                                                   meta.CoordRect.width(),
                                                                   meta.CoordRect.height()
                                                                   );
}
