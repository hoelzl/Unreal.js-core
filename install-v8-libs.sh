#!/bin/sh

VersionHeader=ThirdParty/v8/include/v8-version.h
Major=$(cat $VersionHeader | grep MAJOR | awk -e '{ print $3 }')
Minor=$(cat $VersionHeader | grep MINOR | awk -e '{ print $3 }')
Build=$(cat $VersionHeader | grep BUILD_NUMBER | awk -e '{ print $3 }')
Version=$Major.$Minor.$Build
Tag=V8-$Version
ZipFile=v8-$Version-libs.zip

if [ -d "ThirdParty/v8/lib" ]; then
    echo "Unreal.js is ready to build"
else
    if [ -f "ThirdParty/v8/$ZipFile" ]; then
        echo "Okay you have zip"
    else
        echo "Download prebuilt V8 libraries for Unreal.js"
        (cd ThirdParty/v8; curl -O -L https://github.com/ncsoft/Unreal.js-core/releases/download/$Tag/$ZipFile)
    fi

    (cd ThirdParty/v8; unzip $ZipFile; mv v8-$Version-libs/ lib/)
fi

