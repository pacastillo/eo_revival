
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
  unsigned iterations = 1000000;
  unsigned top_length = 32768;
  do {
    Chrom chrom("", length, 1); chrom.initialize();
    cout << "C++, BitString, " << length << ", ";

    struct timeval t1, t2;
    double elapsedTime;
    gettimeofday(&t1, NULL);
             
    for (unsigned i = 0; i < iterations; i++ ) {
      bitflip(chrom);
    }
    
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    cout << elapsedTime/1000 << endl;
                
    length = length * 2 ;
  } while (length <= top_length);

  return 0;
}

