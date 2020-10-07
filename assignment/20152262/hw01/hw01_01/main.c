//  
//  main.c
//  Assignment one for System Programming, UOU - 201948932
//  Created by Hong Geun Ji on 03/10/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  Change where to print
//  

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

main()
{
    int fd;                         // file descriptor
    char *buff;                     // buffer for user input
    
    fd = creat("printf.txt", 0644); // create printf.txt for print
    dup2(fd, STDOUT_FILENO);        // copy fd value to STDOUT_FILENO
    close(fd);                      // close fd
    
    scanf("%s", buff);              // use %s to input until just before the space character
    printf("%s", buff);             // write the contents

}
