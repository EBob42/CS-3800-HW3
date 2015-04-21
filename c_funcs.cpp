/*******************************************************************************
 * File: c_funcs.cpp                                                           *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Supplementary Functions for the client                               *
*******************************************************************************/

#include "client.h"
using namespace std;


//------------------------ ^C Handler --------------------------------//
void int_blocker (int)
{
    cout << "\nPlease use /exit, /quit, or /part to leave the chatroom." << endl;
}


//----------------------- Reading from Server ------------------------//
void* readIn (void* tid)
{
    char* buffer = new char[256];
    while (read(s, buffer, 256) != 0)
    {
        cout << buffer << endl << endl;
    }
    
    return NULL;
}


//----------------------- Writing to Server --------------------------//
void* writeOut (void* dat)
{
    Data d = *(Data*)dat;
    string username = d.name;
    pthread_t t_read = d.tid;
    char* buffer = new char[256], *input = new char[220];
    bool cont = true;
    
    cin.ignore();
    
    strcpy(buffer, username.c_str());
    strcat(buffer, " has connected to the chatroom.\0");
    write(s, buffer, strlen(buffer)+1);
    
    while(cont)
    {
        cin.getline(input, 220, '\n');
        cout << endl;
        if (strcmp(input, "/quit") && strcmp(input, "/part") && strcmp(input, "/exit"))
        {
            buffer[0] = '\0';
            strcpy(buffer, username.c_str());
            strcat(buffer, ":\t\t");
            strcat(buffer, input);
            write(s, buffer, strlen(buffer)+1);
        }
        else
        {
            strcpy(buffer, username.c_str());
            strcat(buffer, " has left the chatroom.\0");
            write(s, buffer, strlen(buffer)+1);
            cout << "You have left the chatroom." << endl << endl;
            pthread_kill(t_read, SIGTERM);
            cont = false;
        }
    }
    
    return NULL;
}
