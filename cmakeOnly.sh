#!/bin/bash
. ubiquitous_bash.sh

scriptAbsoluteFolder="$(getScriptAbsoluteFolder)"	#Start in script's own location.

#Improves cmake readability.
#Depends on colout (http://nojhan.github.io/colout/) .
readableCMake() {
	if [[ -e $(which colout) && -e $(which unbuffer) ]]
	then 
		cmake "$@" | colout -t cmake
	else
		cmake "$@"
	fi
}

#Produces out-of-source build in Release folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Release
cd ./Release
readableCMake -DCMAKE_BUILD_TYPE=Release ../

#Produces out-of-source build in Debug folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Debug
cd ./Debug
readableCMake -DCMAKE_BUILD_TYPE=Debug ../

#Produces out-of-source build in Pedantic folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Pedantic
cd ./Pedantic
readableCMake -DCMAKE_BUILD_TYPE=Pedantic ../