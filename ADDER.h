#ifndef ADDER_H
#define ADDER_H

#include "FA.h"

class ADDER : public Gate {

private:

    HA m_HA;
	FA m_FA;

public: 

	// Constructor
	ADDER() : Gate("ADDER",2,1,"AB","O") {}

	// Destuctor
	~ADDER() {}

	// Processing method
	virtual inline bitset Process( bitset in ) { 
        return m_HA.Process(in); 
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset output = 0;
        
        bitset outputADDER = 0;
        for( unsigned char i = 0; i < ARCH; ++i ) {
            bitset input = 0;
            for( unsigned char j = 0; j < INPUTS; ++j ) {
                add( input, get(in[j], i) );
            }
            add( input, get( outputADDER, 0 ) );
            
            outputADDER = m_FA.Process(input);
            
            add( output, get(outputADDER, 1) );
        }
        reverse(output);
        return output; 
        
    }

};

#endif
