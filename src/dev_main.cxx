#include<iostream>
#include "sha.h"
#include "health.h"
using namespace std;

int main(int argc, char ** argv)
{
    while(1)
    {
        unsigned short int choice;
        cout<<"\n------------------------------------------";
        cout<<"\n\t\tDEVELOPING MODE MENU";
        cout<<"\n------------------------------------------";
        cout<<"\n1.  SHA1 hash compare operation demo";
        cout<<"\n2.  Accept Nodes";
        cout<<"\n0.  Exit";
        cout<<"\n\n\n\n------------------------------------------";
        cin>>choice;
        
        switch(choice)
        {
            case 0:
                    exit(0);
                    break;
            case 1:
                hash160 h1;
                hash160 h2;
                h1.setter();
                h2.setter();
                if(h1<=h2)   cout<<"\nH1 <= H2";
                else
                {
                    cout<<"\nH1 > H2";
                }
                break;


                /*              char h1[40], h2[40];
                cout<<"\n \n Get SHA1 from https://emn178.github.io/online-tools/sha256.html";
                cout<<"\nEnter SHA1 hash1: ";
                cin>>h1;
                cout<<"Enter SHA1 hash2: ";
                cin>>h2;

                if(isHashSmallerThanOrEqualTo(h1,h2))   cout<<"\nH1 <= H2";
                else
                {
                    cout<<"\nH1 > H2";
                }
                break;
     */


            case 2:
            {
                cout<<"Accepting Nodes... ";
                LiveNodes live_nodes;
                live_nodes.setup_network_for_health();
                cout<<endl<<endl;
                live_nodes.display_live_nodes();
            }
                break;
                 
            default:
                continue;
        }
    }
    return 0;
}
