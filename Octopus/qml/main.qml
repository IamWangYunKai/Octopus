import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4// for TabView
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2//for get screen size
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import BackEndInterface 1.0

Window {
    id:root
    visible: true
    width: 1024//Screen.desktopAvailableWidth*0.618
    height: 576+50//Screen.desktopAvailableHeight*0.618
    title: qsTr("Octopus")

    property bool stopFlag : false
    property int fps : 0
    Interaction{
        id:interaction
    }

    Timer {
        id: fps_timer
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            fps = interaction.getFPS()
            if(stopFlag){
                fps_writer.text = "STOP"
            }
            else{
                fps_writer.text = fps.toString()
            }
        }
    }

    TabView {
        id: tabview
        width:parent.width
        height:parent.height
        onCurrentIndexChanged : {
            if(currentIndex == 0){
                fps_word.visible = true
                fps_writer.visible = true
            }
            else{
                fps_word.visible = false
                fps_writer.visible = false
            }
        }

        Tab {
            title: "Camera"
            Image {
                id:videoFrame
                source: "image://image_provider/camera"
                Timer {
                    id: video_timer
                    property int frameCounter: 0
                    interval: 33
                    repeat: true
                    running: true
                    onTriggered: {
                        frameCounter += 1
//                        console.log(frameCounter)
                        videoFrame.source = "image://image_provider/camera"+frameCounter
//                        console.log(interaction.getLantency())
                    }
                }
            }
        }
        Tab {
            title: "Test"
            Rectangle { color: "blue" }
        }
        Tab {
            title: "Viewer"
            Viewer {}
        }

        Tab {
            title: "Widget"
            WidgetOSRItem {
                id: osrItem
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                height: parent.height
            }
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
                implicitWidth: tabview.width/tabview.count
                implicitHeight: 50
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: styleData.selected ? "#dddddd" : "black"
                }
            }
        }
        Text{
            id : fps_word
            visible: true
            text : qsTr("FPS")
            x:30
            y:10
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        Text{
            id : fps_writer;
            visible: true
            text : "0"
            x:100
            y:10
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
    }

    Shortcut{
        sequence: "Ctrl+C"
        onActivated: {
            stopFlag = !stopFlag
            interaction.setStop(stopFlag)
        }
    }
}
