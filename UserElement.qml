import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    property string login: ""
    property string fio: ""
    Rectangle
    {
        anchors.fill: parent
        GridLayout
        {
            columns: 2

            Text {
                Layout.column: 0
                text: login
            }
            Text {
                Layout.column: 1
                text: fio
            }
        }
    }
}
