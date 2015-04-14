/*******************************************************************************
 * File: client.cpp                                                            *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main executable for the client                                       *
*******************************************************************************/

#include "client.h"
using namespace std;


void* writeOut (void*);

void* readIn (void*);


int main()
{
    string server_name;
    struct hostent *server;
    struct sockaddr_in port = { AF_INET, htons( DEFAULT_PORT ) };
    string username;
    
    cout << "Input server hostname:  ";
    cin >> server_name;
    
    while ((server = gethostbyname(server_name.c_str())) == NULL)
    {
        cout << "\nFailed to find host, please try a different hostname" << endl;
        cin >> server_name;
    }
    
    bcopy(server -> h_addr_list[0], &port.sin_addr, server -> h_length);
    
    cout << "\nChoose a username:  ";
    cin >> username;
    
    //TODO: Actually connect to server and what-not
    
    return 0;
}

void* readIn (void*)
{
    
    return NULL;
}

void* writeOut (void*)
{
    
    return NULL;
}
