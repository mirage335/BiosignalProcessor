#!/bin/bash

cat "$1" | baudline -stdin -format le32f -samplerate 150
