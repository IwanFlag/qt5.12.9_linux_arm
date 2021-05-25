#include "drawview.h"
#include <QDebug>
#include "main.h"
#include "common_fun.h"


DrawView::DrawView(QWidget *parent):QGraphicsView(parent)
{
    qDebug("%s",__func__);
    //设置鼠标追踪
    setMouseTracking(true);
    //视图的视口安装事件过滤器，主要是处理view的事件函数,否则没有事件
    //this->viewport()->installEventFilter(this);
    //设置视图视口背景色(视图背景色会覆盖场景背景色)
    //this->setBackgroundBrush(QBrush(Qt::white));

    //实例化场景,并把视图作为此场景的父窗口
    wal_scene = new DrawScene(this);
    //设置场景背景色为红色
    //wal_scene->setBackgroundBrush(QBrush(Qt::red));
    //int tabmain_w = g_widget->central_tab_main->width();
    //int tabmain_h = g_widget->central_tab_main->height();

    //隐藏水平/竖直滚动条
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //设置场景大小
    qDebug("[DrawScene - -%s]>>setSceneRect:(%f,%f)", __FUNCTION__, this->sceneRect().width(), this->sceneRect().height());

    //把scene的左上角和view左上角对齐,尽量在view中设置scene的setSceneRect范围大小
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);


    //视图加载显示此场景,场景和视图的大小均在label的resize重新设置
    this->setScene(wal_scene);

    //反锯齿
    setRenderHints(QPainter::Antialiasing);

    //视图展示场景
    this->show();
}

/**
 * @brief DrawView::eventFilter
 * 视图必须要视口来安装一个事件过滤器，来接收某些事件
 */
//bool DrawView::eventFilter(QObject * obj, QEvent *event)
//{
//    if(obj == this->viewport())     //小部件事件对象
//    {
//        //qDebug("[DrawView]:eventFilter,viewport");
//        if(event->type() == QEvent::MouseMove)
//        {
//            //QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//            //强行把事件转为鼠标移动事件，否则拿不到鼠标的即时坐标
//            QMouseEvent *mmove = static_cast<QMouseEvent*>(event);
//            //如果是鼠标移动事件
//            QString str = Q_NULLPTR;
//            str.sprintf("coord(%d,%d)",mmove->pos().x(),mmove->pos().y());
//            g_widget->mouse_coord_label->setText(str);

//            return QGraphicsView::eventFilter(obj, event);        //返回true表示事件截止，不再向父传递
//        }
//        else
//        {
//            //事件继续广播出去，按照普通的方式去处理这个事件。
//            qDebug("[DrawView:%s],(%d)",__func__, event->type());
//            return QGraphicsView::eventFilter(obj, event);
//        }
//    }
//    else
//    {
//        //qDebug("[DrawView]:eventFilter,other...");
//        //事件继续广播出去，按照普通的方式去处理这个事件。
//        return QGraphicsView::eventFilter(obj, event);
//    }
//}

void DrawView::mousePressEvent(QMouseEvent *event)
{
    //视图坐标
    QPoint view_point = event->pos();
    qDebug("[DrawView- -%s]:view_point:[%d,%d]", __func__,view_point.x(),view_point.y());

    //场景坐标
    QPointF scene_point = mapToScene(view_point);
    qDebug("[DrawView- -%s]:scene_point:[%f,%f]", __func__,scene_point.x(),scene_point.y());
    QGraphicsView::mousePressEvent(event);
}

void DrawView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("[DrawView- -%s]:",__func__);
    QGraphicsView::mouseReleaseEvent(event);
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug("[DrawView- -%s]:",__func__);
    //保存最后一个鼠标坐标,借此坐标值来画十字坐标线
    mouse_lastPos = event->pos();
    //qDebug("[DrawView- -%s]:mouse_lastPos[%d,%d]",__func__,mouse_lastPos.x(),mouse_lastPos.y());

    //视图坐标
    QPoint view_point = event->pos();
    //场景坐标
    QPointF scene_point = mapToScene(view_point);

    //在右下角坐标区域显示view的坐标
    QString str = Q_NULLPTR;
    //QMouseEvent *mmove = static_cast<QMouseEvent*>(event);
//    str.sprintf("view(%d,%d) scene(%0.2f,%0.2f)",
//                view_point.x(),view_point.y(),
//                scene_point.x(),scene_point.y()
//                );
    str.sprintf("vpix:(%d,%d) spix:(%0.1f,%0.1f) mm:(%0.1f,%0.1f)",
                view_point.x(),view_point.y(),
                scene_point.x(),scene_point.y(),
                pix2mm(scene_point.x(), ENUM_DIR_H), pix2mm(scene_point.y(), ENUM_DIR_V)
                );
    g_widget->mouse_coord_label->setText(str);

//    QPainter painter(this);

//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::DotLine);
//    painter.setPen(pen);

//    //绘制横向线
//    painter.drawLine(0, mouse_lastPos.y(), width(), mouse_lastPos.y());
//    //绘制纵向线
//    painter.drawLine(mouse_lastPos.x(), 0, mouse_lastPos.x(), height());

//    qDebug("[DrawView- -%s]:mouse_lastPos:[%d,%d]",__func__,mouse_lastPos.x(),mouse_lastPos.y());
//    qDebug("[DrawView- -%s]:[%d,%d]",__func__,width(), height());

    QGraphicsView::mouseMoveEvent(event);
}

void DrawView::paintEvent(QPaintEvent *event)
{
    //qDebug("[DrawView- -%s]:",__func__);
//    QPainter painter(this);

//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::DotLine);
//    painter.setPen(pen);

//    //绘制横向线
//    painter.drawLine(0, mouse_lastPos.y(), width(), mouse_lastPos.y());
//    //绘制纵向线
//    painter.drawLine(mouse_lastPos.x(), 0, mouse_lastPos.x(), height());

//    qDebug("[DrawView- -%s]:mouse_lastPos:[%d,%d]",__func__,mouse_lastPos.x(),mouse_lastPos.y());
//    qDebug("[DrawView- -%s]:[%d,%d]",__func__,width(), height());


    QGraphicsView::paintEvent(event);
}

void DrawView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

/**
 * @brief DrawView::resizeEvent
 * 大小改变事件
 * 1.scene跟着改变
 * @param event
 */
void DrawView::resizeEvent(QResizeEvent *event)
{
    qDebug("[DrawView- -%s]:view_rect:(%d,%d)",__func__,width(), height());
    //设置scene的范围
    this->scene()->setSceneRect(0, 0, width() - MM2PIX_H(ROD_OFFSET_LABEL_MM), height() - MM2PIX_V(ROD_OFFSET_LABEL_MM));
}

/**
 * @brief DrawView::showEvent
 *在此处才能显示视图真实大小，否则返回100*30
 * @param event
 */
void DrawView::showEvent(QShowEvent *event)
{
    qDebug("[DrawView- -%s]>>size:(%d,%d)",__func__, size().width(), size().height());
    QGraphicsView::showEvent(event);
}
