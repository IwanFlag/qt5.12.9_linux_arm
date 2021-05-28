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


//PacketMenu
Rectangle {
    id: compPacketMenu
    visible: true
    x: factoryToolstatusBar.x
    y: factoryToolstatusBar.height         //50//factoryToolstatusBar.bottom
    width: parent.width
    height: parent.height - factoryToolstatusBar.height
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
        text: "return"
        height: factoryToolstatusBar.height
        onClicked:{
            console.log("bt_return");
            //close present page
            compPacketMenu.visible = false;
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


        //1.1 re_TwoCode
        Rectangle{
                id: re_TwoCode
                width: compPacketMenu.grid_w * 2
                height: compPacketMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                    Text {
                        //id: name
                        text: qsTr("TwoCode")
                        }
                }

        //1.2 showTwoCode
        Rectangle{
                id: showTwoCode
                width: compPacketMenu.grid_w * 2
                height: compPacketMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    //id: name
                    text: qsTr("showTwoCode")
                }
        }

        //1.3 re_adaptor
        Rectangle{
                id: re_adaptor
                width: compPacketMenu.grid_w * 2
                height: compPacketMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                    Text {
                        //id: name
                        text: qsTr("adaptor")
                        }
                }

        //1.4 showAdaptor
        Rectangle{
                id: showAdaptor
                width: compPacketMenu.grid_w * 2
                height: compPacketMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    //id: name
                    text: qsTr("showAdaptor")
                }
        }


        //2.1 clear
        Button{
            id: bt_clear
            text:qsTr("clear")
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            Layout.columnSpan: 2
            onClicked:{
                console.log("bt_clear");
            }
        }

        //2.2 print
        Button{
            id: bt_bind
            text: qsTr("print");
            width: compLogin.grid_w / 2
            height: compLogin.grid_h
            onClicked:{
                console.log("bt_bind");
            }
        }


    }
}
