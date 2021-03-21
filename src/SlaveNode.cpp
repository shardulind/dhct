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




int SNode :: establish_connection_with_master(char* master_ip)
{
    int sock = 0, valread; 
    struct sockaddr_in serv_addr, my_addr; 

    my_addr.sin_addr.s_addr = INADDR_ANY;

    char* my_ip = inet_ntoa(my_addr.sin_addr);
    
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
    if(inet_pton(AF_INET, master_ip, &serv_addr.sin_addr)<=0)  
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
    
    Node temp;
    valread = read( sock , &temp, 104);
    
    //cout<<endl;
    //temp.print_node_info();
    //printf("%s\n",buffer ); 

    
    return 1;
}

