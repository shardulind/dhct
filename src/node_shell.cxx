#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <thread>

#include "SlaveNode.h"
using namespace std;

void print(string msg)
{
    cout<<"> "<<msg<<endl;
}

SNode me;
PartitionedDHT local_dht;
static bool is_live = true;


void con_live_state()
{
   
    while(is_live)
        local_dht.live_state();

    return;
}


int main(int argc, char **argv)
{
    string master_ip;
    int connection_status;
    print("IP address of Master Node:");   //look forward for environemnt variables
    cin>>master_ip;

    
    Node previous_node, next_node, my_clone;
    
    
    connection_status = me.establish_connection_with_master(master_ip);
    cout<<endl<<"Connection status= "<<connection_status<<endl;

    thread worker(con_live_state);

    cin.get();
    is_live = false;

    worker.join();

    cin.get();
    return 0;
}
