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
import "../login"


Rectangle {
    id: compFactoryTool
    visible: true
    width:parent.width
    height: parent.height
    color: "gray"
    property int sonMenuIndex: 0              //0:mei you jin ru zicai dan


    //1.display main menu
    FactoryStatusBar{
            id: compFactoryStatusBar
            visible: true
            width: parent.width
            height: 50
            color: "gray"
    }

    //2.display main menu
    FactoryMenu{
        id: compFactoryMenu
        visible: true
        anchors.top: compFactoryStatusBar.bottom
        width: parent.width
        height: parent.height - compFactoryStatusBar.height
        color: "blue"
    }
}

