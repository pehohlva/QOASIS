#!/bin/bash
dir=$(pwd)
echo "$dir"
echo RUNNING MAKE PACKAGE FOR MAC OSX....
macdeployqt OasiSpeaker.app -dmg
