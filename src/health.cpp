#include "health.h"
#include<fstream>
#include<sstream>
#include<vector>
#include<string.h>
using namespace std;




int LiveNodes :: run_hash_cal(string start_hash, string end_hash, string no_of_div)
{
	string filename = "hash_cal.py";
	string str = "python3 ";
	str = str + filename + " " + start_hash + " " + end_hash + " "+ no_of_div;
	// Convert string to const char * as system requires
	// parameter of type const char *
	
	const char *command = str.c_str();
	system(command);

    fstream file;
    file.open("hash-partitions-temp.txt", ios::in);
    
    if(!file)   cout<<"\n ERROR: Partitions temp file not found!";
    else
    {
        string temp;
        while(getline(file, temp)){
            this->space_separated_hash_partitions_at_epoch = this->space_separated_hash_partitions_at_epoch + temp + " ";
        }    
        file.close();
    }

    return 1;
}

string LiveNodes :: get_all_hash_partitions_value()
{
     return this->space_separated_hash_partitions_at_epoch;
}


/*string get_hash_partition_value_at(int total_parts, int current_part, int start_or_end)      //0 for start, 1 for end
{
   //from, to
    //from, to
    string hash160_partition_2[2][2] = {
            {"0000000000000000000000000000000000000000\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
            {"8000000000000000000000000000000000000000\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
            };

    string const hash160_partition_4[4][2] = {
        {"0000000000000000000000000000000000000000\0", "3fffffffffffffffffffffffffffffffffffffff\0"},
        {"4000000000000000000000000000000000000000\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
        {"8000000000000000000000000000000000000000\0", "bfffffffffffffffffffffffffffffffffffffff\0"},
        {"c000000000000000000000000000000000000000\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
    };


    string const hash160_partition_6[6][2] = {
        {"0000000000000000000000000000000000000000\0", "2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0"},
        {"2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\0", "5555555555555555555555555555555555555555\0"},
        {"5555555555555555555555555555555555555556\0", "7fffffffffffffffffffffffffffffffffffffff\0"},
        {"8000000000000000000000000000000000000000\0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0"},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\0", "d555555555555555555555555555555555555555\0"},
        {"d555555555555555555555555555555555555556\0", "ffffffffffffffffffffffffffffffffffffffff\0"}
    };

    string const hash160_partition_8[8][2] = {
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
*/


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

    return 0;
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


//int comm_with_single_node(char msg[256], struct sockaddr node_addr, ) /// working on the communication protocol


//propoer communication methods are to be done
//till then

//function for sending msg to the nodes

int Node :: give_identity_to_node(char msg[1024])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[1024];

     struct sockaddr_in serv_addr;
     struct sockaddr_in node_addr = this->nodeIp;
     
     int n;

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
   
    listen(sockfd,5);
    clilen = sizeof(node_addr);
    newsockfd = accept(sockfd, 
                    (struct sockaddr *) &node_addr, 
                    &clilen);

    if (newsockfd < 0) 
        error("ERROR on accept");
    
    
    char* a = inet_ntoa(node_addr.sin_addr);

    std:: cout<<"\nIP of node is : "<<a;
        
    bzero(buffer,1024);
    n = write( newsockfd , msg , 1024);

    if (n < 0) error("ERROR writing to socket");
            close(newsockfd);

        
    //close(sockfd);
    return 1;
}

int LiveNodes :: setup_network_for_health(short int no_of_nodes_to_add_at_start)
{

    this->run_hash_cal(HASH160_MIN, HASH160_MAX, to_string(no_of_nodes_to_add_at_start));
    string space_sep_hash_partition = this->get_all_hash_partitions_value();
    istringstream iss(space_sep_hash_partition);

    vector<pair<string, string>> hash_partitions;

    for(string s,e; iss>>s, iss>>e;)
        hash_partitions.push_back(make_pair(s,e));
        
    //cout<<"\n size"<<hash_partitions.size()<<endl;
    //for(int i=0; i<no_of_nodes_to_add_at_start; i++)
    //    cout<<hash_partitions[i].first<<"  "<<hash_partitions[i].second<<endl;

    

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


    //int total_live_nodes = no_of_nodes_to_add_at_start;
    for(short int i=0; i<no_of_nodes_to_add_at_start; i++)
    {
    //bool flag;

    listen(sockfd,5);

    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) 
        error("ERRORtotal_live_nodes on accept");


    char* a = inet_ntoa(cli_addr.sin_addr);

    std:: cout<<"\nIP of node is : "<<a;


    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
        cout<<" \n";

    Node new_node;
    new_node.createNode(atoi(buffer), cli_addr);  //here adding node id is to be defined

    new_node.nodeId = i;

    this->add_new_node(new_node);

    
    /* old method.. hard coded hash values
    live_nodes[i].add_hash_range(get_hash_partition_value_at(total_live_nodes, i, 0), get_hash_partition_value_at(total_live_nodes, i, 1));     
    */

    live_nodes[i].add_hash_range(hash_partitions[i].first, hash_partitions[i].second);

    

    //try sending object.. serialization, deserialization
    //cout<<"\nSize of New Node:"<<sizeof(new_node)<<endl;

    

    n = write(newsockfd, &new_node, sizeof(new_node));
    if (n < 0) error("ERROR writing to socket");
        close(newsockfd);

     }

     close(sockfd);
     return 0;
}

char* Node :: getIP()
{
    return inet_ntoa(this->nodeIp.sin_addr);
}

char* LiveNodes ::  get_IP_address_of(int nodeId)
{
    return live_nodes[nodeId].getIP();
}

int LiveNodes :: routing(string hash)
{
    hash160 temp;
    temp.setter(hash);

    for(int i=0; i<=live_node_counter; i++)
    {
        cout<<endl<<i;
        if(temp <= live_nodes[i].end_hash)    return i;
    }
    cout<<"\n DEBUG: Error in routing";
    return -1;

}


int send_hash_to_node(string hash, const char * nodeIP)
{
    cout<<"\nSending hash to node";
    int sock = 0, valread=0; 
    struct sockaddr_in node_addr; 
    
    char *hello = &hash[0]; 
    char buffer[1024] = {0}; 
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    node_addr.sin_family = AF_INET; 
    node_addr.sin_port = htons(DHCT_PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, nodeIP, &node_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&node_addr, sizeof(node_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    send(sock , hello , strlen(hello) , 0 ); 
    printf("hash message sent\n"); 
    
    //waiting from them.. expected "OK"
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
}



void Node :: add_hash_range(string start_hash, string end_hash)
{
    this->start_hash.setter(start_hash);
    this->end_hash.setter(end_hash);

}