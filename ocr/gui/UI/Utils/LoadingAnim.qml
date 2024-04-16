import QtQuick 2.15
import QtQuick.Layouts

RowLayout {

    id: loadingStateWrapper

    Layout.fillWidth: true
    Layout.fillHeight: true

    visible: true

    // Animated loader
    AnimatedImage {
        id: loadingState
        playing: true
        visible: true
        source: loaderGif
        width: loaderSize
        fillMode: Image.PreserveAspectFit
        Layout.alignment: Qt.AlignCenter

    }
}
