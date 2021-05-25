#include "drawscene.h"
#include <QDebug>
#include <QString>
#include <main.h>
#include "QGraphicsSceneMouseEvent"
#include <QGraphicsRectItem>
#include <drawtextitem.h>


/**
 * @brief DrawScene::DrawScene
 * 构造有参构造函数
 * @param parent
 */
DrawScene::DrawScene(QObject *parent)
    :QGraphicsScene(parent)
{
    qDebug("[DrawScene]", __FUNCTION__);
    draw_scene_set_init_finish_flag(true);
}

/**
 * @brief DrawScene::mouseMoveEvent
 *      重写Scene层的mouse移动事件
 * @param event
 */
void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("[DrawScene]:mouseMoveEvent");
//        QPainter painter;

//        QPen pen;
//        pen.setWidth(1);
//        pen.setColor(Qt::red);
//        pen.setStyle(Qt::DotLine);
//        painter.setPen(pen);

//        //绘制横向线
//        painter.drawLine(0, 100, 300, 100);
//        //绘制纵向线
//        //painter.drawLine(mouse_lastPos.x(), 0, mouse_lastPos.x(), height());

        //qDebug("[DrawView- -%s]:mouse_lastPos:[%d,%d]",__func__,mouse_lastPos.x(),mouse_lastPos.y());
        //qDebug("[DrawView- -%s]:[%d,%d]",__func__,width(), height());

    QGraphicsScene::mouseMoveEvent(event);
}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawScene--mousePressEvent]>>");
    draw_scene_attr_widget_tab_meta_update();
    QGraphicsScene::mousePressEvent(event);
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[DrawScene]:mouseReleaseEvent");
    //draw_scene_attr_widget_tab_meta_update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void DrawScene::keyPressEvent(QKeyEvent *event)
{
    qDebug("[DrawScene]:mouseReleaseEvent");

    QGraphicsScene::keyPressEvent(event);
}

/**
 * @brief DrawScene::draw_scene_attr_widget_tab_meta_update
 *      选中的图元，及时更新并显示meta属性框
 */
void DrawScene::draw_scene_attr_widget_tab_meta_update()
{
    //QList<QGraphicsItem *> list_items = this->selectedItems();
    QGraphicsItem *list_items = this->focusItem();

    //qDebug("[DrawScene--%s]>>list_items_size:%d;", __FUNCTION__, list_items.size());


    if(list_items)         //如果刚好只选中了一个item
    {
        g_widget->attr_widget_tab_meta_update_show(list_items);
    }
    else
    {
        qDebug("[DrawScene--%s]>>not item, noshow meta!", __FUNCTION__);
        //画板设置，目前还未做画板设置,显示的是无效界面，表示没有选中图元
        //g_widget->attr_tabmeta_show_invalid();
        g_widget->central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
        g_widget->central_tab_meta->insertTab(TAB_META_INDEX_ATTR, g_widget->tab_label_attr_manager,tr("Attribute"));
        g_widget->central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);
    }
}

void DrawScene::draw_scene_set_init_finish_flag(bool val)
{
    this->scene_init_finish = val;
}

bool DrawScene::draw_scene_get_init_finish_flag()
{
    return this->scene_init_finish;
}


