#ifndef DRAWRECTITEMEX_H
#define DRAWRECTITEMEX_H


#include <QGraphicsRectItem>
#include <QGraphicsScene>

class DrawRectItemEX:public QGraphicsRectItem
{

public:
    explicit DrawRectItemEX(QGraphicsItem *parent = 0);
protected:
    // Shift+左键：进行选择  Alt：准备缩放
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // Alt+拖拽：进行缩放  移动
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    // 使item可使用qgraphicsitem_cast
    int type() const;
private:
    QPointF m_centerPointF;
    bool m_bResizing;
};

#endif // DRAWRECTITEMEX_H
