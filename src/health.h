#ifndef HEATLH_H_
#define HEALTH_H_



#include<strings.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>

#define MAX_LIVE_NODES 10
#define HEALTH_PORT 6969



class Node{
    //char node_id[160];        //make it SHA1
    private:
        short int nodeId;
        struct sockaddr_in nodeIp;
    public:
        Node(){}
        void print_node_info();
        void createNode(int, struct sockaddr_in);

};

class LiveNodes{
    private:
        Node live_nodes[MAX_LIVE_NODES];
        int live_node_counter;
    
    public:
    LiveNodes()
    {
        this->live_node_counter = -1; //counting starts from 1
    }
        int display_live_nodes();   //prints live node details and returns total count
        int add_new_node(Node);
        int setup_network_for_health();        
};





#endif