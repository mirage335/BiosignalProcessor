#!/bin/bash
. ubiquitous_bash.sh

scriptAbsoluteFolder="$(getScriptAbsoluteFolder)"	#Start in script's own location.

#Produces out-of-source build in Release folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Release
cd ./Release
cmake -DCMAKE_BUILD_TYPE=Release ../

#Produces out-of-source build in Debug folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Debug
cd ./Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../

#Produces out-of-source build in Pedantic folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Pedantic
cd ./Pedantic
cmake -DCMAKE_BUILD_TYPE=Pedantic ../