#include "health.h"

using namespace std;


int error(const char *msg)
{
    perror(msg);
    return -1;
}



void Node :: print_node_info()
{
        
        char *ip = inet_ntoa(this->nodeIp.sin_addr);
        cout<<"Node ID: "<< this->nodeId << "\t IP: ";
        cout<<"Node IP: "<<ip<<endl;

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




int LiveNodes :: setup_network_for_health()
{
    cout<<"Mi jivant aahe @setup_network_for_health\n\n";
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
     
     while(1){
        bool flag;
       
        listen(sockfd,5);
        
        clilen = sizeof(cli_addr);
        
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        
        
        char* a = inet_ntoa(cli_addr.sin_addr);

        std:: cout<<"\nIP of node is : "<<a;
        
        //atta tatpurta add krun ghetle //./... nntr proper PROTOCOL bnvaicha baki aahe in context with BIG PIC
        


        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
           printf("Here is the message: %s\n",buffer);

        Node new_node;
        new_node.createNode(atoi(buffer), cli_addr);
        
        n = write(newsockfd,"You got added , bahutek",24);
        if (n < 0) error("ERROR writing to socket");
            close(newsockfd);

        this->add_new_node(new_node);

        cout<<"0: Exit 1: Continue";
        cin>>flag;
        if(!flag)  break;

   
     }

     close(sockfd);
     return 0;
}

