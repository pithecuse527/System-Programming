#!/bin/bash
##  MyCompiler.sh
##  Created by Hong Geun Ji on 30/09/2020
##  Updated by Hong Geun Ji on 12/10/2020 - v0.3
##  VIM - Vi IMproved 8.0
##  Copyleft © 2020 Hong Geun Ji. You can revise this if you'd like.
##
##  Using static apue library for a link.
##  

cmd()
{
    # let user know where the script running
    working_dir_absolute=$(pwd)
    echo -n "I am running from here ->  "
    echo $working_dir_absolute
    
    # input what to compile and link then look up the file
    while (true); do
        echo -n "Type what to compile -> "
        read c_to_be_compiled   # the .c file
        loc_of_c_to_be_compiled=$(realpath $c_to_be_compiled)       # save absolute path
        if [ -f ${loc_of_c_to_be_compiled} ]; then                  # check whether the file exists or not
            break;
        fi
        echo "Cannot find the given .c file on $loc_of_c_to_be_compiled"
        echo "Please check the file location"
    done
    
    # input the library
    while (true); do
        echo "Type the relative file path for custom library."
        echo -n "-> "
        read lib_to_be_used     # the static library relative path without the file name
        
        if [[ $lib_to_be_used != *"libapuelib.a" ]]; then   # if user did not explicitly type the file name, 
            lib_to_be_used+="/libapuelib.a"                 # append the name to it
        fi
        
        if [ -f ${lib_to_be_used} ]; then                   # check whether the file exists or not
            break;
        fi
        echo "Cannot find the given library on $(realpath $lib_to_be_used)"
        echo "Please check the library location"
    done
 
    if [ ! -d ${loc_of_c_to_be_compiled%/*}/out ] ; then      # to save every out file in one dir.
    mkdir ${loc_of_c_to_be_compiled%/*}/out
    fi
    
    # compile and link
    base_to_be_compiled=$(basename $c_to_be_compiled)
    gcc -o "${loc_of_c_to_be_compiled%/*}/out/${base_to_be_compiled%%.c}" $c_to_be_compiled $lib_to_be_used -pthread;  # the location where to save will be absolute
    
    if [ $? -ne 0 ]     # gcc returns 0 on success
    then
        echo "Something went wrong..." 
        exit 1
    else
        echo "Compile & Link finished!"
        echo " "
    fi
    
    echo
    echo "The out file is in ${loc_of_c_to_be_compiled%/*}/out/"
    echo
    
    echo -n "Do you want me to execute? (y/n) "
    while (true); do
        read execute
        case "$execute" in
            y | yes | Y | Yes | YES )   echo
                                        echo "=============================="
                                        ${loc_of_c_to_be_compiled%/*}/out/${base_to_be_compiled%%.c}     # Execute the file
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
    
    return
}

cmd
