#ifndef FA_H
#define FA_H

#include "HA.h"
#include "OR.h"

class FA : public Gate {

private:

	HA m_HA;
	XOR m_OR;

public: 

	// Constructor
	FA() : Gate("FA",3,2,"ABC","RC") {}

	// Destuctor
	~FA() {}

	// Processing method
	virtual inline bitset Process( bitset in ) {
        
        bitset inputHA1 = 0;
        add( inputHA1, get(in, 2) );    // A
        add( inputHA1, get(in, 1) );    // B
        bitset outputHA1 = m_HA.Process( inputHA1 );
        
        bitset inputHA2 = 0;
        add( inputHA2, get(in, 0) );    // C
        add( inputHA2, get(outputHA1, 1) ); //HA1_R
        bitset outputHA2 = m_HA.Process( inputHA2 );
        
        bitset inputOR = 0;
        add( inputOR, get(outputHA1, 0) );  // HA1_C
        add( inputOR, get(outputHA2, 0) );  // HA2_C
        
        bitset output = 0;
        add( output, get(outputHA2, 1) );   // HA2_R
        add( output, m_OR.Process( inputOR ) ); // OR_O
        
        return output;
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
