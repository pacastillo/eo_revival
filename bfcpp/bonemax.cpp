
#include <random>
#include <time.h>

#include <iostream>
using namespace std;
#include "EOBin.h"

#include "EOBinOp.h"
#include <sys/time.h>

typedef EOBin<float> Chrom;

//-----------------------------------------------------------------------------

int main() {
  EOBitFlip<float> bitflip;

  unsigned length = 16;
  unsigned iterations = 100000;
  unsigned top_length = 65536;
  do {
    cout << "C++-BitString, " << length << ", ";

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
             
    for (unsigned i = 0; i < iterations; i++ ) {
      Chrom chrom("", length, 1); chrom.initialize();
      unsigned ones = 0;
      for (unsigned j=0; j<chrom.length(); j++ ){ 
        ones += (chrom[j])?1:0;
      }
    }
    
    gettimeofday(&t2, NULL);
    double elapsedTime = (t2.tv_sec - t1.tv_sec);      
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1e6;   // us to s
    cout <<  elapsedTime << endl;
                
    length = length * 2 ;
  } while (length <= top_length);

  return 0;
}

