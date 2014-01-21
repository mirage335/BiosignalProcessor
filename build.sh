#!/bin/bash
. ubiquitous_bash.sh

scriptAbsoluteFolder="$(getScriptAbsoluteFolder)"	#Start in script's own location.

#Improves readability.
#Depends on colormake (https://github.com/pagekite/Colormake) and unbuffer (http://expect.sourceforge.net/) .
readableMake() {

	if [[ -e $(which colormake) && -e $(which unbuffer) ]]
	then
		unbuffer colormake -j6 2>&1 | grep --color=always -E '^|undefined reference'
	else
		make -j6
	fi
}

#Produces out-of-source build in Release folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Release
cd ./Release
cmake -DCMAKE_BUILD_TYPE=Release ../
readableMake

#Produces out-of-source build in Debug folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Debug
cd ./Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../
readableMake

#Produces out-of-source build in Pedantic folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Pedantic
cd ./Pedantic
cmake -DCMAKE_BUILD_TYPE=Pedantic ../
readableMake