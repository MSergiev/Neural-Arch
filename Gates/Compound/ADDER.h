#ifndef ADDER_H
#define ADDER_H

#include "FA.h"

class ADDER : public Gate {

private:

	FA m_FA;

public: 

	// Constructor
	ADDER() : Gate("ADDER",2,1,"AB","O") {}

	// Destuctor
	~ADDER() {}

	// Processing method
	virtual inline IO Process( IO in ) { 
        return m_FA.Process(in); 
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) override {
        
        BUS output = { IO() };
        
        IO outputADDER = { 0, 0 };
        for( unsigned char i = 0; i < ARCH; ++i ) {
            IO input = { outputADDER[1], in[1][ARCH-1-i], in[0][ARCH-1-i] };
            
            outputADDER = m_FA.Process(input);
            output[0].push_back( outputADDER[0] );
        }
        
        ReverseIO( output[0] );
        return output; 
        
    }

};

#endif
