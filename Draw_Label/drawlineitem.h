#ifndef DRAWLINEITEM_H
#define DRAWLINEITEM_H
#include <QRectF>
#include <QPainter>
#include <QGraphicsLineItem>
#include "common_def.h"


//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(LineItemMetaPS)


//初始化时的一维码属性取值
extern LineItemMetaPS line_item_meta_init;


class DrawLineItem : public QGraphicsLineItem
{
public:
    LineItemMetaPS meta;

    DrawLineItem(QGraphicsItem *parent = Q_NULLPTR);

    //自定义函数
    void setLineEditMeta(LineItemMetaPS meta);
    LineItemMetaPS getLineEditMeta(void);
    void updateLineEditItemWidget();
    void updatePullBoundRect(QPainter *painter);
    void updateLineItemNowCoord();
    void itemChangedUpdateMetaAndTabWidget();

    //重写
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;


    enum { Type = UserType + ENUM_LINE_EDIT };
    int type() const Q_DECL_OVERRIDE;

    QPen pen() const;
    void setPen(const QPen &pen);

    QLineF line() const;
    void setLine(const QLineF &line);
//    inline void setLine(qreal x1, qreal y1, qreal x2, qreal y2)
//    { setLine(QLineF(x1, y1, x2, y2)); }

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
    qreal m_bound_offset;                       //此为偏移,以点为中心,开始画矩形,且来判断bound区域
    QRectF m_start_rf;                          //起始点伸缩点位区域
    QRectF m_end_rf;                            //结束点伸缩点位区域
    bool m_s_pulling_flag;                        //起点正在拉伸
    bool m_e_pulling_flag;                        //终点正在拉伸

};


#endif // DRAWLINEITEM_H
