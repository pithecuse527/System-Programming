#!/bin/zsh
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
    echo "Something went wrong...\n"
    echo "usage: MyCompile2.sh [.c file name] [static library name]\n"
    exit 1
else
    echo "Compile & Link finished!"
    echo "The out file is in ./out\n"
fi

echo -n "Do you want me to execute? (y/n) "
while (true); do
    read execute
    case "$execute" in
        y | yes | Y | Yes | YES )   echo
                                    echo "=============================="
                                    ./out/$obj_file     # Execute the file
												sleep 5				  # give some time for execution
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
