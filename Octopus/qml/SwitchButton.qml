import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4

Switch {
      id: control
      text: qsTr("Handbreak")

      indicator: Rectangle {
          implicitWidth: 64
          implicitHeight: 26
          x: control.leftPadding
          y: parent.height / 2 - height / 2
          radius: width/2
          color: control.checked ? "#f03949" : "#cccccc"
          border.color: control.down ? "grey" : "#cccccc"

          Rectangle {
              x: control.checked ? parent.width - width : 0
              width: 26
              height: 26
              radius: width/2
              color: control.down ? "grey" : "#cccccc"
              border.color: control.down ? "grey" : "#cccccc"
          }
      }

      contentItem: Text {
          text: control.text
          font: control.font
          color: control.checked ? "#f03949" : "grey"
          anchors.left: control.right
          anchors.leftMargin: 0
          anchors.verticalCenter: parent.verticalCenter
      }
}
