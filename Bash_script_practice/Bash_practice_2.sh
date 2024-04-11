#!/bin/bash


function progress_bar() {
    local inter=$1
    local tot=$2
    local lefter=$3 

    
    while [ $inter -lt $tot ]; do
        
        percent=$((inter * 100 / tot))
        ((inter += (tot / 10)))  # Increment inter by 10% of tot
   
        local progress=()
        for (( i = 0; i < percent / 10; i++ )); do
            progress+=("#")
        done
        for (( i = percent / 10; i < 10; i++ )); do
            progress+=("-")
        done
        echo -ne "\r[${progress[*]}] $percent%"
        progress=()
        sleep 1  
    done
     percent=$((inter * 100 / tot))
     for (( i = 0; i < percent / 10; i++ )); do
            progress+=("#")
        done
        for (( i = percent / 10; i < 10; i++ )); do
            progress+=("-")
        done
        echo -ne "\r[${progress[*]}] $percent%"
        progress=()
    echo "" 
}


progress_bar "$1" "$2" "$3"
