/*******************************************************************************
 * File: server.h                                                              *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main header for the server                                           *
*******************************************************************************/

#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#ifndef SERVER_H
#define SERVER_H
const int MAX_CLIENTS = 10;
const unsigned int DEFAULT_PORT = 22222;

void int_blocker(int);
void* client_handler (void*);

struct Client
{
    int sd;
    bool active;
    pthread_t tid;
    sockaddr_in addr;
    static int* s;
    
    Client() {active = false; addr = {AF_INET};}
};

extern Client clients[MAX_CLIENTS];
extern pthread_mutex_t clients_lock;

#endif
