#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>

#include "SlaveNode.h"
using namespace std;

void print(string msg)
{
    cout<<"> "<<msg<<endl;
}

int main(int argc, char **argv)
{
    string master_ip;
    int connection_status;
    print("IP address of Master Node:");   //look forward for environemnt variables
    cin>>master_ip;

    SNode me;
    Node previous_node, next_node, my_clone;
    
    
    connection_status = me.establish_connection_with_master(master_ip);
    cout<<endl<<"Connection status= "<<connection_status<<endl;
    

}
