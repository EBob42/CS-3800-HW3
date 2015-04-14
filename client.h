/*******************************************************************************
 * File: client.h                                                              *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Main header for the client                                           *
*******************************************************************************/

#include <iostream>
#include <csignal>
#include <cstring>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

const unsigned int DEFAULT_PORT = 22222;

void int_blocker (int);
