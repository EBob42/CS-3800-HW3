/*******************************************************************************
 * File: c_funcs.cpp                                                           *
 * Authors: Eric Hopkins and Zack Brinkley                                     *
 * Brief: Supplementary Functions for the client                               *
*******************************************************************************/

#include "client.h"
using namespace std;

void int_blocker (int)
{
    cout << "\nPlease use /exit, /quit, or /part to leave the chatroom." << endl;
}
