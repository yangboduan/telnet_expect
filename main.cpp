/*
filename      : main.cpp
description :????????
*/
#include "switchexpect.h"
using namespace std;  
char user[] = "admin\n"; //username
char passwd[] = "cisco\n";  //password
char enable_passwd[] = "cisco\n"; //enable password 
char enable_str[] = "enable\n"; //enable password 
Tcl_Interp *tcl;  

int main(){  
    int result;  
    const int exp_timeout =100; 
    const char *switch_ip= "192.168.2.80"; 
  
    tcl = Tcl_CreateInterp();
 
    if (Expect_Init(tcl) != TCL_OK){  
        puts("failure");  
        return 1;  
    }  
      
    int fd = exp_spawnl("telnet", "telnet" ,switch_ip, (char *)0); 
 
    if(fd < 0)  {  
        cout<<"Fail to telnet"<<endl;  
        return -1;  
    }

    expect_cisco_username( fd,result,user);
    expect_cisco_password( fd,result,passwd);
    expect_cisco_enable_password( fd,result,enable_passwd);


      Tcl_DeleteInterp(tcl);  
}  

