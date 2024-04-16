import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import xy.myapp.AppCtrl


ColumnLayout {

    Layout.fillWidth: true
    Layout.fillHeight: true

    Component {
        id: translationProcess
        TranslationProcess {}
    }

    // SubView loader
    // Default view : upload action
    Loader {
        id: subViewLoader
        sourceComponent: translationProcess
        Layout.alignment: Qt.AlignHCenter
    }

    // Signal handler to update UI and views
    // when translation process starts
    Connections {
        target: AppCtrl
        function onTranslationStarted() {
            subViewLoader.sourceComponent = loadingState
        }
    }

}
