import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0
import QtAV 1.7
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick 2.0
import "utils.js" as Utils


Window {

    id:root



    objectName: "root"
    property bool changeOfWidth: false
    property bool changeOfHeight: false
    property bool newOrientation: false
    property int largerDimension: Math.max(root.width,root.height )
    property int smallDimension: Math.min(root.width,root.height )
    property int  scwi: Math.max(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    property int  schi: Math.min(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight) - 22
    property alias screen_wi: root.width
    //// full hd 3840×2160) 16:9
    //// dev screen 1400
    property string positiontxt: "P:"
    property string totaltxt: " T:"
    property real fullhdscreen: 3840 /// positiontxt + Utils.msec2string(media.position) + totaltxt Utils.msec2string(media.duration)
    property real devscreen: 500 // SKALEKEIEND67 //  emulate screen & mobile screen
    property real scaleRatio: 0.88888 // pixel item devscreen  / fullhdscreen
    property real scalePercentage: devscreen / (fullhdscreen / 100)
    visible: true
    width: devscreen
    height: (devscreen / 4) * 3

    color: "#ffffff"
    title: qsTr("non adesso")
    onWidthChanged: {
        changeOfWidth = true;
        newOrientation = (changeOfWidth && changeOfHeight)
        resizeEvent()
    }
    onHeightChanged: {
        changeOfHeight = true;
        newOrientation = (changeOfWidth && changeOfHeight)
        console.log("resizeevent:" + root.width + ":" +  root.height )
        resizeEvent()
    }
    /// onScreenChanged: resizeEvent()
    onScalePercentageChanged: resizeEvent()
    onScreen_wiChanged: resizeEvent()




    Video {
        id: media
        /// v_play =  0 novideo or end - 1 play - 2 pause
        /// m_status = 0 idle - 1 loading 100.buffering 101.buffered 404.end 500.error or?
        objectName: "media"
        autoPlay: true
        property int  m_status:0
        property int  v_play:0
        anchors.fill: parent
        onPositionChanged: updateProgress()
        onStateChanged: {
            //// v_play = media.playbackState == MediaPlayer.PlayingState ? 1 : 2
            /// auto play chance button play stop
            drawButton()
        }
        onStatusChanged: {
                        if (status == MediaPlayer.Loading) {
                            m_status=1;
                        } else if (status == MediaPlayer.Buffering) {
                            m_status=100;
                        } else if (status == MediaPlayer.Buffered) {
                            m_status=101;
                            v_play=1;
                            drawButton()
                        } else if (status == MediaPlayer.EndOfMedia) {
                            m_status=404;
                            v_play=0;
                            console.log("MediaPlayer.EndOfMedia")
                            drawButton()
                        } else if (status == MediaPlayer.InvalidMedia) {
                            m_status=500;
                        }
                        updateProgress()
        }

    }

    Item {
        anchors.fill: parent
        focus: true
        id: virtualkeyboard
        objectName: "virtualkeyboard"
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_O:
                fileDialog.open()
                break
            case Qt.Key_N:
                media.source = "file:////Users/dev/Desktop/cd_scfilm/rubinorosso.mp4"
                updateProgress()
                break
            case Qt.Key_Right:
                 jumpnext()
                 break
            case Qt.Key_Left:
                 jumpback()
                 break
            }
        }

        MouseArea {
                 id: controller_timetrack
                 objectName: "controller_timetrack"
                 property int spacebar: devscreen / 6
                 x: 0; y:0
                 width: devscreen
                 height: (devscreen / 4) * 3 - spacebar
                 property int status: media.position
                 onClicked: {
                     ooprogress.visible = (ooprogress.visible == true)? false:true
                     ooprogress_timer.stop()
                     ooprogress_timer.start()
                     switchPlay()
                     msg.info(positiontxt + Utils.msec2string(media.position) + totaltxt + Utils.msec2string(media.duration))
                     updateProgress()
                  }

        }


    }







   ToolTipTime {
       text:"00:00:00"
       id:displaytrack
       objectName: "displaytrack"
       largewi: root.width /2
       property real  xdistanceFork: 2.4555
       property real  ybridge: {
           if (root.height > 680) {
               return 200
           } else {
               return 70
           }
       }
       property real  tmpscale: 800/root.width
       /// 500x500 is start from canvas
       property int childwidth:largewi*(largewi/500)
       visible: false
       x:root.width/xdistanceFork
       y:Math.max((root.height /2) - childwidth,ybridge) //// width-height is same by child
       property alias  lasttext: displaytrack.text
       /// center by resize
       function resizeevent(x) {
          var nowscale=800/(x*2)
          var toolwidth=largewi*(x/500) /// tooltip scale self this way
          largewi=x
          x=root.width/xdistanceFork
          y=Math.max((root.height /2) - toolwidth,ybridge)
          console.log("ToolTipTime y " + y  )
          displaytrack.update()
       }
       /// draw time from frame
       function frametime(txt) {
           color = "green"
           text=txt
           lasttext=txt
           largewi=root.width /2
       }
   }


   Rectangle {
       id:bottomcontroll
       property real childscale:800/root.width
       property int  c_margin: root.height*0.03
       width:root.width-c_margin-c_margin
       height:root.height*0.08
       x:c_margin
       y:root.height - height - c_margin
       color: "#0d52a0"
       opacity: 0.6
       radius: 20
       z:50
       visible: true
       property real itemWidth :width*0.5
       Rectangle {
           width: parent.itemWidth
           height: parent.height
           y:0
           x:0 ///// parent.itemWidth*1
           color: "transparent"
           property int buttonwi:root.width*0.08
           /// property real buttonscale:0.4
           anchors.horizontalCenter: parent.horizontalCenter

         Row {

         spacing: 5
         scale: 0.7

         Rectangle {
               height:28
               width:28
               color:"transparent"
               scale:1
               ///// jumpback()
           }

        Rectangle {
            height:28
            width:28
            color:"transparent"
            scale:1
            /////  switchPlay()
        }

        Rectangle {
            height:28
            width:28
            color:"transparent"
            scale:1
            ///// jumpnext()
        }

         }


       }
   }




   Timer {
       id: bottomcontroll_timer
       interval: 4000
       onTriggered: {
           ////displaytrack.visible=false
          ////  bottomcontroll.visible = false
       }
   }



   MouseArea {
     id:mouseControllBottom
     objectName: "mouseControllBottom"
     width: root.width
     height: root.height/2
     x:0
     y:root.height/2
     hoverEnabled: true
     propagateComposedEvents: true
     onEntered: {
            console.log("mouseControllBottom work here..")
            if (bottomcontroll.visible!=true) {
                /// show hide go self
                bottomcontroll.visible=true
                displaytrack.visible=true
            }
            ////bottomcontroll_timer.stop()
           ////  bottomcontroll_timer.start()
     }

   }




    Slider {
        id:ooprogress
        objectName: "ooprogress"
        from: 0
        visible:false
        value: media.position
        to: media.duration
        onMoved: {
            media.seek(value)
            ///// sconsole.log("send pos " + Utils.msec2string(value))
            msg.info(positiontxt + Utils.msec2string(value) + totaltxt + Utils.msec2string(media.duration))
            visible = true
            ooprogress_timer.stop()
            ooprogress_timer.start()
        }

        Timer {
            id: ooprogress_timer
            interval: 4000
            onTriggered: ooprogress.visible = false
        }
    }


         Text {
            id: msg
            objectName: "msg"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Utils.scaled(40)
            style: Text.Outline
            styleColor: "green"
            color: "white"
            y: root.height / 6
            width: root.width
            height: root.height / 6
            onTextChanged: {
                msg_timer.stop()
                visible = true
                msg_timer.start()
            }
            Timer {
                id: msg_timer
                interval: 4000
                onTriggered: msg.visible = false
            }
            function error(txt) {
                styleColor = "red"
                text = txt
            }
            function info(txt) {
                styleColor = "green"
                text = txt
            }
        }



         function updateProgress() {
             displaytrack.frametime(Utils.msec2string(media.position))
              ooprogress.value = media.position
              var x = (root.width / scalePercentage) *100
              console.log("percentuale:" + scalePercentage + " %:" + x)

             }


            function drawButton() {

                console.log("drawButton" + media.v_play)
                if (media.v_play == 0 ) {
                    /// button_play.icon=awesome.icons.fa_youtube_play
                   //// button_play.text="Play"
                    return
                }
                if (media.playbackState == MediaPlayer.PlayingState) {
                    ////button_play.icon=awesome.icons.fa_stop
                    ////button_play.text="Pause/Stop"
                    return
                } else {
                    ////button_play.icon=awesome.icons.fa_youtube_play
                    ///// button_play.text="Play"
                    return
                }
            }

            function switchPlay() {
                 console.log("switchPlay")
                 if (media.source=="") {
                    fileDialog.open()
                    return
                 } else {
                    if (media.playbackState == MediaPlayer.PlayingState) {
                       media.pause()
                        media.v_play=2
                        ///console.log("switchPlay go pause")
                       drawButton()
                    } else {
                        media.play()
                        media.v_play=1
                       /// console.log("switchPlay go play")
                       drawButton()

                    }
                 }
            }

         function resizeEvent() {
             var maxpixel = Math.max(Screen.desktopAvailableWidth,Screen.desktopAvailableHeight)
             displaytrack.resizeevent(root.width / 2)
             var childscale=root.width/maxpixel
             root.scaleRatio=childscale
             //// button_play.scale=childscale
         }


         FileDialog {
             id: fileDialog
             onAccepted: media.source = fileUrl
         }


         function scaleRatio(x) {
             return x*scaleRatio;
         }

         function isOnRange(x) {
             if ( x < media.duration && x > 0) {
               return true
             } else {
                 return false
             }
         }
         function jumpnext() {
             if (media.source=="") {
                fileDialog.open()
                return
             }
             updateProgress()
             if (media.position !=0) {
                 var fiveminute = 5 * 60 * 1000 //// put setting
                 var gotoframe = media.position + fiveminute
                 if (isOnRange(gotoframe)) {
                 media.seek(gotoframe)
                 ooprogress.value = gotoframe
                 //// console.log("avanti" + screen_wi + " 28 VP: /"  +  Utils.msec2string(media.position) + "/ ")
                 //// msg.info(positiontxt + Utils.msec2string(gotoframe) + totaltxt + Utils.msec2string(media.duration))
                 displaytrack.frametime(Utils.msec2string(gotoframe))
                 }
             }
         }

         function jumpback() {
             if (media.source=="") {
                fileDialog.open()
                return
             }
             updateProgress()
             if (media.position !=0) {
                 var fiveminute = 5 * 60 * 1000 //// put setting
                 var gotoframe = media.position - fiveminute
                 if (isOnRange(gotoframe)) {
                 media.seek(gotoframe)
                 ooprogress.value = gotoframe
                 //// console.log("avanti" + screen_wi + " 28 VP: /"  +  Utils.msec2string(media.position) + "/ ")
                 ///// msg.info(positiontxt + Utils.msec2string(gotoframe) + totaltxt + Utils.msec2string(media.duration))
                 displaytrack.frametime(Utils.msec2string(gotoframe))
                 }
             }
         }



         MultiPointTouchArea {
             anchors.fill: parent
             id:touchcow
             objectName: "touchcow"
             mouseEnabled: true
             minimumTouchPoints: 2
             maximumTouchPoints: 4 /// / 4 finger pad
             property real lastdist: 0
             onUpdated: {

                 if (media.position < 11)
                     return
                     var second = 2 * 1000 //// put setting

                 for (var touch in touchPoints)
                     var pX = touchPoints[touch].x
                     var pY = touchPoints[touch].y
                     var pointa = Math.max(pX,pY)
                     var pointb = Math.min(pX,pY)
                     var distance = Math.abs(pointa - pointb)
                     if ( touchcow.lastdist < distance ) {
                         var gotoframe = media.position - second
                          media.seek(gotoframe)
                          ooprogress.value = gotoframe
                         //// console.log("bakward"  + distance  + " id." + touchPoints[touch].pointId)
                     } else {
                         var gotoframe = media.position + second
                          media.seek(gotoframe)
                          ooprogress.value = gotoframe
                         /// console.log("forward "   + distance  + " id." + touchPoints[touch].pointId)
                     }
                     touchcow.lastdist=distance
             }
         }


}
