import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import com.taskdb.client 1.0

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Task base")
    id:root

    property TaskField taskField: null

    function getTaskList()
    {
        console.log("Get task list")
    }

    ClientInterface {
        id: client
        onAddTaskTofield:
        {
        }
        onInitTaskField:
        {
            connectField.destroy()
            taskField = Qt.createQmlObject("TaskField{}", root, "comp")
            taskField.client = client
            for (let i = 0; i < 1000;i++)taskField.addTask('','','','',0)
        }
    }

    Rectangle {
        id:connectField
        color: '#eeeee4'
        width: 400
        height: 200

        Rectangle {
            x:15
            width: 380
            height: 30
            color: '#eeeee0'
            y:30
            Text{
                text: qsTr("IP of server:")
            }
            Rectangle{
                anchors.fill: ipedit
            }
            TextEdit{
                id:ipedit
                x:130
                width: 150
                text: "192.168.1.155"
            }
        }

        Rectangle {
            x:15
            width: 380
            height: 30
            color: '#eeeee0'
            y:60
            Text{
                text: qsTr("Port:")
            }
            Rectangle{
                anchors.fill: portedit
            }
            TextEdit{
                id:portedit
                x:130
                width: 150
                text: "10232"
            }
        }
        Rectangle {
            x:15
            width: 380
            height: 30
            color: '#eeeee0'
            y:100
            Text{
                text: qsTr("Login:")
            }
            Rectangle{
                anchors.fill: useredit
            }
            TextEdit{
                id:useredit
                x:130
                width: 150
            }
        }
        Rectangle {
            x:15
            width: 380
            height: 30
            color: '#eeeee0'
            y:130
            Text{
                text: qsTr("Password:")
            }
            Rectangle{
                anchors.fill: passwdedit
            }
            TextInput{
                id:passwdedit
                x:130
                width: 150
                passwordCharacter: '*'
                echoMode: TextInput.Password
            }
        }
        Button {
            id:connectButton
            text: qsTr("Connect")
            width: 150
            height: 30
        }
        Button {
            id:localDBButton
            text: qsTr("Use local")
            width: 150
            height: 30
            onClicked: {
                client.connectToBase("127.0.0.1", portedit.text, useredit.text, passwdedit.text)
            }
        }
    }

    Component.onCompleted:  {
        connectField.x = (width - connectField.width) / 2
        connectField.y = (height - connectField.height) / 2

        connectButton.x = connectField.width - connectButton.width
        connectButton.y = connectField.height - connectButton.height
        localDBButton.y = connectButton.y
        localDBButton.x = connectButton.x - localDBButton.width
    }
}
