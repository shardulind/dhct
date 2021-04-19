#include<iostream>
#include "sha.h"
#include "health.h"
using namespace std;

int main(int argc, char ** argv)
{

    LiveNodes live_nodes;

    hash160 h1;
    hash160 h2;
    string temp;
    int targetNode;
    string start_hash, end_hash, divs;
    while(1)
    {
        unsigned short int choice;
        cout<<"\n------------------------------------------";
        cout<<"\n\t\tDEVELOPING MODE MENU (Testing each funct)";
        cout<<"\n------------------------------------------";
        cout<<"\n1.  SHA1 hash compare operation demo";
        cout<<"\n2.  Accept Nodes";
        cout<<"\n3.  Active Nodes in the network";
        cout<<"\n4.  Get Partition hash160 value";
        cout<<"\n5.  Send Hash to Node";
        cout<<"\n6.  Get ip address of node";
        cout<<"\n7.  UPDATED: get hash partitions:";
        cout<<"\n0.  Exit";
        cout<<"\n\n\n\n------------------------------------------";
        cin>>choice;
        




        switch(choice)
        {
            case 0:
                    exit(0);
                    break;
            case 1:
                cout<<"\n \n Get SHA1 from https://emn178.github.io/online-tools/sha256.html\n";
                h1.setter();
                h2.setter();
                if(h1<=h2)   cout<<"\nH1 <= H2";
                else
                {
                    cout<<"\nH1 > H2";
                }
                break;
            case 2:
            {


                short int no_of_nodes_to_add_at_start;
                cout<<"\nEnter Number of Nodes to be added: ";
                cin>>no_of_nodes_to_add_at_start;
                
                cout<<"\nAccepting Nodes... (waiting for Slave nodes to send req.) ";
                //LiveNodes live_nodes;
                live_nodes.setup_network_for_health(no_of_nodes_to_add_at_start);
                cout<<endl<<endl;
                live_nodes.display_live_nodes();


                //workin progress 18-03 16:10
                //live_nodes.init_node_map_table();
            }
                break;
            
            case 3:
                live_nodes.display_live_nodes();
                break;
            
            case 4:
                cout<<"Partition value for enter: ( total_nodes, node_number(index), (start=0/end=1)) ";
                int a,b,c;
                cin>>a>>b>>c;
                cout<<get_hash_partition_value_at(a,b,c);
                break;
            

            case 5:
                cout<<"\n TESTING";
                //we will be sending data to first node just to check
                cout<<"\n Enter hash to send to node: ";
                cin>>temp;
                targetNode = live_nodes.routing(temp);
                
                send_hash_to_node(temp, live_nodes.get_IP_address_of(targetNode));

                break;
            
            case 6:
                cout<<"\nGet IP address of NOde:  ";
                int temp_nodeid;
                cin>>temp_nodeid;
                cout<<endl<<live_nodes.get_IP_address_of(temp_nodeid);
                cout<<endl;
                break;
            
            case 7:
                
                cout<<"enter start hash, end hash and no-of-divisions";
                cin>>start_hash>>end_hash>>divs;
                live_nodes.run_hash_cal(start_hash,end_hash, divs);
                cout<<live_nodes.get_all_hash_partitions_value();

                break;
            default:
                continue;
        }
    }
    return 0;
}
