#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QGraphicsView>
#include <drawscene.h>
//#include <filter.h>


class DrawView : public QGraphicsView
{
public:
    //必须是有参构造函数
    DrawView(QWidget *parent = Q_NULLPTR);

    //重写事件过滤器
    //bool eventFilter(QObject *, QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);                  //视图的大小改变事件
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;


    //把场景作为视图的成员
    DrawScene           *wal_scene;                         //工作区域的场景

    QPoint mouse_lastPos;                                     //鼠标即时坐标
};

#endif // DRAWVIEW_H
