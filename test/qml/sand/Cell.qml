import QtQuick 2.0
import QtQuick.Controls 2.2
import "controls" as Awesome


Rectangle {
    id: button
    property bool checked: false
    Awesome.Button {
      anchors.horizontalCenter: parent.horizontalCenter
      icon: awesome.icons.fa_money
      text: "fa_money"
      }
}
