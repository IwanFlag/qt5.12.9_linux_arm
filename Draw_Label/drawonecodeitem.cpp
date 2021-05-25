#include "drawonecodeitem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include "main.h"
#include "common_def.h"
#include <QGraphicsRectItem>
#include <QPen>
#include "common_fun.h"


/**
因为我们是在继承了item去绘画一维码，也就是画了矩形图元，再在矩形里面绘画自己的子图元,理解这个，就能看懂代码，和理解那些坐标了
*/


//初始化时的一维码属性取值
OneCodeItemMetaPS onecode_item_meta_init =
{
    QObject::tr("onecode"),                     //name
    "1234567890",                               //内容至少2个字符，有些编码有规定,默认CODE128码
    GRAPHIC_ONECODE_CODE128_INDEX,              //编码类型，有些类型打不出来，暂时先默认这个
    GRAPHIC_ONECODE_FRAME_NO_BORDER,            //边框类型,协议没用到
    false,                                      //是否显示外边框
    50,                                         //实际高度,暂时未用到
    GRAPHIC_ONECODE_UINTW_1,                    //一维码码宽
    0,                                          //不旋转，协议支持，暂时默认
    0,                                          //安全等级,目前协议不支持
    QRectF(0,0,0,0),                            //boundrect显示范围
    QRectF(0,0,0,0)                             //图元的坐标矩形暂时可以跟外接定一样，但是用的时候，一定要区分开来
};

/**
 * @brief DrawOneCodeItem::DrawOneCodeItem
 *构造函数
 * @param parent
 */
DrawOneCodeItem::DrawOneCodeItem(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    qDebug("[DrawOneCodeItem--%s]:%s", __func__, "create a onecode");
    //设置标签
    this->setFlags(QGraphicsRectItem::ItemIsMovable | QGraphicsRectItem::ItemIsSelectable | QGraphicsRectItem::ItemIsFocusable);
    //一维码初始化
    bc = new Zint::QZint();

    //名字
    onecode_item_meta_init.name = QObject::tr("onecode");

    //内容
    onecode_item_meta_init.dataString = "1234567890";

    //高度
    onecode_item_meta_init.CoordRect.setHeight(MM2PIX_V(ONECODE_ITEM_HEIGHT_DEFAULT_MM));

    setOneCodeMetaPS(onecode_item_meta_init);
    setFocus();
}

DrawOneCodeItem::~DrawOneCodeItem()
{
    if(bc != NULL)
    {
       delete bc;
    }
}

QRectF DrawOneCodeItem::boundingRect() const
{
//    return QGraphicsRectItem::boundingRect();
    qreal adjusts;
    adjusts = MM2PIX_H(ITEM_PULL_RECT_LEN_MM);
    QRectF rc = QGraphicsRectItem::boundingRect();
    rc.adjust(-adjusts, -adjusts, adjusts, adjusts);
    return rc;      //注意不同的参数的区别
}

QPainterPath DrawOneCodeItem::shape() const
{
    return QGraphicsRectItem::shape();
}

bool DrawOneCodeItem::contains(const QPointF &point) const
{
    return QGraphicsRectItem:: contains(point);
}

void DrawOneCodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->meta.display_boundframe)
    {
        showDrawRect(painter);                      //显示绘画的Boundrect
    }

    qDebug("[DrawOneCodeItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __func__,
           meta.CoordRect.x(), meta.CoordRect.y(), meta.CoordRect.width(), meta.CoordRect.height());

    //获取目前实际rect范围
    QRectF rf = this->rect();

    //这个一定要跟随rect的范围去绘画
//    drawBarcode(
//                painter,
//                rf.left(),
//                rf.top(),
//                rf.width(),
//                rf.height()
//                );
    drawBarcode(
                painter,
                rf.left(),          //这是条码相对于该矩形的相对位置
                rf.top(),          //这是条码相对于该矩形的相对位置
                rf.width(),
                rf.height()
                );
    QGraphicsRectItem::paint(painter, option, widget);
}

