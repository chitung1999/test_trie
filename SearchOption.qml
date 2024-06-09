import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    width: 250 + 30 + 100 + 30 + 100 + 100 + 150 + 30 + 100
    height: 40

    Rectangle {
        id: search_box
        width: 250
        height: 40
        radius: 20
        border.color: "black"

        TextInput {
            anchors {
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
            font.pixelSize: 15
            clip: true
            width: 170
            onTextChanged: CTRL.queryData(text)
        }

        Image {
            source: "qrc:/search.png"
            scale: 0.7
            anchors {
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
        }
    }

    ComboBox {
        id: comboBox
        width: 100
        model: ["300", "3.000", "30.000", "300.000"]
        font.pixelSize: 20
        anchors {
            left: search_box.right
            leftMargin: 30
            verticalCenter: search_box.verticalCenter
        }

        onCurrentIndexChanged: {
        }
    }

    Button {
        id: reload_button
        width: 100
        height: 40
        text: "Reload"
        font.pixelSize: 20
        anchors {
            left: comboBox.right
            leftMargin: 30
            verticalCenter: comboBox.verticalCenter
        }
    }

    Rectangle {
        id: insert_box
        width: 150
        height: 40
        border.color: "black"
        anchors {
            left: reload_button.right
            leftMargin: 100
            verticalCenter: parent.verticalCenter
        }

        TextInput {
            anchors.centerIn: parent
            font.pixelSize: 15
            width: 130
            clip: true
            anchors {
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
        }
    }

    Button {
        id: insert_button
        width: 100
        height: 40
        text: "Insert"
        font.pixelSize: 20
        anchors {
            left: insert_box.right
            leftMargin: 30
            verticalCenter: insert_box.verticalCenter
        }
    }
}
