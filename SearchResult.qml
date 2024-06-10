import QtQuick 2.0

Item {
    id: root
    width: parent.width * 0.4
    height: 500

    property var listdata
    property var listtimer
    property string label

    Text {
        id: count
        text: (listview.count) + " result (" + label + ")"
        font.pixelSize: 20
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: list
        width: parent.width * 0.8
        height: 300
        border.color: "black"
        anchors {
            top: count.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        ListView {
            id: listview
            width: parent.width * 0.9
            height: parent.height * 0.9
            clip: true
            anchors.centerIn: parent
            model: root.listdata
            delegate: Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: listdata[index]
                font.pixelSize: 20
            }
        }
    }

    Rectangle {
        id: time
        width: parent.width * 0.8
        height: 150
        border.color: "black"
        anchors {
            top: list.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        ListView {
            id: listviewtime
            width: parent.width * 0.9
            height: parent.height * 0.9
            clip: true
            anchors.centerIn: parent
            model: root.listtimer
            delegate: Text {
                text: listtimer[index]
                font.pixelSize: 17
            }
            onCountChanged: {
                listviewtime.positionViewAtEnd()
            }
        }
    }
}
