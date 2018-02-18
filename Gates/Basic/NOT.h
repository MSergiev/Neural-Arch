#ifndef NOT_H
#define NOT_H

#include "NAND.h"

class NOT : public Gate {
	
private:
	NAND m_NAND;

public: 

	// Constructor
	NOT() : Gate("NOT",1,1,"I","O") {}

	// Destuctor
	~NOT() {}

	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset input = (in<<1)|in;
        return m_NAND.Process(input);
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
