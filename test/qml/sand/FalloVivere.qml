import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Canvas {
        property real dd: 0

        SequentialAnimation on dd {
            loops: Animation.Infinite
            PropertyAnimation { duration: 2000; to: 1 }
            PropertyAnimation { duration: 2000; to: 0 }
        }

        onDdChanged: requestPaint()

        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.fillStyle = "black"
            ctx.fillRect(0, 0, width, height);

            ctx.fillStyle = Qt.rgba(0.25, 0.8, 0.32, 1);
            ctx.fillRect(dd * width, dd * height, 100, 100);
        }
    }
}

