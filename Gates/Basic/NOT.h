#ifndef NOT_H
#define NOT_H

#include "NAND.h"

class NOT : public Gate {

public:
    
    static const byte I = 0;    // Input
    
    static const byte O = 0;    // Output

private:
	NAND m_NAND;

public: 

	// Constructor
	NOT() : Gate("NOT",1,1,"I","O") {}

	// Destuctor
	~NOT() {}

	
    // Processing method
	virtual inline IO Process( IO in ) {
        IO input = m_NAND.CreateInputIO();
        input[NAND::A] = in[I];
        input[NAND::B] = in[I];
        
        IO output( OUTPUTS, 0 );
        output[O] = m_NAND.Process(input)[NAND::O];
        return output;
    }
    
};

#endif
