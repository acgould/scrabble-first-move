#
# Makefile for Scrabble First Move
# 

###############################################################################
# MAKEFILE VARIABLES
###############################################################################

# CXX is the name of the compiler we are using (clang++)

CXX = clang++-3.5

# CXXFLAGS are the flags we will be passing each compile

CXXFLAGS       = -g -std=c++11 -Wall -Wextra -pedantic

# TARGETS is the list of all programs created when we do "make all"
#   (and which should be deleted when we do "make clean")

TARGETS = mytiles

###############################################################################
# "PHONY" (BUT USEFUL) MAKEFILE TARGETS
###############################################################################


# "make all" brings all programs up-to-date (recursively)
#     and then runs no commands.

all: $(TARGETS)

# "make clean" brings nothing up to date, but always
#      runs commands to delete all created files

clean:
	rm -f $(TARGETS)
	rm -rf *.o

tilechecker: mytiles

###############################################################################
# CREATING PROGRAMS
###############################################################################

mytiles: mytiles.o scrabbler.o
	$(CXX) $(CXXFLAGS) -o mytiles $^

###############################################################################
# GENERATING OBJECT FILES
###############################################################################

# Our tile checking files

scrabbler.o: scrabbler.cpp scrabbler.hpp
	$(CXX) $(CXXFLAGS) -c scrabbler.cpp

mytiles.o: mytiles.cpp scrabbler.hpp
	$(CXX) $(CXXFLAGS) -c mytiles.cpp
