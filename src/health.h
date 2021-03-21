#ifndef HEATLH_H_
#define HEALTH_H_



#include<strings.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
//#include<QDataStream> //for sending objects over network
#include "sha.h"

#define MAX_LIVE_NODES 10
#define HEALTH_PORT 6969

char* get_hash_partition_value_at(int total_parts, int current_part, int start_or_end);      //0 for start, 1 for end



class Node{
    
    protected:
        //char node_id[160];        //SHA1,  UNCOMMENT IT WHILE STARTING WITH ROUTING CODE
        short int nodeId;
        struct sockaddr_in nodeIp;
        hash160 start_hash; // from where the hash table starts in that node    //init has garbage vals
        hash160 end_hash;  // ending hash included to that node i.e.  last hash  // init has garbage vals

    public:
        Node(){}
        void print_node_info();
        void createNode(int, struct sockaddr_in);
        void add_hash_range(char start_hash[40], char end_hash[40]);
        int give_identity_to_node(char msg[1024]);

        //methods for Slave NOdes

        

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
        int init_node_map_table();  // initializes the NodeMapTable, which has all details regarding the hash distributions throughtout the live nodes
        
};


#endif