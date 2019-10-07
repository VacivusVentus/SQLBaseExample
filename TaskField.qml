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
            layer.enabled: true
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
    property int posEl: 0
    function addTask(idtask, task, describe, dates, progress)
    {
        let comp = Qt.createQmlObject('TaskElement{width:parent - 80; height:30;x:0;}', scrolltask, "taskel" + posEl)
        comp.y = 40 * posEl
        posEl++
        scrolltask.contentHeight = posEl * 40
        comp.width = scrolltask.width - 40
        comp.idtask = idtask
        comp.task = task
        comp.describe = describe
        comp.date = dates
        comp.progress = progress
    }
}
