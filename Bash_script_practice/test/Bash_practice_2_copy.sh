#!/bin/bash


function progress_bar {
    local inter=0
    local tot=0
    local lefter=0
    local fill="#"

    # Parse command-line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -i) 
                inter=$2 
                shift 2
                ;;
            -t) 
                tot=$2 
                shift 2
                ;;
            -d) 
                dec=$2    
                shift 2
                ;;
            -l) 
                lefter=$2   
                shift 2
                ;;
            -f) 
                fill=$2    
                shift 2
                ;;
            -*)
                echo "invalid option: $1" >&2
                exit 1
                ;;
            *)
                echo "invalid argument: $1" >&2
                exit 1
                ;;
        esac
    done
    echo $inter
    while [ $inter -lt $tot ]; do
        ((inter += (tot / 10)))  # Increment inter by 10% of tot
        percent=$((inter * 100 / tot))
        local progress=()
        for (( i = 0; i < percent / 10; i++ )); do
            progress+=("$fill")
        done
        for (( i = percent / 10; i < 10; i++ )); do
            progress+=("-")
        done
        echo -ne "\r[${progress[*]}] $percent%"
        sleep 1
    done

    echo "" 
}


