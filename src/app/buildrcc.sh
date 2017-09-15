#!/bin/bash
dir=$(pwd)
echo "$dir"
echo delete zz_end_oasiresource.cpp if exist...
echo GENERATE RESOURCE zz_end_oasiresource.cpp compresed.
rm zz_end_oasiresource.cpp
rcc oasispeech.qrc -o zz_end_oasiresource.cpp

