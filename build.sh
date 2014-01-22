#!/bin/bash
. ubiquitous_bash.sh

scriptAbsoluteFolder="$(getScriptAbsoluteFolder)"	#Start in script's own location.

#Improves make readability.
#Depends on colout (http://nojhan.github.io/colout/) and unbuffer (http://expect.sourceforge.net/) .
readableMake() {

	if [[ -e $(which colout) && -e $(which unbuffer) ]]
	then
		unbuffer make -j6 2>&1 | colout -t cmake | grep --color=always -E '^|undefined reference'
	else
		make -j6
	fi
}

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

echo -e '\E[1;32;46m Compiling: Release. \E[0m'
#Produces out-of-source build in Release folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Release
cd ./Release
readableCMake -DCMAKE_BUILD_TYPE=Release ../
readableMake

echo -e '\E[1;32;46m Compiling: Debug \E[0m'
#Produces out-of-source build in Debug folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Debug
cd ./Debug
readableCMake -DCMAKE_BUILD_TYPE=Debug ../
readableMake

echo -e '\E[1;32;46m Compiling: Pedantic \E[0m'
#Produces out-of-source build in Pedantic folder.
cd "$scriptAbsoluteFolder"
mkdir -p ./Pedantic
cd ./Pedantic
readableCMake -DCMAKE_BUILD_TYPE=Pedantic ../
readableMake

echo -e '\E[1;32;46m Compilation finished. \E[0m'