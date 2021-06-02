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

//import QSerialPortInfo 1.1
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
    signal uart_open_close_signals(string txt, string portName, string bound)


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
                                uart_search_port();
                                //cbItems.append(UartThread.m_port);
                            }
                    }
            }

            //1.2 uart select
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //


                    ListModel{
                        id: combobox_items
//                        ListElement { text: "uart0"; color: "Yellow" }
//                        ListElement { text: "uart1"; color: "Yellow" }
//                        ListElement { text: "uart2"; color: "Yellow" }
                            ListElement { text: "uart0"}
                    }

                    //uart select
                        ComboBox {
                                id: combobox_bound_select
                                objectName: "combobox_bound_select"
                                anchors.centerIn: parent
                                anchors.fill: parent

                                currentIndex: 0
                                model:{combobox_items}
                                //id:serialName
                                //model: serial.querySerialInfo()// [ "Banana", "Apple", "Coconut" ]
                                //model: UartThread.m_port
                                onActivated:{
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


            //1.4 open
            Rectangle{
                    //id: bt_open_close
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        id: bt_open_close
                        text: qsTr("Open")
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
                            console.log("bt_open_close");
                            //bt_open_close.text
                            uart_open_close_signals(bt_open_close.text, combobox_bound_select.currentText, combox_bound_select.currentText);
                        }
                    }
            }


//            //recevie
//            Rectangle{
//                    id: text_into_recevie
//                    Layout.columnSpan: 4
//                    Layout.rowSpan: 3

//                    Layout.fillWidth: true;
//                    Layout.fillHeight: true;
////                    Text {
////                        //id: name
////                        text: qsTr("text")


////                    }
//                    Text{
//                         //text: backend.userName
////                         placeholderText: qsTr("receive data")
//                         anchors.centerIn: parent
//                        wrapMode: Text.WrapAnywhere
//                        elide: Text.ElideRight
//                        maximumLineCount:2
//                        color: "lightgray"
//                         onTextChanged:{
//                             //backend.userName = text
//                         }
//                     }
//            }

            //send
//            Rectangle{
//                    id: text_into_send
//                    Layout.columnSpan: 4
//                    Layout.rowSpan: 2

//                    Layout.fillWidth: true;
//                    Layout.fillHeight: true;
////                    color: "orange"
//                    TextField {
//                        //id: name
//                        placeholderText: qsTr("input data")
//                        anchors.fill: parent
//                        style: TextFieldStyle{
//                               background: Rectangle{
//                               //color: ""
//                               border.color: "gray"
//                               radius: 5
//                               }//设置风格为蓝底灰边，圆角
//                               //但是TextField不能定制光标
//                    }
//                }
//            }



            Rectangle {
                id: receiveData
                //anchors.top: parent.top
                //anchors.left: parent.left
//                border.color: "#d7cfcf"
//                height: parent.height/1.5
//                width: parent.width
                Layout.columnSpan: 4
                Layout.rowSpan: 3

                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Flickable {
                    id: flickReceive
                    anchors.fill: parent
                    clip: true
                    anchors.margins: 5

//                    function ensureVisible(r)
//                    {
//                        if (contentX >= r.x)
//                            contentX = r.x;
//                        else if (contentX+width <= r.x+r.width)
//                            contentX = r.x+r.width-width;
//                        if (contentY >= r.y)
//                            contentY = r.y;
//                        else if (contentY+height <= r.y+r.height)
//                            contentY = r.y+r.height-height;
//                    }

                    TextEdit {
                        id: editReceive
                        width: flickReceive.width
                        focus: false
                        wrapMode: TextEdit.Wrap
//                        onCursorRectangleChanged: flickReceive.ensureVisible(cursorRectangle)
                        color: "red"
                    }

                }
            }

            Rectangle {
                id: sendData
//                width: parent.width
//                height: parent.height-receiveData.height-buttons.height
//                border.color: "#d7cfcf"
//                anchors.top: receiveData.bottom
                Layout.columnSpan: 4
                Layout.rowSpan: 3

                Layout.fillWidth: true;
                Layout.fillHeight: true;

                Flickable {
                    id: flickSend
                    anchors.fill: parent
                    clip: true
                    anchors.margins: 5

//                    function ensureVisible(r)
//                    {
//                        if (contentX >= r.x)
//                            contentX = r.x;
//                        else if (contentX+width <= r.x+r.width)
//                            contentX = r.x+r.width-width;
//                        if (contentY >= r.y)
//                            contentY = r.y;
//                        else if (contentY+height <= r.y+r.height)
//                            contentY = r.y+r.height-height;
//                    }

                    TextEdit {
                        id: editSend
                        width: flickSend.width
                        focus: true
                        wrapMode: TextEdit.Wrap
//                        onCursorRectangleChanged: flickSend.ensureVisible(cursorRectangle)
                        color: "green"

                    }
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
        }


        Component.onCompleted: {
            //qml 信号 连接 c++ slot
            uart_search_port.connect(UartThread.uart_search_com_slots);
            uart_open_close_signals.connect(UartThread.uart_open_close_slots);
        }


        Connections {
              target: UartThread;
              onUart_vaild_ports_to_qml:{
                  console.log("hhahah");
                  combobox_items.clear();
                  combobox_items.append({ text: port});
                  console.log("port:%s", port);
              }
          }
    }
}
