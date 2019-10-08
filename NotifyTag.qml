import QtQuick 2.0

Item {
    property string message: ""
    Text
    {
        text: message
        height: parent.height
        color: '#ee0000'
        width: parent.width * 2.0 / 30
        x: (parent.width - width) / 2.0
    }
    MouseArea{
        anchors.fill: symbclose
        cursorShape: "PointingHandCursor"
        onPressed: {
            parent.destroy()
        }
    }
    Text{
        id:symbclose
        text: 'X'
        color: 'red'
        x:parent.width - 30
    }
}
