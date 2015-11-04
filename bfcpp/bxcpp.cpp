
#include <random>
#include <time.h>

#include <iostream>
using namespace std;
#include "EOBin.h"
#include "EOBinOp.h"
#include "EOGOps.h"
#include <sys/time.h>

typedef EOBin<float> Chrom;

//-----------------------------------------------------------------------------

int main() {

  unsigned length = 16;

  Chrom chrom0("", length, 1); chrom0.initialize();
  Chrom chrom1("", length, 1); chrom1.initialize();

  struct timeval t1, t2;
  gettimeofday(&t1, NULL);

  cout << "Original chroms:  " << chrom0 << "  " << chrom1 << endl;
  EOUniformCrossover<Chrom> uxover;
  uxover(chrom0, chrom1);
  cout << "UniformCrossover: " << chrom0 << "  " << chrom1 << endl;

  gettimeofday(&t2, NULL);
  double elapsedTime = (t2.tv_sec - t1.tv_sec);      // sec to ms
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1e6;   // us to ms
  cout <<  elapsedTime << endl;

  return 0;
}

