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