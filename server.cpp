/*******************************************************************************
 * File: server.cpp                                                            *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main executable for the server                                       *
*******************************************************************************/

#include "server.h"
using namespace std;


void* client_handler (void*);


int main()
{
    int s;
    struct sockaddr_in server = {AF_INET, htons(DEFAULT_PORT)};
    
    
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cerr << "Could not create socket" << endl;
    }
    
    if (bind(s, (struct sockaddr*)&server, sizeof(server)))
    {
        cerr << "Could not bind socket to " << DEFAULT_PORT << endl;
    }
    
    if (listen(s, 10))
    {
        cerr << "Failed to listen" << endl;
    }
    
    //TODO: Figure out how to accept connections on different threads
    //      keep track of which threads have an active connection
    //      allow a thread to be ready to accept again when its connection is closed
    
    //TODO: Get messages from clients, output to other clients
    
    return 0;
}


void* client_handler (void*)
{
    
    return NULL;
}
