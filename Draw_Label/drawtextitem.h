#ifndef DrawTextItem_H
#define DrawTextItem_H

#include <QGraphicsTextItem>
#include <QRectF>
#include "common_def.h"

//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***不然会崩溃..我次奥...
Q_DECLARE_METATYPE(TextItemMetaPS)


extern TextItemMetaPS text_meta_init_val;

class DrawTextItem : public QGraphicsTextItem //QGraphicsItem
{
private:
    qreal    m_pw;                              //画笔
    QRectF   m_rect;                            //矩形范围

public:
    TextItemMetaPS meta;                          //此item的属性，与每个item对象绑定

    DrawTextItem(QGraphicsTextItem *parent = Q_NULLPTR);


    //重写
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;
    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;
    enum { Type = UserType + ENUM_TEXT_EDIT };
    int type() const Q_DECL_OVERRIDE;


    //自定义函数
    void setTextEditMeta(TextItemMetaPS meta);
    TextItemMetaPS getTextEditMeta(void);
    void updateTextEditItemWidget();
    qint16 getTextItemFontType();
    void itemChangedUpdateMetaAndTabWidget();
    void updateTextItemNowCoord();

protected:
    bool sceneEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void inputMethodEvent(QInputMethodEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

    QVariant inputMethodQuery(Qt::InputMethodQuery query) const Q_DECL_OVERRIDE;

    bool supportsExtension(Extension extension) const Q_DECL_OVERRIDE;
    void setExtension(Extension extension, const QVariant &variant) Q_DECL_OVERRIDE;
    QVariant extension(const QVariant &variant) const Q_DECL_OVERRIDE;
};

#endif // DrawTextItem_H
