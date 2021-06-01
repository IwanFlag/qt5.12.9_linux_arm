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


//!!!!!!!!!!!!!!

// Grid bu ju ,zhi you quan bu peizhi wancheng  ,caihui  youshengxiao "columSPAN",diu

//Packet menu
Rectangle {
    id: compPacketMenu
    visible: true
    x: compFactoryStatusBar.x
    y: compFactoryStatusBar.height         //50//compFactoryStatusBar.bottom
    width: parent.width
    height: parent.height - compFactoryStatusBar.height
    color: "gray"


    //title
    Rectangle{
        id:compFactoryTitleBar
        width: parent.width
        height: 50


        Row{
            anchors.fill: parent
            Rectangle{
                width: parent.width/2
                height: 50
                //color: "red"
                Label{
                    //id: name
                    text: qsTr("Product")
                    //anchors.fill: parent
                    //anchors.centerIn: parent
                    font.pointSize: 20
                    }
                }

            Rectangle{
                //color: "green"

                width: parent.width/2
                height: 50

                Button{
                    id: bt_return
                    text: "return"
                    anchors.fill: parent
                    onClicked:{
                        console.log("bt_return");
                        compPacketMenu.visible = false;
                        compFactoryMenu.visible = true;
                    }
                }
            }
        }
    }

    //gridlayout
    Rectangle{
        color: "blue"
        anchors.top: compFactoryTitleBar.bottom
        width: parent.width;
        height: parent.height - bt_return.height

        GridLayout{
//            id: menu_grid;
            columns: 5;
//            rows: 4;
//            width: parent.width
//            height: parent.height
            anchors.fill: parent
            anchors.margins: 5;
            columnSpacing: 10;
            rowSpacing: 10;


            //1.1 readImei
            Rectangle{
                    id: readImei
//                    color: "blue";
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度
                    Text {
                        id: txt_showImei
                        text: qsTr("pls sweep TwoCode")
                        //anchors.centerIn: parent
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }

            //1.2
            Rectangle{
                    id: showImei
                    Layout.preferredWidth: 4
                    Layout.columnSpan: 4

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        //id: txt_showImei
                        //text: qsTr("txt_showImei")
                        //anchors.centerIn: parent
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }


            //2.1
            Rectangle{
                    //id: readImei
//                    color: "blue";
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度
                    Text {
                        //id: txt_showImei
                        text: qsTr("pls sweep TwoCode")
                        //anchors.centerIn: parent
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }

            //2.2 showImei
            Rectangle{
                    //id: showImei
                    Layout.preferredWidth: 4
                    Layout.columnSpan: 4

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        //id: txt_showImei
                        //text: qsTr("txt_showImei")
                        //anchors.centerIn: parent
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }


            //3.1 clear
            Rectangle{
//                    Layout.preferredWidth: 20
//                    Layout.columnSpan: 1
                Layout.row:  3
                Layout.column: 1

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_clear
                        text: qsTr("clear")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
    //                            font.family: "Helvetica"
                                font.pointSize: 20
    //                            color: "blue"
                                text: control.text
                                         }
                            }
                        onClicked:{
                            console.log("bt_clear");
                        }
                    }

            }

            //3.2 print
            Rectangle{
//                Layout.preferredWidth: 20
//                Layout.columnSpan: 1
                Layout.row:  3
                Layout.column: 3

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_bind
                        text: qsTr("bind")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
    //                            font.family: "Helvetica"
                                font.pointSize: 20
    //                            color: "blue"
                                text: control.text
                              }
                        }

                        onClicked:{
                            console.log("bt_bind");
                        }
                    }
            }

            //4.1
            Rectangle{
                Layout.row:  4
                Layout.column: 0

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                id:combox
                                anchors.centerIn: parent
                                currentIndex: 0
                                model: ListModel {
                                    id: cbItems
                                    ListElement { text: "1 page"; color: "Yellow" }
                                    ListElement { text: "2 page"; color: "Yellow" }
                                    ListElement { text: "3 page"; color: "Yellow" }

                                }
                                //width: 160
                                onCurrentIndexChanged: {
//                                                if(currentIndex==0){
//                                                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//                                                    console.debug("0")
//                                                }
//                                                if(currentIndex==1){
//                                                     console.debug("1")
//                                                }
                                                    }
                                }
            }

            //4.2
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                //id:combox
                                anchors.centerIn: parent
                                currentIndex: 0
                                model: ListModel {
                                    //id: cbItems
                                    ListElement { text: "2 into 1"; color: "Yellow" }
                                    ListElement { text: "3 into 1"; color: "Yellow" }
                                    ListElement { text: "4 into 1"; color: "Yellow" }

                                }
                                //width: 160
                                onCurrentIndexChanged: {
//                                                if(currentIndex==0){
//                                                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//                                                    console.debug("0")
//                                                }
//                                                if(currentIndex==1){
//                                                     console.debug("1")
//                                                }
                                                    }
                                }
            }

            //4.2
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                //id:combox
                                anchors.centerIn: parent
                                currentIndex: 0
                                model: ListModel {
                                    //id: cbItems
                                    ListElement { text: "small printer"; color: "Yellow" }
                                    ListElement { text: "big printer"; color: "Yellow" }

                                }
                                //width: 160
                                onCurrentIndexChanged: {
//                                                if(currentIndex==0){
//                                                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//                                                    console.debug("0")
//                                                }
//                                                if(currentIndex==1){
//                                                     console.debug("1")
//                                                }
                                                    }
                                }
            }


            //4.3
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                //id:combox
                                anchors.centerIn: parent
                                currentIndex: 0
                                model: ListModel {
                                    //id: cbItems
                                    ListElement { text: "CN"; color: "Yellow" }
                                    ListElement { text: "USA"; color: "Yellow" }

                                }
                                //width: 160
                                onCurrentIndexChanged: {
//                                                if(currentIndex==0){
//                                                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//                                                    console.debug("0")
//                                                }
//                                                if(currentIndex==1){
//                                                     console.debug("1")
//                                                }
                                                    }
                                }
            }

            //4.4
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                //id:combox
                                anchors.centerIn: parent
                                currentIndex: 0
                                model: ListModel {
                                    //id: cbItems
                                    ListElement { text: "CutPaper"; color: "Yellow" }
                                    ListElement { text: "NoCutPaper"; color: "Yellow" }

                                }
                                //width: 160
                                onCurrentIndexChanged: {
//                                                if(currentIndex==0){
//                                                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//                                                    console.debug("0")
//                                                }
//                                                if(currentIndex==1){
//                                                     console.debug("1")
//                                                }
                                                    }
                                }
            }
        }
    }
}
