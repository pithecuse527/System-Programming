//  
//  main.c
//  Assignment two for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 03/10/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
// 
//  

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void print_to_file(char *buff, char *file_name);

int main(int argc, char *argv[])
{
    int fd;                 // file descriptor for the file
    off_t curpos;           // file offset
    char sub;               // a character what to substitute
    char *file_name;        // string pointer for file name
    
    if (argc != 2)          // check the argv first
    {
        printf("usage: main textfile\n");
        return -1;
    }
    
    file_name = argv[1];                    // point the file name
    fd = open(argv[1], O_RDWR);             // save file descriptor for the file
    int f_size = lseek(fd, 0, SEEK_END);    // save the file size (on bytes)   
    char buff[f_size];                      // string buffer ready
    lseek(fd, 0, SEEK_SET);                 // put offset back
    read(fd, buff, f_size);                 // save the string to buff using offset
    printf("%d\n", f_size);                 // print the size
    
    if (f_size % 2 != 0)    // if the size is odd
    {
        curpos = lseek(fd, 1, SEEK_SET);    // offset starts from 1 and is increased for 2 everytime
        sub = 'o';
    }
    else                    // if the size is even
    {
        curpos = lseek(fd, 0, SEEK_SET);    // offset starts from beginning and is increased for 2 everytime
        sub = 'e';
    }
    
    while(curpos < f_size)  // while the offset is inside of the string
    {
        if(buff[curpos] != '\n') buff[curpos] = sub;    // substitution without '\n'
        curpos = lseek(fd, 2, SEEK_CUR);
    }
    
    print_to_file(buff, file_name);     // print to the given file
    close(fd);                          // close the fd
    return 0;
}

void print_to_file(char *buff, char *file_name)
{
    close(open(file_name, O_TRUNC | O_WRONLY)); // truncate first
    int fd = creat(file_name, 0644);            // then replace the file to print
    dup2(fd, STDOUT_FILENO);                    // copy fd value to STDOUT_FILENO
    close(fd);                                  // close fd
    printf("%s", buff);                         // write the contents
}