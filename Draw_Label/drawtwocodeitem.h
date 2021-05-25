#ifndef DRAWTWOCODEITEM_H
#define DRAWTWOCODEITEM_H

#include <QGraphicsRectItem>
#include "third_party/qrencode/include/qrencode.h"
#include "common_def.h"


//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(TwoCodeItemMeta)
extern TwoCodeItemMeta twocode_item_init;

class DrawTwoCodeItem : public QGraphicsRectItem         //QGraphicsItem             //QGraphicsRectItem
{
public:
    //构造函数
    DrawTwoCodeItem(QGraphicsRectItem *parent = Q_NULLPTR);
    ~DrawTwoCodeItem();


    void setString(QString str);
    QString getString();            //获取该item的String数据
    void setDrawRect(QRectF r);    //改变外接矩形，就是改变二维码坐标和宽高
    QRectF getDrawRect();
    void showDrawRect(QPainter *painter);
    void setString(QString str, GRAPHIC_TWOCODE_ECLEVEL ecl, GRAPHIC_TWOCODE_MODE mode);
    void setTwoCodeMeta(TwoCodeItemMeta meta);
    TwoCodeItemMeta getTwoCodeMeta(void);
    void updateTwoCodeItemWdiget();
    void itemChangedUpdateMetaAndTabWidget();
    void updateTwoItemNowCoord(void);


    TwoCodeItemMeta meta;


    //重写
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;
    enum { Type = UserType + ENUM_TWOCODE_EDIT };
    int type() const Q_DECL_OVERRIDE;

    //鼠标事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;

protected:
    bool supportsExtension(Extension extension) const Q_DECL_OVERRIDE;
    void setExtension(Extension extension, const QVariant &variant) Q_DECL_OVERRIDE;
    QVariant extension(const QVariant &variant) const Q_DECL_OVERRIDE;

private:
    void draw(QPainter &painter, int width, int height);
    void drawTwoCode(QPainter &painter, QRectF f);
    QString string;
    QRcode *qr;
    QRectF m_bound_rect;          //外接矩形的范围
};
#endif // DRAWTWOCODEITEM_H
