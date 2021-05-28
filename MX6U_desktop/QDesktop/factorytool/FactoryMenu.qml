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


//factoryToolMenu
Rectangle {
    id: compFactoryMenu
    visible: true
    x: factoryToolstatusBar.x
    y: factoryToolstatusBar.height         //50//factoryToolstatusBar.bottom
    width: parent.width
    height: parent.height - factoryToolstatusBar.height
    color: "gray"
    property int grid_w: Screen.desktopAvailableWidth/4   //100
    property int grid_h: Screen.desktopAvailableHeight/4         //60

    //
//        signal login_verify_signal(string name, string pwd)
    Component.onCompleted:
    {
        //qml 信号 连接 c++ slot
//            login_verify_signal.connect(lg.login_verift_slot);
    }


    //gridlayout
    GridLayout{
        id: menu_grid;
        columns: 4;
        rows: 4;
        anchors.fill: parent
        anchors.margins: 5;
        columnSpacing: 50;
        rowSpacing: 50;
        //anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter


        //1.product menu
        Rectangle{
                id: product_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_product_menu
                    text: "product"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("product");

                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Product.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 1;
                    }
                }
        }

        //2.packet menu
        Rectangle{
                id: package_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_package_menu
                    text: "packet"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("packet");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Packet.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 2;

                    }
                }
        }

        //3.sendOut
        Rectangle{
                id: sendOut_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_sendOut_menu
                    text: "sendOut"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("sendOut_menu");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/SendOut.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 3;
                    }
                }
        }

        //4.service menu
        Rectangle{
                id: service_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_service_menu
                    text: "service"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("service");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Service.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 4;
                    }
                }
        }


        //5.setting menu
        Rectangle{
                id: setting_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_setting_menu
                    text: "setting"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("setting");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/Setting.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 5;
                    }
                }
        }


        //6.photo_setting menu
        Rectangle{
                id: photo_setting_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_photo_setting_menu
                    text: "photo_setting"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("photo_setting");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/PhotoSetting.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 6;
                    }
                }
        }

        //7.sweepCode menu
        Rectangle{
                id: sweepCode_menu
                width: compLogin.grid_w * 2
                height: compLogin.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_sweepCode_menu
                    text: "sweepCode"
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("sweepCode");
                        // 隐藏登录页面
                        compFactoryMenu.visible = false;
                        // 在主窗口（mainWindow）上显示主页面
                        var compFactorytoolPage = Qt.createComponent("qrc:/factorytool/PhotoSetting.qml").createObject(mainWindow, {});
                        compFactoryTool.sonMenuIndex = 7;
                    }
                }
        }
    }
}