bool DrawOneCodeItem::isObscuredBy(const QGraphicsItem *item) const
{
    qDebug("[DrawOneCodeItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::isObscuredBy(item);
}

QPainterPath DrawOneCodeItem::opaqueArea() const
{
    qDebug("[DrawOneCodeItem--%s]:", __FUNCTION__);
    return QGraphicsRectItem::opaqueArea();
}

/**
 * @brief DrawOneCodeItem::type
 *          自定义的要自定义类型值
 * @return
 */
int DrawOneCodeItem::type() const
{
    //return QGraphicsRectItem::type();
    return  Type;
}

void DrawOneCodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawOneCodeItem--%s]:", __FUNCTION__);
    setCursor(Qt::SizeAllCursor);

    QGraphicsRectItem::mouseMoveEvent(event);
}

void DrawOneCodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawOneCodeItem--%s]:", __FUNCTION__);
    setCursor(Qt::SizeAllCursor);
    QGraphicsRectItem::mousePressEvent(event);
}

void DrawOneCodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawOneCodeItem--%s]:", __FUNCTION__);
    //setCursor(QCursor(Qt::OpenHandCursor));
    setCursor(Qt::ArrowCursor);
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void DrawOneCodeItem::keyPressEvent(QKeyEvent *event)
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

void DrawOneCodeItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsRectItem::keyReleaseEvent(event);
}

void DrawOneCodeItem::focusInEvent(QFocusEvent *event)
{
    itemChangedUpdateMetaAndTabWidget();
    QGraphicsRectItem::focusInEvent(event);
}

void DrawOneCodeItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsRectItem::focusOutEvent(event);
}

bool DrawOneCodeItem::supportsExtension(QGraphicsRectItem::Extension extension) const
{
    return QGraphicsRectItem::supportsExtension(extension);
}

void DrawOneCodeItem::setExtension(QGraphicsRectItem::Extension extension, const QVariant &variant)
{
    QGraphicsRectItem::setExtension(extension, variant);
}

QVariant DrawOneCodeItem::extension(const QVariant &variant) const
{
    return QGraphicsRectItem::extension(variant);
}

/**
 * @brief DrawOneCodeItem::setDrawRect
 *  设置绘图区域
 * @param r
 */
void DrawOneCodeItem::setDrawRect(QRectF r)
{
    //this->m_bound_rect = r;
    this->meta.viewRect = r;
}

/**
 * @brief DrawOneCodeItem::getDrawRect
 * 获取绘图区域
 * @return
 */
QRectF DrawOneCodeItem::getDrawRect()
{
    //return this->m_bound_rect;
    return this->meta.viewRect;
}

/**
 * @brief DrawOneCodeItem::showDrawRect
 *      画外接矩形框
 * @param painter
 */
void DrawOneCodeItem::showDrawRect(QPainter *painter)
{
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
}

/**
 * @brief DrawOneCodeItem::updateOneItemNowCoord
 *          及时更新此时的坐标范围(特别是鼠标或者键盘移动时)
 */
void DrawOneCodeItem::updateOneItemNowCoord()
{
    QRectF rf = this->rect();       //获取目前rect的实际位置
    QPointF pf_tl = rf.topLeft();
    QPointF pf_br = rf.bottomRight();


    qDebug("[DrawOneCodeItem--%s]>>pf_tl:(%f,%f)", __FUNCTION__,pf_tl.x(), pf_tl.y());
    QPointF pf_tl_map = mapToScene(pf_tl);
    QPointF pf_br_map = mapToScene(pf_br);


    meta.CoordRect.setTopLeft(pf_tl_map);       //设置左上角
    //meta.CoordRect.setWidth(rf.width());
    //meta.CoordRect.setHeight(rf.height());
    meta.CoordRect.setBottomRight(pf_br_map);

    qDebug("[DrawOneCodeItem--%s]>>pf_tl_map:(%f,%f)", __FUNCTION__,pf_tl_map.x(), pf_tl_map.y());
    qDebug("[DrawOneCodeItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __FUNCTION__,
                                                                   meta.CoordRect.x(),
                                                                   meta.CoordRect.y(),
                                                                   meta.CoordRect.width(),
                                                                   meta.CoordRect.height()
                                                                   );
}

