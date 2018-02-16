#ifndef NOR_H
#define NOR_H

#include "AND.h"
#include "NOT.h"

class NOR : public Gate {
	
private:
	AND m_AND;
	NOT m_NOT;

public: 

	// Constructor
	NOR() : Gate("NOR",2,1,"AB","O") {}

	// Destuctor
	~NOR() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputAND = 0;
        
        for( unsigned char i = 0; i < 2; ++i ) {
            bitset inputNOT = get(in,i);
            add( inputAND, m_NOT.Process(inputNOT) );
        }
        
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
