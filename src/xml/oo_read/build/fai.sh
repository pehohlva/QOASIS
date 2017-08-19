#!/bin/bash
dir=$(pwd)
echo "$dir"
rm -f build/*  Makefile test.pro.user && qmake && make