QRectF DrawOneCodeItem::rect() const
{
    return QGraphicsRectItem::rect();
}

void DrawOneCodeItem::setRect(const QRectF &rect)
{
    return QGraphicsRectItem::setRect(rect);
}

void DrawOneCodeItem::setRect(qreal x, qreal y, qreal w, qreal h)
{
    return QGraphicsRectItem::setRect(x, y, w, h);
}

/**
 * @brief DrawOneCodeItem::drawBarcode
 *          画一维码
 * @param painter
 * @param x
 * @param y
 * @param width
 * @param height
 */
void DrawOneCodeItem::drawBarcode(QPainter *painter, qreal x, qreal y, qreal width, qreal height)
{
    if (bc == 0)
    {
        painter->drawText(QRectF(x,y,width,height), Qt::AlignCenter,"Zint library not found");
        return;
    }
    //bc->setSymbol(m_BarcodeType);
    qDebug("[DrawOneCodeItem--%s]>>meta.type:(%d)", __FUNCTION__, g_onecode_type_index[meta.type]);

    bc->setSymbol((BarcodeTypes)g_onecode_type_index[meta.type]);


    //bc.setPrimaryMessage("dprimaryMessage");  //???
    //bc->setBorderType((Zint::QZint::BorderType)m_FrameType);
    bc->setBorderType((Zint::QZint::BorderType)meta.frame_type);

    //bc->setHeight(height);
    bc->setWidth(width);
    //bc->setSecurityLevel(0);
    bc->setSecurityLevel(meta.sec_level);
    //bc.setBorderWidth(1);
    /*bc.setPdf417CodeWords(d->pdf417Max);
    bc.setFgColor(d->barcodeColor);*/
    bc->setBgColor(QColor(0,0,0,0));
    //bc->setText(m_value);
    bc->setText(meta.dataString);
    //bc->setWhitespace(5);
    bc->setWhitespace(0);
    bc->render(*painter,QRectF(x,y,width,height), Zint::QZint::IgnoreAspectRatio);
}


//QString DrawOneCodeItem::getTypeName(BarcodeTypes type)
//{
//    BarcodeTypePairList list = getTypeList();
//    for (int i=0; i < list.size(); i++)
//    {
//        if (list.at(i).first == type)
//            return list.at(i).second;
//    }
//    return QString();
//}

