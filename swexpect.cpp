#include "switchexpect.h"
using namespace std;

int expect_cisco_username(int fd,int result,char user[]){
    result = exp_expectl(fd,
                             exp_glob, "Username:", 1, 
                             exp_exact, "Connection closed by foreign host.", 7, 
                             exp_end); 
        switch(result)  
        {  
            case 1:  
                //write(fd, user, sizeof(user) - 1); 
                write(fd, user, strlen(user)); 
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
    
    
int expect_cisco_password(int fd,int result, char passwd[]){
    result = exp_expectl(fd,
                         exp_glob, "Password:*", 1, 
                         exp_exact, "Connection closed by foreign host.", 7, 
                         exp_end); 
    switch(result)  
    {  
        case 1:
            write(fd, passwd, strlen(passwd));
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

int expect_cisco_enable_password(int fd, int result,char enable_passwd[]){
    int loop = 1;

    while(loop){ 
        result = exp_expectl(fd,
                             exp_glob, "*>", 1, 
                             exp_glob, "Password:*", 2, 
                             exp_exact, "Connection closed by foreign host.", 7, 
                             exp_end); 
        switch(result){  
                case 1: 
                    write(fd, "enable\n", sizeof("enable\n") - 1);
                    break;  
                case 2:  
                    write(fd, enable_passwd, strlen(enable_passwd));
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
                    cout<<"logged failure "<<result<<endl;  
                    loop = 0;  
                    break;  
        }  
        
    }   
}

int expect_save_config_cmd(int fd, int result){
                char sav_cmd[] ="write\n";
    result = exp_expectl(fd,
                         exp_glob, "#", 1,                             
                         exp_exact, "Connection closed by foreign host.", 7,
                         exp_end);
    switch(result){
            case 1:
		cout <<"strlen:"<<strlen("write\n");
                write(fd, sav_cmd, strlen(sav_cmd));
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


int expect_test_cmd(int fd, int result){
    
        result = exp_expectl(fd,
                             exp_glob, "#", 1,                             
                             exp_exact, "Connection closed by foreign host.", 7,
                             exp_end);
        switch(result){
                case 1:
                    cout<<"what fuck";
                    break;                
                case 7:
                    cout <<"Incorrect username or password;"<<endl;
                    break;

                case EXP_EOF:
                    cout << "EOF\n";
                case EXP_TIMEOUT:
                    cout<<"Time out\n";
                default:
                    cout<<"logged failure "<<result<<endl;
                    break;
        }

    
}

