import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import xy.myapp.AppCtrl


Item {

    anchors.fill: parent

    readonly property int wOffset: 40
    readonly property int hOffset: 100
    readonly property int topOffset: 20
    readonly property int btnRadius : 4
    readonly property int btnWidth : 100

    // Unfocus text area
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }

    // image to text wrapper
    ScrollView {
        id: scrollview
        // anchors.centerIn: parent
        anchors.top: parent.top
        anchors.topMargin: topOffset
        anchors.margins: 20
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - wOffset
        height: parent.height - hOffset - save_btn.height*2

        // enable vertical scroll bar
        contentWidth: translation.implicitWidth
        contentHeight: translation.implicitHeight
        clip: true

        // image to text content
        TextArea  {
            id: translation
            placeholderText: "Translation"
            text: AppCtrl.translation
            wrapMode: TextEdit.Wrap
        }

        // scrollbar position
        ScrollBar.vertical: ScrollBar {
            anchors.top: scrollview.top
            anchors.right: scrollview.right
            anchors.bottom: scrollview.bottom
            anchors.topMargin: 8
        }
    }

    RoundButton {
        id: save_btn
        text: "Next"
        radius: btnRadius
        width: btnWidth
        anchors.top: scrollview.bottom
        anchors.right: scrollview.right
        Material.theme: Material.Red
        highlighted: true
        onClicked: {
            stack.push(saveResults)
            AppCtrl.setTranslation(translation.text) // update textarea modification
        }
    }

    RoundButton {
        text: "Back"
        width: btnWidth
        radius: btnRadius
        anchors.top: scrollview.bottom
        anchors.right: save_btn.left
        enabled: stack.depth > 1
        onClicked: stack.pop()
    }

}