//const QStringList DrawOneCodeItem::getTypeNameList()
//{
//    QStringList bstyle_text;
//        bstyle_text<<"CODE11";
//        bstyle_text<<"C25MATRIX";
//        bstyle_text<<"C25INTER";
//        bstyle_text<<"C25IATA";
//        bstyle_text<<"C25LOGIC";
//        bstyle_text<<"C25IND";
//        bstyle_text<<"CODE39";
//        bstyle_text<<"EXCODE39";
//        bstyle_text<<"EANX";
//        bstyle_text<<"EAN128";
//        bstyle_text<<"CODABAR";
//        bstyle_text<<"CODE128";
//        bstyle_text<<"DPLEIT";
//        bstyle_text<<"DPIDENT";
//        bstyle_text<<"CODE16K";
//        bstyle_text<<"CODE93";
//        bstyle_text<<"FLAT";
//        bstyle_text<<"RSS14";
//        bstyle_text<<"RSS_LTD";
//        bstyle_text<<"RSS_EXP";
//        bstyle_text<<"TELEPEN";
//        bstyle_text<<"UPCA";
//        bstyle_text<<"UPCE";
//        bstyle_text<<"POSTNET";
//        bstyle_text<<"MSI_PLESSEY";
//        bstyle_text<<"FIM";
//        bstyle_text<<"LOGMARS";
//        bstyle_text<<"PHARMA";
//        bstyle_text<<"PZN";
//        bstyle_text<<"PHARMA_TWO";
//        bstyle_text<<"PDF417";
//        bstyle_text<<"PDF417TRUNC";
//        bstyle_text<<"MAXICODE";
//        bstyle_text<<"QRCODE";
//        bstyle_text<<"CODE128B";
//        bstyle_text<<"AUSPOST";
//        bstyle_text<<"AUSREPLY";
//        bstyle_text<<"AUSROUTE";
//        bstyle_text<<"AUSREDIRECT";
//        bstyle_text<<"ISBNX";
//        bstyle_text<<"RM4SCC";
//        bstyle_text<<"DATAMATRIX";
//        bstyle_text<<"ITF14";
//        bstyle_text<<"CODABLOCKF";
//        bstyle_text<<"NVE18";
//        bstyle_text<<"KOREAPOST";
//        bstyle_text<<"RSS14STACK";
//        bstyle_text<<"RSS14STACK_OMNI";
//        bstyle_text<<"RSS_EXPSTACK";
//        bstyle_text<<"PLANET";
//        bstyle_text<<"MICROPDF417";
//        bstyle_text<<"ONECODE";
//        bstyle_text<<"PLESSEY";
//        bstyle_text<<"KIX";
//        bstyle_text<<"AZTEC";
//        bstyle_text<<"DAFT";
//        bstyle_text<<"ITALYPOST";
//        bstyle_text<<"DPD";
//        bstyle_text<<"MICROQR";
//        bstyle_text<<"TELEPEN_NUM";
//        bstyle_text<<"CODE32";
//        bstyle_text<<"EANX_CC";
//        bstyle_text<<"EAN128_CC";
//        bstyle_text<<"RSS14_CC";
//        bstyle_text<<"RSS_LTD_CC";
//        bstyle_text<<"RSS_EXP_CC";
//        bstyle_text<<"UPCA_CC";
//        bstyle_text<<"UPCE_CC";
//        bstyle_text<<"RSS14STACK_CC";
//        bstyle_text<<"RSS14_OMNI_CC";
//        bstyle_text<<"RSS_EXPSTACK_CC";
//    return bstyle_text;
//}

QString DrawOneCodeItem::getValue()
{
    //return m_value;
    return meta.dataString;
}

void DrawOneCodeItem::setValue(QString value)
{
    //m_value = value;
    this->meta.dataString = value;
    this->update();
}

/**
 * @brief DrawOneCodeItem::setOneCodeMeta
 *              设置自身属性
 * @param item
 * @param meta
 */
void DrawOneCodeItem::setOneCodeMetaPS(OneCodeItemMetaPS meta)
{
    //1根据字符数据长度,计算条码实际宽度
    qDebug("[DrawOneCodeItem--%s]>>11CoordRect:%f,%f,%f,%f", __func__,
           meta.CoordRect.x(), meta.CoordRect.y(),
           meta.CoordRect.width(), meta.CoordRect.height());

    int count = meta.dataString.count();
    qDebug("[DrawOneCodeItem--%s]>>count:%d", __func__, count);
    qreal infact_width_mm = (count) * 11 * 0.125;                   //mm,2是空白符,3是开始，停止和校验字符,0.125mm取码宽

    //根据1-4种码宽
    if(meta.uintw)
    {
        infact_width_mm = meta.uintw*infact_width_mm;
    }

    qreal infact_width_pix = mm2pix(infact_width_mm, ENUM_DIR_H);       //mm
    qDebug("[DrawOneCodeItem--%s]>>count:%d,%f,%f", __func__, count, infact_width_mm, infact_width_pix);
    meta.CoordRect.setWidth(infact_width_pix);

    qDebug("[DrawOneCodeItem--%s]>>22CoordRect:%f,%f,%f,%f", __func__,
           meta.CoordRect.x(), meta.CoordRect.y(),
           meta.CoordRect.width(), meta.CoordRect.height());

    //21.先把meta设置到item的meta
    this->meta = meta;
    qDebug("[DrawOneCodeItem--%s]>>name:%s", __func__, qPrintable(this->meta.name));


    //2.更新界面item
    updateOneCodeItemWdiget();
}

