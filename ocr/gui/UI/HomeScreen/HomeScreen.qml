import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import xy.myapp.AppCtrl

ColumnLayout {

    Layout.fillHeight: true
    Layout.fillWidth: true

    Component {
        id: uploadView
        Upload {}
    }

    // SubView loader
    // Default view : upload action
    Loader {
        id: subViewLoader
        sourceComponent: uploadView
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    }

    // Signal handler to update UI and views
    // when image is ready
    Connections {
        target: AppCtrl
        function onProcessImgStarted() {
            subViewLoader.sourceComponent = loadingState
        }
        function onImageChanged() {
            stack.push(resultScreen)            
            subViewLoader.sourceComponent = uploadView
        }
    }

}
