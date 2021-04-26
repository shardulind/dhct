#ifndef SLAVENODE_H_
#define SLAVENODE_H_

#include<cstring>
#include<strings.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include<set>

#include "health.h"
#define DHCT_PORT 7000



class SNode : public Node
{
    public:
        int establish_connection_with_master(string master_ip);        

};



struct Dht_unit{
	string sha1;
	bool is_hash_stored;
	
	bool operator < (const Dht_unit &obj1) const
	{
		unsigned short int index = 0;
		while(index < 40)
		{
		        if(this->sha1[index] < obj1.sha1[index])       return true;
		        else if(this->sha1[index]> obj1.sha1[index])   return false;
		        else if(this->sha1[index] == obj1.sha1[index])
		                index++;
		}

		return true; //not confirmed if its true or false.. just to avoid warnings its added,, hoping control never reach here
	}

    /* Not working... Needed more understanding..  Till then make a custom linear search. ;
    //hhttp...journaldev/stl
    bool operator ==(const string &temp) const{
        return this->sha1 == temp;
    }
    */
};


class PartitionedDHT
{
    private:
        	set<struct Dht_unit> s;
			bool is_live;

    public:
		PartitionedDHT() { is_live = false; }

		void turn_on_live_state();
		void turn_off_live_state();
        void print_all_local_dht();
        int insert_sha_to_local_dht(string hash);
		void live_state();
};


#endif