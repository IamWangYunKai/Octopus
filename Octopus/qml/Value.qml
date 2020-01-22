import QtQuick 2.0

Rectangle{
    id:root;
    height:parent.itemHeight || 20;
    width:parent.itemWidth || 100;
    color:"transparent";
    property double value : 1.0;
    property int textWidth : 60;
    Text{
        x:0;
        y:0;
        color:"#303030";
        width:root.textWidth;
        height:root.height;
        text:Math.floor((value)*100)+"%";
    }
    Rectangle{
        id:vRec;
        y:0;
        x:root.textWidth;
        height : root.height;
        width : root.value*(root.width-root.textWidth*1.2);
        color:"#5cb85c";
        radius: height/2;
        Behavior on width{
            NumberAnimation{duration: 1000}
        }
        Behavior on color {
            ColorAnimation {duration: 1000}
        }
    }
    onValueChanged: {
        var c = "#5cb85c";
        if(value < 0.2)
            c = "#d9534f";
        else if(value < 0.4)
            c = "#f0ad4e";
        vRec.color = c;
    }

}
