
#ifndef _EOBIN_H
#define _EOBIN_H

//-----------------------------------------------------------------------------

#include <random>

#include <vector>
typedef vector<bool> bit_vector;

#include <iostream>
#include <strstream>    // for strstream
#include <iterator>
#include <stdexcept>    // for out_of_range

using namespace std;

#include "EOBase.h"
#include "EO.h"


//-----------------------------------------------------------------------------

/** 
 Binary chromosome for EO; this is the classical bitstring chromosome
 described by Holland, Goldberg and others.

 @author Gustavo Romero Lopez
 */
template<class fitnessT = float>
class EOBin: public EO<bool, fitnessT>, public bit_vector
{
 public:
  /// constructor
  EOBin(  const string& _ID = "", unsigned _num_genes = 1, unsigned _geneSize = 1 ):
    EO<bool, fitnessT> (_ID ), 
    bit_vector( _num_genes * _geneSize ), 
    repGeneSize( _geneSize ) {}
  
  /// copy constructor
  EOBin( const EOBin& eobin ):
    EO<bool, fitnessT> ( eobin ), bit_vector( eobin ), 
    repGeneSize( eobin.repGeneSize ) {}

  /// Operator =
  const EOBin& operator = ( const EOBin& _eobin ) {
	  if ( this  != &_eobin ) {
		  // Copy bit_vector part
		  bit_vector::operator = (_eobin );

		  // Change EO part
		  EO<bool, fitnessT>::operator = (_eobin);

		  // Change this part
		  repGeneSize = _eobin.repGeneSize;
	  }
	  return *this;
  }

  /// destructor
  ~EOBin() {}
  
  /// 
  void initialize() {
    int myseed = time(NULL);
    std::default_random_engine rng(myseed);
    std::uniform_int_distribution<int> rng_dist(0, length()-1 ) ;
    for ( unsigned j = 0; j < length(); j++ )  {
      unsigned oo = rng_dist(rng);
      //cout << "DEBUG oo="<<oo;
      writeGene( j, (oo%2) ? true: false );
    }
    return ;
  }

  /// 
  bool readGene( unsigned _i ) const {
    if ( _i >= length() ) 
      throw out_of_range( "out_of_range when reading gene");
    return ( *this )[ _i ];
  }
  
  ///
  void writeGene( unsigned _i, bool _val ) {
    if ( _i < length() ) {
      (*this)[_i] = _val;
    } else 
      throw out_of_range( "out_of_range when writing gene");
  }
  
  ///
  void insertGene( unsigned _i, bool _val ) {
    if (_i <= this->size() ) {
      insert( begin() + _i, _val );
    } else 
      throw out_of_range( "out_of_range when inserting gene");
  };
  
  ///
  void deleteGene( unsigned _i ) {
    if (_i < this->size() ) {
      erase( begin() + _i );
    } else 
      throw out_of_range( "out_of_range when deleting gene");
  };
  
  ///
  unsigned length() const { return size();}
  
  ///
  unsigned numGenes() const {
      return size() / geneSize();
    }

  /// number of bits per gen
  unsigned geneSize() const {
      return repGeneSize;
    }
  

 private:
  unsigned repGeneSize;
};

/// 
template< class fitT>
ostream& operator<<( ostream& os, const EOBin<fitT> & chrom )  {
    copy( chrom.begin(), chrom.end(), ostream_iterator<bool>(os));
    return os;
};
  

#include "EOFactory.h"

/// Factory method
template<class T, class fitT = float>
class EOBinFactory: public EOFactory< EOBin<fitT> >{
 public:
	 typedef EOBin<fitT> Chrom;

  /// constructor
  EOBinFactory(  const string& _prefix, unsigned _numGenes, unsigned _bitsXGen ):
    prefix( _prefix ), counter( 0 ), numGenes(_numGenes), 
    numBits( _bitsXGen) {};

  /// destructor
  ~EOBinFactory() {}
  
  ///
  virtual unsigned length() const { return numBits*numGenes;}

  /// One of the factory methods: creates a random EO
  virtual Chrom* make() {
    string thisID= newID();
    
    /*
    Uniform< float > on_off( -1, 1 );
    EOBin<fitT>* newEO = new EOBin<fitT>( thisID, numGenes, numBits );
    // Assigns values randomly
    for ( unsigned j = 0; j < newEO->length(); j++ )  {
      float oo = on_off( );
      newEO->writeGene( j, (oo > 0) ? true: false );
    }
    */

    EOBin<fitT>* newEO = new EOBin<fitT>( thisID, numGenes, numBits );
    int myseed = time(NULL);
    std::default_random_engine rng(myseed);
    std::uniform_int_distribution<int> rng_dist(0, newEO->length()-1 ) ;
    for ( unsigned j = 0; j < newEO->length(); j++ )	{
      unsigned oo = rng_dist(rng);
      cout << "DEBUG oo="<<oo;
      newEO->writeGene( j, (oo%2) ? true: false );
    }
    return newEO;
  };
    

  /** One of the factory methods: creates an EOBin from another
	with an unary operator
	*/
  Chrom* make( const Chrom& _eo, 				
	  const MonOp<Chrom>* _eop = 0) {
    string thisID= newID();
    Chrom* newEO = new Chrom( _eo );
	if ( _eop ) {	// Applies genetic operator
		(*_eop)(*newEO );
	}
	newEO->ID( thisID );
    return newEO;
  };

 
private:
	 /// Instance variables
	string prefix;	
	unsigned long counter;
	unsigned numGenes;
	unsigned numBits;


	/// Real function: creates a new ID
	string newID (){
	  //	  char IDbuf[IDBUFLEN] = "";// strstreams don't work properly
	  // sprintf( IDbuf, "%lu", counter++ );
	  strstream s;
	  s << counter++ << "\0" ;
	  string tmp;
	  s >> tmp;
	  string thisID= prefix + tmp;
	  return thisID;
	}
};


#endif 
