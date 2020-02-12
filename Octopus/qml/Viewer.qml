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
        columns:1;
        property int itemHeight : 100;
        property int itemWidth : width;
        Repeater{
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
