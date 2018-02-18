#ifndef AND_H
#define AND_H

#include "NAND.h"
#include "NOT.h"

class AND : public Gate {
	
private:
    
	NAND m_NAND;
	NOT m_NOT;

public: 

	// Constructor
	AND() : Gate("AND",2,1,"AB","O") {}

	// Destuctor
	~AND() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset outputNAND = m_NAND.Process(in);
        return m_NOT.Process( outputNAND );
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
