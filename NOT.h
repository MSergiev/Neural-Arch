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
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
