


import QtQuick.Controls.Styles 1.4
import QtAV 1.7
import "utils.js" as Utils

import Qt.labs.platform 1.0
import QtQuick 2.2
import QtQuick.Controls 1.2



ApplicationWindow {
    visible: true
    width: 1000
    height: 600
	id: mainroot
    title: qsTr("Press key 'O' to open a file")

    //// signal moveminiframe(int Xposition)

    Video {
        id: video
        objectName: "video"
        autoPlay: true
        anchors.fill: parent
        onPositionChanged: updateProgress()
        onSeekFinished: {
        console.log("seek finished " + Utils.msec2string(position) )
        }
    }

    Item {
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_O:
                mediaselect()
                break
            case Qt.Key_N:
                video.source = "file:////Users/dev/Desktop/cd_scfilm/151202_wahrheit_kzu_kue_436k_p9v12.mp4"
                checkits()
                break
            case Qt.Key_Right:
                video.seek(video.position + 1000)
				console.log("event 28 VP: /"  +  Utils.msec2string(video.position) + "/ ")
                break
            case Qt.Key_Left:
                video.seek(video.position - 1000)
				console.log("event 27 VP: /"  +  Utils.msec2string(video.position) + "/ ")
                break
            case Qt.Key_M:
                video.volume.mute = !video.volume.mute
                break
            case Qt.Key_Up:
                video.volume = Math.min(2, video.volume+0.05)
                break
             case Qt.Key_Down:
               video.volume = Math.max(0, video.volume-0.05)
               break
            case Qt.Key_Space:
                video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
               break
            }
        }

        MouseArea {
            anchors.fill: parent
            id: windowAreaMouse
            focus: true;
            hoverEnabled: true;
            //// spropagateComposedEvents:false;
            onMouseYChanged: {
               console.log("La:show/hide:" + Utils.GlobalStateTimeTrack + "Elaps:" + Utils.runningTot() + ",X:" + windowAreaMouse.mouseX + ",Y:" + windowAreaMouse.mouseY);
            }
         }
    }




    Rectangle {
         id: controller_timetrack
         x: 0; y:mainroot.height - Utils.item_hi + 5
         width: mainroot.width; height:1000
         color: "transparent"
         opacity:1


    Rectangle {
        id: timetrack //// mainroot.height - 44 + 200 place to write onEntered story time trak audio/video
        x:0; y:500 /// hidden
        width: controller_timetrack.width ; height: Utils.item_hi

        opacity: 1
        visible: true
        color: "#0d52a0"
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#0d52a0";
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }

        Rectangle {
                id: textCursor
                width:120; height: 18;x:50;y:15
                color: "transparent";
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: "blue"
                    text: "T." + Utils.msec2string(video.position)  + "/" + Utils.msec2string(video.duration)
                }
            }






        PropertyAnimation { id: ahide;
                                target: timetrack;
                                property: "y";
                                to: 200;
                                duration: 1700;
         }

        PropertyAnimation { id: ashow;
                                target: timetrack;
                                property: "y";
                                to: 0;
                                duration: 1700;

         }

        states: [

                    State {
                        name: "t_show"
                        PropertyChanges {
                            target: controller_timetrack
                            opacity: 1
                        }
                     }, State {
                        name: "t_hide"
                            PropertyChanges {
                            target: controller_timetrack
                            opacity: 0
                       }
                    },   State {
                         name: "t_anim"
                    }

          ]

        ProgressBar {
              id: progressbar_a;
              value:0 ;minimumValue:0 ;maximumValue:100
              width: parent.width - (Utils.track_margin * 2) ; height:15
        }



       }



       MouseArea {
           id: trackAreaMouse
           /// trackAreaMouse.containsMouse console.log("run " + Utils.UnixTimenow() );  trackAreaMouse.mouseX
           anchors.fill: controller_timetrack;
           hoverEnabled: !Utils.isTouchScreen;
           //// propagateComposedEvents:false;
           onMouseXChanged: {
                Utils.no_activityfrom(1); ///  register this action times
                 swapProgressTimeTrack();
                 //// mainroot.moveminiframe(Utils.frameXcursor);
                 ///// console.log("send to moveminiframe "   +  Utils.frameXcursor +    "   progress_timetrack.qml")
           }
       }
    }
	
    function play() {
        video.play();
    }

    function swapProgressTimeTrack() {
        if (Utils.GlobalStateTimeTrack == 1 && !trackAreaMouse.containsMouse) {
            if (Utils.no_activityfrom(0) > 1) {
                ahide.running = true;
                timetrack.state = "t_hide";
                Utils.GlobalStateTimeTrack = 0;
                Utils.no_activityfrom(2); /// reset time
            }
        } else if (Utils.GlobalStateTimeTrack == 0 && trackAreaMouse.containsMouse) {
          /// fast show
          timetrack.state = "t_show"
          ashow.running = true;
          Utils.GlobalStateTimeTrack = 1;
          Utils.no_activityfrom(1); /// restart time
        }
    }

    function updateProgress() {
      progressbar_a.value=video.position
      progressbar_a.minimumValue=0
      progressbar_a.maximumValue=video.duration
      swapProgressTimeTrack();
        Utils.syncro_frame( mainroot.width , video.position , video.duration );
        //// controller.framemove.running = true;
        ///// progress_handler.controller.framemove.running = true;
        //// move preview Frame if drag..
        ///// progress_handlaer.sourceComponent
        //// progress_handler.controller.moveminiframe(Utils.frameXcursor);
        console.log("send to moveminiframe "   +  Utils.frameXcursor +    "   progress_timetrack.qml")
    }

    function checkits() {
       console.log("unixtime" + Utils.UnixTimenow() +
                       ";video.position:" + Utils.msec2string(video.position) + " video end" + Utils.msec2string(video.duration))
    }

    function dReport(xin,xen) {
            console.log(x);
    }

    function mediaselect() {
        title: "Audio Video File."
        source: "://qml/FileDialogs.qml"
        id: fileDialog
        onAccepted: outputOpenFile.text = "File selected: " + openFile.fileUrl
        onRejected: outputOpenFile.text = "File selected: –"
    }


}
