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
    width: WINenv ? 800 : Screen.desktopAvailableWidth
    height: WINenv ? 480 : Screen.desktopAvailableHeight
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
    Rectangle {
        id: login_rect
        visible: true
        x: statusBar.x
        y: statusBar.height         //50//statusBar.bottom
        width: parent.width
        height: parent.height - statusBar.height
        color: "gray"
        property int grid_w: 100
        property int grid_h: 60

        //
        //signal login_verify_signal(int ret)
        signal login_verify_signal(string name, string pwd)
        //signal btn_2dec_click(string str_num)
        Component.onCompleted:
        {
            //qml 信号 连接 c++ slot
            login_verify_signal.connect(lg.login_verift_slot);
        }


        //gridlayout
        GridLayout{
            id: login_grid;
            columns: 2;
            rows: 4;
            anchors.margins: 5;
            columnSpacing: 20;
            rowSpacing: 20;
            //anchors.centerIn: parent
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.verticalCenter: parent.verticalCenter


            //welcome tips
            Rectangle{
                    width: login_rect.grid_w
                    height: login_rect.grid_h
                    color: "lightgray";
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Layout.columnSpan: 2

                    Text {
                        id: login_text
                        text: qsTr("Welcome")
                        anchors.centerIn: parent
                        font.pointSize:              24;
                    }
            }

            //user name
            Rectangle{
                    width: login_rect.grid_w
                    height: login_rect.grid_h
                    color: "lightgray";
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        id: txt_user_name
                        text: qsTr("user name")
                        anchors.centerIn: parent
                        font.pointSize:              14;
                    }
            }

            //user name input
            Rectangle{
//                    id: val_user_name
                    width: login_rect.grid_w * 2
                    height: login_rect.grid_h
                    //color: "blue";
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    TextInput {
                                id: val_user_name
                                anchors.fill: parent
                                font.pointSize:              14;
                    }
            }

            //user pwd
            Rectangle{
                    width: login_rect.grid_w
                    height: login_rect.grid_h
                    color: "lightgray";
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        id: txt_user_pwd
                        text: qsTr("user pwd")
                        anchors.centerIn: parent
                        font.pointSize:              14;
                    }
            }

            //user input
            Rectangle{
                    //id: val_user_pwd
                    width: login_rect.grid_w * 2
                    height: login_rect.grid_h
                    //color: "blue";
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    TextInput {
                                id: val_user_pwd
                                anchors.fill: parent
                                font.pointSize:              14;
                    }
            }

            //function void login_verift
            //login button
            Button{
                id: login_button
                text: "Login"
                width: login_rect.grid_w / 2
                height: login_rect.grid_h
                Layout.columnSpan: 2
                onClicked:{
                    console.log("login:%s,%s", val_user_name.text, val_user_pwd.text);
                    if(val_user_name.text === "sd" && val_user_pwd.text == "123")
                    {
                        console.log("login:ok");
                    }
                    else
                    {
                        console.log("login:error!");

                    }
                    login_rect.login_verify_signal(val_user_name.text, val_user_pwd.text);
                    //Settings.visible = true;
                }
            }
        }
    }


    //
    Login{}
}
