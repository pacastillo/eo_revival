CXX=g++ 
prefix=..
CXXFLAGS=-Wall -O4

###############################################################################

SRC = bfcpp.cpp bxcpp.cpp bonemax.cpp
BIN = bfcpp bxcpp bonemax

all: bfcpp bxcpp bonemax

###############################################################################

clean:	
	rm -f ${BIN} *~ core

bfcpp: bfcpp.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bfcpp.cpp -o bfcpp
bxcpp: bxcpp.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bxcpp.cpp -o bxcpp
bonemax: bonemax.cpp	
	g++ -Wall -Wno-deprecated -std=c++11 bonemax.cpp -o bonemax

###############################################################################

.NOEXPORT:
