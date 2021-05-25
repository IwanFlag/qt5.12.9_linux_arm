#include "mainwindow.h"
#include "common_res.h"
#include "common_fun.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QLabel>
#include <QDockWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <drawlineitem.h>
#include <drawrectitem.h>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QListView>
#include <QCheckBox>
#include <QGraphicsTextItem>
#include <QPlainTextEdit>
#include <drawtextitem.h>
#include <drawrectitemex.h>
#include <QPen>
#include <drawtwocodeitem.h>
#include <drawonecodeitem.h>
#include <QPushButton>
#include <QMessageBox>
#include <QDesktopWidget>
#include <attrlabeltabwidget.h>
#include <QTranslator>
#include <QFileDialog>
#include "common_def.h"


/**
 * @brief MainWindow::MainWindow
 *              构造函数
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget_main_init(0);                //界面初始化
    widget_main_connect_init();         //信号槽初始化
    setMouseTracking(true);             //设置鼠标跟踪
}

/**
 * @brief MainWindow::~MainWindow
 *              析构函数
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::tabmain_file_new
 * 新建选项卡槽函数-关联(File-New菜单和新建工具项按钮)
 * 初始化tabmain这个tab控件,先创建一个label     创建画布背景label,
 * @return
 */
bool MainWindow::tabmain_file_new()
{
    qDebug("tabmain_file_new");
    QString name;
    //创建一个lanel，作为标尺背景,也作为view的父窗口,在创建label的时候，也会创建一个view
    wal = new DrawLabel;

    //tabwidget控件加入一个label子控件
    if(wal->getSaveFlag() == false)
    {
        name = wal->meta.name;
        name= name.append(STR_FILE_UNSAVE_FLAG);
    }

    qDebug("MainWindow--%s>>name:%s", __func__, qPrintable(wal->meta.name));
    central_tab_main->addTab(wal, name);
    //qDebug("MainWindow--%s>>count:%d", __func__, central_tab_main->count());

    central_tab_main->setCurrentIndex(central_tab_main->count()-1);
    //qDebug("[work_label_size]:(%d,%d);(%d,%d)",wal->width(), wal->height(),central_tab_main->width(),central_tab_main->height());
}

/**
 * @brief MainWindow::tabmain_file_open
 *              打开一个已经存在的文件，解析XML
 * @return
 */
bool MainWindow::tabmain_file_open()
{
    qDebug("MainWindow--%s>>", __func__);

    QString path;
    path = path.append(SAVE_DIR_PATH);
    path = path.append(SAVE_DIR_NAME);

    //当打开open时,
//    QString absFileName = QFileDialog::getOpenFileName(this,
//                                                    tr("file select"),
//                                                    path,
//                                                    tr("图片文件(*png *jpg);;"
//                                                       "本本文件(*txt)"));

    QString absFileName = QFileDialog::getOpenFileName(
                                                        this,
                                                        tr("file select"),
                                                        path,
                                                        Q_NULLPTR
                                                    );
    qDebug("MainWindow--%s>>absFileName:%s", __func__, qPrintable(absFileName));

    QFile file(absFileName);

    //如果此文件名,已经在软件打开,也就是tabname有相同的话，则禁止打开
    QString curPath = QDir::homePath();//获取系统当前目录
    QFileInfo fileInfo(absFileName);
    //ui->label->setText(fileInfo.fileName());
    QString fn = fileInfo.fileName();       //单纯的文件名字，不包括路径

    for(int i = 0; i < central_tab_main->count(); i++)
    {
        QString name = central_tab_main->tabText(i);
        name = name.left(name.size() - 1);  /* 取 name 左边size - 1长度的数据 */
        qDebug("MainWindow--%s>>name:%s", __func__, qPrintable(name));
        if(QString::compare(name, fn, Qt::CaseInsensitive) == 0)
        {
            QMessageBox::warning(NULL, tr("file"), tr("file already open!"));
            //central_tab_main->removeTab(central_tab_main->currentIndex());
            return false;
        }
    }
    //central_tab_main->
    //遍历目前的tab
    //QList<DrawLabel*> p_wal_lists = central_tab_main->children();
//    QList<QObject*> list_children = central_tab_main->children();
//    qDebug("MainWindow--%s>>list_children.size():%d", __func__, list_children.size());

//    for(int i = 0; i < list_children.size(); i++)
//    {
//        QObject *child =  list_children.at(i);
//        DrawLabel *p_wal = dynamic_cast<DrawLabel*>(child);
//        qDebug("MainWindow--%s>>name:%s", __func__, qPrintable(p_wal->meta.name));
//        if(QString::compare(p_wal->meta.name, fn, Qt::CaseInsensitive) == 0)
//        {
//            QMessageBox::warning(NULL, tr("file"), tr("file already open!"));
//            return false;
//        }
//    }
    //DrawLabel *p_wal_lists = central_tab_main->findChild<DrawLabel *>();
    //qDebug("MainWindow--%s>>size:%d", __func__, p_wal_lists->size());


    if(file.exists())
    {
        qDebug("MainWindow--%s>>文件存在", __func__);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
//                //实例化一个XML阅读器
//                QXmlStreamReader xmlRead(&file);
//                while(!xmlRead.atEnd())     //是否是最后一个节点
//                {
//                    //指针下移
//                    xmlRead.readNext();
//                    if(xmlRead.isStartElement())//起始节点
//                    {
//                        //如果节点有等于 title 的
//                        qDebug("MainWindow--%s>>name:%s", __func__, xmlRead.name());
//                        if(xmlRead.name() == "DrawLabel")
//                        {
//                            str = xmlRead.readElementText();
//                            qDebug("MainWindow--%s>>找到WorkAreaLabel", __func__);


////                            wal = new DrawLabel;
////                            central_tab_main->addTab(wal, tr("page"));
////                            central_tab_main->setCurrentIndex(central_tab_main->count()-1);
//                        }
//                        else
//                        {
//                            qDebug("MainWindow--%s>>无此节点", __func__);
//                        }
//                    }
//                    else
//                    {
//                        qDebug("MainWindow--%s>>没有从起始节点开始读取", __func__);
//                    }
//                }
            // 以文本流的形式访问
            QTextStream stream(&file);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            stream.setCodec(codec);
            QString content = stream.readAll();

            //还是用doc方式读取吧,
            QDomDocument doc;
            if (!doc.setContent(content))
            {
                file.close();
                QMessageBox::warning(NULL, tr("file"), tr("file load fail"));
                return false;
            }
            file.close();


                QDomElement root = doc.documentElement();  //返回根元素
                //确定根元素是否正确,不正确,则直接返回,防止读取错误的XML,导致程序崩溃
                qDebug("MainWindow--%s>>root.tagName():%s", __func__, qPrintable(root.tagName()));

                if(QString::compare(root.tagName(), STR_DRAW_LABEL, Qt::CaseInsensitive) != 0)
                {
                    QMessageBox::warning(NULL, tr("file"), tr("file abnormal"));        //文件异常
                    return false;
                }


                LabelPanelMeta meta;                                    //labelpanel属性
                TextItemMetaPS text_meta;
                OneCodeItemMetaPS onecode_meta;
                TwoCodeItemMeta twocode_meta;
                RectItemMeta rect_meta;
                LineItemMetaPS line_meta;


                QDomNode n = root.firstChild();   //返回根节点的第一个子节点
                while(!n.isNull())  //如果节点不为空
                {
                    if (n.isElement()) //如果节点是元素
                    {
                        QDomElement e = n.toElement(); //将其转换为元素
                        qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));


//-----------LabelPanelMeta 节点解析 ,第一个标签一定要是 LabelPanelMeta 这个标签,因为要先一步创建wal
                        if(QString::compare(e.tagName(), STR_DRAW_LABEL_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点 LabelPanelMeta 的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));
                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_DRAW_LABEL_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        meta.name  = e_child.text();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_DRAW_LABEL_META_RECT, Qt::CaseInsensitive) == 0)
                                    {
                                        meta.labelRect.setLeft(e_child.attribute("labelRect_l").toFloat());
                                        meta.labelRect.setTop(e_child.attribute("labelRect_t").toFloat());
                                        meta.labelRect.setWidth(e_child.attribute("labelRect_w").toFloat());
                                        meta.labelRect.setHeight(e_child.attribute("labelRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_DRAW_LABEL_META_V, Qt::CaseInsensitive) == 0)
                                    {
                                        meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_DRAW_LABEL_META_S, Qt::CaseInsensitive) == 0)
                                    {
                                        meta.sceneRect.setLeft(e_child.attribute("sceneRect_l").toFloat());
                                        meta.sceneRect.setTop(e_child.attribute("sceneRect_t").toFloat());
                                        meta.sceneRect.setWidth(e_child.attribute("sceneRect_w").toFloat());
                                        meta.sceneRect.setHeight(e_child.attribute("sceneRect_h").toFloat());
                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }

                            }


                            //退出for,正常来到此处,说明 LabelPanelMeta 解析正确，先画wal，最好是等所有都解析完毕，再画,这里先测试
                            wal = new DrawLabel;
                            wal->setLabelTabmeta(meta);
                            central_tab_main->addTab(wal, wal->meta.name);
                            central_tab_main->setCurrentIndex(central_tab_main->count()-1);
                            tab_label_attr_manager->attr_label_update_item_tabmeta_widget(meta);
                        }

