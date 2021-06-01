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

//SettingMenu
Rectangle {
    id: compSettingMenu
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
                color: "lightgray"
                Label{
                    //id: name
                    text: qsTr("Product")
                    //anchors.fill: parent
                    //anchors.centerIn: parent
                    font.pointSize: 20
                    }
                }

            Rectangle{
                color: "lightgray"

                width: parent.width/2
                height: 50

                Button{
                    id: bt_return
                    text: "return"
                    anchors.fill: parent
                    onClicked:{
                        console.log("bt_return");
                        compSettingMenu.visible = false;
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
            columns: 2;
            anchors.fill: parent
            anchors.margins: 5;
            columnSpacing: 10;
            rowSpacing: 10;

                //wifi
                GridLayout{
                    columns: 3;
                        Rectangle{
                                //id: readImei
                                color: "lightgray"
                                Layout.columnSpan: 3
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                    Text {
                                        //id: name
                                        text: qsTr("Setting WIFI")
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignHCenter
            //                            font.family: "Helvetica"
                                        font.pointSize: 20

                                    }
                        }

                        Rectangle{
                                //id: readImei
                            color: "lightgray"
                                Layout.columnSpan: 1
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                    Text {
                                        //id: name
                                        text: qsTr("WIFI Num")
                                        Layout.alignment: horizontalCenter|  verticalCenter
                                    }
                        }

                        Rectangle{
                                //id: readImei
                            //color: "lightgray"
                                Layout.columnSpan: 2
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                TextInput {
                                        id: val_user_pwd
                                        anchors.fill: parent
                                        font.pointSize:              14;
                                        color: "lightgray"
                                }
                        }



                        Rectangle{
                                //id: readImei
                            color: "lightgray"
                                Layout.columnSpan: 1
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                    Text {
                                        //id: name
                                        text: qsTr("WIFI pwd")
//                                        Layout.alignment: horizontalCenter|  verticalCenter
                                        color: "lightgray"

                                    }
                        }

                        Rectangle{
                                //id: readImei
                            //color: "lightgray"
                                Layout.columnSpan: 2
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                TextInput {
                                            //id: val_user_pwd
                                            anchors.fill: parent
                                            font.pointSize:              14;
                                }
                        }

                        //Set
                        Rectangle{
                            Layout.columnSpan: 1

                                Layout.fillWidth: true;
                                Layout.fillHeight: true;
                                Button{
                                    id: bt_unbind
                                    text: qsTr("Set")
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

                        //Clear
                        Rectangle{
                            Layout.row:  3
                            Layout.column: 2
                            Layout.columnSpan: 1

                                Layout.fillWidth: true;
                                Layout.fillHeight: true;
                                Button{
                                    //id: bt_unbind
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
                                        console.log("bt_unbind");
                                    }
                                }
                        }
                }

                //ip
                GridLayout{
                    columns: 3;

                        Rectangle{
                                //id: readImei
                            color: "lightgray"
//                                Layout.preferredWidth: 1
                                Layout.columnSpan: 3
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                    Text {
                                        //id: name
                                        text: qsTr("Setting IP")
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignHCenter
            //                            font.family: "Helvetica"
                                        font.pointSize: 20
                                    }
                        }


                        Rectangle{
                                //id: readImei
                            color: "lightgray"
                                Layout.columnSpan: 1
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                    Text {
                                        //id: name
                                        text: qsTr("WIFI pwd")
                                        Layout.alignment: horizontalCenter|  verticalCenter
                                    }
                        }

                        Rectangle{
                                //id: readImei
                                Layout.columnSpan: 2
                                Layout.fillWidth: true
                                Layout.fillHeight: true     //占据为其分配的所有高度
                                TextInput {
                                            //id: val_user_pwd
                                            anchors.fill: parent
                                            font.pointSize:              14;
                                }
                        }

                        //Set
                        Rectangle{
                            Layout.row:  3
                            Layout.column: 0
//                            Layout.preferredWidth: 20
                            Layout.columnSpan: 1

                                Layout.fillWidth: true;
                                Layout.fillHeight: true;
                                Button{
                                    //id: bt_unbind
                                    text: qsTr("Set")
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

                        //Clear
                        Rectangle{
                            Layout.row:  3
                            Layout.column: 2
//                            Layout.preferredWidth: 20
                            Layout.columnSpan: 1

                                Layout.fillWidth: true;
                                Layout.fillHeight: true;
                                Button{
                                    //id: bt_unbind
                                    text: qsTr("Clear")
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
                }
        }
    }

}
