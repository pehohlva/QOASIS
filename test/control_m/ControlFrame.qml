import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick 2.7
import "utils.js" as Utils

Item {
    id:box
    width:500
    height:500
    Rectangle {
            id :canvasroot
            property real item:7
            width:410
            height:500
            color: "green"
            scale:1  //// from 0.5 to 1 is ok
            property int frame:1000*33
            readonly property real cellquadri:45 //// mousearea must read
            //// property bool playstatus:false
            //// property bool mutestatus:false
            y:22
            x:0
            opacity:0.8999
            Canvas {
                id: canvas
                objectName: "canvas"
                //// line 1 31y
                ///  line 2 127y
                ///  line 3 224y
                ///  all line beginn 15x
                /// cursor 2=495 ----440
                width:canvasroot.width
                height:canvasroot.height
                opacity: 1
                readonly property string pixelurl:"fontplay.png" /// one image
                readonly property color cBorder: "black"
                readonly property color cFill: "white"
                readonly property int fromTop:0 /// 372 or distance from top canvas
                property int capsulate:canvasroot.cellquadri
                property int border:10
                property bool play:false
                property bool mute:false
                property var theArray: new Array()
                property var theDate: new Date()
                property int cursor:0
                property bool hoverdraw:true
                property string activeitem:"none"
                scale:1
                //// renderStrategy: Canvas.Immediate
                antialiasing: true
                onPlayChanged:requestPaint();
                onMuteChanged:requestPaint();
                onActiveitemChanged:requestPaint();
                onPaint: {
                theDate=new Date()
                cursor=0 /// draw 2 time increment
                theArray=new Array()
                var ctx = canvas.getContext('2d');
                if (!isImageLoaded(pixelurl)) {
                    ctx.fillStyle = 'red'
                    ctx.fillRect(0,0,canvas.width,canvas.height);
                    ctx.save()
                    ctx.fillStyle = "white";
                    ctx.font = "bold 27px Arial";
                    ctx.fillText("Image not load.. sorry.. ",30, 70);
                    ctx.fillText("Image not load.. sorry.. ",30, 70*2);
                    ctx.fillText("Image not load.. sorry.. ",30, 70*3);
                    ctx.fillText("Image not load.. sorry.. ",30, 70*4);
                    return
                }
                //// console.log("image is load ok..")
                ctx.fillStyle = cFill
                ctx.fillRect(0,0,canvas.width,canvas.height);
                ctx.save()
                ctx.strokeStyle = cBorder
                ctx.lineWidth = 2
                /// bu 1- bakward play frame
                drawCell(ctx,4,2,"Backward")
                cursor=cursor+border
                /// bu 2- button play or pause same time
                if (play) {
                    drawCell(ctx,1,2,"Play-Pause")
                } else {
                    drawCell(ctx,0,2,"Play-Pause")
                }
                cursor=cursor+border
                /// bu3 forward play frame
                drawCell(ctx,3,2,"Forward")
                cursor=cursor+border
                /// bu4 repeat running at end  media
                drawCell(ctx,5,2,"Repeat")
                cursor=cursor+100

                if (mute) {
                   drawCell(ctx,8,2,"Mute-Volume")
                } else {
                  drawCell(ctx,7,2,"Mute-Volume")
                }
                cursor=cursor+border
                drawCell(ctx,6,2,"Setting-all")
                if (fromTop!=3) {
                    var initpainton = fromTop + capsulate
                    ctx.fillStyle = cFill
                    ctx.fillRect(0,initpainton,canvas.width,canvas.height);
                }
                ctx.save()
                cursor=0
                ctx.restore() /// end...
                //// debugJs()
                }

                //// show data from any icon
                function debugJs() {
                    /// var data = JSON.stringify(objChild);
                    console.log("There are", theArray.length, "items in the array")
                    console.log("The time is", theDate.toUTCString())
                    for (var i = 0; i < theArray.length; i++) {
                        var a = theArray[i].split('|');
                        console.log("M name: " + a[0] + " - left:" +  a[1] + " - top:" + a[2])
                    }
                }

                function picData() {
                    var ctx = canvas.getContext('2d');
                    var im = ctx.createImageData(pixelurl);
                    //// im.data[3] = 128;
                    return im
                }

                function drawCell(ct,col,row,name) {
                    var ic=cursor
                    ct.save()
                    ct.fillStyle = cFill
                    if (hoverdraw && activeitem==name) {
                     ct.strokeStyle = "red"
                    } else {
                     ct.strokeStyle = cBorder
                    }
                    var lastFrame =Utils.msec2string(canvasroot.frame)
                    theArray.push(name+"|"+ cursor +"|"+ fromTop +"|"+capsulate+"|"+lastFrame)
                    ct.putImageData(picData(),cursor,fromTop,colNr(col),rowNr(row),515,315)
                    ct.lineWidth = 1
                    //// ct.strokeStyle = cBorder
                    ct.strokeRect(cursor,fromTop,capsulate,capsulate)
                    //// report next cursor position
                    canvas.cursor=cursor+capsulate
                    //// hide all other icon from png
                    ct.fillRect(cursor,fromTop,canvas.width,canvas.height);
                    ct.lineWidth =2
                    var posx = ic + capsulate*0.5
                    var posy = fromTop + capsulate*0.5
                    /// x,y

                    ct.beginPath()
                    ct.arc(posx,posy,capsulate*0.476,0,2*Math.PI, true)
                    ct.stroke();
                    ct.restore()
                }


                function rowNr(x) {
                        if (x == 0) {
                            return 15
                        } else if (x==1) {
                            return capsulate*1 + 18
                        } else if (x==2) {
                            return capsulate*2 + 23
                        }
                        return 0
                }


                function colNr(x) {
                    if (x == 0) {
                        return 7
                    } else if (x > 0) {
                        return 7 + (28.3*x) - x + 1
                    }
                    return 0
                }
                /// pic info 515x318
                Component.onCompleted: { loadImage(pixelurl) }
            }

            Timer {
            id: fullsignal_timer
            property bool work:false
            interval:300
                onTriggered: {
                    work=false
                }
            }

            Timer {
            id: ihover_timer
            interval:2100
                onTriggered: {
                   /// tooltip also here
                   canvas.activeitem="none"
                }
            }

            MouseArea {
                width: canvasroot.width
                height: canvasroot.height
                hoverEnabled:true
                cursorShape:Qt.PointingHandCursor
                propagateComposedEvents: true
                /// x:0
               //// y:0
                id:wallico
                objectName: "wallico"
                onClicked: { fireMouse(mouseX,mouseY,true) }
                onPositionChanged: { fireMouse(mouseX,mouseY,false) }
                onMouseXChanged: { fireMouse(mouseX,mouseY,false) }
                onEntered:{ fireMouse(mouseX,mouseY,false) }
                function fireMouse(x,y,powerclick) {
                    //// console.log("hover 1/2:"+ hover)
                      if (fullsignal_timer.work) {
                          return
                      }


                    for (var i = 0; i < canvas.theArray.length; i++) {
                        var a = canvas.theArray[i].split('|');
                        var from=Number(a[1])
                        var name=a[0]
                        var to=from + Number(canvas.capsulate)
                        if (x > from && x < to && y < canvas.capsulate) {
                            canvas.activeitem=name
                            if (powerclick) {
                               /// to fast click handling
                               fullsignal_timer.stop()
                               fullsignal_timer.start()
                               fullsignal_timer.work=true
                                console.log("signal name:"+name+"-" +x+ " f:"+from+"t:"+to + "F:"+a[4] )
                                if (i==1) {
                                   canvas.play=(canvas.play)? false:true
                                }
                                if (i==4) {
                                  canvas.mute=(canvas.mute)?false:true
                                }
                            } else {
                                console.log("hover draw name:"+name+"-" +i)
                            }
                            ihover_timer.stop()
                            ihover_timer.start()
                        }
                    }
                }

            }
    }
}


