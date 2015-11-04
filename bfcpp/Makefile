CXX=g++ 
prefix=..
CXXFLAGS=-Wall -O4

###############################################################################

SRC = bfcpp.cpp bxcpp.cpp
BIN = bfcpp bxcpp

all: bfcpp bxcpp

###############################################################################

clean:	
	rm -f ${BIN} *~ core

bfcpp: bfcpp.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bfcpp.cpp -o bfcpp
bxcpp: bxcpp.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bxcpp.cpp -o bxcpp

###############################################################################

.NOEXPORT:
