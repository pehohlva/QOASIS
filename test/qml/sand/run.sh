#!/bin/bash
dir=$(pwd)
echo "$dir"
rm *.qmlc *.jsc
qmlscene Main.qml
