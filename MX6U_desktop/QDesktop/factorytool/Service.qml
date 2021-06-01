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

//compServiceMenu
Rectangle {
    id: compServiceMenu
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
                    text: qsTr("SendOut")
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
                        compServiceMenu.visible = false;
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
            columns: 4;
            anchors.fill: parent
            anchors.margins: 5;
            columnSpacing: 10;
            rowSpacing: 10;


            //0.1 file
            Rectangle{
//                Layout.preferredWidth: 20
                Layout.columnSpan: 1
//                Layout.row:  0
//                Layout.column: 4

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_bind
                        text: qsTr("WiFi Config")
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
                            console.log("bt_file");
                        }
                    }
            }


            //0.2
            Rectangle{
                    //id: showImei
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

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


            //1.1 APN Config
            Rectangle{
//                    Layout.preferredWidth: 20
//                    Layout.columnSpan: 1
                Layout.row:  1
                Layout.column: 1
                Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_clear
                        text: qsTr("APN Config")
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

            //1.1 FactoryWIFISet
            Rectangle{
//                Layout.preferredWidth: 20
//                Layout.columnSpan: 1
//                Layout.row:  3
//                Layout.column: 3
                Layout.row:  2
                Layout.column: 1
                Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        //id: bt_bind
                        text: qsTr("FactoryWIFISet")
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

            //2.2 SweepCode
            Rectangle{
//                Layout.preferredWidth: 20
//                Layout.columnSpan: 1
                Layout.row:  3
                Layout.column: 1
                Layout.columnSpan: 2

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        //id: bt_bind
                        text: qsTr("ClearWIFI")
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
        }
    }
}
