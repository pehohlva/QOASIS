#!/bin/bash
dir=$(pwd)
echo "$dir"
rm *.qmlc *.jsc
qmlscene ControlFrame.qml
