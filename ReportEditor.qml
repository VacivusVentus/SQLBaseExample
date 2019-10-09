import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.taskdb.client 1.0

Item {
    Rectangle
    {
        anchors.fill: parent
        color: '#eeeee4'
        GridLayout
        {
            width: parent.width
            height: parent.height - 25
            columns: 2
            Flickable {
                Layout.column: 0
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
                TextArea
                {
                    id: taskofuser
                    width: parent.width
                    height: parent.height
                    wrapMode: TextEdit.wrapMode
                    clip: true
                    selectByMouseChanged: true
                    readOnly: true
                }
            }
            Flickable {
                Layout.column: 1
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
                TextArea
                {
                    id: reportuser
                    width: parent.width
                    height: parent.height
                    wrapMode: TextEdit.wrapMode
                    clip: true
                    selectByMouseChanged: true
                }
            }
        }
        Button
        {
            text: qsTr("Send report")
            width: 150
            height: 25
            y: parent.height - height
            x: parent.width - width
        }
    }
}
