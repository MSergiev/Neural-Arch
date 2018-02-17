#ifndef MUX_H
#define MUX_H

#include "NOT.h"
#include "NAND.h"

class MUX : public Gate {
	
private:
	NOT m_NOT;
	NAND m_NAND;
// 	OR m_OR;

public: 

	// Constructor
	MUX() : Gate("MUX",3,1,"ABS","O") {}

	// Destuctor
	~MUX() {}

    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputNAND1 = 0;
        bitset inputNOT = get(in,0);
        add( inputNAND1, m_NOT.Process(inputNOT) );
        add( inputNAND1, get(in,2) );
        
        bitset inputNAND2 = 0;
        add( inputNAND2, get(in,0) );
        add( inputNAND2, get(in,1) );
        
        bitset inputNAND3 = 0;
        add( inputNAND3, m_NAND.Process( inputNAND1 ) );
        add( inputNAND3, m_NAND.Process( inputNAND2 ) );
        
        return m_NAND.Process( inputNAND3 );
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset output = 0;
        
        for( unsigned char i = 0; i < ARCH; ++i ) {
            bitset input = 0;
            for( unsigned char j = 0; j < INPUTS-1; ++j ) {
                add( input, get(in[j], ARCH-i-1) );
            }
			add( input, get(in[INPUTS-1], 0) );
            add( output, Process(input) );
        }
        
        return output; 
        
    }

};

#endif
