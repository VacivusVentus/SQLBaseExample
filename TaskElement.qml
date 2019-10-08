import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.taskdb.client 1.0

Item {
    width: 500
    height: 30
    property int idtask: 0
    property string task: ""
    property string describe: ""
    property string date: ""
    property int progress: 0
    property ClientInterface client:null
    Rectangle{
        anchors.fill: parent
        color: '#aaffaa'
        GridLayout {
            rows: 1
            columns: 3
            anchors.fill: parent
            Text
            {
                text: task
                Layout.column: 0
            }
            Text
            {
                text: date
                Layout.column: 1
            }
            Text
            {
                text: progress + "%"
                Layout.column: 2
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: "PointingHandCursor"
            onClicked: {
                client.openTask(idtask)
            }
        }
    }
}
