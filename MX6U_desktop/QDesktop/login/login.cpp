#include "login.h"
#include <QtGui/QGuiApplication>
//#include "qtquick2applicationviewer.h"
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>
#include <QMessageBox>

#include <QQmlApplicationEngine>
#include <QQmlContext>


Login::Login(QObject *parent) :
    QObject(parent)
{

}

/**
 * @brief Login::login_verift_slot
 * user name and pwd is ok?
 */
void Login::login_verift_slot(QString name, QString pwd)
{
//    qDebug("Login--%s>>name:%s, pwd:%s", __func__, qPrintable(name), qPrintable(pwd));
//    if((QString::compare(name, "sd", Qt::CaseInsensitive) == 0)
//            &&(QString::compare(pwd, "123", Qt::CaseInsensitive) == 0))
//     {
         qDebug("Login--%s>>", __func__);
         QQmlApplicationEngine engine;
         engine.load(QUrl(QStringLiteral("qrc:/factorytool/Factorytool.qml")));
         QList<QObject*> objs = engine.rootObjects();
         //objs.at(0)->setProperty("visible", false);

         objs.at(1)->setProperty("visible", true);
//    }
//    else
//    {
//        QMessageBox::about(NULL, tr("Login"), tr("user name or pwd error!"));
//    }
}

