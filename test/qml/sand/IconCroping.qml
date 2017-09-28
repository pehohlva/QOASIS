

import QtQuick 2.7


Rectangle {
    width:600
    height:515
    y:9
    color: "red"
    scale:1
    Image {
        scale:1
        //// x inizia a x -18 y -32
        /// line 1 begin at y-18
        property int emulapezzi:11
        property int spaceX:7
        property int capsulate:45
        //// line 1 31y
        ///  line 2 127y
        ///  line 3 224y
        ///  all line beginn 15x
        /// cursor 2=495 ----440
        property int jumpLineX:0
        property int lastdirtyX:9
        property real cursorX:capsulate+10
        property int diffsY:127 /// start31 Y from top down
        property int diffsX:14   /// start30 X from left to right
        horizontalAlignment:Image.AlignLeft
        verticalAlignment:Image.AlignTop
            x:(0 - diffsX) - (cursorX*jumpLineX) /// diffsX;
            y:(0 - diffsY)
            width:diffsX + (cursorX*(jumpLineX+1)) - lastdirtyX
            height:diffsY + capsulate
            source: "fontplay.png"
            fillMode:Image.Pad
            clip: false
            mirror:false
            opacity:0.88888888
    }
}
