/*******************************************************************************
 * File: client.cpp                                                            *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main executable for the client                                       *
*******************************************************************************/

#include "client.h"
using namespace std;

int s;

int main()
{
    string server_name;
    struct hostent *server;
    struct sockaddr_in port = { AF_INET, htons( DEFAULT_PORT ) };
    string username;
    pthread_t t_read, t_write;
    
    //------------------------ Finding Host --------------------------//
    
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
    cout << endl;
    
    signal(SIGINT, int_blocker);
    
    //-------------- Creating and Connecting Socket ------------------//
    
    if ((s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cerr << "Failed to create socket" << endl;
        exit(1);
    }
    
    if (connect(s, (struct sockaddr*)&port, sizeof(port)) == -1)
    {
        cerr << "Connection Failed" << endl;
        exit(1);
    }
    
    cout << "You have connected to the chatroom." << endl << endl;
    
    //---------------- Create Read/Write threads ---------------------//
    
    pthread_create(&t_read, NULL, readIn, NULL);
    Data dat = {username, t_read};
    pthread_create(&t_write, NULL, writeOut, &dat);
    
    pthread_join(t_read, NULL);
    pthread_kill(t_write, SIGTERM);
    pthread_join(t_write, NULL);
    
    return 0;
}
