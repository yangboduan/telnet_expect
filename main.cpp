/*
filename      : main.cpp
description :自动保存交换配置
*/

#include <tcl.h>  
#include <expect.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <iostream>  
#include <expect_tcl.h>  
  
using namespace std;  
  
int main(){  
    int loop = 1;  
    int result;  
    const int exp_timeout =100; 
    const char *switch_ip= "192.168.2.80"; 
    char user[] = "admin\n"; //用户名 
    char passwd[] = "cisco\n";  //密码
    char enable_passwd[] = "cisco\n"; //enable密码 
    Tcl_Interp *tcl;  
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
   
//LOGIN-MODE:Telnet  (username-password-superpassword or password-superpassword)
//Switch Model:WS-C3550-48-SMI 
//image file  :c3550-ipservicesk9-mz.122-50.SE3.bin

/*------------------------------------
User Access Verification

Username: admin
Password:
Switch>enable
Password:
Switch#wr
Building configuration...
[OK]
Switch#

*/


      
    while(loop){  
        result = exp_expectl(fd,
                             exp_glob, "Username:", 1, 
                             exp_glob, "Password:",2,
                             exp_exact, "Connection closed by foreign host.", 7, 
                             exp_end);  
        switch(result)  
        {  
            case 1:  
                write(fd, user, sizeof(user) - 1);  
                break;  
            case 2:
                write(fd, passwd, sizeof(passwd) - 1); 
                loop = 0; 
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
                cout<<"logged in "<<result<<endl;  
                loop = 0;  
                break;  
        }  
    }

    loop = 1; 
    while (loop){
	
    result = exp_expectl(fd,
                             exp_glob, "*>",1,
			     exp_glob, "Password:",2,
                             exp_glob, "*[OK]*", 3,
			     exp_glob, "*#",4,
                             exp_exact, "Connection closed by foreign host.", 7,
                             exp_end);   
	switch(result)
	    {
		case 1:
		    write(fd, "enable\n", sizeof("enable\n") - 1);
		    break;
		case 2:
		    write(fd, enable_passwd, sizeof(enable_passwd) - 1); 
		    break;  
		case 3:
		    cout <<"save ok!";
		    break;  
		case 4:
		    write(fd, "write\n", sizeof("write\n") - 1); 
		    write(fd, "exit\n", sizeof("exit\n") - 1); 
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
                    cout<<"logged in "<<result<<endl;
                    loop = 0;
                    break;
	    }
    }

    
    Tcl_DeleteInterp(tcl);  
}  
