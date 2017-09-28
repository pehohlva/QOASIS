
import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

/* remember install font Ubuntu Condensed

now bold 19px Arial
running 22px Ubuntu Condensed
*/


Item {
    id:container
    /*
    function readValues(anArray, anObject) {
            for (var i=0; i<anArray.length; i++)
                console.log("Array item:", anArray[i])

            for (var prop in anObject) {
                console.log("Object item:", prop, "=", anObject[prop])
            }
        }
    */
    ///property int  scwi: Math.max(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    /// property int  schi: Math.min(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    //// property int fullhdwidth: 3840
    property int work_wi: 500  /// this is scale 1
    ///// property int workdev_wi: 1400 / 10  /// this is scale 1
    property alias  largewi: container.work_wi
    property alias  text: canvas.content
    property color current_color: "#0d52a0"
    property alias  color: container.current_color
    scale: 1
    property alias  afterscale: container.scale
    width: work_wi*scale
    height: work_wi*scale
    property bool changeOfWidth: false
    property bool changeOfHeight: false
    property bool newOrientation: false

    onWidthChanged: {changeOfWidth = true; newOrientation = (changeOfWidth && changeOfHeight)}
    onHeightChanged: {
        changeOfHeight = true;
        newOrientation = (changeOfWidth && changeOfHeight)
        //// console.log("width:" + width + " max:"+ scale)
        //// console.log("idealwidth:" + work_wi + " max:"+ scale)

    }
    /* max scale 1 fullhdwidth is top only -1 accept  */

    onLargewiChanged: {
        ////console.log("ToolTipTime event->workwi " + largewi)
        afterscale = largewi/500
        //// console.log("element width:" + largewi + " max:"+ afterscale)
        scale=afterscale
    }


    Rectangle {
        id :rectid
        width: 500
        height: 500
        color: "transparent"
        scale: 1
        opacity: 1
        //// border.width : width / 55
        //// border.color: Qt.darker(color, 2)
        x:0
        y:0
        //// property string playState: "T.00:00:00"

        Canvas {
            id: canvas
            width: 280 /// draw text e canvas on this
            height: 280
            opacity: 0.6
            property int xcenter: width / 2
            property string content: "00:00:00"
            property string playState: "T."+content
            scale: 1.855555
           //// anchors.fill: parent
            x: xcenter / scale - 40
            y: xcenter / scale - 40
            z: 100 /// z-index
            property color fillStyle: current_color // blue/or parent order
            property color strokeStyle:  Qt.darker(fillStyle, 2)
            property int lineWidth: 1
            property bool fill: true
            property bool stroke: true
            property real alpha: 0.8
            property real rotate :0.2

            SequentialAnimation on rotate {
                loops: Animation.Infinite
                PropertyAnimation { duration: 5000; to: -0.2 }
                PropertyAnimation { duration: 5000; to: 0.2 }
            }

            SequentialAnimation on scale {
                loops: Animation.Infinite
                PropertyAnimation { duration: 1000; to: 1.855555 }
                PropertyAnimation { duration: 1000; to: 1.6 }
            }

            antialiasing: true
            onStrokeStyleChanged: requestPaint();
            onPlayStateChanged:requestPaint();
            onLineWidthChanged:requestPaint();
            onFillChanged:requestPaint();
            onStrokeChanged:requestPaint();
            onScaleChanged:requestPaint();
            onRotateChanged:requestPaint();

            onPaint: {
                var ctx = canvas.getContext('2d');
                var originX = 66
                var originY = 75

                ctx.save();
                ctx.clearRect(0, 0, canvas.width, canvas.height);
                ctx.translate(originX, originX);
                ctx.strokeStyle = canvas.strokeStyle;
                ctx.fillStyle = canvas.fillStyle;
                ctx.lineWidth = canvas.lineWidth;

                ctx.translate(originX, originY)
                ctx.rotate(canvas.rotate);
                ctx.scale(canvas.scale, canvas.scale);
                ctx.translate(-originX, -originY)

                // ![0]
                ctx.beginPath();
                ctx.moveTo(75,25);
                ctx.quadraticCurveTo(25,25,25,62.5);
                ctx.quadraticCurveTo(25,100,50,100);
                ctx.quadraticCurveTo(50,120,30,125);
                ctx.quadraticCurveTo(60,120,65,100);
                ctx.quadraticCurveTo(125,100,125,62.5);
                ctx.quadraticCurveTo(125,25,75,25);
                ctx.closePath();
                // ![0]

                if (canvas.fill)
                    ctx.fill();
                if (canvas.stroke)
                    ctx.stroke();

                // ![1]
                ctx.fillStyle = "white";
                ctx.font = "bold 19px Arial";
                ctx.fillText(playState,30, 70);
                // ![1]
                ctx.restore();
            }
        }

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onMouseXChanged: {
                 console.log(" scale is:"+ container.scale)
            }
        }
    }

}