//-------------text STR_TEXT_ITEM_META 节点解析
                        if(QString::compare(e.tagName(), STR_TEXT_ITEM_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点 LabelPanelMeta 的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    //qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));
                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.name  = e_child.text();
                                        qDebug("MainWindow--%s>>name:%s", __func__, qPrintable(text_meta.name));

                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_DATA, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.dataString  = e_child.text();
                                        qDebug("MainWindow--%s>>dataString:%s", __func__, qPrintable(text_meta.dataString));

                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_HEIGHT, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.height = (GRAPHIC_TEXT_FONT_HEIGHT_INDEX)e_child.attribute(STR_TEXT_ITEM_HEIGHT).toInt();
                                        qDebug("MainWindow--%s>>height:%d", __func__, text_meta.height);
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_BOLD, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.isbold = e_child.attribute(STR_TEXT_ITEM_BOLD).toInt();
                                        qDebug("MainWindow--%s>>isbold:%d", __func__, text_meta.isbold);
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_UNDERLINE, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.isunderline  = e_child.attribute(STR_TEXT_ITEM_UNDERLINE).toInt();
                                        qDebug("MainWindow--%s>>isunderline:%d", __func__, text_meta.isunderline);

                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_ROTATE, Qt::CaseInsensitive) == 0)
                                    {
                                        //text_meta.name  = e_child.text();
                                        text_meta.rotate  = e_child.attribute(STR_TEXT_ITEM_ROTATE).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_MAGW, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.mag_w  = (GRAPHIC_TEXT_FONT_MAG)e_child.attribute(STR_TEXT_ITEM_MAGW).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_MAGH, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.mag_h  = (GRAPHIC_TEXT_FONT_MAG)e_child.attribute(STR_TEXT_ITEM_MAGH).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_VR, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        text_meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        text_meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        text_meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TEXT_ITEM_CR, Qt::CaseInsensitive) == 0)
                                    {
                                        text_meta.CoordRect.setLeft(e_child.attribute("CoordRect_l").toFloat());
                                        text_meta.CoordRect.setTop(e_child.attribute("CoordRect_t").toFloat());
                                        text_meta.CoordRect.setWidth(e_child.attribute("CoordRect_w").toFloat());
                                        text_meta.CoordRect.setHeight(e_child.attribute("CoordRect_h").toFloat());
                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }
                            }

                            //正常来到此处,说明 STR_TEXT_ITEM_META 解析正确，
                            DrawTextItem *txt_item = new DrawTextItem;
                            txt_item->setTextEditMeta(text_meta);
                            if(wal)
                            {
                                wal->wal_view->wal_scene->addItem(txt_item);
                                wal->wal_view->show();
                            }
                        }

//-------------onecode STR_TEXT_ITEM_META 节点解析
                        if(QString::compare(e.tagName(), STR_OC_ITEM_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点 LabelPanelMeta 的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));
                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.name  = e_child.text();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_DATA, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.dataString  = e_child.text();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_TYPE, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.type  = (GRAPHIC_ONECODE_TYPE_INDEX)e_child.attribute(STR_OC_ITEM_TYPE).toFloat();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_FRAME_TYPE, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.frame_type  = (GRAPHIC_ONECODE_FRAME)e_child.attribute(STR_OC_ITEM_FRAME_TYPE).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_DBF, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.display_boundframe  = e_child.attribute(STR_OC_ITEM_DBF).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_DHEIGHT, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.display_height  = e_child.attribute(STR_OC_ITEM_DHEIGHT).toFloat();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_UINTW, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.uintw  = (GRAPHIC_ONECODE_UINTW)e_child.attribute(STR_OC_ITEM_UINTW).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_ROTATE, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.rotate  = e_child.attribute(STR_OC_ITEM_ROTATE).toFloat();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_SEC_LEVEL, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.sec_level  = e_child.attribute(STR_OC_ITEM_SEC_LEVEL).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_VR, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        onecode_meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        onecode_meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        onecode_meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_OC_ITEM_CR, Qt::CaseInsensitive) == 0)
                                    {
                                        onecode_meta.CoordRect.setLeft(e_child.attribute("CoordRect_l").toFloat());
                                        onecode_meta.CoordRect.setTop(e_child.attribute("CoordRect_t").toFloat());
                                        onecode_meta.CoordRect.setWidth(e_child.attribute("CoordRect_w").toFloat());
                                        onecode_meta.CoordRect.setHeight(e_child.attribute("CoordRect_h").toFloat());
//                                        qDebug("[MainWindow--%s]>>CoordRect:(%f,%f,%f,%f)", __func__,
//                                               e_child.attribute("CoordRect_l").toFloat(),
//                                               e_child.attribute("CoordRect_t").toFloat(),

//                                               e_child.attribute("CoordRect_w").toFloat(),
//                                               e_child.attribute("CoordRect_h").toFloat());

                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }

                            }

                            //正常来到此处,说明 onecode 解析正确，
                            DrawOneCodeItem *onecode_item = new DrawOneCodeItem;
                            onecode_item->setOneCodeMetaPS(onecode_meta);
                            if(wal)
                            {
                                wal->wal_view->wal_scene->addItem(onecode_item);
                                wal->wal_view->show();
                            }
                        }


//-------------twocode STR_TC_ITEM_META 节点解析
                        if(QString::compare(e.tagName(), STR_TC_ITEM_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));
                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.name  = e_child.text();        //如果是中文..
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_DATA, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.dataString  = e_child.text();
                                        //qDebug("MainWindow--%s>>dataString:%s", __func__, qPrintable(twocode_meta.dataString));
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_ECL, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.ecl  = (GRAPHIC_TWOCODE_ECLEVEL)e_child.attribute(STR_TC_ITEM_ECL).toInt();
                                        //qDebug("[MainWindow--%s]>>mode:%d,%s", __func__, twocode_meta.mode, e_child.text().toInt(), QString::fromUtf8(e_child.text()));
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_MODE, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.mode  = (GRAPHIC_TWOCODE_MODE)e_child.attribute(STR_TC_ITEM_MODE).toInt();
                                        //qDebug("[MainWindow--%s]>>mode:%d,%s", __func__, twocode_meta.mode, e_child.text().toInt(), QString::fromUtf8(e_child.text()));
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_UINTW, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.uintw  = (GRAPHIC_TWOCODE_UINTW)e_child.attribute(STR_TC_ITEM_UINTW).toInt();
                                        //qDebug("[MainWindow--%s]>>uintw:%d,%d", __func__, twocode_meta.uintw, e_child.text().toInt());

                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_DBF, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.display_boundframe  = e_child.attribute(STR_TC_ITEM_DBF).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_VR, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        twocode_meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        twocode_meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        twocode_meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_TC_ITEM_CR, Qt::CaseInsensitive) == 0)
                                    {
                                        twocode_meta.CoordRect.setLeft(e_child.attribute("CoordRect_l").toFloat());
                                        twocode_meta.CoordRect.setTop(e_child.attribute("CoordRect_t").toFloat());
                                        twocode_meta.CoordRect.setWidth(e_child.attribute("CoordRect_w").toFloat());
                                        twocode_meta.CoordRect.setHeight(e_child.attribute("CoordRect_h").toFloat());
                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }

                            }

                            //正常来到此处,说明 STR_TEXT_ITEM_META 解析正确，
                            DrawTwoCodeItem *dtc_item = new DrawTwoCodeItem;
                            qDebug("[MainWindow--%s]>>uintw:%d, mode:%d, ecl:%d, dataString:%s", __func__, twocode_meta.uintw, twocode_meta.mode, twocode_meta.ecl, qPrintable(twocode_meta.dataString));
                            dtc_item->setTwoCodeMeta(twocode_meta);
                            if(wal)
                            {
                                wal->wal_view->wal_scene->addItem(dtc_item);
                                wal->wal_view->show();
                            }
                        }


//--------line
                        //-------------text STR_TEXT_ITEM_META 节点解析
                        if(QString::compare(e.tagName(), STR_LINE_ITEM_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点 LabelPanelMeta 的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));
                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.name  = e_child.text();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_DBF, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.display_boundframe  = e_child.attribute(STR_LINE_ITEM_META_DBF).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_XYOFFSET, Qt::CaseInsensitive) == 0)
                                    {
//                                        line_meta.xy_offset  = (GRAPHIC_TEXT_FONT_HEIGHT_INDEX)e_child.text().toInt();
                                        line_meta.xy_offset.setX(e_child.attribute("xy_offset_x").toFloat());
                                        line_meta.xy_offset.setY(e_child.attribute("xy_offset_y").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_ROTATE, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.rotate  = e_child.attribute(STR_LINE_ITEM_META_ROTATE).toFloat();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_PEN, Qt::CaseInsensitive) == 0)
                                    {
//                                        line_meta.pen  = e_child.text().toInt();
                                        line_meta.pen.setWidthF(e_child.attribute("pen_w").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_LEN, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.len  = e_child.attribute(STR_LINE_ITEM_META_LEN).toFloat();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_SP, Qt::CaseInsensitive) == 0)
                                    {
//                                        line_meta.start_point  = (GRAPHIC_TEXT_FONT_MAG)e_child.text().toInt();
                                        line_meta.start_point.setX(e_child.attribute("start_point_x").toFloat());
                                        line_meta.start_point.setY(e_child.attribute("start_point_y").toFloat());

                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_META_EP, Qt::CaseInsensitive) == 0)
                                    {
//                                        line_meta.end_point  = (GRAPHIC_TEXT_FONT_MAG)e_child.text().toInt();
                                        line_meta.end_point.setX(e_child.attribute("end_point_x").toFloat());
                                        line_meta.end_point.setY(e_child.attribute("end_point_y").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_VR, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        line_meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        line_meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        line_meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_LINE_ITEM_CR, Qt::CaseInsensitive) == 0)
                                    {
                                        line_meta.CoordRect.setLeft(e_child.attribute("CoordRect_l").toFloat());
                                        line_meta.CoordRect.setTop(e_child.attribute("CoordRect_t").toFloat());
                                        line_meta.CoordRect.setWidth(e_child.attribute("CoordRect_w").toFloat());
                                        line_meta.CoordRect.setHeight(e_child.attribute("CoordRect_h").toFloat());
                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }

                            }

                            //正常来到此处,说明 line 解析正确，
                            DrawLineItem *m_lineItem = new DrawLineItem;
                            m_lineItem->setLineEditMeta(line_meta);
                            if(wal)
                            {
                                wal->wal_view->wal_scene->addItem(m_lineItem);
                                wal->wal_view->show();
                            }
                        }

