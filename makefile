################################################################################
# File:   makefile                                                             #
# Author: Eric Hopkins      CS3800                                             #
# Brief:  Makefile for Assignment 3                                            #
################################################################################

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -pedantic-errors -pthread

SOURCES = $(wildcard *.cpp)

CLIENT = client.cpp c_funcs.cpp
SERVER = server.cpp s_funcs.cpp

HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)

COBJECTS = $(CLIENT:%.cpp=%.o)
SOBJECTS = $(SERVER:%.cpp=%.o)

%.o: %.cpp
	-@echo "--- Compiling $< ---"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

default: all

all: client server

clean:
	-@echo "--- Cleaning ---"
	rm -f core
	rm -f client.exe
	rm -f server.exe
	rm -f ${OBJECTS}
	rm -f depend

client: ${COBJECTS}
	-@echo "--- Building Client ---"
	@${CXX} ${CXXFLAGS} ${COBJECTS} -o client.exe

server: ${SOBJECTS}
	-@echo "--- Building Server ---"
	@${CXX} ${CXXFLAGS} ${SOBJECTS} -o server.exe

depend: $(SOURCES) $(HEADERS)
	-@echo "--- Including dependencies ---"
	-@$(CXX) -MM *.cpp > $@

-include depend
