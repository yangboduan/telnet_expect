/*
filename      : main.cpp
description :????????
*/

#include <tcl.h>  
#include <expect.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <iostream>  
#include <expect_tcl.h>  
  
using namespace std;  
char user[] = "admin\n"; //username
char passwd[] = "cisco\n";  //password
char enable_passwd[] = "cisco\n"; //enable password 
char enable_str[] = "enable\n"; //enable password 
Tcl_Interp *tcl;  
int loop = 1;

int main(){  
    int loop = 1;  
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

    int expect_username(int fd,int result);
    int expect_password(int fd,int result);
    int expect_enable_password(int fd,int result);
    expect_username( fd,result);
    expect_password( fd,result);
    expect_enable_password( fd,result);


      Tcl_DeleteInterp(tcl);  
}  

    int expect_username(int fd,int result){
	result = exp_expectl(fd,
                             exp_glob, "Username:", 1, 
                             exp_exact, "Connection closed by foreign host.", 7, 
                             exp_end); 
        switch(result)  
        {  
            case 1:  
                write(fd, user, sizeof(user) - 1);  
                break;  
            case 7:  
                cout <<"Incorrect username or password;"<<endl; 
                break;  
  
            case EXP_EOF:  
                cout << "EOF\n";  
                break; 
 
            case EXP_TIMEOUT:  
                cout<<"Time out\n";  
                break;  
            default:  
                cout<<"logged failure "<<result<<endl;  
                break;  
        }  
	
	
    }
    
    
    int expect_password(int fd,int result){
	result = exp_expectl(fd,
                             exp_glob, "Password: ", 1, 
                             exp_exact, "Connection closed by foreign host.", 7, 
                             exp_end); 
        switch(result)  
        {  
            case 1: 
                write(fd, passwd, sizeof(passwd) - 1);
                break;  
            case 7:  
                cout <<"Incorrect username or password;"<<endl; 
                loop = 0 ; 
                break;  
  
            case EXP_EOF:  
                cout << "EOF\n";  
                loop = 0;  
                break; 
 
            case EXP_TIMEOUT:  
                cout<<"Time out\n";  
                loop = 0;  
                break;  
            default:  
                cout<<"logged failure "<<result<<endl;  
                loop = 0;  
                break;  
        }  
	
	
    }
    
    int expect_enable_password(int fd, int result){
	
        while(loop){ 
            result = exp_expectl(fd,
                                 exp_glob, "*>", 1, 
                                 exp_glob, "Password:", 2, 
                                 exp_exact, "Connection closed by foreign host.", 7, 
                                 exp_end); 
            switch(result)  
                {  
                    case 1: 
                	cout <<"pippei"; 
                        write(fd, enable_str, sizeof(enable_str) - 1);
                	cout <<"111111111111111111111111111111";
                        break;  
                    case 2:  
                        write(fd, passwd, sizeof(passwd) - 1);
                        break;  
                    case 7:  
                        cout <<"Incorrect username or password;"<<endl; 
                        loop = 0 ; 
                        break;  
  
                    case EXP_EOF:  
                        cout << "EOF\n";  
                        loop = 0;  
                        break; 
 
                    case EXP_TIMEOUT:  
                        cout<<"Time out\n";  
                        loop = 0;  
                        break;  
                    default:  
                        cout<<"logged failure "<<result<<endl;  
                        loop = 0;  
                        break;  
                }  
            
        }	
    }

