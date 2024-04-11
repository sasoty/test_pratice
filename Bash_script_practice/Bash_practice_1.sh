#!/bin/bash

filename=$1


#---
a=0
b=0


a=$(grep -c "OK" $filename)
b=$(grep -c "FAILED" $filename)


echo -e "\e[32m [  OK  ] line :$a\e[0m"
echo -e "\e[31m [FAILED]line :$b\e[0m"