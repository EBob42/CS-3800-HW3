/*******************************************************************************
 * File: server.h                                                              *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main header for the server                                           *
*******************************************************************************/

#include <iostream>
#include <csignal>
#include <cstring>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

const int MAX_CLIENTS = 10;
const unsigned int DEFAULT_PORT = 22222;

struct Client
{
    int sd;
    bool active;
    pthread_t tid;
    sockaddr_in addr;
    
    Client() {active = false; addr = {AF_INET};}
};
