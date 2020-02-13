import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

CircularGaugeStyle {
    id: tachometerStyle
    tickmarkInset: toPixels(0.04)
    minorTickmarkInset: tickmarkInset
    labelStepSize: 100
    tickmarkStepSize: 50
    labelInset: toPixels(0.23)

    property real xCenter: outerRadius
    property real yCenter: outerRadius
    property real needleLength: outerRadius - tickmarkInset * 1.25
    property real needleTipWidth: toPixels(0.02)
    property real needleBaseWidth: toPixels(0.06)
    property bool halfGauge: false

    function toPixels(percentage) {
        return percentage * outerRadius;
    }

    function degToRad(degrees) {
        return degrees * (Math.PI / 180);
    }

    function radToDeg(radians) {
        return radians * (180 / Math.PI);
    }

    function paintBackground(ctx) {
        if (halfGauge) {
            ctx.beginPath();
            ctx.rect(0, 0, ctx.canvas.width, ctx.canvas.height / 2);
            ctx.clip();
        }

        ctx.beginPath();
        ctx.fillStyle = "black";
        ctx.ellipse(0, 0, ctx.canvas.width, ctx.canvas.height);
        ctx.fill();

        ctx.beginPath();
        ctx.lineWidth = tickmarkInset;
        ctx.strokeStyle = "black";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, outerRadius - ctx.lineWidth / 2, 0, Math.PI * 2);
        ctx.stroke();

        ctx.beginPath();
        ctx.lineWidth = tickmarkInset / 2;
        ctx.strokeStyle = "#222";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, outerRadius - ctx.lineWidth / 2, 0, Math.PI * 2);
        ctx.stroke();

        ctx.beginPath();
        var gradient = ctx.createRadialGradient(xCenter, yCenter, 0, xCenter, yCenter, outerRadius * 1.5);
        gradient.addColorStop(0, Qt.rgba(1, 1, 1, 0));
        gradient.addColorStop(0.7, Qt.rgba(1, 1, 1, 0.13));
        gradient.addColorStop(1, Qt.rgba(1, 1, 1, 1));
        ctx.fillStyle = gradient;
        ctx.arc(xCenter, yCenter, outerRadius - tickmarkInset, outerRadius - tickmarkInset, 0, Math.PI * 2);
        ctx.fill();
    }

    background: Canvas {
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            paintBackground(ctx);
        }

//        Text {
//            id: rpmText
//            font.pixelSize: tachometerStyle.toPixels(0.3)
//            text: rpmInt
//            color: "white"
//            horizontalAlignment: Text.AlignRight
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.top: parent.verticalCenter
//            anchors.topMargin: 20

//            readonly property int rpmInt: valueSource.rpm
//        }
        Text {
            id: rpmText
//            font.pixelSize: toPixels(0.3)
            font.pixelSize: tachometerStyle.toPixels(0.3)
            text: rpmInt
            color: "white"
            horizontalAlignment: Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: toPixels(0.1)

            readonly property int rpmInt: control.value
        }
        Text {
            text: "x0.01"
            color: "white"
            font.pixelSize: tachometerStyle.toPixels(0.1)
            anchors.top: parent.top
            anchors.topMargin: parent.height / 4
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "Yaw(rad/s)"
            color: "white"
            font.pixelSize: tachometerStyle.toPixels(0.1)
            anchors.top: rpmText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}