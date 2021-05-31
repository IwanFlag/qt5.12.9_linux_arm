import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: rec

    property alias textInformation : myText.text
    signal destroyMyself(var object)

    Text {
        id: myText
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 24
        font.family: "Î¢ÈíÑÅºÚ"
        color: "black"
    }

    Button {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: "delete"

        onClicked: {
            destroyMyself(rec)
        }
    }
}