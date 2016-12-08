# Makefile for compilation of program
# also includes all features from helpers.mk

# Compiler
CC=g++-4.9

# Flags
DEBUG_FLAGS=-Wall -O0 -g -std=c++11

# File locations
BASENAME=radiation
EXE_LOC=./bin/$(BASENAME)
CPP_NAME=$(BASENAME).cpp

all:
	if [ ! -d bin ] ; then mkdir bin ; fi;
	$(CC) $(DEBUG_FLAGS) -o $(EXE_LOC) $(CPP_NAME)

clean:
	if [ -d bin ] ; then rm -R bin ; fi;

include helpers.mk
