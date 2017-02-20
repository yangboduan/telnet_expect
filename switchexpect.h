#include <tcl.h>
#include <expect.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <expect_tcl.h>
int expect_cisco_username(int fd,int result,char user[]);
int expect_cisco_password(int fd,int result, char passwd[]);
int expect_cisco_enable_password(int fd, int result,char enable_str[]);
