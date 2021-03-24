#ifndef HEATLH_H_
#define HEALTH_H_




#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include "sha.h"

#define MAX_LIVE_NODES 10
#define HEALTH_PORT 6969
#define DHCT_PORT 7000

using namespace std;

string get_hash_partition_value_at(int total_parts, int current_part, int start_or_end);      //0 for start, 1 for end

int send_hash_to_node(string hash, const char* nodeIP);

class Node{
    //private
    public:
        
        short int nodeId;
        struct sockaddr_in nodeIp;
        hash160 start_hash; // from where the hash table starts in that node    //init has garbage vals
        hash160 end_hash;  // ending hash included to that node i.e.  last hash  // init has garbage vals

    //public:
        Node(){}
        void print_node_info();
        void createNode(int, struct sockaddr_in);
        void add_hash_range(string start_hash,string end_hash);
        int give_identity_to_node(char msg[1024]);
        char* getIP();
        

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
        int setup_network_for_health(short int no_of_nodes_to_add_at_start);  
        char* get_IP_address_of(int nodeId);
        int routing(string hash);
};


#endif