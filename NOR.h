#ifndef NOR_H
#define NOR_H

#include "AND.h"
#include "NOT.h"

class NOR : public Gate {
	
private:
	AND m_AND;
	NOT m_NOT;

public: 

	// Constructor
	NOR() : Gate("NOR",2,1,"AB","O") {}

	// Destuctor
	~NOR() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputAND = 0;
        add( inputAND, m_NOT.Process(get(in,0)) );
        add( inputAND, m_NOT.Process(get(in,1)) );
        return m_AND.Process( inputAND );
    }

};

#endif
