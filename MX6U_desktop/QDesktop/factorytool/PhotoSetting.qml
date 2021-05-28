import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Controls 1.2
import "../helpbutton"
import myDesktop 1.0
import QtQuick.Layouts 1.1


//productMenu
Rectangle {
    id: compPhotoSettingMenu
    visible: true
    x: compFactoryStatusBar.x
    y: compFactoryStatusBar.height         //50//compFactoryStatusBar.bottom
    width: parent.width
    height: parent.height - compFactoryStatusBar.height
    color: "gray"
    property int grid_w: Screen.desktopAvailableWidth/4   //100
    property int grid_h: 60 //Screen.desktopAvailableHeight/4         //60

    //
//        signal login_verify_signal(string name, string pwd)
    Component.onCompleted:
    {
        //qml 信号 连接 c++ slot
//            login_verify_signal.connect(lg.login_verift_slot);
    }

    Button{
        id: bt_return
        x: parent.width - bt_return.width
        //y:compFactoryStatusBar.height
        //anchors.top: compFactoryStatusBar.bottom
        text: "return"
        height: compFactoryStatusBar.height
        onClicked:{
            console.log("bt_return");
            //close present page
            compPhotoSettingMenu.visible = false;
            compFactoryMenu.visible = true;
        }
    }

    //gridlayout
    GridLayout{
        id: menu_grid;
        columns: 4;
        rows: 4;
        anchors.top: bt_return.bottom
        width: parent.width;
        height: parent.height - bt_return.height
//        anchors.fill: parent
        anchors.margins: 5;
        columnSpacing: 50;
        rowSpacing: 50;
        //anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter


        //1.1 readImei
        Rectangle{
                id: readImei
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_readImei
                    text: "readImei"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2

                    onClicked:{
                        console.log("readImei");

//                        // 隐藏登录页面
//                        compFactoryTool.visible = false;

//                        // 在主窗口（mainWindow）上显示主页面
//                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Product.qml").createObject(mainWindow, {});
                    }
                }
        }

        //1.2 showImei
        Rectangle{
                id: showImei
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    id: txt_showImei
                    text: qsTr("txt_showImei")
                    anchors.centerIn: parent
                    font.pointSize:              14;
                }
        }

        //1.3 readSimnum
        Rectangle{
                id: readSimnum
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_readSimnum
                    text: "readSimnum"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("readSimnum");
                    }
                }
        }

        //1.4 showSimnum
        Rectangle{
                id: showSimnum
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_showSimnum
                    text: "showSimnum"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("showSimnum");
                    }
                }
        }

        //2.1 re_TwoCode
        Rectangle{
                id: re_TwoCode
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                    Text {
                        //id: name
                        text: qsTr("TwoCode")
                        }
                }

        //2.2 showTwoCode
        Rectangle{
                id: showTwoCode
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    //id: name
                    text: qsTr("showTwoCode")
                }
        }

        //2.3 re_adaptor
        Rectangle{
                id: re_adaptor
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                    Text {
                        //id: name
                        text: qsTr("adaptor")
                        }
                }

        //2.4 showAdaptor
        Rectangle{
                id: showAdaptor
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    //id: name
                    text: qsTr("showAdaptor")
                }
        }

        //3.1 ??
        Rectangle{
                id: lineTxt_show
                width: compPhotoSettingMenu.grid_w * 2
                height: compPhotoSettingMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.columnSpan: 4
                Text {
                    //id: name
                    text: qsTr("lineTxt_show")
                    }
                }

        //4.1 clear
        Button{
            id: bt_clear
            text: "clear"
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            onClicked:{
                console.log("bt_clear");
            }
        }

        //4.2 bind
        Button{
            id: bt_bind
            text: "bind"
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            onClicked:{
                console.log("bt_bind");
            }
        }

        //4.3 unbind
        Button{
            id: bt_unbind
            text: "unbind"
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            onClicked:{
                console.log("bt_unbind");
            }
        }

        //4.4 popup
        Button{
            id: bt_popup
            text: "popup"
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            onClicked:{
                console.log("bt_popup");
            }
        }
    }
}
