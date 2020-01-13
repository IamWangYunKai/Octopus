import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4// for TabView
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2//for get screen size
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Window {
    id:root
    visible: true
    width: 2*512//Screen.desktopAvailableWidth*0.618
    height: 2*288+50//Screen.desktopAvailableHeight*0.618
    title: qsTr("Octopus")
    TabView {
        id: tabview
        width:parent.width
        height:parent.height
        Tab {
            title: "Camera"
            Image {
                id:videoFrame
                source: "image://image_provider/camera"
                Timer {
                    id: video_timer
                    property int frameCounter: 0
                    interval: 60
                    repeat: true
                    running: true
                    onTriggered: {
                        frameCounter += 1
//                        console.log(frameCounter)
                        videoFrame.source = "image://image_provider/camera"+frameCounter
                    }
                }
            }
        }
        Tab {
            title: "Test"
            Rectangle { color: "blue" }
        }
        Tab {
            title: "Settings"
//            Rectangle { color: "blue" }
            Settings{
                width:parent.width
                height:parent.height
            }
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
