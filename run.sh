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

cd "$(getScriptAbsoluteFolder)"	#Start in script's own location.

#cat /dev/urandom | ./Release/src/BiosignalProcessor | baudline -stdin -format le32f -samplerate 150
stty -F /dev/ttyACM0 raw ; echo -n "" > /dev/ttyACM0 ; cat /dev/ttyACM0 | ./Release/src/BiosignalProcessor | tee ./dataLog | baudline -stdin -format le32f -samplerate 150
