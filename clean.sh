#!/bin/bash
. ubiquitous_bash.sh

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