//----rect
                        //-------------rect  STR_RECT_ITEM_META节点解析
                        if(QString::compare(e.tagName(), STR_RECT_ITEM_META, Qt::CaseInsensitive) == 0)
                        {
                            //遍历该节点 LabelPanelMeta 的子节点
                            QDomNodeList list = e.childNodes();
                            for(int i = 0; i < list.size(); i++)
                            {
                                QDomNode node = list.at(i);
                                if(node.isElement())
                                {
                                    qDebug("MainWindow--%s>>tagName:%s,text:%s", __func__, qPrintable(e.tagName()), qPrintable(e.text()));

                                    QDomElement e_child = node.toElement();
                                    if(QString::compare(e_child.tagName(), STR_RECT_ITEM_META_NAME, Qt::CaseInsensitive) == 0)
                                    {
                                        rect_meta.name  = e_child.text();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_RECT_ITEM_META_PEN, Qt::CaseInsensitive) == 0)
                                    {
//                                        rect_meta.pen  = e_child.text();
                                        rect_meta.pen.setWidthF(e_child.attribute("pen_w").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_RECT_ITEM_META_DBF, Qt::CaseInsensitive) == 0)
                                    {
                                        rect_meta.display_boundframe  = e_child.attribute(STR_RECT_ITEM_META_DBF).toInt();
                                    }
                                    if(QString::compare(e_child.tagName(), STR_RECT_ITEM_META_VR, Qt::CaseInsensitive) == 0)
                                    {
                                        rect_meta.viewRect.setLeft(e_child.attribute("viewRect_l").toFloat());
                                        rect_meta.viewRect.setTop(e_child.attribute("viewRect_t").toFloat());
                                        rect_meta.viewRect.setWidth(e_child.attribute("viewRect_w").toFloat());
                                        rect_meta.viewRect.setHeight(e_child.attribute("viewRect_h").toFloat());
                                    }
                                    if(QString::compare(e_child.tagName(), STR_RECT_ITEM_META_CR, Qt::CaseInsensitive) == 0)
                                    {
                                        rect_meta.CoordRect.setLeft(e_child.attribute("CoordRect_l").toFloat());
                                        rect_meta.CoordRect.setTop(e_child.attribute("CoordRect_t").toFloat());
                                        rect_meta.CoordRect.setWidth(e_child.attribute("CoordRect_w").toFloat());
                                        rect_meta.CoordRect.setHeight(e_child.attribute("CoordRect_h").toFloat());
                                    }
                                  }
                                else
                                {
                                    //异常,兄弟节点全是元素,不可能是其它
                                    qDebug("[MainWindow--%s]>>异常,兄弟节点全是元素,不可能是其它", __func__);
                                    return false;
                                }

                            }

                            //正常来到此处,说明 STR_TEXT_ITEM_META 解析正确，
                            DrawRectItem *drect_item = new DrawRectItem;
                            drect_item->setRectMeta(rect_meta);
                            if(wal)
                            {
                                wal->wal_view->wal_scene->addItem(drect_item);
                                wal->wal_view->show();
                            }
                        }

                    }
                    n = n.nextSibling();  //下一个兄弟节点
                }
            }
            else
            {
                QMessageBox::warning(NULL, tr("file"), tr("file open fail,errno:-1"));
            }
        }
        else
        {
            QMessageBox::warning(NULL, tr("file"), tr("file no exist!"));
        }
}

/**
 * @brief MainWindow::widget_main_connect_init
 *          action信号槽初始化
 */
void MainWindow::widget_main_connect_init()
{
    //1.关联 File 的action
    connect(File_New, SIGNAL(triggered(bool)), this, SLOT(tabmain_file_new()));
    connect(File_Open, SIGNAL(triggered(bool)), this, SLOT(tabmain_file_open()));
    connect(File_Save, SIGNAL(triggered(bool)), this, SLOT(tabmain_file_save()));

    //2.关联 Edit 的action
    connect(Edit_text, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_text_item()));
    connect(Edit_one_code, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_onecode_item()));
    connect(Edit_two_code, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_twocode_item()));
    connect(Edit_pic, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_pic_item()));
    connect(Edit_line, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_line_item()));
    connect(Edit_rect, SIGNAL(triggered(bool)), this, SLOT(tabmain_create_edit_rect_item()));

    //3.关联 Tool 的action
    connect(Tool_Print, SIGNAL(triggered(bool)), this, SLOT(tabmain_uart_print_data()));
    connect(Tool_Remove, SIGNAL(triggered(bool)), this, SLOT(tabmain_remove_scene_item()));
    connect(Tool_RemoveAll, SIGNAL(triggered(bool)), this, SLOT(tabmain_remove_scene_all_item()));

    //当画板切换时,wal要指向当前的画板
    connect(central_tab_main, SIGNAL(currentChanged(int)), this, SLOT(tabmain_current_index_changed()));
    //关闭标签页
    connect(central_tab_main,SIGNAL(tabCloseRequested(int)),this,SLOT(tabmain_remove_sub_tab(int)));


    //Language主菜单
    connect(lang_zh, SIGNAL(triggered(bool)), this, SLOT(tabmain_language_zh_clicked()));
    connect(lang_en, SIGNAL(triggered(bool)), this, SLOT(tabmain_language_en_clicked()));


}

/**
 * @brief MainWindow::widget_main_show_coord
 * tabmain鼠标移动触发的响应槽函数
 */
void MainWindow::widget_main_show_coord()
{
    qDebug("[ysheng]MainWindow::widget_main_show_coord");
}

/**
 * @brief MainWindow::tabmain_file_save
 * 保存当前文件的槽函数
 * @return
 */
bool MainWindow::tabmain_file_save()
{
    if(wal)
    {
        //序列化 DrawLabel 类
        bool ret = this->wal->toXML();
        qDebug("MainWindow--%s>>ret:%d", __func__, ret);
        if(ret)
        {
            this->wal->setSaveFlag(true);
            //wal->meta.name = wal->meta.name.append("*");
            central_tab_main->setTabText(central_tab_main->currentIndex(), wal->meta.name);
        }
    }
    else
    {
        qDebug("MainWindow--%s>>wal不存在", __func__);
    }
}

/**
 * @brief MainWindow::tabmain_create_edit_text_item
 * 画文本框
 * @return
 */
bool MainWindow::tabmain_create_edit_text_item()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    else
    {
        wal->clearFocus();                              //使其子控件失去焦点
        wal->wal_view->clearFocus();                    //使其子控件失去焦点
        wal->wal_view->wal_scene->clearFocus();         //使其子控件失去焦点，只有这个在view范围外的图元，才能清楚掉焦点，上面两种都不请，只能清楚完全在view范围的图元的焦点
        DrawTextItem *txt_item = new DrawTextItem;
        wal->wal_view->wal_scene->addItem(txt_item);
        wal->wal_view->show();
        qDebug("[MainWindo- -%s]>>text item create ok!", __FUNCTION__);
        return true;
    }
}

/**
 * @brief MainWindow::tabmain_create_edit_onecode_item
 * 画一维码
 * @return
 */
bool MainWindow::tabmain_create_edit_onecode_item()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    wal->clearFocus();
    wal->wal_view->clearFocus();
    wal->wal_view->wal_scene->clearFocus();

    DrawOneCodeItem *onecode_item = new DrawOneCodeItem;
    wal->wal_view->wal_scene->addItem(onecode_item);
    wal->wal_view->show();
}

/**
 * @brief MainWindow::tabmain_create_edit_twocode_item
 * 画二维码
 * @return
 */
bool MainWindow::tabmain_create_edit_twocode_item()
{
    qDebug("[MainWindow--%s]:", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    wal->clearFocus();
    wal->wal_view->clearFocus();
    wal->wal_view->wal_scene->clearFocus();

    DrawTwoCodeItem *dtc_item = new DrawTwoCodeItem;
    wal->wal_view->wal_scene->addItem(dtc_item);
    wal->wal_view->show();
}

/**
 * @brief MainWindow::tabmain_create_edit_pic_item
 * 画图片
 * @return
 */
bool MainWindow::tabmain_create_edit_pic_item()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    wal->clearFocus();
    wal->wal_view->clearFocus();
    wal->wal_view->wal_scene->clearFocus();

}

/**
 * @brief MainWindow::tabmain_create_edit_line_item
 * 划直线
 * @return
 */
