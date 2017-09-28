import QtQuick 2.5
import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Rectangle {
    id: root
    width: 800
    height: 300

    MultiPointTouchArea {
        anchors.fill: parent
        id:touchcow
        objectName: "touchcow"
        mouseEnabled: true
        minimumTouchPoints: 2
        maximumTouchPoints: 4 /// / 4 finger pad
        property real lastdist: 0
        property int default_pix_density: 4  //pixel density of my current screen
        property int scale_factor: Screen.pixelDensity/default_pix_density

        onUpdated: {
            console.log("M pix <" + scale_factor + "> - Screen.pixelDensity " + Screen.pixelDensity)
            for (var touch in touchPoints)
                var pDens = touchPoints[touch].velocity
                 var pPre = touchPoints[touch].pressure
                var pX = touchPoints[touch].x
                var pY = touchPoints[touch].y
                var pointa = Math.max(pX,pY)
                var pointb = Math.min(pX,pY)
                var distance = Math.abs(pointa - pointb)
                if ( touchcow.lastdist < distance ) {
                    console.log("bakward"  + distance  + " id." + touchPoints[touch].pointId)
                    console.log("pDens-" + pDens)
                    console.log("pPre-" + pPre)
                } else {
                    console.log("forward "   + distance  + " id." + touchPoints[touch].pointId)
                }

                touchcow.lastdist=distance

                //// console.log("Multitouch updated touch", touchPoints[touch].pointId, "at", touchPoints[touch].x, ",", touchPoints[touch].y)
        }
    }
}
