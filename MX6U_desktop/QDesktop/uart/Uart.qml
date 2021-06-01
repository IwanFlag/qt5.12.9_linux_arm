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
import "../factorytool"

import QSerialPortInfo 1.1
//!!!!!!!!!!!!!!

// Grid bu ju ,zhi you quan bu peizhi wancheng  ,caihui  youshengxiao "columSPAN",diu

//productMenu
Rectangle {
    id: compUartMenu
    visible: true
    x: compFactoryStatusBar.x
    y: compFactoryStatusBar.height         //50//compFactoryStatusBar.bottom
    width: parent.width
    height: parent.height - compFactoryStatusBar.height
    color: "gray"


    signal uart_search_port()
    Component.onCompleted:
    {
        //qml 信号 连接 c++ slot
        uart_search_port.connect(UartThread.uart_search_com_slots);
    }


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
                    text: qsTr("Uart")
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
                        compUartMenu.visible = false;
                        compFactoryMenu.visible = true;
                    //UartObj.destory()
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
//            row: 8
            columns: 4;
            anchors.fill: parent
            anchors.margins: 5;
            columnSpacing: 10;
            rowSpacing: 10;


            //1.1 searchUart
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true


                    Button{
                        id: bt_searchUart
                        text: qsTr("searchUart")
                        anchors.centerIn: parent
                        anchors.fill: parent

                            style: ButtonStyle {
                                  label: Text {
                                    renderType: Text.NativeRendering
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
        //                            font.family: "Helvetica"
                                    font.pointSize: 20
                                    text: control.text
                                  }
                            }


                            onClicked:{
                                console.log("bt_searchUart");
                                //
                                //uart_search_port();
                                //QList<QSerialPortInfo> list = availablePorts()
                            }
                    }
            }

            //1.2 uart select
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //

                    //uart select
                        ComboBox {
                                anchors.centerIn: parent
                                anchors.fill: parent

                                currentIndex: 0
//                                model: ListModel {
//                                    id: cbItems
//                                    ListElement { text: "uart0"; color: "Yellow" }
//                                    ListElement { text: "uart1"; color: "Yellow" }
//                                    ListElement { text: "uart2"; color: "Yellow" }

//                                }

                                id:serialName
                                //model: serial.querySerialInfo()// [ "Banana", "Apple", "Coconut" ]
                                onActivated: {
                                    //serial.setPortName(currentText)
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

            //1.3 readSimnum
            Rectangle{
                    id: readSimnum
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "green"

                    //uart select
                        ComboBox {
                                    id:combox_bound_select
                                    anchors.centerIn: parent
                                    anchors.fill: parent

//                                    currentIndex: 0
//                                    model: ListModel {
//                                        //id: cbItems
//                                        ListElement { text: "4800"; color: "Yellow" }
//                                        ListElement { text: "9600"; color: "Green" }
//                                        ListElement { text: "115200"; color: "Green" }

//                                    }

                                    model: [ "9600", "19200", "38400", "57600","115200"]
                                    onActivated: {
                                        //serial.setBaud(currentText)
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


            //1.4 showSimnum
            Rectangle{
                    //id: showSimnum
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        id: bt_open_close
                        text: qsTr("open")
                        //anchors.fill: parent
                        anchors.centerIn: parent
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


            //recevie
            Rectangle{
                    id: text_into_recevie
                    Layout.columnSpan: 4
                    Layout.rowSpan: 3

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    Text {
//                        //id: name
//                        text: qsTr("text")


//                    }
                    TextField {
                         //text: backend.userName
                         placeholderText: qsTr("receive data")
                         anchors.centerIn: parent

                         onTextChanged:{
                             //backend.userName = text
                         }
                     }
            }

            //send
            Rectangle{
                    id: text_into_send
                    Layout.columnSpan: 4
                    Layout.rowSpan: 2

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Text {
                        //id: name
                        text: qsTr("text")
                    }
            }

            //3.1 bt_uart_clear
            Rectangle{
                    id: bt_uart_clear

                    Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        //id: bt_open_close
                        text: qsTr("clear")
                        anchors.fill: parent
                        anchors.centerIn: parent
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
                            console.log("bt_uart_clear");
                        }
                    }
            }

            //3.2 bt_uart_send
            Rectangle{
                    id: bt_uart_send
                    //Layout.preferredWidth: 1
//                    Layout.preferredHeight: 50

                    Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        //id: bt_open_close
                        text: qsTr("send")
                        anchors.fill: parent
                        anchors.centerIn: parent
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
                            console.log("bt_uart_send");
                        }
                    }
            }



            Component.onCompleted: {
                //serial.setPortName(serialName.currentText)
                //serial.setBaud(baud.currentText)
            }
        }

    }
}
