import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.taskdb.client 1.0

Item {
    property ClientInterface client: null
    Rectangle{
        width: parent.width
        height: 50
        y:parent.height - 100
        GridLayout
        {
            rows: 4
            columns: 3
            Text {
                text: qsTr("Login")
                Layout.row: 0
                Layout.column: 0
            }
            Text {
                text: qsTr("Password")
                Layout.row: 0
                Layout.column: 1
            }
            Text {
                text: qsTr("Name of user")
                Layout.row: 2
                Layout.column: 0
            }

            Flickable
            {
                Layout.row: 1
                Layout.column: 0
                TextEdit
                {
                    id:loginedit
                    width: parent.width
                    height: parent.height
                    clip: true
                    wrapMode: TextEdit.wrapMode
                    selectByMouseChanged: true
                }
            }

            Flickable
            {

                Layout.row: 1
                Layout.column: 1
                TextEdit
                {
                    id:passwrdedit
                    width: parent.width
                    height: parent.height
                    clip: true
                    wrapMode: TextEdit.wrapMode
                    selectByMouseChanged: true
                }
            }

            Flickable
            {

                Layout.row: 3
                Layout.column: 0
                Layout.columnSpan: 2
                TextEdit
                {
                    id:fioedit
                    width: parent.width
                    height: parent.height
                    clip: true
                    wrapMode: TextEdit.wrapMode
                    selectByMouseChanged: true
                }
            }
            Button
            {
                Layout.row: 3
                Layout.column: 2
                text: qsTr("Add user")
                onClicked:
                {
                }
            }
        }
    }
    ScrollView
    {
        width: parent.width
        height: parent.height - 50
        Rectangle {
            id:contentRectangle
        }
    }

}
