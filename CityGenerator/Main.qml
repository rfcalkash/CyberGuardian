import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("City Generator test")
    ColumnLayout{
        Label{
            text: qsTr("Chunks amount (line width and number of lines)")
        }
        SpinBox{
            id:chunksAmount
            from: 1
            to: 10000
            value: 500
        }
    }
}
