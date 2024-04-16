import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Material
import xy.myapp.AppCtrl


Item {

    // to get default image filepath
    FileDialog {
        id: file_dialog
        currentFolder: AppCtrl.folderPath()
        onAccepted: {
            AppCtrl.initProcess(selectedFile)
            btn_open.visible = false
        }
    }

    // Open File dialog
    RoundButton {
        id: btn_open
        text: qsTr("open image")
        radius: 4
        width: 120
        visible: true
        onClicked: {
            file_dialog.open()
        }
        Material.theme: Material.Red
        anchors.centerIn: parent
    }
}
