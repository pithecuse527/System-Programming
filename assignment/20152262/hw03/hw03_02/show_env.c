//  
//  show_env.c
//  Assignment three for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 25/11/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  print who am I with USER env. value
//  

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("USER=%s\n", getenv("USER"));
    exit(0);
}