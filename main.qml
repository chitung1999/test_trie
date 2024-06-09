import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1120
    height: 630
    title: qsTr("Hello World")

    SearchOption {
        id: search
        anchors {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: line
        width: 5
        height: 400
        color: "black"
        anchors {
            top: search.bottom
            topMargin: 130
            horizontalCenter: parent.horizontalCenter
        }
    }

    SearchResult {
        id: result_trie
        anchors {
            top: search.bottom
            topMargin: 30
            left: parent.left
            leftMargin: parent.width * 0.05
        }
    }

    SearchResult {
        id: result_for
        anchors {
            top: result_trie.top
            right: parent.right
            rightMargin: parent.width * 0.05
        }
        listdata: CTRL.nomalQuery
        listtimer: CTRL.nomalTime
        label: "Linear Search"
    }

}
