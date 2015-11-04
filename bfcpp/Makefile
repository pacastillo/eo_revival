CXX=g++ 
prefix=..
CXXFLAGS=-Wall -O4

###############################################################################

SRC = bfcpp.cpp
BIN = bfcpp

all: bfcpp

###############################################################################

clean:	
	rm -f ${BIN} *~ core

bfcpp: bfcpp.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bfcpp.cpp -o bfcpp

###############################################################################

.NOEXPORT:
