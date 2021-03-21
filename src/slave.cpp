// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>

#include "SlaveNode.h"
using namespace std;


Node my_identity;


int establish_connection_with_master(string master_ip)
{
    int sock = 0, valread; 
    struct sockaddr_in serv_addr, my_addr; 

    my_addr.sin_addr.s_addr = INADDR_ANY;

    char* my_ip = inet_ntoa(my_addr.sin_addr);
    
    //char* a = "Hello from ";
    char *hello = my_ip; 
    //char buffer[1024] = {0}; 

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
    printf("\nRequest sent to Master to connect to Overlay Network\n"); 
    
    //Node my_identity;

    valread = read( sock , &my_identity, 104); 
    cout<<endl;
    my_identity.print_node_info();
    //printf("%s\n",buffer ); 

    return 1;
}


   
int main(int argc, char const *argv[]) 
{   
    int connection_status=0;

    PartitionedDHT local_dht; 
    while(1)
    {

        //Node my_identity;

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
        cout<<"\n3.  My Identity";
        cout<<"\n4.  INsert HASH into local DHT";
        cout<<"\n5.  Print All Hash";
        cout<<"\n6.  live state";
        cout<<"\n0.  Exit";

        cout<<"\n\n\n\n------------------------------------------"<<endl;
        cin>>choice;
        
        string master_ip;
        bool status;
        string temp;
        switch(choice)
        {
            case 0:
                    exit(0);
                    break;
            case 1:
                cout<<"\n\nEnter IP address of Master Node"<<endl;
                
                cin>>master_ip;

                connection_status = establish_connection_with_master(master_ip);
                //cout<<"\nDEBUG SLAVE"<<endl;
                my_identity.print_node_info();
                
                break;
            case 2:
            
                cout<<"\nWork in Progress";
                break;
            
            case 3:
                cout<<"\n My Identity";
                cout<<endl;
                my_identity.print_node_info();
                break;
            
            case 4:
                cout<<"\n TEST Insert hash ";
                    
                cin>>temp;
                status = local_dht.insert_sha_to_local_dht(temp);
                if(status)
                    cout<<"\n Hash is already in it!";
                else
                    cout<<"\n Hash inserted into local_dht";

                break;
            case 5:
                cout<<"\n Print all hash's stored in local dht";
                local_dht.print_all_local_dht();
                break;
            
            case 6:
                local_dht.live_state();
                cout<<"\n\n Wow";
                break;
            default:
                continue;
        }
    }
    return 0;
}