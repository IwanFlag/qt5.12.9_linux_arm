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
    //width: 640
    //height: 480
    width: WINenv ? 480 : Screen.desktopAvailableWidth
    height: WINenv ? 320 : Screen.desktopAvailableHeight
    property bool smallScreen: width == 480 ? true : false
    title: qsTr("sd factory tool")
    color: "gray"
    //flags:  Qt.FramelessWindowHint


    //status bar
    StatusBar{
        id: statusBar
        visible: true
        width: parent.width
        height: 50


        //row layout
        RowLayout{
            spacing: 20  //相邻间距

            //conn status
            Text{
                id:tcp_conn_status
                text: qsTr("not connect")
                height: statusBar.height

                font.bold:  true;
                font.pointSize:              18;
            }

            //remote ip addr
            Text{
                id:remote_ip_addr
                text: qsTr("127.0.0.1")
                height: statusBar.height

                font.bold:  true;
                font.pointSize:              18;

            }

            //nowtimestamp
            Text{
                id:nowtimestamp
                text: qsTr("2021.5.26 15:17:01")
                height: statusBar.height

                font.bold:  true;
                font.pointSize:              18;
            }
        }
    }


    //login frame:
    Login{}
}
