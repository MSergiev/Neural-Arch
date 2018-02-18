#ifndef MUX4WAY_H
#define MUX4WAY_H

#include "MUX.h"

class MUX4WAY : public Gate {
	
private:
    
	MUX m_MUX;

public: 

	// Constructor
	MUX4WAY() : Gate("MUX4WAY",6,1,"ABCDSS","O") {}

	// Destuctor
	~MUX4WAY() {}

    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputMUX1 = 0;
        add( inputMUX1, get(in,5) );
        add( inputMUX1, get(in,4) );
        add( inputMUX1, get(in,0) );
        
        bitset inputMUX2 = 0;
        add( inputMUX2, get(in,3) );
        add( inputMUX2, get(in,2) );
        add( inputMUX2, get(in,0) );
        
        bitset inputMUX3 = 0;
        add( inputMUX3, m_MUX.Process(inputMUX1) );
        add( inputMUX3, m_MUX.Process(inputMUX2) );
        add( inputMUX3, get(in,1) );
        
        return m_MUX.Process( inputMUX3 );
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
