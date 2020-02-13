import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4// for TabView
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2//for get screen size
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4

import BackEndInterface 1.0

Window {
    id:root
    visible: true
    width: 1440;//Screen.desktopAvailableWidth*0.618
    height: 720;//Screen.desktopAvailableHeight*0.618
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
        interval: 16
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
//                        console.log(frameCounter)
                        videoFrame.source = "image://image_provider/camera"+frameCounter
//                        console.log(interaction.getLatency())
                    }
                }
            }
        }
        Tab {
            title: "Test"
            Row {
                id: gaugeRow
                spacing: parent.width * 0.05
                padding: parent.width * 0.1
                anchors.centerIn: parent
                CircularGauge {
                    id: speedometer
                    value: v*100    // here get value of v, which comes from frame_timer
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 0
                    maximumValue: 240
                    width: parent.width/4
                    height: width
                    style: DashboardGaugeStyle {}
                    Behavior on value {
                        NumberAnimation {
                            duration: 500
                        }
                    }
                }
                Column{
                    topPadding : parent.height/8
                    CircularGauge {
                        id: fuelGauge
                        value: 0.6
                        maximumValue: 1
                        width: gaugeRow.width/8
                        height: width
                        style: IconGaugeStyle {
                            id: fuelGaugeStyle

                            icon: "qrc:/resource/fuel-icon.png"
                            minWarningColor: Qt.rgba(0.5, 0, 0, 1)

                            tickmarkLabel: Text {
                                color: "white"
                                visible: styleData.value === 0 || styleData.value === 1
                                font.pixelSize: fuelGaugeStyle.toPixels(0.225)
                                text: styleData.value === 0 ? "E" : (styleData.value === 1 ? "F" : "")
                            }
                        }
                    }
                    CircularGauge {
                        value: 0.4
                        maximumValue: 1
                        width: gaugeRow.width/8
                        height: width
                        style: IconGaugeStyle {
                            id: tempGaugeStyle

                            icon: "qrc:/resource/temperature-icon.png"
                            maxWarningColor: Qt.rgba(0.5, 0, 0, 1)

                            tickmarkLabel: Text {
                                color: "white"
                                visible: styleData.value === 0 || styleData.value === 1
                                font.pixelSize: tempGaugeStyle.toPixels(0.225)
                                text: styleData.value === 0 ? "C" : (styleData.value === 1 ? "H" : "")
                            }
                        }
                    }
                }
                CircularGauge {
                    id: tachometer
                    width: parent.width/4
                    height: width
                    value: w*500    // here get value of w, which comes from frame_timer
                    minimumValue: -500
                    maximumValue: 500
                    anchors.verticalCenter: parent.verticalCenter
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
            title: "Viewer"
            Viewer{}
        }
        Tab {
            title: "OpenGL"
            Rectangle{
                width:400
                height:400
                GLItem {
                    id: cube
                    anchors.centerIn: parent
                    ParallelAnimation {
                        running: true
                        NumberAnimation {
                            target: cube
                            property: "rotateAngle"
                            from: 0
                            to: 360
                            duration: 5000
                        }

                        Vector3dAnimation {
                            target: cube
                            property: "axis"
                            from: Qt.vector3d( 0, 1, 0 )
                            to: Qt.vector3d( 1, 0, 0 )
                            duration: 5000
                        }
                        loops: Animation.Infinite
                    }
                }
            }
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
            x:30
            y:10
            color:"blue"
            font.pointSize: 16
            font.weight:  Font.Bold
        }
        Text{
            id : latency_word
            visible: true
            text : qsTr("Latency:")
            x:30
            y:60
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
        Text{
            id : latency_writer;
            visible: true
            text : "--"
            x:150
            y:60
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
