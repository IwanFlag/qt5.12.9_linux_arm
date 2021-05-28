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
    id: compServiceMenu
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
            compServiceMenu.visible = false;
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


        //1.1 setWIFI
        Rectangle{
                width: compServiceMenu.grid_w * 2
                height: compServiceMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_readImei
                    text: qsTr("txt_setWIFI")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("txt_setWIFI");
                    }
                }
        }

        //1.2 txt_showWIFI
        Rectangle{
                width: compServiceMenu.grid_w * 2
                height: compServiceMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    id: txt_showWIFI
                    text: qsTr("txt_showWIFI")
                    anchors.centerIn: parent
                    font.pointSize:              14;
                }
        }

        //2.1 setAPN
        Rectangle{
                width: compServiceMenu.grid_w * 2
                height: compServiceMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_readImei
                    text: qsTr("txt_setAPN")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("txt_setAPN");
                    }
                }
        }

        //2.2 setFactoryWIFI
        Rectangle{
                width: compServiceMenu.grid_w * 2
                height: compServiceMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    text: qsTr("txt_setFactoryWIFI")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("setFactoryWIFI");
                    }
                }
        }


        //2.2 clearWIFI
        Rectangle{
                width: compServiceMenu.grid_w * 2
                height: compServiceMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    text: qsTr("txt_clearWIFI")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("clearWIFI");
                    }
                }
        }
    }
}
