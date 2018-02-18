#ifndef XOR_H
#define XOR_H

#include "NAND.h"
#include "OR.h"
#include "AND.h"

class XOR  : public Gate {
	
private:
	NAND m_NAND;
	OR m_OR;
	AND m_AND;

public: 

	// Constructor
	XOR() : Gate("XOR",2,1,"AB","O") {}

	// Destuctor
	~XOR() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputAND = 0;
        add( inputAND, m_NAND.Process(in) );
        add( inputAND, m_OR.Process(in) );
        return m_AND.Process( inputAND );
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset output = 0;
        
        for( unsigned char i = 0; i < ARCH; ++i ) {
            bitset input = 0;
            for( unsigned char j = 0; j < INPUTS; ++j ) {
                add( input, get(in[j], ARCH-i-1) );
            }
            add( output, Process(input) );
        }
        
        return output; 
        
    }

};

#endif
