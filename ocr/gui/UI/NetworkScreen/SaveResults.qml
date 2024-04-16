import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import xy.myapp.ApiCtrl

Item {

    readonly property int popupWidth: 360
    readonly property int popupHeight : 160

    // fetch data when ready
    Component.onCompleted: {
        ApiCtrl.apiDataRequest()
    }

    // Unfocus text area
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }

    // SubView loader
    // Default view : register form
    Loader {
        id: subViewLoader
        anchors.fill: parent
        sourceComponent: registerForm
    }

    // Register form component
    Component {
        id: registerForm
        RegisterForm {}
    }

    // Server response
    Component {
        id: createCompleted
        CreateCompleted {}
    }

    // Signal handler to update UI and views
    // when book extract has been saved
    Connections {
        target: ApiCtrl
        function onPostRequestStarted() {
            subViewLoader.sourceComponent = loadingState
        }

        function onPassageSavedDone() {
            subViewLoader.sourceComponent = createCompleted
        }
    }

    // Display server error response
    Popup {
        id: popup
        visible: ApiCtrl.hasError
        anchors.centerIn: Overlay.overlay
        width: popupWidth | message.width
        height: popupHeight
        focus: true
        modal: true
        closePolicy: Popup.CloseOnPressOutsideParent

        ColumnLayout {
            spacing: 20
            anchors {
                centerIn: parent
            }
            Text {
                id: typeError
                text : ApiCtrl.typeError
                color: "white"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignCenter
            }
            Text {
                id: message
                text : ApiCtrl.msg
                color: "white"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignCenter
            }
            Button {
                id: refresh
                text: "Refresh"
                Layout.alignment: Qt.AlignCenter

                // refresh service
                onClicked: {
                    subViewLoader.sourceComponent = registerForm
                    ApiCtrl.apiDataRequest()
                }
            }
        }

    }
}
