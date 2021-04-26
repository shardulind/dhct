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
    local_dht.turn_on_live_state();
    local_dht.live_state();
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
    cin.get();
    cout<<"\nPressed enter";
    local_dht.turn_off_live_state();

    worker.join();
    cout<<"\n>";
    local_dht.print_all_local_dht();

    return 0;
}
