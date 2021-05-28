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
import "../factorytool"


//login frame:
Rectangle {


    //
    signal login_verify_signal(string name, string pwd)
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
        property int grid_w: 200
        property int grid_h: 60

        //welcome tips
        Rectangle{
                width:parent.grid_w
                height: parent.grid_h
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
                width: parent.grid_w
                height: parent.grid_h
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
                width: parent.grid_w * 2
                height: parent.grid_h
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
                width: parent.grid_w
                height: parent.grid_h
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
                width: parent.grid_w * 2
                height: parent.grid_h
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
            width: parent.grid_w / 2
            height: parent.grid_h
            Layout.columnSpan: 2
            onClicked:{
                console.log("login:%s,%s", val_user_name.text, val_user_pwd.text);
                //parent.login_verify_signal(val_user_name.text, val_user_pwd.text);

                // 隐藏登录页面
                parent.visible = false;
                // 在主窗口（mainWindow）上显示主页面
                //var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Factorytool.qml").createObject(mainWindow, {x:50, y:50, width:200, height:250});
//                var compFactorytoolPage = Qt.createComponent("qrc:/main.qml").createObject(mainWindow, {});
                var compFactorytoolPage = Qt.createComponent("qrc:/homeMenu.qml").createObject(mainWindow, {});
            }
        }
    }
}
