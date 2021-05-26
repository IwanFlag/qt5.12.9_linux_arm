#include "login.h"
#include <QtGui/QGuiApplication>
//#include "qtquick2applicationviewer.h"
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>



Login::Login(QObject *parent) :
    QObject(parent)
{

}

/**
 * @brief Login::login_verift_slot
 * user name and pwd is ok?
 */
void Login::login_verift_slot(int val)
{
    qDebug("Login--%s>>val:%d", __func__, val);
}
