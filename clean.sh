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

if [[ "$scriptAbsoluteFolder" != "$PWD" ]]
then
	echo -e '\E[1;33;41m ABORTING! Current directory does not match script directory! \E[0m'
	exit
fi

if [[ ! -d Release || ! -d Debug || ! -d Pedantic ]]
then
	echo -e '\E[1;33;41m ABORTING! Missing build directories! \E[0m'
	exit
fi

#If script reaches here, we should be safe to proceed.
rm -rf ./Release ./Debug ./Pedantic