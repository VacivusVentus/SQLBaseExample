import QtQuick 2.0

Item {
    property string message: ""
    Text
    {
        text: message
        height: parent.height
        color: 'red'
        width: parent.width * 2.0 / 30
        x: (parent.width - width) / 2.0
    }
}
