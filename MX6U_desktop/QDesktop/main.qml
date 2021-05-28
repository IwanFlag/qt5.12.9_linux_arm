/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2030. All rights reserved.
* @projectName   QDesktop
* @brief         main.qml
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @date          2020-07-31
*******************************************************************/
import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Controls 1.2
import an.weather 1.0
import an.model 1.0
import myDesktop 1.0
import QtQuick.Layouts 1.1

import "./calculator"
import "./weather"
import "./desktop"
import "./music"
import "./media"
import "./wireless"
import "./fileview"
import "./tcpclient"
import "./tcpserver"
import "./alarms"
import "./udpchat"
import "./photoview"
import "./aircondition"
import "./iotest"
import "./sensor"
import "./system"
import "./radio"
import "./settings"
import "./cameramedia"
import "./login"


ApplicationWindow {
    id: mainWindow
    visible: true
    width: WINenv ? 480 : Screen.desktopAvailableWidth
    height: WINenv ? 320 : Screen.desktopAvailableHeight
    property bool smallScreen: width == 480 ? true : false
    title: qsTr("soudian")
    color: "gray"
    //flags:  Qt.FramelessWindowHint


    //login frame:
    Login{
        id: compLogin
        visible: true
//        width: parent.width
//        height: parent.height
        anchors.fill: parent
        color: "gray"
    }
}
