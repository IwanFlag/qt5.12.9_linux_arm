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


Rectangle {
    property int sonMenuIndex: 0              //0:mei you jin ru zicai dan
    color: 'lightgray'


    //status bar
    StatusBar{
        id: compFactoryStatusBar
        visible: true
        width: parent.width
        height: 50


        //row layout
        RowLayout{
            anchors.fill: parent
            //spacing: 20  //相邻间距

            //nowtimestamp
            Rectangle {
                color: 'lightgray'
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text{
                    id:nowtimestamp
                    text: qsTr("2021.5.26 15:17:01")
                    height: parent.height
                    font.bold:  true;
                    font.pointSize:              18;
                    //Layout.alignment: left
                }
            }


            //conn status
//            Text{
//                id:tcp_conn_status
//                text: qsTr("not connect")
//                height: compFactoryStatusBar.height

//                font.bold:  true;
//                font.pointSize:              18;
//            }

            //remote ip addr
            Rectangle {
                color: 'lightgray'
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text{
                    id:remote_ip_addr
                    text: qsTr("127.0.0.1")
                    height: parent.height
                    font.bold:  true;
                    font.pointSize:              18;
                    //Layout.alignment: Text.AlignRight
                }
            }


//            Button{
//                id: bt_return
//                x: parent.width - bt_return.width
//                text: "return"
//                height: compFactoryStatusBar.height
//                onClicked:{
//                    console.log("bt_return");
//                    //close present page
//                    //FactoryMenu.visible = false;
//                    //FactoryMenu.visible = true;
//                }
//            }
        }
    }
}

