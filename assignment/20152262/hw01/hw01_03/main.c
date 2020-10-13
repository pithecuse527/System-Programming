//  
//  main.c
//  Assignment two for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 03/10/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  Print every file including subdirectory's one
//  

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int dir_list(char *dir, int *dir_cnt, int *file_cnt);   // recursive function which takes the path of directory and counters

int main(int argc, char *argv[])
{
    int dir_cnt = 1;        // should start from one as it always needs to count the directory itself???
                            // I am writing these codes based on the given HW01 PPT (it is based on find command)
                            // as the find command always gives us the given directory path first, I will count the first directory itself
                            // please let me know if this can be a problem
    int file_cnt = 0;
    
    if (argc != 2)          // check the argv first
    {
        printf("usage: Problem3_20152262 directory_name\n");
        return -1;
    }
    
    if(dir_list(argv[1], &dir_cnt, &file_cnt) < 0)              // first recrsive call
    {
        printf("Something went wrong... cannot open directory\n");
        return -1;
    }
    
    printf("# dirs : %d\n# files : %d\n", dir_cnt, file_cnt);   // print the result
    return 0;
}

int dir_list(char *dir, int *dir_cnt, int *file_cnt)
{
    DIR *dp;
    struct dirent *dirp;
    struct stat buf;            // buffer for the file
    int path_len;               // file path length
    
    if((dp = opendir(dir)) == NULL) return -1; // if fail to open
    
    while((dirp = readdir(dp)) != NULL)        // check every files located in the directory
    {   
        if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, "..")) continue; // except for . and ..
        
        // ===================== create the file path string ===================== //
        path_len = strlen(dir) + strlen(dirp->d_name) + 1;  // dir/dirp->name
        char *file_path = (char*) malloc(path_len);         // memory ready for file path
        strcpy(file_path, dir);
        strcat(file_path, "/");
        strcat(file_path, dirp->d_name);
        // ===================== create the file path string ===================== //
        
        if(stat(file_path, &buf) < 0)   // try the given file_path
        {
            printf("canot open %s\n", dirp->d_name);
            return -1;
        }
        
        if (S_ISDIR(buf.st_mode & 0xF000))   // if the file type is directory, do recursive call
        {
            *dir_cnt += 1;      // directory counter increment
            if(dir_list(file_path, dir_cnt, file_cnt) < 0)   // recursive call happens
            {
                printf("Something went wrong... cannot open directory\n");
                return -1;
            }
        }
        else *file_cnt += 1;    // file counter increment
        free(file_path);        // release the memory for file path
    }
    
    return 0;
    
}