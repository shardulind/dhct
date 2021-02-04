#ifndef hash_H
#define hash_H
#pragma once



class hash160{
        
    public:
         char h[40];
         void setter();     // method to set hashvalue
         char* getter();     // method to get hashvalue

};

//bool isHashSmallerThanOrEqualTo(char h1[40], char h2[40]);

bool operator <= (hash160 const &obj1, hash160 const &obj2);   // Operator overloading


#endif 
