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
	virtual inline IO Process( IO in ) {
        IO input = { in[0], in[0] };
        return m_NAND.Process(input);
    }
    
};

#endif
