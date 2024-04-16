import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import "UI/HomeScreen"
import "UI/ResultScreen"
import "UI/NetworkScreen"
import "UI/Utils"

ApplicationWindow {
    id: root

    minimumHeight: 840 // 700
    minimumWidth: 1120 // 1000
    maximumHeight: 840
    maximumWidth: 1120

    visible:true

    readonly property int loaderSize: 100
    readonly property string loaderGif :  Qt.resolvedUrl("Resources/images/spinner1.gif")

    Material.theme: Material.Teal
    Material.accent: Material.Indigo

    Shortcut {
        sequence: "q"
        onActivated: Qt.quit()
    }

    StackView {
        id: stack
        initialItem: homeScreen
        anchors.fill: parent
    }

    // Defining components to be used
    // in the stackview and other loader subviews

    // main page
    Component {
        id: homeScreen
        HomeScreen {}
    }

    // image results and actions
    Component {
        id: resultScreen
        ResultScreen {}
    }

    // ocr results and actions
    Component {
        id: ocrResults
        OcrResults {}
    }

    // form and api interactions
    Component {
        id: saveResults
        SaveResults {}
    }

    // animation spinner
    Component {
        id: loadingState
        LoadingAnim {}
    }

}
