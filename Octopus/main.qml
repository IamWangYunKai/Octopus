import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id:root
    visible: true
    width: 1280
    height: 960
    title: qsTr("Octopus")
    TabView {
        id: tabview
        width:parent.width
        height:parent.height
        Tab {
          title: "Red"
          Rectangle { color: "red" }
        }
        Tab {
          title: "Blue"
          Rectangle { color: "blue" }
        }
        Tab {
          title: "Green"
          Rectangle { color: "green" }
        }
        style: TabViewStyle {
          frameOverlap: 0
          tabOverlap: 0
          tab: Rectangle {
              color: styleData.selected ? "#303030" : "grey"
              implicitWidth: tabview.width/tabview.count;
              implicitHeight: 50
              Text {
                  id: text
                  anchors.centerIn: parent
                  text: styleData.title
                  color: styleData.selected ? "#dddddd" : "black"
              }
          }
        }
      }

}
