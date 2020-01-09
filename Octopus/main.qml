import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4// for TabView
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2//for get screen size

Window {
    id:root
    visible: true
    width: Screen.desktopAvailableWidth*0.618
    height: Screen.desktopAvailableHeight*0.618
    title: qsTr("Octopus")
    TabView {
        id: tabview
        width:parent.width
        height:parent.height
        Tab {
            title: "Red"
            Image { source: "image://image_provider/camera" }
        }
        Tab {
            title: "Blue"
            Rectangle { color: "blue" }
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
