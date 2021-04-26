#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>

#include "SlaveNode.h"
using namespace std;


Node my_identity;
string master_ip; // load it from env var


int establish_connection_with_master(string master_ip)
{
    int sock = 0, valread; 
    struct sockaddr_in serv_addr, my_addr; 
    my_addr.sin_addr.s_addr = INADDR_ANY;

    char* my_ip = inet_ntoa(my_addr.sin_addr);
    
    
    char *hello = my_ip; 
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(HEALTH_PORT); 
       
    char* const mip = &master_ip[0];
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, mip, &serv_addr.sin_addr)<=0)  
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
    printf("\nRequest sent to Master \n"); 
    
    
    Node temp;
    valread = read( sock , &temp, 104); 
    cout<<endl;
    temp.print_node_info();
    //my_identity.print_node_info();
    return 1;
}



void print(string msg)
{
    cout<<"> "<<msg<<endl;
}

int main(int argc, char **argv)
{
    int connection_status;
    print("IP address of Master Node:");
    cin>>master_ip;
    connection_status = establish_connection_with_master(master_ip);
    //my_identity.print_node_info();

}
