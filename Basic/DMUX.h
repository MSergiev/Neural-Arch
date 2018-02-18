#ifndef DMUX_H
#define DMUX_H

#include "NOT.h"
#include "AND.h"

class DMUX : public Gate {
	
private:

	NOT m_NOT;
	AND m_AND;

public: 

	// Constructor
	DMUX() : Gate("DMUX",2,2,"IS","AB") {}

	// Destuctor
	~DMUX() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset output = 0;
        
        bitset inputAND = 0;
        add( inputAND, get(in,1) );
        add( inputAND, m_NOT.Process( get(in,0) ) );
        add( output, m_AND.Process(inputAND) );
        add( output, m_AND.Process(in) );
        
        return output;
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
