#ifndef WORKAREALABEL_H
#define WORKAREALABEL_H

#include <QLabel>
#include "common_res.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
//#include <filter.h>
#include <drawscene.h>
#include "drawview.h"
#include "common_fun.h"
#include <QtXml>

/********************************宏定义相关**********************************/
//标尺与label的间距（毫米）
#define ROD_OFFSET_LABEL_MM                 10           //外标尺原点基于label原点的偏移,留出给外标尺的宽和高,单位mm

//view(scene)与标尺的间距（毫米）,后期最好设置为可调整的
//商家说左右两边有四毫米无法打印
#define VIEW_OFFSET_ROD_LEFT_MM              2       //两边的偏移间隙
#define VIEW_OFFSET_ROD_TOP_MM               2       //上下的偏好已间隙


//外标尺偏移（毫米）
#define OUT_ROD_OFFSET_MM                	ROD_OFFSET_LABEL_MM


//内标尺偏移（毫米）,内标尺是因为防止 VIEW_OFFSET_ROD_LEFT_MM  VIEW_OFFSET_ROD_TOP_MM存在,如果存在,则要给view单独画一个标尺
#define INNER_ROD_OFFSET_LEFT_MM                	(OUT_ROD_OFFSET_MM + VIEW_OFFSET_ROD_LEFT_MM)
#define INNER_ROD_OFFSET_TOP_MM                	(OUT_ROD_OFFSET_MM + VIEW_OFFSET_ROD_TOP_MM)


//SCENE的宽和高（毫米）
#define SCENE_LABEL_WIDTH_MM             	70  //实际标签白底/画布大小
#define SCENE_LABEL_HEIGHT_MM               40  //实际标签白底/画布大小


//VIEW的宽和高（毫米）
#define VIEW_LABEL_WIDTH_MM              	SCENE_LABEL_WIDTH_MM
#define VIEW_LABEL_HEIGHT_MM             	SCENE_LABEL_HEIGHT_MM


//LABEL的宽和高（毫米）
#define LABEL_LABEL_WIDTH_MM             	(VIEW_LABEL_WIDTH_MM + ROD_OFFSET_LABEL_MM*2)
#define LABEL_LABEL_HEIGHT_MM            	(VIEW_LABEL_HEIGHT_MM + ROD_OFFSET_LABEL_MM*2)


//标尺刻度线长度,负数s表示内标尺刻度线向外，正数表示向内
#define LONG_ROD_LEN_MM                 -2       //标尺的长刻度线长度（每10mm一个）
#define SHORT_ROD_LEN_MM                -1       //标尺的短刻度线长度


//打印机支持的最大的打印范围(单位是打印点)
#define PRINTER_SUPPORT_WIDTH_DOT_MAX                 576
#define PRINTER_SUPPORT_HEIGHT_DOT_MAX                384

/*
没办法了，必须要在主工作区域的tabmain用一个Label来作为子控件，来画刻度和实现坐标十字线
*/
//初始化label,view和scene
extern LabelPanelMeta label_init_meta;


class DrawLabel : public QLabel
{
public:
    QPoint workAreaMousePos;                                //记录鼠标实时坐标

//---自定义接口
    DrawLabel();
    void mousePressEvent(QMouseEvent *event);               //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);                //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);             //鼠标释放事件
    void paintEvent(QPaintEvent *event);

    void setLabelTabmeta(LabelPanelMeta meta);
    LabelPanelMeta getLabelTabmeta(void);
    void updateLabelWidget();
    void drawOutRod();
    void drawInnerRod();
    void drawMouseCrossLine();
    bool toXML();
    bool getSaveFlag();
    void setSaveFlag(bool);

    QGraphicsItem       *wal_item;                          //工作区域的项
    DrawView            *wal_view;                          //工作区域的视图
    LabelPanelMeta      meta;

protected:
    void wal_label_create_draw_view();                      //初始化场景
    void resizeEvent(QResizeEvent *event);                  //窗口大小发生变化的时候，该函数触发

private:
    bool isSave;                                            //是否保存
};

#endif // WORKAREALABEL_H
