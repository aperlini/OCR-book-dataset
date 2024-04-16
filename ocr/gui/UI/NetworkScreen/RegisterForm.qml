import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import xy.myapp.AppCtrl
import xy.myapp.ApiCtrl
import xy.myapp.AuthorModel
import xy.myapp.BookModel

Item {

    readonly property int formWidth: 550

    Layout.fillWidth: true
    Layout.fillHeight: true

    // Form elements

    GridLayout {
        id: formLayout
        columns: 1
        rowSpacing: 10
        columnSpacing: 15
        width: formWidth

        function isFormValid () {
            return (bookTitlesList.currentValue !== 0) && (authorsList.currentValue !== 0) && (page.acceptableInput)
        }

        anchors {
            centerIn: parent
        }

        ComboBox {
            id: authorsList
            Layout.fillWidth: true
            model: AuthorModel
            textRole: "authorFullname"
            valueRole: "authorId"
            // currentIndex: 0
            onActivated: {
                var selectedAuthor = authorsList.currentText;
                var selectedAuthorId = authorsList.currentValue;

                // console.log("Selected author :", selectedAuthor, "select author id:", selectedAuthorId);
            }
        }

        ComboBox {
            id: bookTitlesList
            Layout.fillWidth: true
            model: BookModel
            textRole: "bookTitle"
            valueRole: "bookId"
            // currentIndex: 0
            onActivated: {
                var selectedBookTitle = bookTitlesList.currentText;
                var selectedBookTitleId = bookTitlesList.currentValue;

                // console.log("Selected BookTitle :", selectedBookTitle, "select BookTitle id:", selectedBookTitleId);
            }
        }

        TextField {
            id: page
            Layout.fillWidth: true
            placeholderText: qsTr("pages index")
            validator: IntValidator{bottom: 1; top: 9999;}
            onTextChanged: acceptableInput ? validPageIndex.text = qsTr("") : validPageIndex.text = qsTr("Page number is invalid")
        }

        Label {
            Text {
                id: validPageIndex
                color: "white"
                font.pointSize: 10
            }
        }

        RoundButton {
            id: save_btn
            text: "Save"
            radius: 4
            width: 200
            enabled: formLayout.isFormValid()
            Layout.alignment: Qt.AlignRight
            onClicked: {
                ApiCtrl.persistDataRequest(bookTitlesList.currentValue, AppCtrl.translation, page.displayText);
            }
        }

    }
}