bool MainWindow::tabmain_create_edit_line_item()
{
    qDebug("[MainWindow:%s]", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    wal->clearFocus();
    wal->wal_view->clearFocus();
    wal->wal_view->wal_scene->clearFocus();

    DrawLineItem *m_lineItem = new DrawLineItem;

//    GraphicsLineItem *m_lineItem = new GraphicsLineItem;
    wal->wal_view->wal_scene->addItem(m_lineItem);
    wal->wal_view->show();
}

/**
 * @brief MainWindow::tabmain_create_edit_rect_item
 * 画矩形
 * @return
 */
bool MainWindow::tabmain_create_edit_rect_item()
{
    qDebug("[MainWindow--%s]", __FUNCTION__);
    if(wal == Q_NULLPTR)
    {
        qDebug("[MainWindo- -%s]>>ERROR:-1", __FUNCTION__);
        return false;
    }
    wal->clearFocus();
    wal->wal_view->clearFocus();
    wal->wal_view->wal_scene->clearFocus();

    DrawRectItem *drect_item = new DrawRectItem;
    wal->wal_view->wal_scene->addItem(drect_item);
    wal->wal_view->show();
}

/**
 * @brief MainWindow::tabmain_uart_print_data
 * 通过串口打印scene的所有item
 */
void MainWindow::tabmain_uart_print_data()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    //先检测串口是否准备OK
    //是否存在可用串口
    //串口是否打开
    //检测串口的打开按钮的文本是否是"Open"

    //if(tab_uart_manager->open_close_bt->text() == tr(STR_UART_CLOSE))

    if(QString::compare(tab_uart_manager->open_close_bt->text(), tr("Close"), Qt::CaseInsensitive) == 0)
    {
        qDebug("[MainWindow--%s]>>", __FUNCTION__);

        QString str_text;
        str_text = "1B 40\
                1B 45 01\
                B2 FA C6 B7 C3 FB B3 C6 A3 BA 38 30 4D 4D C4 DA C7 B6 CA BD B1 EA C7 A9 B4 F2 D3 A1 BB FA 0D 0A\
                B2 FA C6 B7 D0 CD BA C5 A3 BA 47 59 2D 4E 51 42 32 34 50 0D 0A\
                B9 A4 D7 F7 B5 E7 D1 B9 A3 BA 32 34 56 33 41 0D 0A\
                CD A8 D1 B6 BD D3 BF DA A3 BA 52 53 32 33 32 2B 54 54 4C 2B 55 53 42 BD D3 BF DA 0D 0A\
                B2 A8 20 CC D8 20 C2 CA A3 BA 31 31 35 32 30 30 0D 0A\
                1B 40 1B 61 01 1D 48 02 1D 68 50 00 1D 77 03 00 1D 6B 49 0b 31 32 33 34 35 36 37 38 39 31 30\
                1D 56 42 00";
        //this->tab_uart_manager->uart_send_HEX_byte(str_text);


//        wal = (DrawLabel*)central_tab_main->currentWidget();


        //1.设置页面， 宽/高范围(576 /384)
        if(wal && wal->wal_view)
        {
            if(tab_uart_manager)
            {
                qDebug("[MainWindow--%s]>>333", __FUNCTION__);
                tabmain_print_all();
            }
            else
            {
                qDebug("[MainWindow--%s]>>撒也不是!确定对象是否创立了。", __FUNCTION__);
            }
        }
        else
        {
            qDebug("[MainWindow--%s]>>ERROR:还没建立view，不要打印了，return", __FUNCTION__);
            return;
        }
    }
    else
    {
        qDebug("[MainWindow--%s]>>WARN:uart not open!!!", __FUNCTION__);
        QMessageBox::about(NULL, tr("Uart Tip"), tr("Uart not open"));
        this->central_tab_meta->setCurrentIndex(TAB_META_INDEX_UART);
        return;
    }
}

/**
 * @brief MainWindow::tabmain_remove_scene_item
 * 移除画板的选中的图元
 */
void MainWindow::tabmain_remove_scene_item()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    if(wal)
    {
        //this->wal->wal_view->wal_scene->clearSelection();
        QList<QGraphicsItem *> list_items = this->wal->wal_view->wal_scene->selectedItems();
        qDebug("[MainWindow--%s]>>size:%d", __FUNCTION__, list_items.size());

        for(int i = 0; i < list_items.size(); i++)
        {
            this->wal->wal_view->wal_scene->removeItem(list_items[i]);
            delete list_items[i];
        }
    }
}

/**
 * @brief MainWindow::tabmain_remove_scene_all_item
 * 移除画板中所有的图元
 */
void MainWindow::tabmain_remove_scene_all_item()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    if(wal)
    {
        this->wal->wal_view->wal_scene->clear();
    }
}

/**
 * @brief MainWindow::tabmain_current_index_changede
 *              tab改变槽函数,这个改变具体是什么改变
 */
void MainWindow::tabmain_current_index_changed()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    wal = (DrawLabel*)central_tab_main->currentWidget();    //把当前选择的page页赋值给wal
}

/**
 * @brief MainWindow::tabmain_remove_sub_tab
 * 关闭当前tab页面
 * @param index
 */
void MainWindow::tabmain_remove_sub_tab(int index)
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);
    central_tab_main->removeTab(index);


    //确定当前是否还有标签页，没有则关闭标签页属性栏
    if(!central_tab_main->count())
    {
        central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
    }
}

void MainWindow::tabmain_language_zh_clicked()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);

    QTranslator translator;
    if(translator.load(":/language/draw_label_zh.qm"))
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        this->show();
    }
    else
    {
        QMessageBox::about(NULL, tr("langauage"), tr("not support chinese"));
        qDebug("[MainWindow--%s]>>not support this language", __FUNCTION__);
    }
}

void MainWindow::tabmain_language_en_clicked()
{
    qDebug("[MainWindow--%s]>>", __FUNCTION__);

    QTranslator translator;
    if(translator.load(":/language/draw_label_en.qm"))
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
    else
    {
        QMessageBox::about(NULL, tr("langauage"), tr("not support english"));
        qDebug("[MainWindow--%s]>>not support this language", __FUNCTION__);
    }
}

/**
 * @brief MainWindow::mousePressEvent
 * 鼠标按下事件处理函数
 * @param event
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug("[MainWindow:%s]", __FUNCTION__);

}

/**
 * @brief MainWindow::mouseMoveEvent
 * 鼠标移动事件处理函数
 * @param event
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug("[MainWindow:%s]", __FUNCTION__);
    //mainlastPos = event->pos();
    //QString str = "coord:";
    //str.sprintf("(%d,%d)", mainlastPos.x(), mainlastPos.y());

    //this->mouse_coord_label->setText(str);
    //update();
}

/**
 * @brief MainWindow::mouseReleaseEvent
 * 鼠标释放事件处理函数
 * @param event
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("[MainWindow:%s]", __FUNCTION__);

}

/**
 * @brief Widget::paintEvent
 *
 * @param event
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    //qDebug("[MainWindow:%s]", __FUNCTION__);
}

/**
 * @brief MainWindow::widget_main_init
 *                  主界面初始化
 * @param from
 * @return
 */
bool MainWindow::widget_main_init(uint from)
{
    qDebug("%s", __FUNCTION__);
    //设置主界面窗体大小(按道理是要根据每个设备的分辨率来设置的，目前先不管这个，随便定一个)
    //this->resize(QSize(WIDGET_MAIN_WIDE,  WIDGET_MAIN_HEGIHT));
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    //获取设备屏幕大小
    QRect screenRect = desktopWidget->screenGeometry();
    //获取系统设置的屏幕个数（屏幕拷贝方式该值为1）
    int g_nScreenCount = desktopWidget->screenCount();
    qDebug("MainWindow--%s>>screenRect:(%d,%d)", __FUNCTION__,screenRect.width(),screenRect.height());

    //设置主界面的大小
    //this->resize(screenRect.width()/2 + 200, screenRect.height()/2);
    this->resize(MM2PIX_H(WIDGET_MAIN_WIDE_MM), MM2PIX_V(WIDGET_MAIN_HEGIHT_MM));

    //设置主界面标题（程序/软件名字）
    this->setWindowTitle(tr("DrawLabel"));
    //菜单栏初始化
    widget_main_menu_bar_init();
    //工具栏初始化
    widget_main_tool_bar_init();
    //状态栏初始化
    widget_main_status_bar_init();
    //作区域初始化
    widget_main_work_area_init();
    //主界面底色为浅灰色
    setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);
}

/**
widget_main_menu_bar_init * 主界面菜单栏初始化(ui->方式获取菜单栏)
 */
