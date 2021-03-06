#!/bin/bash

#Retrieves absolute path of current script, while maintaining symlinks, even when "./" would translate with "readlink -f" 
#Suitable for allowing scripts to find other scripts they depend on.
getScriptAbsoluteLocation() {                                       
        local absoluteLocation                                                                                           
        if [[ (-e $PWD\/$0) && ($0 != "") ]]                                                                             
                        then                                                                                             
        absoluteLocation="$PWD"\/"$0"                                                                                    
        absoluteLocation=$(realpath -s "$absoluteLocation")         
                        else                               
        absoluteLocation="$0"                              
        fi                                  
                                                           
        if [[ -h "$absoluteLocation" ]]                                                                                  
                        then                                        
        absoluteLocation=$(readlink -f "$absoluteLocation")                                                              
        fi                                                                                                               
                                                                    
        echo $absoluteLocation                                                                                           
}

#Retrieves absolute path of current script, while maintaining symlinks, even when "./" would translate with "readlink -f" 
#Suitable for allowing scripts to find other scripts they depend on.                                                      
getScriptAbsoluteFolder() {                                                                                               
        dirname "$(getScriptAbsoluteLocation)"                                                                            
}

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