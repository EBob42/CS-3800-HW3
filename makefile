################################################################################
# File:   makefile                                                             #
# Author: Eric Hopkins      CS3800                                             #
# Brief:  Makefile for Assignment 3                                            #
################################################################################

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -Wextra -pedantic-errors

SOURCES = $(wildcard *.cpp)

CLIENT = client.cpp
SERVER = server.cpp

HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)

COBJECTS = $(CLIENT:%.cpp=%.o)
SOBJECTS = $(SERVER:%.cpp=%.o)

%.o: %.cpp
	-@echo "--- Compiling $< ---"
	$(CXX) $(CXXFLAGS) -c $< -o $@

default: all

all:
	-@echo "--- Building Client ---"
	${CXX} ${CXXFLAGS} ${COBJECTS} -o client.exe
	-@echo "--- Building Server ---"
	${CXX} ${CXXFLAGS} ${SOBJECTS} -o server.exe

clean:
	-@echo "--- Cleaning ---"
	rm -f core
	rm -f client.exe
	rm -f server.exe
	rm -f ${OBJECTS}

client:
	-@echo "--- Building Client ---"
	${CXX} ${CXXFLAGS} ${COBJECTS} -o client.exe

server:
	-@echo "--- Building Server ---"
	${CXX} ${CXXFLAGS} ${SOBJECTS} -o server.exe

depend: $(SOURCES) $(HEADERS)
	-@echo "--- Including dependencies ---"
	-@$(CXX) -MM *.cpp > $@

-include depend
