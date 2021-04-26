#include "SlaveNode.h"
using namespace std;


void PartitionedDHT :: print_all_local_dht()
{
    	set<struct Dht_unit>::iterator it;
        for(it = s.begin(); it != s.end(); it++)
    	{
		    cout<<endl<< (*it).sha1<<"\t"<<(*it).is_hash_stored;
    	}
}


int PartitionedDHT :: insert_sha_to_local_dht(string received_hash)
{
    //check if hash exists in the set
	set<struct Dht_unit>::iterator it;

    for(it = s.begin(); it != s.end(); it++)
    {
        if(it->sha1 == received_hash){
            cout<<"\nDEBUG  hash ="<<it->sha1<<"\n is_stored = "<<it->is_hash_stored;
            return it->is_hash_stored;
        }
    }
    
    //reached here, it means that hash is not their in local dht..
    //thus needed to add in the local dht
    s.insert(Dht_unit{received_hash, true});
    return false;
}

void PartitionedDHT :: turn_off_live_state()
{
    cout<<"\n TURN OFF LIVE STATE CALLED";
    this->is_live = false;
    return;
}

void PartitionedDHT :: turn_on_live_state()
{
    cout<<"\n TURN ON LIVE STATE CALLED";
    this->is_live = true;
    return;
}

void PartitionedDHT :: live_state()
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];

     struct sockaddr_in serv_addr, cli_addr;
     
     int n;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        cout<<"\nERROR opening socket";
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     portno = DHCT_PORT;

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;  //ip address of this machine
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              cout<<"ERROR on binding";
    

    //bool flag=true;


    cout<<"\n Listening";
    listen(sockfd,5);
    
    clilen = sizeof(cli_addr);
    while(this->is_live)
    {           
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
        if (newsockfd < 0) 
            cout<<"\nERROR on accept";
        
        char* a = inet_ntoa(cli_addr.sin_addr);

        //std::cout<<"\nIP of Master Node is : "<<a;
        

        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) cout<<"ERROR reading from socket\n";

        cout<<"\n===============================================";
        cout<<"\n DEBUG\n Hash received from Master Node is: ";
        cout<<buffer;

        insert_sha_to_local_dht(buffer);

        n = write(newsockfd, "OK", 2);  
        if (n < 0) cout<<"\nERROR writing to socket";
            close(newsockfd);

        //cout<<"\nTEST purpose:  Keep running? (1/0)";
        //cin>>flag;
        cout<<"\nis_live= "<<this->is_live<<endl;

     }

     close(sockfd);
     return;
}



//ithe change kraicha ahe tula
int SNode :: establish_connection_with_master(string master_ip)
{
    int sock = 0, valread=0; 
    struct sockaddr_in serv_addr, my_addr; 
    my_addr.sin_addr.s_addr = INADDR_ANY;

    char* my_ip = inet_ntoa(my_addr.sin_addr);
    char* const mip = &master_ip[0];


    char* a = "Hello from ";
    char *hello = a + *my_ip; 
    char buffer[1024] = {0}; 



    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(HEALTH_PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, mip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("\nRequest sent to Master to connect to Overlay Network\n"); 
    
    //Node temp;
    valread = read( sock , &buffer, 1024);
    
    cout<<buffer<<endl;
    //temp.print_node_info();
    
    
    return 1;
}