/**
 * @brief DrawOneCodeItem::getOneCodeMetaPS
 * 返回meta值
 * @return
 */
OneCodeItemMetaPS DrawOneCodeItem::getOneCodeMetaPS()
{
    return this->meta;
}

/**
 * @brief DrawOneCodeItem::updateOneCodeMeta
 *              根据目前的meta，更新item在主界面的显示
 * @param item
 * @return
 */
void DrawOneCodeItem::updateOneCodeItemWdiget()
{
    qDebug("[DrawOneCodeItem--%s]>>", __func__);

    //1.根据实时坐标(可能是移动造成的实际坐标变化),先同步到meta，设置item位置
    //this->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    QPointF tl_map = meta.CoordRect.topLeft();
    tl_map = mapFromScene(tl_map);

    this->setRect(tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());      //不需要设置其它的
    qDebug("[DrawOneCodeItem--%s]>>meta.CoordRect:(%f,%f,%f,%f)", __func__,
           tl_map.x(), tl_map.y(), meta.CoordRect.width(), meta.CoordRect.height());

    //主动设置一下内容，否则无法触发化内容
    this->setValue(meta.dataString);

    //主动更新界面一次
    update();
}

/**
 * @brief DrawTextItem::getOneCodeTypePS
 * 根据一维码下拉对应的上位机索引，返回协议支持的类型
    GRAPHIC_ONECODE_UPCA = 0,       //0	UPC-A	11	48-57
    GRAPHIC_ONECODE_CODE39 = 4,     //4	CODE39	1-	48-57,65-90,32,36,37,43,45,46,47
    GRAPHIC_ONECODE_CODABAR  = 6,   //6	CODABAR 	1-	48-57,65-68,36,43,45,46,47,58
    GRAPHIC_ONECODE_CODE93 = 7,
    GRAPHIC_ONECODE_CODE128 = 8,
    GRAPHIC_ONECODE_CODE11 = 9,
    GRAPHIC_ONECODE_EAN128 = 12
 * @param index
 * @return
 */
int DrawOneCodeItem::getOneCodeTypePS(GRAPHIC_ONECODE_TYPE type)
{
    qDebug("[DrawTextItem--%s]>>", __func__);
    switch(type)
    {
        case GRAPHIC_ONECODE_UPCA:
            {
                return 0;
            }
            break;

        case GRAPHIC_ONECODE_CODE39:
            {
                return 4;
            }
            break;

        case GRAPHIC_ONECODE_CODABAR:
            {
                return 6;
            }
            break;

        case GRAPHIC_ONECODE_CODE93:
            {
                return 7;
            }
            break;

        case GRAPHIC_ONECODE_CODE128:
            {
                return 8;
            }
            break;

        case GRAPHIC_ONECODE_CODE11:
            {
                return 9;
            }
            break;

        case GRAPHIC_ONECODE_EAN128:
            {
                return 12;
            }
            break;

        default:
            {
                return 0;
            }
            break;
    }
}

void DrawOneCodeItem::itemChangedUpdateMetaAndTabWidget()
{
    qDebug("[DrawOneCodeItem--%s]>>", __func__);
    updateOneItemNowCoord();
    g_widget->onecode_item_select = this;
    g_widget->tab_one_attr_manager->attr_onecode_update_item_tabmeta_widget(this->meta);
}
