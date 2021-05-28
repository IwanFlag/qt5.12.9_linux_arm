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
    id: compSendOutMenu
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
        //y:factoryToolstatusBar.height
        //anchors.top: factoryToolstatusBar.bottom
        text: "return"
        height: factoryToolstatusBar.height
        onClicked:{
            console.log("bt_return");
            //close present page
            compSendOutMenu.visible = false;
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


        //1.1 readFile
        Rectangle{
                id: readImei
                width: compSendOutMenu.grid_w * 2
                height: compSendOutMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_readImei
                    text: qsTr("readFile")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2

                    onClicked:{
                        console.log("readFile");

                    }
                }
        }

        //2.1 txt_plsName
        Rectangle{
                id: showImei
                width: compSendOutMenu.grid_w * 2
                height: compSendOutMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Text {
                    id: txt_showImei
                    text: qsTr("txt_plsName")
                    anchors.centerIn: parent
                    font.pointSize:              14;
                }
        }

        //2.2 inputName
        Rectangle{
                id: readSimnum
                width: compSendOutMenu.grid_w * 2
                height: compSendOutMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                TextInput {
                            id: val_inputName
                            anchors.fill: parent
                            font.pointSize:              14;
                }
        }

        //3.1 clear
        Rectangle{
                //id: showSimnum
                width: compSendOutMenu.grid_w * 2
                height: compSendOutMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Button{
                    id: bt_clear
                    text: qsTr("clear")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("clear");
                    }
                }
        }

        //3.2 sweepCode
        Rectangle{
                //id: re_TwoCode
                width: compSendOutMenu.grid_w * 2
                height: compSendOutMenu.grid_h
                //color: "blue";
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Button{
                    id: bt_sweepCode
                    text: qsTr("sweepCode")
                    width: parent.width
                    height: parent.height
                    Layout.columnSpan: 2
                    onClicked:{
                        console.log("sweepCode");
                             }
                    }
                }
    }
}
