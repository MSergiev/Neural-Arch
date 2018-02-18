#ifndef OR_H
#define OR_H

#include "NOR.h"
#include "NOT.h"

class OR : public Gate {
	
private:
	NOR m_NOR;
	NOT m_NOT;

public: 

	// Constructor
	OR() : Gate("OR",2,1,"AB","O") {}

	// Destuctor
	~OR() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputNOT = m_NOR.Process(in);
        return m_NOT.Process( inputNOT );
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
