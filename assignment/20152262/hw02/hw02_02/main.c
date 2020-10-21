//  
//  main.c
//  Assignment two for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 14/10/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  Divide the given file (might be "main.c" only for this assignmet) into N-byte
//  

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#define TO_BE_DIVIDED "main.c"

char* create_filename(int i);

int main(int argc, char *argv[])
{
    int byte_ = 500;        // default byte
    FILE *new_fp = NULL;    // file pointer for new file
    FILE *ori_fp = NULL;    // file pointer for TO_BE_DIVIDED file
    char *new_file_name;    // new file name (i.e. main.c_01)
    char *buffer;           // buffer ready for get string
    struct stat buff_ori;   // buffer ready for TO_BE_DIVIDED (the original file)
    off_t tmp_size;         // running size from TO_BE_DIVIDED
    int i = 0;              // running index for new file
    
    if (argc != 2)          // check the argv first
        printf("As you did not provide how much bytes to divide, it will be divided on 500-byte\n");
    else
        byte_ = atoi(argv[1]);
    
    // open TO_BE_DIVIDED file
    if((ori_fp = fopen(TO_BE_DIVIDED, "r")) == NULL)
    {
        fprintf(stderr, "error - fopen()\n");
        exit(1);
    }
    
    if (stat(TO_BE_DIVIDED, &buff_ori) < 0)
    {
        printf("cannot load %s\n", TO_BE_DIVIDED);
        exit(1);
    }
    
    tmp_size = buff_ori.st_size;         // TO_BE_DIVIDED file size of byte
    
    while(tmp_size > 0)
    {
        // on the last loop, the size for the last new file will be the leftover
        if (tmp_size < byte_) byte_ = tmp_size;    
        
        // create the new file name
        if((new_file_name = create_filename(i)) == NULL)
        {
            printf("cannot create the new file name from %s\n", TO_BE_DIVIDED);
            exit(1);
        }
        
        // create the file from given new_file_name
        if((new_fp = fopen(new_file_name, "w")) == NULL)
        {
            fprintf(stderr, "error - fopen()\n");
            exit(1);
        }
        
        // create the buffer
        if((buffer = malloc(byte_)) == NULL)
        {
            printf("malloc failed...\n");
            exit(1);
        }
        
        // save the contents to the buffer
        if(fread(buffer, byte_, 1, ori_fp) < 0)
        {
            fprintf(stderr, "error - fread()\n");
            exit(1);
        }
        
        // copy the contents from buffer to the new file
        if(fwrite(buffer, byte_, 1, new_fp) < 0)
        {
            fprintf(stderr, "error - fwrite()\n");
            exit(1);
        }
        
        // ready for the next new file
        free(new_file_name);
        new_file_name = NULL;
        fclose(new_fp);
        free(buffer);
        buffer = NULL;
        i++;
        tmp_size -= byte_;
        
    }
    fclose(ori_fp);
    exit(0);
}

char* create_filename(int i)
{
    int i_digit_len = 1; // counter for i's digit length
    int j;               // only running index for FOR loop
    char *i_str;         // converted string from i
    char *buff;          // string to be returned
    
    // count for i's digit length
    for(j=i;j>9;j/=10) i_digit_len++;
    
    // create the string of i
    if((i_str = malloc(i_digit_len)) == NULL)
    {                                   
        printf("malloc failed...\n");
        return NULL;
    }
    sprintf(i_str, "%d", i);
    
    // create the file name
    if((buff = malloc(sizeof(TO_BE_DIVIDED)+i_digit_len+1)) == NULL) // no need to think about the space for '_' as "main.c" has '\0' at the end
    {                                                                // which means. '_' will use the sapce for '\0'
        printf("malloc failed...\n");
        return NULL;
    }
    strcpy(buff, TO_BE_DIVIDED);        // add the original file name fiest (i.e. buff == "main.c")
    strcat(buff, "_");                  // add '_' to buff (i.e. buff == "main.c_")
    strcat(buff, i_str);                // add the converted string from integer i  (i.e. buff == "main.c_1")
    return buff;
}
