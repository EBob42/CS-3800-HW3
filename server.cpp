/*******************************************************************************
 * File: server.cpp                                                            *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main executable for the server                                       *
*******************************************************************************/

#include "server.h"
using namespace std;

int* Client::s = NULL;

Client clients[MAX_CLIENTS];
pthread_mutex_t clients_lock = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    int s;
    struct sockaddr_in server = {AF_INET, htons(DEFAULT_PORT)};
    clients[0].s = &s;

//----------------- Create and Init Socket ---------------------------//
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cerr << "Could not create socket" << endl;
        exit(1);
    }
    
    if (bind(s, (struct sockaddr*)&server, sizeof(server)))
    {
        cerr << "Could not bind socket to " << DEFAULT_PORT << endl;
        exit(1);
    }
    
    if (listen(s, 10))
    {
        cerr << "Failed to listen" << endl;
        exit(1);
    }
    
    signal (SIGINT, int_blocker);
    
//-------------------- Spawn threads for handling clients ------------//
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (pthread_create(&clients[i].tid, NULL, client_handler, &clients[i]))
        {
            cerr << "Failed to create thread for client connection" << endl;
            exit(1);
        }
    }
    
//------------------- Terminate Gracefully as the server closes ------//
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        void** v = NULL;
        pthread_join(clients[i].tid, v);
    }
    
    close(*clients[0].s);
    
    return 0;
}
