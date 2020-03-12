import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4// for TabView
import QtQuick.Controls.Styles 1.4
//import QtQuick.Window 2.2//for get screen size
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4

import BackEndInterface 1.0

Window {
    id:root
    visible: true
    visibility: Qt.platform.os === "android" ? Window.FullScreen : Window.Windowed
    width: Qt.platform.os === "android" ? 0 : 720*2//Screen.desktopAvailableWidth*0.618
    height: Qt.platform.os === "android" ? 0 : 720//Screen.desktopAvailableHeight*0.618
    title: qsTr("Octopus")

    property bool stopFlag : false
    property int fps : 0
    property int latency : 0
    property double v : 0
    property double w : 0
    Interaction{
        id:interaction
    }

    Timer {
        id: second_timer
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            fps = interaction.getFPS()
            latency = interaction.getLatency()
            interaction.syncCloc(10)
            if(stopFlag){
                fps_writer.text = "STOP"
                latency_writer.text = "STOP"
            }
            else{
                fps_writer.text = fps.toString()
                if(fps == 0){
                    latency_writer.text = "--"
                }
                else{
                    latency_writer.text = latency.toString() + " ms"
                }
            }
        }
    }
    Timer {
        id: frame_timer
        interval: 17
        repeat: true
        running: true
        onTriggered: {
            v = interaction.getV()
            w = interaction.getW()
        }
    }
    onHeightChanged : {
        tabview.height = root.height
    }

    TabView {
        id: tabview
        width:parent.width
        height:parent.height
        tabsVisible:false
        onCurrentIndexChanged : {
            if(currentIndex == 0){
                fps_word.visible = true
                fps_writer.visible = true
                latency_word.visible = true
                latency_writer.visible = true
            }
            else{
                fps_word.visible = false
                fps_writer.visible = false
                latency_word.visible = false
                latency_writer.visible = false
            }

            if(currentIndex == 3){
                tabview.height = 0
            }
            else{
                tabview.height = parent.height
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
                        videoFrame.source = "image://image_provider/camera"+frameCounter
                        interaction.sendCmd()
                    }
                }
                MouseRectangle{
                    id:r1
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.bottom:parent.bottom
                    anchors.bottomMargin:20
                    onValueChanged:{
                        interaction.vel(x, y)
                        interaction.dir(x, y)
                    }
                }
                DelayButton{
                    id:delayButton
                    delay: 700
                    text: "Brake"
                    width: parent.width/8>100 ? parent.width/8 : 100
                    height: width
                    opacity: 0.3
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.bottom:parent.bottom
                    anchors.bottomMargin:20
                    property bool ifPressed: false
                    onPressedChanged: {
                        checked = false
                        ifPressed = !ifPressed
                        opacity = ifPressed ? 0.7 : 0.3
                    }
//                    onActivated: {
//                        console.log("STOP !")
//                    }
                    Timer {
                        interval: 17
                        repeat: true
                        running: true
                        onTriggered: {
                            interaction.setBrake(delayButton.progress)
                        }
                    }
                }
                Dial{
                    id: gear
                    anchors.bottom:delayButton.top
                    anchors.bottomMargin:20
                    anchors.left: delayButton.left
                    width: parent.width/8>100 ? parent.width/8 : 100
                    height: width
                    stepSize: 1
                    minimumValue: 0
                    maximumValue: 5
                    tickmarksVisible:true
                    opacity: 0.7
                    Text {
                        text: qsTr("Gear")
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    onValueChanged: {
                        opacity = value > 0 ? 0.5 - value/20.0 : 0.7
                        interaction.setGear(value)
                    }
                }

                CircularGauge {
                    id: speedometer
                    opacity: 0.7
                    value: v*100    // here get value of v, which comes from frame_timer
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.top:parent.top
                    anchors.topMargin:10
                    minimumValue: 0
                    maximumValue: 240
                    width: parent.width/8>100 ? parent.width/8 : 100
                    height: width
                    style: DashboardGaugeStyle {}
                    Behavior on value {
                        NumberAnimation {
                            duration: 500
                        }
                    }
                }
                CircularGauge {
                    id: tachometer
                    opacity: 0.7
                    width: parent.width/8>100 ? parent.width/8 : 100
                    height: width
                    value: w*500    // here get value of w, which comes from frame_timer
                    minimumValue: -500
                    maximumValue: 500
                    anchors.right: speedometer.left
                    anchors.rightMargin: 20
                    anchors.top:parent.top
                    anchors.topMargin:10
                    style: TachometerStyle {
                        labelStepSize: (tachometer.maximumValue - tachometer.minimumValue)/10
                        tickmarkStepSize: labelStepSize/2
                    }
                    Behavior on value {
                        NumberAnimation {
                            duration: 500
                        }
                    }
                }
            }
        }
        Tab {
            title: "Settings"
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
            text : qsTr("FPS:")
            anchors.top: parent.top
            anchors.topMargin:10
            anchors.left: parent.left
            anchors.leftMargin:30
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        Text{
            id : latency_word
            visible: true
            text : qsTr("Latency:")
            anchors.top: fps_word.bottom
            anchors.topMargin:10
            anchors.left: fps_word.left
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        Text{
            id : fps_writer;
            visible: true
            text : "0"
            anchors.top: fps_word.top
            anchors.left: fps_word.right
            anchors.leftMargin:20
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        Text{
            id : latency_writer;
            visible: true
            text : "--"
            anchors.top: latency_word.top
            anchors.left: latency_word.right
            anchors.leftMargin:20
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        SwitchButton{
            id: handbreak
            anchors.top:latency_word.bottom
            anchors.topMargin:10
            anchors.left:latency_word.left
            opacity: 0.3
            onClicked: {
                interaction.setHandBrake(checked)
                handbreak.opacity = checked ? 1.0 : 0.3
            }
        }
    }

    Shortcut{
        sequence: "Ctrl+C"
        onActivated: {
            stopFlag = !stopFlag
            interaction.setStop(stopFlag)
        }
    }
    Shortcut{
        sequence: "F1"
        onActivated: {
            tabview.currentIndex = 0
        }
    }
    Shortcut{
        sequence: "F2"
        onActivated: {
            tabview.currentIndex = 1
        }
    }
    Shortcut{
        sequence: "F3"
        onActivated: {
            tabview.currentIndex = 2
        }
    }
    Shortcut{
        sequence: "F4"
        onActivated: {
            tabview.currentIndex = 3
        }
    }
    Shortcut{
        sequence: "F5"
        onActivated: {
            tabview.currentIndex = 4
        }
    }
    Shortcut{
        sequence: "F6"
        onActivated: {
            tabview.currentIndex = 5
        }
    }
}
