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
            Text {
                text: "View 1"
                anchors.centerIn: parent
            }
        }
        TaskList{}

    }



}
