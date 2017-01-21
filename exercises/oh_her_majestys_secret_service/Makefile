# Makefile for compilation of program
# also includes all features from helpers.mk

# Compiler
CC=g++-4.9

# Flags
DEBUG_FLAGS=-Wall -O3 -std=c++11

# File locations
BASENAME=oh_her_majestys_secret_service
EXE_LOC=./bin/$(BASENAME)
CPP_NAME=$(BASENAME).cpp

all:
	if [ ! -d bin ] ; then mkdir bin ; fi;
	$(CC) $(DEBUG_FLAGS) -o $(EXE_LOC) $(CPP_NAME)

clean:
	if [ -d bin ] ; then rm -R bin ; fi;

include helpers.mk
