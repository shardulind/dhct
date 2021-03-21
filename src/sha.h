#ifndef hash_H
#define hash_H
#pragma once

#define HASH160_MIN "0000000000000000000000000000000000000000\0" 
#define HASH160_MAX "ffffffffffffffffffffffffffffffffffffffff\0"

using namespace std;


class hash160{
        
    public:
         string h;
         void setter();     // method to set hashvalue
         void setter(string hash);
         string getter();     // method to get hashvalue

};

//bool isHashSmallerThanOrEqualTo(char h1[40], char h2[40]);

bool operator <= (hash160 const &obj1, hash160 const &obj2);   // Operator overloading


#endif 


/*
Spliting hash160


for 2 NODES:

    node1 = 0000000000000000000000000000000000000000  to  7fffffffffffffffffffffffffffffffffffffff 
    node2 = 8000000000000000000000000000000000000000  to  ffffffffffffffffffffffffffffffffffffffff

for 4 nodes:

    node1 = 0000000000000000000000000000000000000000  to  3fffffffffffffffffffffffffffffffffffffff
    node2 = 4000000000000000000000000000000000000000  to  7fffffffffffffffffffffffffffffffffffffff
    node3 = 8000000000000000000000000000000000000000  to  bfffffffffffffffffffffffffffffffffffffff
    node4 = c000000000000000000000000000000000000000  to  ffffffffffffffffffffffffffffffffffffffff

for 6 nodes:
    
    node1 = 0000000000000000000000000000000000000000  to  2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    node2 = 2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab  to  5555555555555555555555555555555555555555
    node3 = 5555555555555555555555555555555555555556  to  7fffffffffffffffffffffffffffffffffffffff
    node4 = 8000000000000000000000000000000000000000  to  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    node5 = aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab  to  d555555555555555555555555555555555555555
    node6 = d555555555555555555555555555555555555556  to  ffffffffffffffffffffffffffffffffffffffff

for 8 nodes:

    node1 = 0000000000000000000000000000000000000000  to  1fffffffffffffffffffffffffffffffffffffff
    node2 = 2000000000000000000000000000000000000000  to  3fffffffffffffffffffffffffffffffffffffff
    node3 = 4000000000000000000000000000000000000000  to  5fffffffffffffffffffffffffffffffffffffff
    node4 = 6000000000000000000000000000000000000000  to  7fffffffffffffffffffffffffffffffffffffff
    node5 = 8000000000000000000000000000000000000000  to  9fffffffffffffffffffffffffffffffffffffff
    node6 = a000000000000000000000000000000000000000  to  bfffffffffffffffffffffffffffffffffffffff
    node7 = c000000000000000000000000000000000000000  to  dfffffffffffffffffffffffffffffffffffffff
    node8 = e000000000000000000000000000000000000000  to  1fffffffffffffffffffffffffffffffffffffff

for 10 nodes:

    node1 = TBC..

*/