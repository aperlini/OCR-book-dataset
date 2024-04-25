import QtQuick 2.15
import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import xy.myapp.AppCtrl


RowLayout {

    property int startX: 0
    property int startY: 0
    property real imgOpacity: 0.75
    readonly property string selectionColor: "yellow"

    ColumnLayout {

        Rectangle {
            id: imgDisplay
            Layout.fillWidth: true
            Layout.fillHeight: true
            width: parent.width/2
            height: parent.height
            color: "purple"
            clip: true            

            // selection behavior
            MouseArea {

                id: area
                enabled: true
                anchors.fill: parent
                cursorShape: Qt.CrossCursor

                onEnabledChanged: {
                    area.cursorShape = area.enabled ? Qt.CrossCursor : Qt.ArrowCursor
                }

                onReleased: (mouse) => {
                    AppCtrl.imgSelection.x = startX
                    AppCtrl.imgSelection.y = startY
                    AppCtrl.imgSelection.w = selectionItem.width
                    AppCtrl.imgSelection.h = selectionItem.height
                    AppCtrl.imgSelection.visible_w = width
                    AppCtrl.imgSelection.visible_h = height
                }

                onPressed: (mouse) => {
                    startX = mouse.x
                    startY = mouse.y
                    selectionItem.x = startX
                    selectionItem.y = startY
                    selectionItem.width = 0
                    selectionItem.height = 0
                }

                onPositionChanged: (mouse) => {
                   if(containsPress) {                                           
                       selectionItem.width = mouse.x - startX
                       selectionItem.height = mouse.y - startY
                   }
               }

            }

            Image {
                id: displayedImg
                width: parent.width
                height: parent.height
                autoTransform: true
                fillMode: Image.PreserveAspectCrop
                source: AppCtrl.image
                smooth: true
                opacity: imgOpacity
            }

            // border selection
            Rectangle {
                id: selectionItem
                border.color: selectionColor
                border.width: 2
                color: "transparent"
                opacity: 0.9;
            }

            // bg selection
            Rectangle {
                id: selection
                color: selectionColor
                opacity: 0.4;
                width: selectionItem.width
                height: selectionItem.height
                x: selectionItem.x
                y: selectionItem.y
            }

        }


    }

    ColumnLayout {

        Item {

            Layout.fillWidth: true
            Layout.fillHeight: true

            // Image to text area
            // Default is button w/ image to text handler
            Loader {
                id: subViewLoader
                anchors.fill: parent
                sourceComponent: imgSettings
            }

            // Image settings component
            Component {
                id: imgSettings
                ImageSettings {}
            }

            // Signal handler to update UI and views
            // on text to image results changed
            Connections {
                target: AppCtrl
                function onTranslationChanged() {
                    subViewLoader.sourceComponent = ocrResults
                    area.enabled = false
                }

            }

        }
    }
}
