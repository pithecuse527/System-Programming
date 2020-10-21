//  
//  main.c
//  Assignment two for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 14/10/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  Change the owner and mode by the given mode
//  

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct stat statbuf;    // buffer ready for agrv[0] (this file)
    
    if (argc != 2)          // check the argv first
    {
        printf("usage: main mode\n");
        return -1;
    }
    
    if(stat(argv[0], &statbuf) < 0)     // save the original info. to buffer
    {
        printf("stat error for %s\n", argv[0]);
        return -1;
    }
    
    // if the mode is 0, change the mode for the current account and turn off the Setuid
    if(!strcmp(argv[1], "0"))
    {
        if(chown(argv[0], getuid(), getgid()) < 0)  // set the owner first for the upcoming effective user
        {
            printf("chown error for %s\n", argv[0]);
            return -1;
        }
        // turn off the Setuid, then add user execution
        if(chmod(argv[0], (statbuf.st_mode & ~S_ISUID) | S_IXUSR) < 0)  
        {
            printf("chmod error for %s\n", argv[0]);
            return -1;
        }
    }
    // if the mode is 1, change the mode for the root and turn on the Setuid
    else if(!strcmp(argv[1], "1"))
    {
        if(chown(argv[0], 0, 0) < 0)     // set the owner first for the upcoming effective user(root)
        {
            printf("chown error for %s\n", argv[0]);
            return -1;
        }
        if(chmod(argv[0], (statbuf.st_mode & ~S_IXUSR) | S_ISUID) < 0)
        {
            printf("chmod error for %s\n", argv[0]);
            return -1;
        }
    }
    else
    {
        printf("Unknown mode...\n");
        return -1;
    }
    
    return 0;
}
