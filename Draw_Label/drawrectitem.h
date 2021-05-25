#ifndef DrawRectItem_H
#define DrawRectItem_H

#include <QGraphicsRectItem>
#include "third_party/qrencode/include/qrencode.h"
#include "common_def.h"


//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(RectItemMeta)


class DrawRectItem : public QGraphicsRectItem         //QGraphicsItem             //QGraphicsRectItem
{
public:
    //构造函数
    DrawRectItem(QGraphicsRectItem *parent = Q_NULLPTR);


    void showDrawRect(QPainter *painter);
    void setRectMeta(RectItemMeta meta);
    RectItemMeta getRectMeta(void);
    void updateRectItemWdiget();
    void itemChangedUpdateMetaAndTabWidget();
    void updateRectItemNowCoord(void);
    void updatePullBoundRect(QPainter *painter);        //更新拉伸矩形


    RectItemMeta meta;


    //重写
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;
    enum { Type = UserType + ENUM_RECT_EDIT };
    int type() const Q_DECL_OVERRIDE;

    //鼠标事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;

    //鼠标悬浮
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);


protected:
    bool supportsExtension(Extension extension) const Q_DECL_OVERRIDE;
    void setExtension(Extension extension, const QVariant &variant) Q_DECL_OVERRIDE;
    QVariant extension(const QVariant &variant) const Q_DECL_OVERRIDE;

private:
    QRectF m_top_left;                     //左上角的拉伸矩形
    QRectF m_bottom_right;                 //右下角的拉伸矩形
    bool m_top_left_flag;                  //左上角的拉伸矩形拉伸标志位
    bool m_bottom_right_flag;              //右下角的拉伸矩形拉伸标志位
    QRectF m_press_rect;                   //鼠标点击时的矩形

};
#endif // DrawRectItem_H
