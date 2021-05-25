#ifndef DRAWSCENE_H
#define DRAWSCENE_H
#include <QGraphicsScene>

class DrawScene : public QGraphicsScene
{
public:
    DrawScene(QObject *parent = Q_NULLPTR);
    //场景的鼠标事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


    //按键事件
    void keyPressEvent(QKeyEvent *event);
    QPointF scene_mouse_point;               //鼠标的坐标

    //自定义函数
    void draw_scene_attr_widget_tab_meta_update();
    void draw_scene_set_init_finish_flag(bool val);
    bool draw_scene_get_init_finish_flag(void);

private:
    bool scene_init_finish;       //场景是否初始化完成
};

#endif // DRAWSCENE_H
