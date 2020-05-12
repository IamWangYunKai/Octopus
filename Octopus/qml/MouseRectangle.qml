import QtQuick 2.10

Rectangle{
    id: root
    width:200
    height:200
    radius: height/2
    color:"#3A3F44"
    opacity:0.0
    signal valueChanged(real x, real y)
    MultiPointTouchArea {
        id: touchArea
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 1
        touchPoints: [
            TouchPoint { id: touch  }
        ]
        onReleased:{
            valueChanged(0, 0)
            parent.opacity = 0.0
            rocker.opacity = 0.0
        }
        onUpdated: {
            valueChanged(touch.x - parent.width/2, touch.y - parent.height/2)
        }
        onPressed: {
            valueChanged(touch.x - parent.width/2, touch.y - parent.height/2)
            parent.opacity = 0.7
            rocker.opacity = 1.0
        }
        states: State {
            name: "reset"; when: touch.pressed
            PropertyChanges {
                target: rocker
                color: "#ee5f5b"
                opacity:1.0
                //x:Math.min(Math.max(0,touch.x - width/2),parent.width - width)
                //y:Math.min(Math.max(0,touch.y - height/2),parent.height - height)
                x:_r * Math.cos(theta) + parent.width/2 - width/2
                y:_r * Math.sin(theta) + parent.height/2 - height/2
            }
        }
    }
    Rectangle{
        id:rocker
        width:50
        height:50
        radius: height/2
        x:parent.width/2 - width/2
        y:parent.height/2 - height/2
        color:"#5bc0de";
        opacity:0.3
        property int _x:touch.x - parent.width/2
        property int _y:touch.y - parent.height/2
        property real _r: Math.min(Math.sqrt(_x*_x + _y*_y), parent.width/2)
        property real theta: Math.atan2(_y,_x)
    }
    function changeAxis(axis_x, axis_y){
        valueChanged(axis_x, axis_y)
    }
}
