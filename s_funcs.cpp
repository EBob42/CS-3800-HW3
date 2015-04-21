/*******************************************************************************
 * File: s_funcs.cpp                                                           *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Supplementary functions for the server                               *
*******************************************************************************/

#include "server.h"
using namespace std;

//---------------------- ^C Handler ----------------------------------//
void int_blocker(int)
{
    char shutdown[] = "\nServer shutting down in 10 seconds\0";
    cout << shutdown << endl;
    
    pthread_mutex_lock(&clients_lock);

//-------------------- Send Shutdown Message -------------------------//
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (clients[i].active)
            write(clients[i].sd, shutdown, strlen(shutdown));
    }
    
    pthread_mutex_unlock(&clients_lock);
    
    sleep(10);
    
    pthread_mutex_lock(&clients_lock);
    
//-------------------- Kill all client threads -----------------------//
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        close(clients[i].sd);
        pthread_kill(clients[i].tid, SIGTERM);
    }
    
    pthread_mutex_unlock(&clients_lock);
    
    return;
}

//-------------------- Client Handler thread main --------------------//
void* client_handler (void* data)
{
    Client* mydata = (Client*)data;
    char* buffer = new char[256];
    
    while(1)
    {
//----------------- Accept a waiting socket connection ---------------//
        unsigned int length = sizeof(mydata->addr);
        if ((mydata->sd = accept(*mydata->s, (struct sockaddr*)&mydata->addr, &length)) == -1)
        {
            cerr << "Failed to accept the socket connection" << endl;
            exit(1);
        }
        
        pthread_mutex_lock (&clients_lock);
        mydata->active = true;
        pthread_mutex_unlock (&clients_lock);
        
//---------------- Read/Write messages from current ------------------//
//------------------ to other client connections ---------------------//
        while (read(mydata->sd, buffer, 256) != 0)
        {
            cout << buffer << endl << endl;
            
            pthread_mutex_lock (&clients_lock);
            for (int i = 0; i < MAX_CLIENTS; ++i)
            {
                if (clients[i].tid != mydata->tid && clients[i].active)
                    write(clients[i].sd, buffer, strlen(buffer)+1);
            }
            pthread_mutex_unlock (&clients_lock);
        }
        
        pthread_mutex_lock (&clients_lock);
        mydata->active = false;
        pthread_mutex_unlock (&clients_lock);
    }
    
    return NULL;
}