void MainWindow::widget_main_menu_bar_init()
{
    qDebug("%s", __FUNCTION__);
    //获取ui的菜单栏
    QMenuBar *mbar = ui->menuBar;
    //创建菜单栏上的主菜单项（File，Edit,Tool,Help）
    FileMenu = mbar->addMenu(tr("File"));
    EditMenu = mbar->addMenu(tr("Edit"));
    ToolMenu = mbar->addMenu(tr("Tool"));
    LanguageMenu = mbar->addMenu(tr("Language"));
    HelpMenu = mbar->addMenu(tr("Help"));


    //1.菜单项FileMenu-菜单子项定义并设置action
    File_New = new QAction(QIcon(MAIN_NEW_ACTION_PNG), tr("New(&N)"), this);
    FileMenu->addAction(File_New);
    File_New->setShortcut(QKeySequence(tr("Ctrl+N")));

    File_Open = new QAction(QIcon(MAIN_OPEN_ACTION_PNG), tr("Open(&O)"), this);
    FileMenu->addAction(File_Open);
    File_Open->setShortcut(QKeySequence(tr("Ctrl+O")));

    File_Save = new QAction(QIcon(MAIN_SAVE_ACTION_PNG), tr("Save(&S)"), this);
    FileMenu->addAction(File_Save);
    File_Save->setShortcut(QKeySequence(tr("Ctrl+S")));

//    File_Save_As = new QAction(tr("Save_As(&A)"), this);
//    FileMenu->addAction(File_Save_As);
//    File_Save_As->setShortcut(QKeySequence(tr("Ctrl+A")));

    //2.实现Edit菜单的Action
    Edit_text = new QAction(QIcon(MAIN_TEMPLATE_TEXTEDIT_PNG), tr("Text"), this);
    EditMenu->addAction(Edit_text);
    //Edit_text->setShortcut(QKeySequence(tr("Ctrl+T")));

    Edit_one_code = new QAction(QIcon(MAIN_TEMPLATE_ONECODE_PNG), tr("OneCode"), this);
    EditMenu->addAction(Edit_one_code);
    //Edit_one_code->setShortcut(QKeySequence(tr("Ctrl+T")));

    Edit_two_code = new QAction(QIcon(MAIN_TEMPLATE_TWOCODE_PNG), tr("TwoCode"), this);
    EditMenu->addAction(Edit_two_code);
    //Edit_two_code->setShortcut(QKeySequence(tr("Ctrl+T")));

    Edit_pic = new QAction(QIcon(MAIN_TEMPLATE_SELFPIC_PNG), tr("Picture"), this);
    EditMenu->addAction(Edit_pic);
    //Edit_pic->setShortcut(QKeySequence(tr("Ctrl+T")));

    Edit_line = new QAction(QIcon(MAIN_TEMPLATE_LINE_PNG), tr("Line"), this);
    EditMenu->addAction(Edit_line);
    //Edit_line->setShortcut(QKeySequence(tr("Ctrl+T")));

    Edit_rect = new QAction(QIcon(MAIN_TEMPLATE_RECT_PNG), tr("Rect"), this);
    EditMenu->addAction(Edit_rect);
    //Edit_rect->setShortcut(QKeySequence(tr("Ctrl+T")));


    //2.菜单项ToolMenu-菜单子项定义并设置
    Tool_Print = new QAction(QIcon(MAIN_PRINT_ACTION_PNG), tr("Print"), this);
    ToolMenu->addAction(Tool_Print);
    Tool_Print->setShortcut(QKeySequence(tr("Ctrl+P")));

    Tool_Template_set = new QAction(QIcon(MAIN_TEMPLATE_ACTION_PNG), tr("Template"), this);
    ToolMenu->addAction(Tool_Template_set);
    File_Open->setShortcut(QKeySequence(tr("Ctrl+O")));

    Tool_Repeal = new QAction(QIcon(MAIN_REPEAL_ACTION_PNG), tr("Repeal"), this);
    ToolMenu->addAction(Tool_Repeal);
    //File_Save->setShortcut(QKeySequence(tr("Ctrl+S")));

    Tool_Recover = new QAction(QIcon(MAIN_RECOVER_ACTION_PNG),tr("Recover"), this);
    ToolMenu->addAction(Tool_Recover);
    //File_Save_As->setShortcut(QKeySequence(tr("Ctrl+A")));

    //移除场景中选中的图元
    Tool_Remove = new QAction(QIcon(MAIN_REPEAL_ACTION_PNG), tr("Remove"), this);
    ToolMenu->addAction(Tool_Remove);

    //移除场景中所有图元
    Tool_RemoveAll = new QAction(QIcon(MAIN_RECOVER_ACTION_PNG),tr("RemoveAll"), this);
    ToolMenu->addAction(Tool_RemoveAll);

    //语言设置主菜单
    lang_zh = new QAction(tr("Chinese"), this);
    LanguageMenu->addAction(lang_zh);

    lang_en = new QAction(tr("English"), this);
    LanguageMenu->addAction(lang_en);
}

/**
 * @brief MainWindow::widget_main_tool_bar_init
 * 初始化工具栏（这不是工具菜单，打印，模板设置，撤销，恢复）
 */
void MainWindow::widget_main_tool_bar_init()
{
    qDebug("%s", __FUNCTION__);

    //这里不再创建，直接使用MainWindow类对象自创建的一个工具栏
    QToolBar *pToolBar = ui->mainToolBar;
    //设置工具栏不可浮动，默认是可浮动的
    pToolBar->setFloatable(false);
    //设置工具栏不可移动，默认是可以移动的
    pToolBar->setMovable(false);


    //1.创建工具栏的子项 加入New ACTION
    pToolBar->addAction(File_New);
    //pToolBar->addSeparator();           //分隔符

    //2.创建工具栏的子项 open button
    pToolBar->addAction(File_Open);

    //3.创建工具栏的子项 save button
    pToolBar->addAction(File_Save);
    pToolBar->addSeparator();           //分隔符

    //4.创建工具栏的子项print button
    pToolBar->addAction(Tool_Print);

    //5.创建工具栏的子项 template button
    pToolBar->addAction(Tool_Template_set);
    pToolBar->addSeparator();           //分隔符

//    //6.创建工具栏的子项 repeal button
//    pToolBar->addAction(Tool_Repeal);

//    //7.创建工具栏的子项 recover button
//    pToolBar->addAction(Tool_Recover);
//    pToolBar->addSeparator();           //分隔符

    //8.创建工具栏的子项 remove button
    pToolBar->addAction(Tool_Remove);

    //9.创建工具栏的子项 removeall button
    pToolBar->addAction(Tool_RemoveAll);
    pToolBar->addSeparator();           //分隔符
}

/**
 * @brief MainWindow::widget_main_tool_bar_init
 * 初始化工具栏（这不是工具菜单，打印，模板设置，撤销，恢复）
 */
//void MainWindow::widget_main_tool_bar_init_ex()
//{
//    qDebug("%s", __FUNCTION__);


//    //1.创建工具栏
//    //QToolBar *pToolBar = addToolBar("toolBar");

//    //这里不再创建，直接使用MainWindow类对象自创建的一个工具栏
//    QToolBar *pToolBar = ui->mainToolBar;
//    //设置工具栏不可浮动，默认是可浮动的
//    pToolBar->setFloatable(false);
//    //设置工具栏不可移动，默认是可以移动的
//    pToolBar->setMovable(false);


//    //1.创建工具栏的子项 new button
//    QToolButton *new_button = new QToolButton(this);
//    new_button->setText(tr(WIDGET_MAIN_MENU_TOOL_NEW));
//    QIcon new_icon(":/icon/tool_icon/new.png");
//    new_button->setIcon(new_icon);
//    new_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    //action->setToolTip("Open");//设置工具栏项的提示文字，即鼠标停在该元素时显示
//    pToolBar->addWidget(new_button);
//    pToolBar->addSeparator();           //分隔符

//    //2.创建工具栏的子项 open button
//    QToolButton *open_button = new QToolButton(this);
//    open_button->setText(tr(WIDGET_MAIN_MENU_TOOL_OPEN));
//    QIcon open_icon(":/icon/tool_icon/open.png");
//    open_button->setIcon(open_icon);
//    open_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(open_button);
//    pToolBar->addSeparator();           //分隔符

//    //3.创建工具栏的子项 save button
//    QToolButton *save_button = new QToolButton(this);
//    save_button->setText(tr(WIDGET_MAIN_MENU_TOOL_SAVE));
//    QIcon save_icon(":/icon/tool_icon/save.png");
//    save_button->setIcon(save_icon);
//    save_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(save_button);
//    pToolBar->addSeparator();           //分隔符

//    //4.创建工具栏的子项print button
//    QToolButton *print_button = new QToolButton(this);
//    print_button->setText(tr(WIDGET_MAIN_MENU_TOOL_PRINT));
//    QIcon print_icon(":/icon/tool_icon/print.png");
//    print_button->setIcon(print_icon);
//    print_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(print_button);
//    pToolBar->addSeparator();           //分隔符

//    //5.创建工具栏的子项 template button
//    QToolButton *template_button = new QToolButton(this);
//    template_button->setText(tr(WIDGET_MAIN_MENU_TOOL_TEMPLATE));
//    QIcon template_icon(":/icon/tool_icon/templateset.png");
//    template_button->setIcon(template_icon);
//    template_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(template_button);
//    pToolBar->addSeparator();           //分隔符

//    //6.创建工具栏的子项 repeal button
//    QToolButton *repeal_button = new QToolButton(this);
//    repeal_button->setText(tr(WIDGET_MAIN_MENU_TOOL_REPEAL));
//    QIcon repeal_icon(":/icon/tool_icon/repeal.png");
//    repeal_button->setIcon(repeal_icon);
//    repeal_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(repeal_button);
//    pToolBar->addSeparator();           //分隔符

//    //7.创建工具栏的子项 recover button
//    QToolButton *recover_button = new QToolButton(this);
//    recover_button->setText(tr(WIDGET_MAIN_MENU_TOOL_RECOVER));
//    QIcon recover_icon(":/icon/tool_icon/recover.png");
//    recover_button->setIcon(recover_icon);
//    recover_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    pToolBar->addWidget(recover_button);
//    pToolBar->addSeparator();           //分隔符
//}

