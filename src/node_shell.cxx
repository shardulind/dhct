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
    string temp;
    bool interpreter=true;
    print("IP address of Master Node:");   //look forward for environemnt variables
    cin>>master_ip;

    
    
    Node previous_node, next_node, my_clone;
    
    
    connection_status = me.establish_connection_with_master(master_ip);
    if(connection_status == 1)  me.print_node_info();
    else{ print("Error in connecting"); exit(1);}

    while(true){

    thread worker(con_live_state);

    

    cin.get();
    cin.get();
    cout<<"\nPressed enter";
    local_dht.turn_off_live_state();

    worker.join();
    cout<<"\n>";
    print("");
    
    while(interpreter){
        print(">");
        cin>>temp;    
        if(temp == "-exit")
            exit(0);
        else if(temp == "-print_all_data")
            local_dht.print_all_local_dht();
        else if(temp == "-node_stats"){
            me.print_node_info();
            local_dht.print_node_stats();
        }
        else  if(temp == "-go_live")
            break;
        else if(temp =="\n" )  
        {
            cout<<"\n\t\t................help...............";
            cout<<"\n\t\t-print_all_data   : To print all hash's (dev)";
            cout<<"\n\t\t-node_stats       : Print Node Stats";
            cout<<"\n\t\t-go_live          : Go Live";
            cout<<"\n\t\t...................................";
        }
        else
        {
            cout<<"\n................help...............";
            cout<<"\n\t\t-print_all_data   : To print all hash's (dev)";
            cout<<"\n\t\t-node_stats       : Print Node Stats";
            cout<<"\n\t\t-go_live          : Go Live";
            cout<<"\n...................................";
        }


        }
    }
    return 0;
}
