import QtQuick 2.0
import QtQuick.Controls 2.12
import com.taskdb.client 1.0

Item {
    width: parent.width
    height: parent.height

    property ClientInterface client: null
    Rectangle
    {
        color: '#eeeee4'
        anchors.fill: parent
        ScrollView{
            id:scrolltask
            width: parent.width
            height: parent.height - 50
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        }
        Rectangle{
            id:adminparam
            width: parent.width
            height: parent.height - scrolltask.height
            y:scrolltask.height
        }
    }
}
