#ifndef ADDER_H
#define ADDER_H

#include "FA.h"

class ADDER : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output

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
        BUS output = CreateOutputBUS();
        IO outputADDER = m_FA.CreateOutputIO();
        
        for( unsigned char i = 0; i < ARCH; ++i ) {
            IO input = m_FA.CreateInputIO();
            input[FA::A] = in[A][ARCH-1-i];
            input[FA::B] = in[B][ARCH-1-i];
            input[FA::CI] = outputADDER[FA::C];
            outputADDER = m_FA.Process(input);
            output[O][i] = outputADDER[FA::O];
        }
        
        ReverseIO( output[O] );
        return output; 
    }

};

#endif
