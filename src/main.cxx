#include<iostream>
#include "sha.h"
#include "health.h"



void print(string msg)
{
    std::cout<<"\n> "<<msg;
    return;
}

int main(int argc, char **argv)
{
    //now see
    //read the environmental variables,, which will be having details about the  T.B.D.  (needed to make changes in other files too)

    //this Program will be a Shell for the program
    //for first release of this shell , keeps things simple
    // make splash screen (additional)
    // >
    // initial setup prompted
    LiveNodes live_nodes;
    string temp;
    int targetNode;
    short int no_of_nodes_to_add_at_start = 0; //infuture think of loading it from envvar
    print("No of nodes to be initialized in DHT");
    std::cin>>no_of_nodes_to_add_at_start;

    print("Ready for incoming connection");

    live_nodes.setup_network_for_health(no_of_nodes_to_add_at_start);
    print(" ");
    live_nodes.display_live_nodes();

    // all nodes will get added automatically,, no multiple keyboard input asked
    // live state will be reached

    while(true){
        print("Enter hash to send to node: ");
        cin>>temp;
        targetNode = live_nodes.routing(temp);
        
        send_hash_to_node(temp, live_nodes.get_IP_address_of(targetNode));
    }


    // here comes threading. 2 threads running 
    // 1st thread  put()
    // 2nd thread  basic shell commands
    return 0;
}