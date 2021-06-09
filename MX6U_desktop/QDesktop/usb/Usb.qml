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
    id: compUsbMenu
    visible: true
    x: compFactoryStatusBar.x
    y: compFactoryStatusBar.height         //50//compFactoryStatusBar.bottom
    width: parent.width
    height: parent.height - compFactoryStatusBar.height
    color: "blue"


    signal usb_search_port()
    signal usb_open_close_signals(string txt, string portName)
    signal usb_sendData_signals(string data)


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
                    text: qsTr("usb")
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
                        compUsbMenu.visible = false;
                        compFactoryMenu.visible = true;
                    //usbObj.destory()
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


            //1.1 searchusb
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true


                    Button{
                        id: bt_searchusb
                        text: qsTr("searchusb")
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
                                console.log("bt_searchusb");
                                combobox_items.clear();
                                usb_search_port();
                                //cbItems.append(UsbThread.m_port);
                            }
                    }
            }

            //1.2 usb select
            Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true     //


                    ListModel{
                        id: combobox_items
//                        ListElement { text: "usb0"; color: "Yellow" }
//                        ListElement { text: "usb1"; color: "Yellow" }
//                        ListElement { text: "usb2"; color: "Yellow" }
//                            ListElement { text: "usb0"}
                    }

                    //usb select
                        ComboBox {
                                id: combobox_usb_select
                                objectName: "combobox_usb_select"
                                anchors.centerIn: parent
                                anchors.fill: parent

                                currentIndex: 0
                                model:{combobox_items}
                                //id:serialName
                                //model: serial.querySerialInfo()// [ "Banana", "Apple", "Coconut" ]
                                //model: UsbThread.m_port
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

                    //usb select
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

//                                    model: [ "9600", "19200", "38400", "57600","115200"]
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
                            usb_open_close_signals(bt_open_close.text, combobox_usb_select.currentText);
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
            //3.1 bt_usb_clear
            Rectangle{
                    id: bt_usb_clear

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
                            console.log("bt_usb_clear");
                            txt_sendEdit.clear();
                            txt_receiveEdit.clear();
                        }
                    }
            }

            //3.2 bt_usb_send
            Rectangle{
                    Layout.columnSpan: 2
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
//                    color: "orange"
                    Button{
                        id: bt_usb_send
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
                            console.log("bt_usb_send");
                            usb_sendData_signals(txt_sendEdit.text);
                        }
                    }
            }
        }


        Component.onCompleted: {
            //qml 信号 连接 c++ slot
            usb_search_port.connect(UsbThread.usb_search_com_slots);
            usb_open_close_signals.connect(UsbThread.usb_open_close_slots);
            usb_sendData_signals.connect(UsbThread.usb_sendData_slots);
        }


        Connections {
              target: UsbThread;
              onUsb_vaild_ports_to_qml:{
                  console.log("onUsb_vaild_ports_to_qml");
                  //combobox_items.clear();
                  combobox_items.append({ text: port});
                  console.log("port:%s", port);
              }
          }


        Connections {
              target: UsbThread;
              onSendDataToQml:{
                  console.log("recevie data:%s", data);
                  txt_receiveEdit.append(data)
              }
          }

        //open flag
        Connections {
              target: UsbThread;
              onUsb_open_flag_signals:{
                  console.log("onusb_open_flag_signals:%d", flag);
                    if(flag)
                    {
                        bt_open_close.text = qsTr("Close");
                        //disabled
                        bt_searchusb.enabled = false;
                        combobox_usb_select.enabled = false;
                        combobox_bound_select.enabled = false;
                        bt_usb_send.enabled = true;
                    }
              }
          }

        //close flag
        Connections {
              target: UsbThread;
              onUsb_close_flag_signals:{
                  console.log("onusb_closed_flag_signals:%d", flag);
//                  txt_receiveEdit.append(data)
                  if(flag)
                  {
                      bt_open_close.text = qsTr("Open")
                      //enabled
                      bt_searchusb.enabled = true;
                      combobox_usb_select.enabled = true;
                      combobox_bound_select.enabled = true;
                      bt_usb_send.enabled = false;
                  }
              }
          }
    }
}
