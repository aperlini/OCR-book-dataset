import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import xy.myapp.AppCtrl


Item {

    readonly property int hControl: 60
    id: settingsWrap

    anchors.centerIn: parent

    // scale control
    Rectangle {
        id: textInfo
        color: "transparent" // navajowhite
        height: hControl / 2
        width: parent.width

        Text {
            id: infos
            text: "Select text area"
            color: "white"
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: btnWrap
        color: "transparent" //  tomato
        height: hControl
        anchors.top:  textInfo.bottom
        // Trigger image to text action
        RoundButton {
            id: translateAction
            text: "Get Text"
            radius: 4
            width: 100
            visible: true
            Material.theme: Material.Red
            highlighted: true
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: AppCtrl.imgSelection.is_active | false
            onClicked: {
                AppCtrl.imgToText()
            }
        }
    }
}
