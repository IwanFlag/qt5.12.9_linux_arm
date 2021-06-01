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

//productMenu
Rectangle {
    id: compProductMenu
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
                        compProductMenu.visible = false;
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
            columns: 8;
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


                    Button{
                        id: bt_readImei
                        text: qsTr("readImei")
                        //                    width: parent.width
                        //                    height: parent.height
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
                                console.log("readImei");
                            }
                    }
            }

            //1.2 showImei
            Rectangle{
                    id: showImei
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        id: txt_showImei
                        //text: qsTr("txt_showImei")
                        //anchors.centerIn: parent
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //1.3 readSimnum
            Rectangle{
                    id: readSimnum
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    Button{
                        id: bt_readSimnum
                        text: qsTr("readSimnum")
    //                    width: parent.width
    //                    height: parent.height
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
                            console.log("readSimnum");
                        }
                    }
            }

            //1.4 showSimnum
            Rectangle{
                    id: showSimnum
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Text {
                        //id: txt_showImei
                        //text: qsTr("txt_showImei")
                        //anchors.centerIn: parent
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }

            //2.1 re_TwoCode
            Rectangle{
                    id: re_TwoCode
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                        Label{
                            //id: name
                            text: qsTr("pls sweep TwoCode:")
                            //anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 20
                            }
                    }

            //2.2 showTwoCode
            Rectangle{
                    id: showTwoCode
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                            //id: name
                            //text: qsTr("showTwoCode")
                            anchors.fill: parent
                    }
            }

            //2.3 re_adaptor
            Rectangle{
                    id: re_adaptor
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Label{
                        //id: name
                        text: qsTr("adaptor:")
                        //anchors.fill: parent
                        anchors.centerIn: parent
                        font.pointSize: 20
                        }
                    }

            //2.4 showAdaptor
            Rectangle{
                    id: showAdaptor
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;

                    Text {
                        //id: name
                        //text: qsTr("showAdaptor")
                        anchors.fill: parent

                    }
            }

            //3.1 ??
            Rectangle{
                    id: lineTxt_show
                    Layout.row:  3
                    Layout.column: 1
                    Layout.preferredWidth: 6
                    Layout.columnSpan: 6
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        //id: name
                        //text: qsTr("lineTxt_show")
                        anchors.fill: parent

                        }
                    }

            //4.1 clear
            Rectangle{
                Layout.row:  4
                Layout.column: 2
                    Layout.preferredWidth: 20
                    Layout.columnSpan: 1
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

            //4.2 bind
            Rectangle{
                Layout.row:  4
                Layout.column: 3
                Layout.preferredWidth: 20
                Layout.columnSpan: 1

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


            //4.3 unbind
            Rectangle{
                Layout.row:  4
                Layout.column: 4
                Layout.preferredWidth: 20
                Layout.columnSpan: 1

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_unbind
                        text: qsTr("unbind")
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
                            console.log("bt_unbind");
                        }
                    }
            }


            //4.4 popup
            Rectangle{
                Layout.row:  4
                Layout.column: 5
                Layout.preferredWidth: 20
                Layout.columnSpan: 1

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Button{
                        id: bt_popup
                        text: qsTr("popup")
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
                            console.log("bt_popup");
                        }
                    }
            }
        }
    }
}
