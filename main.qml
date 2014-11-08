import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: main
    y: 0
    visible: true
    width: 800
    height: 600
    title: qsTr("Regularity")

    SplitView {
        id: main_split
        x: 8
        y: 8
        width: 784
        height: 584
        orientation: Qt.Horizontal
        Rectangle {
            id: main_view
            width: 600
            color: "lightblue"

            ColumnLayout {
                id: columnLayout1
                anchors.topMargin: 0
                anchors.fill: parent
                anchors.top: parent.top
                anchors.left: parent.left

                Rectangle {
                    id: header
                    height: 50
                    color: "#ffffff"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    border.color: "#00ff00"
                    border.width: 2
                }

                Rectangle {
                    id: rectangle2
                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: footer.top
                    anchors.bottomMargin: 0
                    anchors.top: header.bottom
                    anchors.topMargin: 0
                    border.color: "#0000ff"
                    border.width: 2

                    RowLayout {
                        id: rowLayout1
                        anchors.fill: parent

                        ColumnLayout {
                            id: icons
                            width: 32
                            Layout.maximumWidth: 32
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.top: parent.top
                            anchors.topMargin: 0
                        }

                        GridLayout {
                            id: gridLayout1
                            columns: 3
                            rows: 3
                            anchors.left: icon.right
                            anchors.leftMargin: 0
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.top: parent.top
                            anchors.topMargin: 0
                        }
                    }
                }

                Rectangle {
                    id: footer
                    height: 200
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    border.color: "#ff0000"
                    border.width: 2
                }
            }
        }
        TaskList{}

    }



}
