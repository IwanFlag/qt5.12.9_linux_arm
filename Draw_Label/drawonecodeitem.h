#ifndef DRAWONECODEITEM_H
#define DRAWONECODEITEM_H

#include <QGraphicsRectItem>
#include "Barcode.h"
#include "qzint.h"
#include <QMetaEnum>
#include "common_def.h"


//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(OneCodeItemMetaPS)


//初始化时的一维码属性取值
extern OneCodeItemMetaPS onecode_item_meta_init;


/*一维码编辑类*/
class DrawOneCodeItem : public QGraphicsRectItem//QGraphicsRectItem             //QGraphicsRectItem
{
    Q_ENUMS(BarcodeTypes)
    Q_ENUMS(FrameTypes)
    Q_PROPERTY(QString value READ getValue WRITE setValue)

public:
    //枚举
    enum BarcodeTypes
    {
        CODE11		=1,
        C25MATRIX	=2,
        C25INTER	=3,
        C25IATA		=4,
        C25LOGIC	=6,
        C25IND		=7,
        CODE39		=8,
        EXCODE39	=9,
        EANX		=13,
        EAN128		=16,
        CODABAR		=18,
        CODE128		=20,
        DPLEIT		=21,
        DPIDENT		=22,
        CODE16K		=23,
        CODE93		=25,
        FLAT		=28,
        RSS14		=29,
        RSS_LTD		=30,
        RSS_EXP		=31,
        TELEPEN		=32,
        UPCA		=34,
        UPCE		=37,
        POSTNET		=40,
        MSI_PLESSEY	=47,
        FIM		=49,
        LOGMARS		=50,
        PHARMA		=51,
        PZN		=52,
        PHARMA_TWO	=53,
        PDF417		=55,
        PDF417TRUNC	=56,
        MAXICODE	=57,
        QRCODE		=58,
        CODE128B	=60,
        AUSPOST		=63,
        AUSREPLY	=66,
        AUSROUTE	=67,
        AUSREDIRECT	=68,
        ISBNX		=69,
        RM4SCC		=70,
        DATAMATRIX	=71,
        ITF14		=72,
        CODABLOCKF	=74,
        NVE18		=75,
        KOREAPOST	=77,
        RSS14STACK	=79,
        RSS14STACK_OMNI	=80,
        RSS_EXPSTACK	=81,
        PLANET		=82,
        MICROPDF417	=84,
        ONECODE		=85,
        PLESSEY		=86,

        /* TBarcodeItem 8 codes */
        KIX		=90,
        AZTEC		=92,
        DAFT		=93,
        ITALYPOST	=94,
        DPD		=96,
        MICROQR		=97,

        /* Zint specific */
        TELEPEN_NUM	=128,
        CODE32		=129,
        EANX_CC		=130,
        EAN128_CC	=131,
        RSS14_CC	=132,
        RSS_LTD_CC	=133,
        RSS_EXP_CC	=134,
        UPCA_CC		=135,
        UPCE_CC		=136,
        RSS14STACK_CC	=137,
        RSS14_OMNI_CC	=138,
        RSS_EXPSTACK_CC	=139
    };

    enum FrameTypes
    {
        NO_BORDER=0,
        BIND=2,
        BOX=4
    };

public:
    //构造函数
    DrawOneCodeItem(QGraphicsRectItem *parent = Q_NULLPTR);
    ~DrawOneCodeItem();


    //重写
    QRectF rect() const;
    void setRect(const QRectF &rect);
    inline void setRect(qreal x, qreal y, qreal w, qreal h);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;

    enum { Type = UserType + ENUM_ONECODE_EDIT };
    int type() const Q_DECL_OVERRIDE;


    //鼠标事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;

//------ 一维码相关接口
    void drawBarcode(QPainter *painter, qreal x, qreal y, qreal width, qreal height);
    QString getValue();
    void setValue(QString value);


    //自定义部分
    void setOneCodeMetaPS(OneCodeItemMetaPS meta);
    OneCodeItemMetaPS getOneCodeMetaPS(void);
    void updateOneCodeItemWdiget();
    int getOneCodeTypePS(GRAPHIC_ONECODE_TYPE type);
    void itemChangedUpdateMetaAndTabWidget();
    void setDrawRect(QRectF r);    //改变外接矩形，就是改变二维码坐标和宽高
    QRectF getDrawRect();
    void showDrawRect(QPainter *painter);
    void updateOneItemNowCoord();


    OneCodeItemMetaPS meta;


protected:
    bool supportsExtension(Extension extension) const Q_DECL_OVERRIDE;
    void setExtension(Extension extension, const QVariant &variant) Q_DECL_OVERRIDE;
    QVariant extension(const QVariant &variant) const Q_DECL_OVERRIDE;


private:
    QRectF m_bound_rect;            //外接矩形的范围
    Zint::QZint *bc;
    //QString m_value;
    BarcodeTypes m_BarcodeType;
    //FrameTypes m_FrameType;
    //const static QStringList getTypeNameList();

public slots:
};

#endif // DRAWONECODEITEM_H
