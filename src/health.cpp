#include "health.h"

using namespace std;




char* get_hash_partition_value_at(int total_parts, int current_part, int start_or_end)      //0 for start, 1 for end
  {


   //from, to
    //from, to
    char* const hash160_partition_2[2][2] = {
            {"0000000000000000000000000000000000000000\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
            {"8000000000000000000000000000000000000000\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
            };

    char* const hash160_partition_4[4][2] = {
        {"0000000000000000000000000000000000000000\0", "3fffffffffffffffffffffffffffffffffffffff\0"},
        {"4000000000000000000000000000000000000000\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
        {"8000000000000000000000000000000000000000\0", "bfffffffffffffffffffffffffffffffffffffff\0"},
        {"c000000000000000000000000000000000000000\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
    };


    char* const hash160_partition_6[6][2] = {
        {"0000000000000000000000000000000000000000\0", "2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0"},
        {"2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\0", "5555555555555555555555555555555555555555\0"},
        {"5555555555555555555555555555555555555556\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
        {"8000000000000000000000000000000000000000\0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0"},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\0", "d555555555555555555555555555555555555555\0"},
        {"d555555555555555555555555555555555555556\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
    };

    char* const hash160_partition_8[8][2] = {
        {"0000000000000000000000000000000000000000\0", "1fffffffffffffffffffffffffffffffffffffff\0"},
        {"2000000000000000000000000000000000000000\0", "3fffffffffffffffffffffffffffffffffffffff\0"},
        {"4000000000000000000000000000000000000000\0", "5fffffffffffffffffffffffffffffffffffffff\0"},
        {"6000000000000000000000000000000000000000\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
        {"8000000000000000000000000000000000000000\0", "9fffffffffffffffffffffffffffffffffffffff\0"},
        {"a000000000000000000000000000000000000000\0", "bfffffffffffffffffffffffffffffffffffffff\0"},
        {"c000000000000000000000000000000000000000\0", "dfffffffffffffffffffffffffffffffffffffff\0"},
        {"e000000000000000000000000000000000000000\0" ,"ffffffffffffffffffffffffffffffffffffffff\0"}
    };


    if(2 == total_parts)    return hash160_partition_2[current_part][start_or_end];
    else if(4 == total_parts)   return hash160_partition_4[current_part][start_or_end];
    else if(6 == total_parts)   return hash160_partition_6[current_part][start_or_end];
    else if(8 == total_parts)   return hash160_partition_8[current_part][start_or_end];

  }






int error(const char *msg)
{
    perror(msg);
    return -1;
}



void Node :: print_node_info()
{
        
        char *ip = inet_ntoa(this->nodeIp.sin_addr);
        cout<<"\nNode ID: "<< this->nodeId <<endl;
        cout<<"\tIP Addr: "<<ip<<endl;
        cout<<"\n\tStart Hash: "<<this->start_hash.getter();
        cout<<"\n\tEnd Hash: "<<this->end_hash.h;

        return;
}

void Node :: createNode(int id, struct sockaddr_in soc)
{
                this->nodeId = id;
                this->nodeIp = soc;
}




int LiveNodes :: display_live_nodes()
{
    for(int i=0; i<=this->live_node_counter; i++)
    {
        live_nodes[i].print_node_info();
    }
}

int LiveNodes :: add_new_node(Node new_node)
{
    if(this->live_node_counter < MAX_LIVE_NODES)
    {
        this->live_nodes[++this->live_node_counter] = new_node; 

        cout<<"\n new Node added";
        return 1;
    }
    else
    {
        cout<<"NODE LIMIT FULL";
        return -1;
    }
    
}




int LiveNodes :: setup_network_for_health(short int no_of_nodes_to_add_at_start)
{
    cout<<"\nDEBUG: working inside @setup_network_for_health()\n\n";
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];

     struct sockaddr_in serv_addr, cli_addr;
     
     int n;
     /*
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }*/
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = atoi(argv[1]);
     portno = HEALTH_PORT;

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;  //ip address of this machine
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     for(short int i=0; i<no_of_nodes_to_add_at_start; i++)
     {
        //bool flag;
       
        listen(sockfd,5);
        
        clilen = sizeof(cli_addr);
        
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        
        
        char* a = inet_ntoa(cli_addr.sin_addr);

        std:: cout<<"\nIP of node is : "<<a;
        

        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
           printf(" \n");

        Node new_node;
        new_node.createNode(atoi(buffer), cli_addr);  //here adding node id is to be defined
        
        n = write(newsockfd,"You are added into Overlay Network, Your Node ID is:",52);
        if (n < 0) error("ERROR writing to socket");
            close(newsockfd);

        this->add_new_node(new_node);

       // cout<<"\t0: Exit 1: Continue";
       // cin>>flag;
       // if(!flag)  break;

   
     }

     close(sockfd);
     return 0;
}



int LiveNodes :: init_node_map_table()
{
    // table which stores, { nodeID, start_hash, end_hash, NodeIP}
    // nodeID , and node IP are already added in the nodemaptable == livenodes


    int total_live_nodes = this->live_node_counter + 1;  //  live_node_counter starts from 0
   
    
   // hash160 start_hash;   
    //start hash is 
    //cout<<"\n\nStart Hash is: "<<start_hash.getter()<<endl;
    //hash160 end_hash;



    for(int i=0; i<total_live_nodes; i++)
    {

        live_nodes[i].add_hash_range(get_hash_partition_value_at(total_live_nodes, i, 0), get_hash_partition_value_at(total_live_nodes, i, 1));
        
    }

    
    return 1;
    // based upon no_of_nodes ( live_node_counter+1 ) divide total range of sha160
    // assign each node a start and end hash

}
      


void Node :: add_hash_range(char start_hash[40], char end_hash[40])
{
    //cout<<"\nDEBUG: Node::add_hash_range\n";
    //cout<<"start_hash received from params: "<<start_hash<<endl;
    this->start_hash.setter(start_hash);
    this->end_hash.setter(end_hash);

    //cout<<"\n DEBUG: @Node::add_hash_range  values set are \n\tstart_hash="<<this->start_hash.h;
    //cout<<"\n\tend_hash="<<this->end_hash.h;
}