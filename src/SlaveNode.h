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

#include "health.h"

int establish_connection_with_master(char* master_ip, Node &my_identity);





#endif