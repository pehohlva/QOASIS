import QtQuick 2.7
import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick 2.0

Rectangle {
    /// Slider to drag + & - on buffered audio/video

    //// Accessible.role: Accessible.MediaFrameSlider
    // value_frame is read/write.  VECTOR MODUS /// scren&mobile
    property int largerDimension: Math.max(mediaslider.width,mediaslider.height )
    property int smallDimension: Math.min(mediaslider.width,mediaslider.height )
    property int  scwi: Math.max(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    property int  schi: Math.min(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    property real maximumValue: 6000
    property real minimumValue: 0
    property real value_frame: 0
    property real js_scale: 0.6
    property bool simulator_phone: true
    property int tumbspace: (largerDimension / 8) + 60; /// mouse reserve
    property int tumb_wi: (largerDimension / 7)
    property int tumb_hi: (tumb_wi / 16 * 9)
    property int tumb_border: 4
    property int sl_height: (largerDimension / 38)
    property int stepSize: 1
    property int dohavingangle: 0;  ////  tumb_wi tumb_hi   landscape = 0 / portrait = 1
    property bool changeOfWidth: false
    property bool changeOfHeight: false
    property bool newOrientation: false

    id: mediaslider;

    onWidthChanged: {changeOfWidth = true; newOrientation = (changeOfWidth && changeOfHeight)}
    onHeightChanged: {changeOfHeight = true; newOrientation = (changeOfWidth && changeOfHeight)}

    width:scwi
    height:schi;
    ///// color: "black"
    x:0;
    y:(dohavingangle == 0)? 0:tumbspace;
    transform: Rotation {
      origin.y: (smallDimension / 2);
      origin.x: (smallDimension / 2);
      angle:dohavingangle
    }

    Behavior on dohavingangle {
      NumberAnimation { duration: 1500 }
    }

    onNewOrientationChanged: {
     if (newOrientation) {
     changeOfWidth = false;
     changeOfHeight = false;
    if (width > height) {
     dohavingangle = 0;
     console.log("landscape 2")
     } else {
     dohavingangle = (simulator_phone)? 90 : 0;
     console.log("portrait 1 ")
     }
     }
    }


    /* frame prewiev from audio or video   */
    Rectangle {
        width: mediaslider.width; height:tumbspace
        id: imagetrack;
        color: "transparent";
        opacity: 1


    Rectangle {
        id: tumbmedia_pic // 4*3 tumb_wi tumb_hi
        width: tumb_wi
        radius: 5
        opacity: 1
        height: tumb_hi
        color: "transparent"
        x: {
            var start_x = 8+ ((parent.width - 2) / maximumValue) * value_frame - ( tumb_wi / 2)
            var end_limit = parent.width - tumb_wi - 1
            if (start_x < 0 )
                 return 1
            else
               return Math.min(start_x,end_limit)
        }
        y:0
        border.color: "black"
        border.width: 1
        Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "/Users/dev/Pictures/151203_losgetreten_pdi_dbw_436k_p9v1223.280.png"
        }
        //// image XX Frame  hidden go - x 500
        Behavior on x {
          NumberAnimation { duration: 188 }
        }

        Rectangle {
            property int hielement: (18 * js_scale)
             id: time_text; width: tumb_wi; height:hielement;
             color:"black";
             opacity:0.8
             x:0; y:tumb_hi - (18 * js_scale);
             radius: 10
         }

    }
    /* real time track slider here..   */
    Rectangle {
        x:0;y: tumb_hi + 4
        id: longtimetrack;
        opacity: 1
        width: mediaslider.width; height:sl_height
        border.color: "white"; border.width: 0; radius: 4
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#0d52a0" }
            GradientStop { position: 1.0; color: "#ffffff" }
        }
    /* cursor in slider to drag   */
    Rectangle {
        width:sl_height; height:sl_height -2;
        x: ((parent.width - 2) / maximumValue) * value_frame
        y:0
        border.color: "black"
        border.width: 1
        radius: sl_height*0.5
        opacity: 1
        id: slidercursor; smooth: true
            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 1.0; color: "gray" }
            }
            Behavior on x {
              NumberAnimation { duration: 222 }
            }
       }


         MouseArea {
         id: cursormuose

         anchors.fill: parent
         onClicked: {
         var pos = mouse.x / longtimetrack.width * (maximumValue - minimumValue) + minimumValue
         mediaslider.value_frame = pos
         //// console.log("New value:" + pos  + "- "  + dohavingangle );
         }
         onPositionChanged: {
         var pos = mouse.x / longtimetrack.width * (maximumValue - minimumValue) + minimumValue
             //// console.log("x move =" + mouse.x)
         mediaslider.value_frame = pos
         }
         drag {
         target: slidercursor
        axis: Drag.XAxis
        }
     }
    }
   }
}
