// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#define PORT 6969 

using namespace std;

int establish_connection_with_master(char* master_ip)
{
    int sock = 0, valread; 
    struct sockaddr_in serv_addr, my_addr; 

    my_addr.sin_addr.s_addr = INADDR_ANY;

    char* my_ip = inet_ntoa(my_addr.sin_addr);
    
    char* a = "Hello from ";
    char *hello = a + *my_ip; 
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, master_ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("\nRequest sent to Master to connect to Overlay Network\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 

    return 1;
}


   
int main(int argc, char const *argv[]) 
{   
    int connection_status=0;

    while(1)
    {
        unsigned short int choice;
        cout<<"\n------------------------------------------";
        cout<<"\n\t\t@SLAVE NODE";
        cout<<"\n\t\tDEVELOPING MODE MENU (Testing each funct)";
        cout<<"\n------------------------------------------";
        if(!connection_status)
            cout<<"\n1.  Establish Connection with Master Node";
        else
            cout<<"\n1.  PING to Master NODE";
        
        cout<<"\n2.  Who's my neighbour?";
        cout<<"\n0.  Exit";
        cout<<"\n\n\n\n------------------------------------------";
        cin>>choice;
        
        switch(choice)
        {
            case 0:
                    exit(0);
                    break;
            case 1:
                cout<<"\n\nEnter IP address of Master Node";
                char* master_ip;
                cin>>master_ip;

                connection_status = establish_connection_with_master(master_ip);
                break;


            case 2:
            
                cout<<"\nWork in Progress";
                break;
                 
            default:
                continue;
        }
    }
    return 0;
}