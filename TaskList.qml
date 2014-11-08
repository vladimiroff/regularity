import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Rectangle {
    id: task_view
    width: 200
    Layout.minimumWidth: 100
    color: "lightgreen"

    ColumnLayout {
        id: main_split
        spacing: 2

        Rectangle {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 200
            Label {
                text: "Orders"
                anchors.fill: parent
            }
        }
        Rectangle {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: task_view.height - 20
            ListModel {
                id: task_list
                ListElement{
                    name: "Baba"
                }
                ListElement{
                    name: "Dyado"
                }
                ListElement{
                    name: "asd"
                }
            }
            Component {
                id: task_component
                Row {
                    Layout.fillHeight: true
                    spacing: 10
                    Text {
                        text: name
                    }
                }
            }
            ListView {
                Layout.fillHeight: true
                Layout.preferredHeight: 500
                anchors.fill: parent
                model: task_list
                delegate: task_component
            }
        }
    }
}
