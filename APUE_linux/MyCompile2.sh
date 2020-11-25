#!/bin/bash
##  MyCompile2.sh
##  Created by Hong Geun Ji on 21/11/2020
##  VIM - Vi IMproved 8.0
##  Copyleft © 2020 Hong Geun Ji. You can revise this if you'd like.
##
##  Using static apue library for a link (simplified version)
##

# from arguments
c_to_be_compiled=$1
lib_to_be_used=$2

# check the out directory first
if [ ! -d out ] ; then      # to save every out file in one dir.
  mkdir out
fi

# compile and link
obj_file="${c_to_be_compiled%%.c}"
gcc -o "out/$obj_file" $c_to_be_compiled $lib_to_be_used -pthread;  # save out file to out dir

if [ $? -ne 0 ]     # gcc returns 0 on success
then
    echo "Something went wrong..."
    echo "usage: MyCompile2.sh [.c file name] [static library name]"
    echo
    exit 1
else
    echo "Compile & Link finished!"
    echo "The out file is in ./out"
fi

echo -n "Do you want me to execute? (y/n) "
while (true); do
    read execute
    case "$execute" in
        y | yes | Y | Yes | YES )   echo -n "How much time you need to execute? (default is 5sec) "
                                    read exec_time_input
                                    echo
                                    echo "=============================="
                                    ./out/$obj_file     # Execute the file
                                    if [[ $exec_time_input =~ ^[0-9]+$ ]] then   # digit check
                                     sleep $exec_time_input
                                    else    # if it was not a digit sleep for 5sec.
                                     sleep 5
                                    fi
                                    echo "=============================="
                                    echo
                                    echo "Execution complete"
                                    break ;;
        n | no | N | No | NO )  echo
                                echo "bye!"
                                break ;;
        *) echo "Please enter yes or no" ;;
    esac
done
