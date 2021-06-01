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


//compPhotoMenu
Rectangle {
    id: compPhotoSettingMenu
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
                Label{
                    text: qsTr("Product")
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
                        compPhotoSettingMenu.visible = false;
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
            columns: 8;
            anchors.fill: parent
            anchors.margins: 5;
            columnSpacing: 10;
            rowSpacing: 10;


            //0.0
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        id: bt_readImei
                        text: qsTr("lat")
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
                                console.log("lat");
                            }
                    }
            }

            //0.1
            Rectangle{
                    id: showImei
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        id: txt_showImei
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //0.2
            Rectangle{
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    Button{
                        text: qsTr("lon")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pointSize: 20
                                text: control.text
                              }
                        }

                        onClicked:{
                            console.log("readSimnum");
                        }
                    }
            }

            //0.3
            Rectangle{
                    id: showSimnum
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }



            //--------------------
            //1.0
            Rectangle{
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("photoid")
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
                                console.log("lat");
                            }
                    }
            }

            //1.1
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //1.2
            Rectangle{
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    Button{
                        text: qsTr("postcode")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pointSize: 20
                                text: control.text
                              }
                        }

                        onClicked:{
                            console.log("readSimnum");
                        }
                    }
            }

            //1.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }
//----------------------

            //--------------------
            //2.0
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("FTP addr")
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
                                console.log("lat");
                            }
                    }
            }

            //2.1
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //2.2
            Rectangle{
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    Button{
                        text: qsTr("FTP pwd")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pointSize: 20
                                text: control.text
                              }
                        }

                        onClicked:{
                            console.log("readSimnum");
                        }
                    }
            }

            //2.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }
//----------------------

            //--------------------
            //3.0
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("get lat config")
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
                                console.log("lat");
                            }
                    }
            }

            //3.1
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //3.2
            Rectangle{
                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    Button{
                        text: qsTr("get lon config")
                        anchors.fill: parent
                        style: ButtonStyle {
                              label: Text {
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pointSize: 20
                                text: control.text
                              }
                        }

                        onClicked:{
                            console.log("readSimnum");
                        }
                    }
            }

            //3.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    Text {
                        anchors.fill: parent
                        font.pointSize:              14;
                    }
            }
//----------------------

            //--------------------
            //4.0
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("get photo id")
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
                                console.log("lat");
                            }
                    }
            }

            //4.1
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }
//----------------------
            //4.2
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("get postcode")
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
                                console.log("lat");
                            }
                    }
            }

            //4.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

            //4.2
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("get FTPAdrr")
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
                                console.log("lat");
                            }
                    }
            }

            //4.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }
            //4.2
            Rectangle{
//                    Layout.preferredWidth: 1
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度


                    Button{
                        text: qsTr("postcodePWD")
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
                                console.log("lat");
                            }
                    }
            }

            //4.3
            Rectangle{
                    Layout.preferredWidth: 3
                    Layout.columnSpan: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true     //占据为其分配的所有高度

//                    color: "yellow"
                    Text {
                        anchors.fill: parent

                        font.pointSize:              14;
                    }
            }

        }
    }
}
