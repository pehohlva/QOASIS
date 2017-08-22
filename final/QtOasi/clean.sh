#!/bin/bash
dir=$(pwd)
echo "$dir"
echo RUNNING Clean .... hight voltage...rm!!
rm -rf bin mkspecs lib Makefile .qmake.stash .qmake.cache  && qmake && make