/**
 * @brief MainWindow::widget_main_status_bar_init
 *              状态栏初始化
 */
void MainWindow::widget_main_status_bar_init()
{
    qDebug("%s", __FUNCTION__);

    //1.获取状态栏指针
    QStatusBar *stbar = this->statusBar();
    this->status_show_label = new QLabel(tr("status show!"));
    this->mouse_coord_label = new QLabel(tr("mouse coord show!"), this);

    //左下角显示临时信息，6s后关闭
    //stbar->showMessage(tr("gui init finish!"), 3000);

    //label 字体
    QFont ft;
    ft.setPointSize(WIDGET_MAIN_STATUS_BAR_FONT_SIZE);
    mouse_coord_label->setFont(ft);

    //label 颜色
    QPalette pe;            //调色板
    pe.setColor(QPalette::WindowText, Qt::gray);

    //2.干脆用左下角来显示软件的一些状态信息，一个label放在状态栏
    status_show_label->setFont(ft);
    status_show_label->setPalette(pe);
    stbar->addWidget(status_show_label);


    //右下角显示画布坐标（也就是显示鼠标在实际标签纸的位置坐标）
    mouse_coord_label->setFont(ft);
    mouse_coord_label->setPalette(pe);
    stbar->addPermanentWidget(mouse_coord_label);//addPermanentWidget--该函数用于添加永久信息，在最右侧显示。
}

/**
 * @brief MainWindow::widget_main_area_init
 * 主界面工作区域初始化(包括 Dock 和 Central 区域)
 */
void MainWindow::widget_main_work_area_init()
{
    qDebug("%s", __FUNCTION__);

    //右边是画布区域，用tabwidget实现可以展开多个画布
    //this->width();
    //this->height();
    //qDebug("width:%d,height:%d",this->width(), this->height());


    //创建一个铆接部件
    //QDockWidget *dock_widget = new QDockWidget("Dock area...",this);
    //将浮动窗口添加到mainwindow
    //this->addDockWidget(Qt::TopDockWidgetArea, dock_widget);


    //设置central工作区域
    //1.没有办法了，只能这样设置centralWidget控件的样式表了，以此来设置背景色
    //ui->centralWidget->setStyleSheet ("background-color: rgb(125, 125, 125)");


    //2.设置centralWidget区域
    //初始化刚开始，不管现在centralWidget区域是否实际存在控件
    //设置centralWidget区域的控件为布局管理器控件
    //还是不用栅格，用弹簧算了
    QSplitter *splitter= new QSplitter;


    //1.QSplitter左边放一个工具栏
    central_tool_bar = new QToolBar(this);
    //central_tool_bar->setStyleSheet("background-color: rgb(0, 0, 125)");
    //central_tool_bar->resize(900,400);

    //QPalette pe;            //调色板
    //pe.setColor(QPalette::WindowText, Qt::blue);
    //central_tool_bar->setPalette(pe);
    central_tool_bar->setWindowTitle(tr("label template"));
    splitter->addWidget(central_tool_bar);


    //2.QSplitter中间放一个tab控件（这部分就是我们的工作区域）
    central_tab_main = new QTabWidget();
    splitter->addWidget(central_tab_main);

    //3.QSplitter右边也放一个tab控件（此部分作为工作区域内的控件的属性展示）
    central_tab_meta = new QTabWidget();
    splitter->addWidget(central_tab_meta);


    //4.因为splitter默认是使用的水平布局的，所以主要控制各个控件宽度比列
    // 只设置第二个控件可伸缩即可,方便布局,如果第三个部件也伸缩，则默认布局会乱
    //splitter->setStretchFactor(0,1);    //第1个控件占1份，主要控制宽度
    splitter->setStretchFactor(1,7);    //第2个控件占8份
    //splitter->setStretchFactor(2,1);    //第3个控件占1份


    //把主界面的 CentralWidget设置为splitter
    this->setCentralWidget(splitter);

    //1.工作区左边的toolbar区域初始化
    widget_main_work_area_toolbar_init();

    //2.工作区中间tab初始化
    widget_main_work_area_tabmain_init();

    //3.工作区右边tab控件初始化
    widget_main_work_area_tabmanger_init();
}

/**
 * @brief MainWindow::widget_main_work_area_toolbar_init
 * 工作区左侧的工具栏添加Edit 的 action
 */
void MainWindow::widget_main_work_area_toolbar_init()
{
    qDebug("%s", __FUNCTION__);

    //设置工具栏不可浮动，默认是可浮动的
    central_tool_bar->setFloatable(false);
    //设置工具栏不可移动，默认是可以移动的
    central_tool_bar->setMovable(false);
    //设置toolbar里面的tool工具垂直显示
    central_tool_bar->setOrientation(Qt::Vertical);


    central_tool_bar->addSeparator();           //分隔符
    central_tool_bar->addAction(Edit_text);
    central_tool_bar->addSeparator();           //分隔符

    central_tool_bar->addAction(Edit_one_code);
    central_tool_bar->addSeparator();           //分隔符

    central_tool_bar->addAction(Edit_two_code);
    central_tool_bar->addSeparator();           //分隔符

    central_tool_bar->addAction(Edit_line);
    central_tool_bar->addSeparator();           //分隔符

    central_tool_bar->addAction(Edit_rect);
    central_tool_bar->addSeparator();           //分隔符

    central_tool_bar->addAction(Edit_pic);
    central_tool_bar->addSeparator();           //分隔符
}

/**
 * @brief MainWindow::widget_main_work_area_tabmain_init
 *          工作区tab选项卡显示，刚打开软件默认不创建tab选项卡，只有新建才打开
 */
void MainWindow::widget_main_work_area_tabmain_init()
{
    qDebug("[MainWindow:%s]", __FUNCTION__);

    central_tab_main->clear();//清空选项卡

    //QWidget *tab_start=new QWidget(this);
    //QWidget *tabMusic=new QWidget(this);
    //QWidget *tabSoftware=new QWidget(this);
    //QWidget *tabDigital=new QWidget(this);
    //QWidget *tabLanguage=new QWidget(this);

    central_tab_main->setTabPosition(QTabWidget::North);//设置选项卡的方位东南西北，默认在上方

    //central_tab_main->addTab(tabSports,tr("运动"));//在后面添加选项卡
    //central_tab_main->addTab(tabMusic,tr("音乐"));
    //central_tab_main->addTab(tabSoftware,QIcon("F:\\磊神图片\\icons\\1.ico"),tr("软件"));//在后面添加带图标的选项卡
    //central_tab_main->insertTab(3,tabDigital,tr("数码"));//插入选项卡
    //central_tab_main->insertTab(4,tabLanguage,QIcon("F:\\磊神图片\\icons\\3.ico"),tr("语言"));//插入带图标的选项卡
    central_tab_main->setTabShape(QTabWidget::Triangular);//设置选项卡的形状
    //central_tab_main->removeTab(0);//移除选项卡

//    central_tab_main->setTabIcon(0,QIcon("F:\\磊神图片\\icons\\2.ico"));//设置选项卡图标
//    central_tab_main->setTabIcon(1,QIcon("F:\\磊神图片\\icons\\4.ico"));//设置选项卡图标
//    central_tab_main->setTabIcon(3,QIcon("F:\\磊神图片\\icons\\5.ico"));//设置选项卡图标
    //central_tab_main->setIconSize(QSize(50,25));//设置图标的大小(选项卡的大小也会改变)
    central_tab_main->setMovable(true);
    central_tab_main->setTabsClosable(true);//在选项卡上添加关闭按钮

    //qDebug()<<"第一个选项卡名称："<<central_tab_main->tabText(0);//获取选项卡名称
    //qDebug()<<"iconSize:"<<central_tab_main->iconSize();//获取icon的尺寸

    //central_tab_main->setTabEnabled(0,false);//禁用选项卡
    //central_tab_main->setTabEnabled(1,false);
    //central_tab_main->setTabEnabled(0,true);    //使能选项卡
    //central_tab_main->setTabEnabled(1,true);    //使能选项卡
    //central_tab_main->setTabToolTip(2,tr("Beautiful"));//鼠标悬停弹出提示
    central_tab_main->usesScrollButtons();//选项卡太多滚动
    //central_tab_main->removeTab(0);//移除选项卡
    //central_tab_main->setTabWhatsThis(3,tr("Beautiful Girl"));//不知道干嘛的
    //central_tab_main->setTabBarAutoHide(true);//包含少于2个选项卡时会自动隐藏
    //central_tab_main->setTabText(0,tr("软件"));//按索引修改选项卡的名称
    //central_tab_main->setTabText(1,tr("舞蹈"));
    //central_tab_main->setDocumentMode(true);//设置选项卡是否以适合文档页面的模式呈现
    //central_tab_main->setElideMode(Qt::ElideLeft);//标签栏中删除文字

    //central_tab_main->clear();//清空选项卡
    //设置下颜色
    //central_tab_main->setStyleSheet(BG_COLOR_STYLE_KHAKI);
    //不知为何,这里wal会有值,可能是主界面分配的吧,先置为空
    wal = Q_NULLPTR;

    qDebug("[MainWindow--%s]>>wal:%p", __FUNCTION__, wal);
}

/**
 * @brief MainWindow::widget_main_work_area_tabmanger_init
 */
