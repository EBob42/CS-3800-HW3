/*******************************************************************************
 * File: s_funcs.cpp                                                           *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Supplementary functions for the server                               *
*******************************************************************************/

#include "server.h"
using namespace std;

void int_blocker(int)
{
    char shutdown[] = "\nServer shutting down in 10 seconds\0";
    cout << shutdown << endl;
    
    pthread_mutex_lock(&clients_lock);
    
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (clients[i].active)
            write(clients[i].sd, shutdown, strlen(shutdown));
    }
    
    pthread_mutex_unlock(&clients_lock);
    
    sleep(10);
    
    pthread_mutex_lock(&clients_lock);
    
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        close(clients[i].sd);
        pthread_kill(clients[i].tid, SIGTERM);
    }
    
    pthread_mutex_unlock(&clients_lock);
    
    return;
}

void* client_handler (void* data)
{
    Client mydata = *(Client*)data;
    char* buffer = new char[256];
    
    while(1)
    {
        unsigned int length = sizeof(mydata.addr);
        if ((mydata.sd = accept(*mydata.s, (struct sockaddr*)&mydata.addr, &length)) == -1)
        {
            cerr << "Failed to accept the socket connection" << endl;
            exit(1);
        }
        
        pthread_mutex_lock (&clients_lock);
        for (int i = 0; i < MAX_CLIENTS; ++i)
        {
            if (clients[i].tid == mydata.tid)
                clients[i].active = true;
        }
        pthread_mutex_unlock (&clients_lock);
        
        while (!read(mydata.sd, buffer, sizeof(buffer)))
        {
            cout << buffer << endl << endl;
            
            pthread_mutex_lock (&clients_lock);
            for (int i = 0; i < MAX_CLIENTS; ++i)
            {
                if (clients[i].tid != mydata.tid && clients[i].active)
                    write(clients[i].sd, buffer, strlen(buffer));
            }
        }
        
        pthread_mutex_lock (&clients_lock);
        for (int i = 0; i < MAX_CLIENTS; ++i)
        {
            if (clients[i].tid == mydata.tid)
                clients[i].active = false;
        }
        pthread_mutex_unlock (&clients_lock);
    }
    //TODO: Get messages from clients, output to other clients
    
    return NULL;
}
