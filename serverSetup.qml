import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import com.taskdb.server 1.0

Window {
    visible: true
    width: 500
    height: 300
    title: qsTr("Server DB")

    BaseReader
    {
        id:basereader
        onInitdb:
        {
            if (!isInit) Qt.quit();
            else {
                fieldSetting.destroy()
            }
        }
        onQmlLog: console.log(msg)
    }

    Rectangle
    {
        id:fieldSetting
        color: "#eeeee4"
        width: 400
        height: 100
        Rectangle
        {
            color: 'yellow'
            y:10
            Text{
                text: qsTr("Password of admin:");
                width: 100
            }
            Rectangle{
                anchors.fill: rootpasswd
            }

            TextInput{
                echoMode: TextInput.Password
                passwordCharacter: '*'
                id:rootpasswd
                width: 150
                x:200
            }
        }
        //********************************************

        Rectangle
        {
            color: 'yellow'
            y:30
            Text{
                text: qsTr("Listen port:");
                width: 100
            }
            Rectangle{
                anchors.fill: portedit
            }

            TextEdit{
                id:portedit
                width: 150
                x:200
                text: "10232"
            }
        }
        Button{
            id:connectButton
            text: qsTr("Start server")
            width: 100
            height: 30
            onClicked:
            {
                basereader.initServer(rootpasswd.text, portedit.text)
            }
        }

    }


    onXChanged:
    {
        fieldSetting.x = (width - fieldSetting.width) / 2;
    }

    onYChanged:
    {
        fieldSetting.y = (height - fieldSetting.height) / 2;
    }
    Component.onCompleted:
    {
        connectButton.x = fieldSetting.width - connectButton.width
        connectButton.y = fieldSetting.height - connectButton.height
    }
}