void MainWindow::widget_main_work_area_tabmanger_init()
{
    qDebug("%s", __FUNCTION__);
    central_tab_meta->clear();//清空选项卡

    //创建attr属性面板界面
    //tab_attr_manager = new QWidget(this);               //tab_main里的单个焦点控件属性展示
    //tab_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);
    //central_tab_meta->addTab(tab_attr_manager,tr("Attribute"));

    tab_text_attr_manager = new AttrTextTabWidget();               //tab_main里的单个焦点控件属性展示
    tab_text_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);

    tab_one_attr_manager = new AttrOneCodeTabWidget();               //tab_main里的单个焦点控件属性展示
    tab_one_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);

    tab_two_attr_manager = new AttrTwoCodeTabWidget();               //tab_main里的单个焦点控件属性展示
    tab_two_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);

    tab_line_attr_manager = new AttrLineTabWidget();               //tab_main里的单个焦点控件属性展示
    tab_line_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);

    tab_rect_attr_manager = new AttrRectTabWidget();               //tab_main里的单个焦点控件属性展示
    tab_rect_attr_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);


    //创建串口界面工具（包括设置，输出，打印等）
    tab_uart_manager = new UartTabWidget(this);             //tab_main里的控件管理器
    tab_uart_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);
    central_tab_meta->addTab(tab_uart_manager,tr("Uart"));

    //暂未用到
    //tab_res_manager = new QWidget(this);             //tab_main里的控件管理器
    //tab_res_manager->setStyleSheet(COLOR_STYLE_LIGHT_WGRAY);
    //central_tab_meta->addTab(tab_res_manager,tr("Manager"));


    central_tab_meta->setTabPosition(QTabWidget::South);    //设置选项卡的方位东南西北，默认在上方
    //central_tab_meta->setMovable(true);       // 禁止tabbar移动
    central_tab_meta->setTabShape(QTabWidget::Triangular);  //设置选项卡的形状
}

/**
 * @brief MainWindow::attr_widget_tab_meta_update_show
 *          根据选中的图形item，显示其属性
 * @param item:传进来的item指针
 */
void MainWindow::attr_widget_tab_meta_update_show(QGraphicsItem *item)
{
    int item_type = item->type() - 65536;//UserType==65536,不知道UserType为什么引用不了
    qDebug("[MainWindow--%s]>>(%p,%d);", __FUNCTION__,item, item_type);


    //先把原来的布局删除下，否则无法切换不同布局,或者切换会有覆盖问题
//    if(tab_text_attr_manager->layout())
//    {
//        destroyLayoutWidget(tab_text_attr_manager->layout());
//        delete tab_text_attr_manager->layout();
//    }


    //根据类型来加载显示,定义一个枚举来区分此item是什么类型, 且是哪个item
    switch(item_type)
    {
        case ENUM_TEXT_EDIT:
            {
                if(central_tab_meta && tab_text_attr_manager && text_item_select)
                {
                    text_item_select = qgraphicsitem_cast<DrawTextItem*>(item);
//                    tab_text_attr_manager->attr_text_update_item_tabmeta_widget(text_item_select->getTextEditMeta());
//                    central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
//                    central_tab_meta->insertTab(TAB_META_INDEX_ATTR, tab_text_attr_manager,tr("Attribute"));
                }
            }
            break;

        case ENUM_ONECODE_EDIT:
            {
                onecode_item_select = qgraphicsitem_cast<DrawOneCodeItem*>(item);
            }
            break;

        case ENUM_TWOCODE_EDIT:
            {
                twocode_item_select = qgraphicsitem_cast<DrawTwoCodeItem*>(item);
            }
            break;

        case ENUM_RECT_EDIT:
            {
                rect_item_select = qgraphicsitem_cast<DrawRectItem*>(item);
            }
            break;

        case ENUM_LINE_EDIT:
            {
                line_item_select = qgraphicsitem_cast<DrawLineItem*>(item);
            }
            break;

        default:
            {
                qDebug("[AttrTabWidget--%s]>>WARN:no meta.", __FUNCTION__);
                attr_tabmeta_show_invalid();
                central_tab_meta->removeTab(TAB_META_INDEX_ATTR);
                central_tab_meta->insertTab(TAB_META_INDEX_ATTR, tab_attr_manager,tr("Attribute"));
            }
            break;
    }

    central_tab_meta->setCurrentIndex(TAB_META_INDEX_ATTR);
}

/**
 * @brief MainWindow::attr_tabmeta_show_invalid
 *      当item无效，或者点击非item时，显示此界面
 */
void MainWindow::attr_tabmeta_show_invalid()
{
    qDebug("[AttrTabWidget--%s]>>", __FUNCTION__);

    //1.布局（垂直布局）
    QVBoxLayout *vb = new QVBoxLayout();

    //2.加一个label标签，来显示item类别
    QLabel *lab = new QLabel;
    lab->setStyleSheet(COLOR_STYLE_LIGHT_GRAY);
    lab->setText(tr(WIDGET_MAIN_CENTRAL_TOOL_INVALID));

    //设置字号
    QFont ft;
    ft.setPointSize(g_font_size[GRAPHIC_FONT_SIZE_NORMAL]);
    lab->setFont(ft);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    lab->setPalette(pa);

    //对齐
    lab->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    vb->addWidget(lab);

    //5.控件加载布局
    tab_attr_manager->setLayout(vb);       //attr tab页面子控件布局管理
}

/**
 * @brief MainWindow::tabmain_print_all
 * 打印所有的图元
 */
