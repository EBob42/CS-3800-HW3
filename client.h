/*******************************************************************************
 * File: client.h                                                              *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main header for the client                                           *
*******************************************************************************/

#include <iostream>
#include <csignal>
#include <cstring>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#ifndef CLIENT_H
#define CLIENT_H

const unsigned int DEFAULT_PORT = 33333;

// Data to be passed to the writing thread
struct Data
{
    std::string name;
    pthread_t tid;
};

extern int s;

void int_blocker (int);

void* writeOut (void*);

void* readIn (void*);

#endif
