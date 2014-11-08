import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Rectangle {
    id: task_view
    width: 200
    Layout.minimumWidth: 200
    color: "lightgreen"

    ColumnLayout {
        id: main_split
        spacing: 2

        Rectangle {
            z: 1
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 200
            Label {
                text: "Orders"
                z: 1
                font.family: "Verdana"
                font.bold: false
                font.pointSize: 9
                textFormat: Text.PlainText
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                style: Text.Raised
                anchors.fill: parent
            }
        }
        Rectangle {
            width: 20
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: task_view.height - 20
            ListModel {
                id: task_list
                ListElement {
                    name: "Baba"
                    price: 30
                    order: "baba, dada, mama"
                }
                ListElement {
                    name: "Dyado"
                    price: 20
                    order: "dyado, kaka, panda"
                }
                ListElement {
                    name: "Larodi"
                    price: 10
                    order: "larodi, larodi, LAroDl"
                }
            }
            Component {
                id: task_component
                Row {
                    id: component_row
                    spacing: 2
                    height: 100

                    RowLayout {
                        id: order_row_layout
                        ColumnLayout {
                            id: image_and_price_column_layout
                            anchors.left: parent.left
                            Rectangle { id: image; color: "blue"; radius: 8; width: 20 ;height: 20 }
                            Text {
                                id: dollars
                                text: qsTr("$" + price)
                                font.pixelSize: 12
                            }
                        }

                        ColumnLayout {
                            id: order_and_name_column_layout
                            width: 100
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.top: parent.top

                            Text {
                                id: client_type
                                text: name
                                anchors.top: parent.top
                                verticalAlignment: Text.AlignTop
                            }

                            Rectangle {
                                id: order_container
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                Layout.maximumWidth: parent.width

                                Text {
                                    width: parent.width
                                    id: order_text
                                    text: order
                                    anchors.bottom: parent.bottom
                                    anchors.top: parent.top
                                    anchors.topMargin: 0
                                    transformOrigin: Item.Center
                                    anchors.right: parent.right
                                    anchors.rightMargin: 0
                                    wrapMode: Text.WordWrap
                                    verticalAlignment: Text.AlignTop
                                }
                          }

                        }
                    }

                 }
            }
            ListView {
                Layout.fillHeight: true
                Layout.fillWidth:  true
                Layout.preferredHeight: 500
                anchors.fill: parent
                model: task_list
                delegate: task_component
            }
        }
    }
}
