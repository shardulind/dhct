#include<iostream>
#include "sha.h"
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
        cout<<"\n0.  Exit";
        cout<<"\n\n\n\n------------------------------------------";
        cin>>choice;
        
        switch(choice)
        {
            case 0:
                    exit(0);
                    break;
            case 1:
                char h1[40], h2[40];
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
            
            default:
                continue;
        }
    }
    return 0;
}