void MainWindow::tabmain_print_all()
{
    QList<QGraphicsItem *> list_items = wal->wal_view->wal_scene->items();
    QByteArray send_all;         //所有的数据
    QByteArray send_data;        //单条数据
    QFile *uart_data_fp;


    if(list_items.size() > 0)
    {
        uart_data_fp = new QFile;
        tabmain_creaet_uart_data_file(uart_data_fp);                            //创建文件来保存打印数据

        QRectF sceneR = wal->wal_view->rect();

        qDebug("[MainWindow--%s]>>sceneR:(%f,%f),875,545", __FUNCTION__, sceneR.width(), sceneR.height());
//        qint16 pw = pix2mm(sceneR.width(), ENUM_DIR_H);
//        qint16 ph = pix2mm(sceneR.height(), ENUM_DIR_V);
        qint16 pw_pix = sceneR.width();
        qint16 ph_pix = sceneR.height();
        qDebug("[AttrTabWidget--%s]>>pw_pix:%d, ph_pix:%d", __FUNCTION__, pw_pix, ph_pix);

        //qDebug("[MainWindow--%s]>>pix2mm(%f,%f)--(pw:%d, ph:%d)", __FUNCTION__, pix2mm(sceneR.width(), ENUM_DIR_H), pix2mm(sceneR.height(), ENUM_DIR_V), pw, ph);

        //初始化打印机
        send_all.clear();
        send_data.clear();
        send_data= tab_uart_manager->printer_InitFactoryReset_A27();
        send_all = send_all.append(send_data);
        tabmain_write_uart_data_file(uart_data_fp, send_data, "InitFactoryReset_A27");

        //设置纸张
        send_data.clear();
        send_data = tab_uart_manager->printer_PageSet_B02(VIEW_OFFSET_ROD_LEFT_MM, VIEW_OFFSET_ROD_TOP_MM, pw_pix, ph_pix, 0);
        send_all = send_all.append(send_data);
        tabmain_write_uart_data_file(uart_data_fp, send_data, "PageSet_B02");
    }
    else
    {
        qDebug("[AttrTabWidget--%s]>>Not have any item,No print!!!", __FUNCTION__);
        return;
    }


    for(int i = 0; i < list_items.size(); i++)
    {
	    int item_type = list_items[i]->type() - 65536;//UserType==65536,不知道UserType为什么引用不了

        qDebug("[AttrTabWidget--%s]>>item_type[%d]:%d", __FUNCTION__, i, item_type);

	    //根据类型来加载显示,定义一个枚举来区分此item是什么类型, 且是哪个item
	    switch(item_type)
	    {
	        case ENUM_TEXT_EDIT:		//2.设置文本绘制
	            {
                    QByteArray send_text;        //所有的数据
                    DrawTextItem *text_item_select = qgraphicsitem_cast<DrawTextItem*>(list_items[i]);
	                TextItemMetaPS text_meta = text_item_select->getTextEditMeta();
                    static qint8 count = 0;

                    send_text = tab_uart_manager->printer_TextEditSetPrint_B06(
                                text_meta.CoordRect.left()+ MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                text_meta.CoordRect.top(),// + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
	                            g_text_font_height[text_meta.height],
	                            text_item_select->getTextItemFontType(),
	                            text_meta.dataString,
	                            text_meta.dataString.size()
	                            );
                    send_all.append(send_text);
                    count++;                //打印元素次数计数
                    QString str_count = "Text_";
                    str_count += QString::number(count, 'count', 0);
                    tabmain_write_uart_data_file(uart_data_fp, send_text, str_count);
	            }
	            break;

            case ENUM_ONECODE_EDIT://3.设置一维码绘制参数
	            {
                       DrawOneCodeItem *onecode_item_select = qgraphicsitem_cast<DrawOneCodeItem*>(list_items[i]);
                       QByteArray send_onecode;        //所有的数据
                       static qint8 count = 0;

                       send_onecode = tab_uart_manager->printer_OneBarCodeEditSetPrint_B10(
                                                onecode_item_select->meta.CoordRect.left(),// + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                                onecode_item_select->meta.CoordRect.top(),//  + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
                                                onecode_item_select->getOneCodeTypePS(g_onecode_type_index[onecode_item_select->meta.type]),
                                                onecode_item_select->meta.CoordRect.height(),   //onecode_item_select->meta.viewRect.height()/2
                                                onecode_item_select->meta.uintw,                //编码宽
                                                onecode_item_select->meta.rotate,               //不旋转
                                                onecode_item_select->meta.dataString,
                                                onecode_item_select->meta.dataString.size()
                                   );
                       send_all.append(send_onecode);

                       count++;                //打印元素次数计数
                       QString str_count = "BarCode_";
                       str_count += QString::number(count, 'count', 0);
                       tabmain_write_uart_data_file(uart_data_fp, send_onecode, str_count);
	            }
	            break;

            case ENUM_TWOCODE_EDIT:     //设置二维码绘制
	            {
                    DrawTwoCodeItem *twocode_item_select = qgraphicsitem_cast<DrawTwoCodeItem*>(list_items[i]);
                    QByteArray send_twocode;        //所有的数据
                    static qint8 count = 0;

                    send_twocode = tab_uart_manager->printer_QRCodeEditSetPrint_B11(
                                            0x05,                           //ver
                                            twocode_item_select->meta.ecl,      //ecl
                                            twocode_item_select->meta.CoordRect.left() + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),  //x
                                            twocode_item_select->meta.CoordRect.top(),//  + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),   //y
                                            twocode_item_select->meta.uintw,           //uw
                                            0,              //ro
                                            twocode_item_select->meta.dataString,
                                            twocode_item_select->meta.dataString.size()
                                            );
                    send_all.append(send_twocode);

                    count++;                                                        //打印元素次数计数
                    QString str_count = "QRCode_";
                    str_count += QString::number(count, 'count', 0);

                    tabmain_write_uart_data_file(uart_data_fp, send_twocode, str_count);
	            }
	            break;

            case ENUM_LINE_EDIT:
                {
                    DrawLineItem *line_item = qgraphicsitem_cast<DrawLineItem*>(list_items[i]);
                    LineItemMetaPS meta = line_item->getLineEditMeta();
                    QByteArray send_line;        //所有的数据
                    static qint8 count = 0;


                    send_line = tab_uart_manager->printer_LineEditSetPrint_B07(
                                    (qint16)meta.start_point.x()  + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                    (qint16)meta.start_point.y(),// + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
                                    (qint16)meta.end_point.x()  + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                    (qint16)meta.end_point.y(),// + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
                                    (qint16)meta.pen.width(),
                                    (qint8)1//meta.pen.color()                      //固定为黑色线段
                                );
                    send_all.append(send_line);

                    count++;
                    QString str_count = "Line_";
                    str_count += QString::number(count, 'count', 0);

                    tabmain_write_uart_data_file(uart_data_fp, send_line, str_count);
                }
                break;

	        case ENUM_RECT_EDIT:
	            {
                    DrawRectItem *rect_item = qgraphicsitem_cast<DrawRectItem*>(list_items[i]);
                    RectItemMeta meta = rect_item->getRectMeta();
                    QByteArray send_rect;        //所有的数据
                    static qint8 count = 0;


                    send_rect = tab_uart_manager->printer_RectFrameEditSetPrint_B08(
                                    (qint16)meta.CoordRect.topLeft().x() + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                    (qint16)meta.CoordRect.topLeft().y(),// + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
                                    (qint16)meta.CoordRect.bottomRight().x() + MM2PIX_H(VIEW_OFFSET_ROD_LEFT_MM),
                                    (qint16)meta.CoordRect.bottomRight().y(),// + MM2PIX_V(VIEW_OFFSET_ROD_TOP_MM),
                                    (qint16)meta.pen.width(),
                                    (qint8)1//meta.pen.color()                   //固定为黑色线段
                                );
                    send_all.append(send_rect);

                    count++;                                                        //打印元素次数计数
                    QString str_count = "Rect_";
                    str_count += QString::number(count, 'count', 0);

                    tabmain_write_uart_data_file(uart_data_fp, send_rect, str_count);
	            }
	            break;

	        default:
	            {

	            }
	            break;
	    }
   }

    //追加内容打印完毕的结束语句
    send_data.clear();
    send_data = tab_uart_manager->printer_PageOver_B03();
    send_all.append(send_data);
    tabmain_write_uart_data_file(uart_data_fp, send_data, "PageOver_B03");

    //打印语句
    send_data.clear();
    send_data = tab_uart_manager->printer_PagePrint_B04(0x01);
    send_all.append(send_data);          //页结束
    tabmain_write_uart_data_file(uart_data_fp, send_data, "PagePrint_B04");

    //切纸
    send_data.clear();
    send_data = tab_uart_manager->printer_CutDownPaper_A25();
    send_all.append(send_data);
    tabmain_write_uart_data_file(uart_data_fp, send_data, "CutDownPaper_A25");


    //新增需求,要把串口数据保存在文件中
    uart_data_fp->close();

    //把发送的数据放到串口的发送显示框
    tab_uart_manager->send_plain_text->clear();
    QString send_str;
    for(int i = 0; i < send_all.size(); i++)
    {
        //send_str += "0X";                                                        //可以根据item的长度，决定是否在前面叫0，补足两位数
        send_str = send_str.append(QString::number((quint8)send_all.at(i), 16));           //16进制数字转为16进制字符串,一定要强制转换类型(quint8)
        send_str = send_str.toUpper();

//        if(i == (send_all.size() - 1))
//            str += "\n";
//        else
            send_str += " ";         //空格
    }
    tab_uart_manager->send_plain_text->setPlainText(send_str);


    //最后发送数据
    //this->tab_uart_manager->uart_send_HEX_byte(send_all);
    emit printerUart_sendDataToPrinter(send_all);

    //再全切一次，切纸,最好切三次
    //this->tab_uart_manager->uart_send_cut_over_slots();
}

/*
    把串口数据保存在文件中
*/
bool MainWindow::tabmain_creaet_uart_data_file(QFile *fp)
{
    //创建目录操作示例
    QDir *dir = new QDir;
    QString dir_pathname;


    dir_pathname = dir_pathname.append(SAVE_DIR_PATH);
    dir_pathname = dir_pathname.append(SAVE_DIR_NAME);


    if(dir->exists(dir_pathname))
    {
        qDebug("[DrawLabel--%s]>>目录已经存在,不需要再创建,%s", __func__, qPrintable(dir_pathname));
    }
    else
    {
        bool ret = dir->mkdir(dir_pathname);
        if(ret)
        {
            qDebug("[DrawLabel--%s]>>目录创建成功,%s", __func__, qPrintable(dir_pathname));
        }
        else
        {
            qDebug("[DrawLabel--%s]>>目录创建失败,%s", __func__, qPrintable(dir_pathname));
            QMessageBox::warning(NULL, tr("dir"), tr("create dir fail!"));
            return false;
        }
    }


    //目录创建后,开始创建文件
    //文件操作
    //QFile fp;
    QString file_name;

    file_name.append(wal->meta.name);
    file_name.append(SAVE_UART_DATA_FILE_NAME);

    QString filename = dir_pathname.append(file_name);
    fp->setFileName(filename);

    if(fp->exists())
    {
        //QMessageBox::warning(NULL, tr("file"), tr("file exist"));
        //return false;
        //如果文件 已经存在,先删除文件
        qDebug("[DrawLabel--%s]>>file exist,delete!", __func__);
        fp->remove();


        //如果保存多分,则按文件保存
//        QString str;
//        QDateTime time;
//        time = QDateTime::currentDateTime();
//        str = time.toString("yyyy-MM-dd hh:mm:ss");   // strBuffer = 2010-07-02 17:35:00
    }


    if(!fp->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("[DrawLabel--%s]>>open failed! %s", __func__, qPrintable(filename));
        return false;
    }
}

/**
 * @brief MainWindow::tabmain_write_uart_data_file
 *          写串口数据文件,对数据序列化后，输出到文件
 *          ！！！QByteArray取出来的单字节,一定要强制转换类型(quint8)
 * @param qba
 * @return
 */
bool MainWindow::tabmain_write_uart_data_file(QFile *fp, QByteArray qba, QString extra_str)
{
    QString str;


    for(int i = 0; i < qba.size(); i++)
    {
        if(i == 0)
        {
            str += extra_str;
            str += "={";                                                     //可以根据item的长度，决定是否在前面叫0，补足两位数
        }
        str += "0X";                                                        //可以根据item的长度，决定是否在前面叫0，补足两位数
        str = str.append(QString::number((quint8)qba.at(i), 16));           //16进制数字转为16进制字符串,一定要强制转换类型(quint8)
        str = str.toUpper();

        if(i == (qba.size() - 1))
            str += "};\n";
        else
            str += ", ";
    }


    fp->write(str.toUtf8());
}

/**
 * @brief MainWindow::destroyLayoutWidget
 * @param layout
 */
void MainWindow::destroyLayoutWidget(QLayout* layout)
{
    QLayoutItem *child;
    int num = layout->count();

    if(num != 0)
    {
        while (!layout->isEmpty())
        {
            child = layout->takeAt(0);
            if(child->widget())
            {
                child->widget()->setParent(nullptr);
            }
            else if(child->layout())
            {
                destroyLayoutWidget(child->layout());
            }
            delete child;
        }
    }
}
