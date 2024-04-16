import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material

// Form elements
Item {

    Layout.fillWidth: true
    Layout.fillHeight: true

    ColumnLayout {
        spacing: 20
        anchors {
            centerIn: parent
        }

        Text {
            id: message
            text : "New book entry was successfully created"
            color: "white"
            font.pixelSize: 18
            Layout.alignment: Qt.AlignCenter
        }

        Button {
            id: reset
            text: "Start again"
            Layout.alignment: Qt.AlignCenter

            // refresh service
            onClicked: {
                stack.pop(null); // start from beginning
            }
        }

    }
}

