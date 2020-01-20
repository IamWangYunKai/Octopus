import QtQuick 2.10
import QtQuick.Layouts 1.3
import BackEndInterface 1.0
import "."

Item {
    ViewerInterface{
        id : viewerInterface;
    }

    Grid{
        anchors.fill: parent;
        spacing: 0;
        rowSpacing: 0;
        columns:2;
        property int itemHeight : 40;
        property int itemWidth : width/2;
        Repeater{
//            model:[0,7,8,9,10,11,12,13,14,15,16];
            model: viewerInterface;
            Robot{
                number: mID;
                team : mTeam;
                battery : mBattery;
                capacity: mCapacitance;
                infrared: mInfrared;
            }
        }
    }
}
