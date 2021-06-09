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
    color: "blue"


    signal uart_search_port()
    signal uart_open_close_signals(string txt, string portName, string bound)
    signal uart_sendData_signals(string data)


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
                                combobox_items.clear();
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
//                            ListElement { text: "uart0"}
                    }

                    //uart select
                        ComboBox {
                                id: combobox_uart_select
                                objectName: "combobox_uart_select"
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
                                    id:combobox_bound_select
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
                            uart_open_close_signals(bt_open_close.text, combobox_uart_select.currentText, combobox_bound_select.currentText);
                            //bt_open_close.text = "aaa"
                        }
                    }
            }

            Rectangle {
                id: receiveData
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

                    TextArea  {
                        id: txt_receiveEdit
                        width: flickReceive.width
                        focus: false
                        enabled: false
                        selectByKeyboard: false
                        wrapMode: TextEdit.Wrap
                        anchors.fill: parent
//                        onCursorRectangleChanged: flickReceive.ensureVisible(cursorRectangle)
                        style: TextAreaStyle {

                            backgroundColor: "lightgray"
                            textColor: "black"
//                            font.pixelSize: 18
                            selectedTextColor: "red"
                            selectionColor: "blue"
                        }
                    }

                }
            }

            Rectangle {
                id: txt_sendData
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

//                    TextEdit {
//                        id: txt_sendEdit
//                        anchors.fill: parent

//                        width: flickSend.width
//                        focus: true
//                        wrapMode: TextEdit.Wrap
////                        onCursorRectangleChanged: flickSend.ensureVisible(cursorRectangle)
//                        color: "green"

//                    }
                    TextArea  {
                        id: txt_sendEdit
                        width: flickReceive.width
                        focus: false
                        //enabled: false
                        selectByKeyboard: false
                        wrapMode: TextEdit.Wrap
                        anchors.fill: parent
//                        onCursorRectangleChanged: flickReceive.ensureVisible(cursorRectangle)
                        style: TextAreaStyle {

                            //backgroundColor: "lightgray"
                            textColor: "green"
//                            font.pixelSize: 18
                            selectedTextColor: "red"
                            selectionColor: "blue"
                        }
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
                            txt_sendEdit.clear();
                            txt_receiveEdit.clear();
                        }
                    }
            }

            //3.2 bt_uart_send
            Rectangle{
                    //id: bt_uart_send
                    //Layout.preferredWidth: 1
//                    Layout.preferredHeight: 50

                    Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        id: bt_uart_send
                        enabled: false;
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
                            uart_sendData_signals(txt_sendEdit.text);
                        }
                    }
            }
        }


        Component.onCompleted: {
            //qml 信号 连接 c++ slot
            uart_search_port.connect(UartThread.uart_search_com_slots);
            uart_open_close_signals.connect(UartThread.uart_open_close_slots);
            uart_sendData_signals.connect(UartThread.uart_sendData_slots);
        }


        Connections {
              target: UartThread;
              onUart_vaild_ports_to_qml:{
                  console.log("hhahah");
                  //combobox_items.clear();
                  combobox_items.append({ text: port});
                  console.log("port:%s", port);
              }
          }


        Connections {
              target: UartThread;
              onSendDataToQml:{
                  console.log("recevie data:%s", data);
                  txt_receiveEdit.append(data)
              }
          }

        //open flag
        Connections {
              target: UartThread;
              onUart_open_flag_signals:{
                  console.log("onUart_open_flag_signals:%d", flag);
                    if(flag)
                    {
                        bt_open_close.text = qsTr("Close");
                        //disabled
                        bt_searchUart.enabled = false;
                        combobox_uart_select.enabled = false;
                        combobox_bound_select.enabled = false;
                        bt_uart_send.enabled = true;
                    }
              }
          }

        //close flag
        Connections {
              target: UartThread;
              onUart_close_flag_signals:{
                  console.log("onUart_closed_flag_signals:%d", flag);
//                  txt_receiveEdit.append(data)
                  if(flag)
                  {
                      bt_open_close.text = qsTr("Open")
                      //enabled
                      bt_searchUart.enabled = true;
                      combobox_uart_select.enabled = true;
                      combobox_bound_select.enabled = true;
                      bt_uart_send.enabled = false;

                  }
              }
          }
    }
}
