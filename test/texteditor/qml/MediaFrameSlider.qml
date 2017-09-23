import QtQuick 2.7
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
    property bool simulator_phone: false
    property int tumbspace: (largerDimension / 8) + 60; /// mouse reserve
    property int tumb_wi: (largerDimension / 7)
    property int tumb_hi: (tumb_wi / 4 * 3)
    property int tumb_border: 4
    property int sl_height: (largerDimension / 38)
    property int stepSize: 1
    property int dohavingangle: 0;  ////  landscape = 0 / portrait = 1
    property bool changeOfWidth: false
    property bool changeOfHeight: false
    property bool newOrientation: false

    id: mediaslider;

    onWidthChanged: {changeOfWidth = true; newOrientation = (changeOfWidth && changeOfHeight)}
    onHeightChanged: {changeOfHeight = true; newOrientation = (changeOfWidth && changeOfHeight)}

    width:scwi
    height:schi
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
        id: tumbmedia_pic // 4*3
        width: tumb_wi
        radius: 5
        opacity: 0.2
        height: tumb_hi
        color: "green"
        x: {
            var start_x = 8+ ((parent.width - 2) / maximumValue) * value_frame - ( tumb_wi / 2)
            var end_limit = parent.width - tumb_wi - 1
            if (start_x < 0 )
                 return 1
            else
               return Math.min(start_x,end_limit)
        }
        y:tumbspace - (tumb_wi / 4 * 3) - tumb_border
        //// image XX Frame  hidden go - x 500
        Behavior on x {
          NumberAnimation { duration: 15 }
        }

        Rectangle {
            property int hielement: (18 * js_scale)
             id: time_text; width: tumb_wi; height:hielement;
             color:"black";
             opacity:0.8
             x:0; y:tumb_hi - hielement;
             radius: 10
         }



    }
    /* real time track slider here..   */
    Rectangle {
        x:0;y:tumbspace - 1
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
        width:sl_height; height:sl_height -1; radius: 8
        x: ((parent.width - 2) / maximumValue) * value_frame
        y:0
        opacity: 1
        id: slidercursor; smooth: true
        transform: Rotation { origin.x: sl_height / 2; origin.y: sl_height / 2; angle: 45}

            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 1.0; color: "gray" }
            }
            Behavior on x {
              NumberAnimation { duration: 15 }
            }
       }
         MouseArea {
         anchors.fill: parent
         onClicked: {
         var pos = mouse.x / longtimetrack.width * (maximumValue - minimumValue) + minimumValue
         mediaslider.value_frame = pos
         console.log("New value:" + pos  + "- "  + dohavingangle );
         }

     }
    }
   }
}
