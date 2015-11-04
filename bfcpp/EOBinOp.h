//-----------------------------------------------------------------------------
// EOBinOp.h
//-----------------------------------------------------------------------------

#ifndef _EOBINOP_H
#define _EOBINOP_H

//-----------------------------------------------------------------------------

#ifdef _MSC_VER
#define min _MIN
#endif

#include <random>

#include "EOBase.h"
#include "EO.h"

#include "EOBin.h"
#include <functional>
#include <algorithm>

//-----------------------------------------------------------------------------
/** 
 * EOBitFlip: operator for binary chromosomes 
 * Changes one bit in the chromosome every time that is aplied
 */
//-----------------------------------------------------------------------------

template<class fitness = float> class EOBitFlip: public MonOp< EOBin<fitness> >
{
 public:
  typedef EOBin<fitness> Chrom;

  ///
  EOBitFlip( float _priority = 1 ): 
    MonOp< Chrom > ( _priority ) {}
  
  ///
  void operator()( Chrom& chrom ) const
    {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<int> rng_dist(0, chrom.size() - 1 ) ;
      applyAt( chrom, rng_dist(rng) );
    }
  
  ///
  void applyAt( Chrom& chrom, unsigned bit, unsigned = 0 ) const
    {
      if (chrom[bit])
	chrom[bit] = false;
      else
	chrom[bit] = true;
    }
};

//-----------------------------------------------------------------------------
/** 
 * EORandom: operator for binary chromosomes 
 * random change for all bits in the chromosome
 */
//-----------------------------------------------------------------------------

template<class fitness = float> class EORandom: public MonOp< EOBin<fitness> >
{
 public:
  typedef EOBin<fitness> Chrom;

  ///
  EORandom( float _priority = 1 ): 
    MonOp< Chrom > ( _priority ) {}

  ///  
  void operator()( Chrom& chrom ) const
    {
      for (unsigned bit = 0; bit < chrom.size(); bit++)
	applyAt( chrom, bit );
    }

  ///
  void applyAt( Chrom& chrom, unsigned bit, unsigned = 0 ) const {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<int> rng_dist(0, 10 ) ;
      
	   if ( rng_dist(rng)%2)
	     chrom[bit] = true;
     else
	     chrom[bit] = false;
  }

};


//-----------------------------------------------------------------------------
/** 
 * EOMutation: operator for binary chromosomes 
 * Mutation change for all bits in the chromosome
 */
//-----------------------------------------------------------------------------

template<class fitness = float> 
class EOMutation: public MonOp< EOBin<fitness> >
{
 public:
  typedef EOBin<fitness> Chrom;

  ///
  EOMutation( float _rate, float _priority = 1 ): 
    MonOp< Chrom > ( _priority ), rate( _rate ) {}
  
  ///
  void operator()( Chrom& chrom ) const
    {
      for (unsigned bit = 0; bit < chrom.size(); bit++)
	applyAt( chrom, bit );
    }

  ///
  void applyAt( Chrom& chrom, unsigned bit, unsigned = 0 ) const {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<int> rng_dist(0, 10 ) ;
      int tmp = (int) (rate * 10.0);
      if (rng_dist(rng) < tmp)
	       chrom[bit] = !chrom[bit];
  }

 private:
  float rate; /// rate of mutation
};


#endif 
