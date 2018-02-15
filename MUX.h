#ifndef MUX_H
#define MUX_H

#include "NOT.h"
#include "OR.h"
#include "AND.h"

class MUX : public Gate {
	
private:
	NOT m_NOT;
	AND m_AND;
	OR m_OR;

public: 

	// Constructor
	MUX() : Gate("MUX",3,1,"ABS","O") {}

	// Destuctor
	~MUX() {}

    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputAND1 = 0;
        add( inputAND1, get(in,0) );
        add( inputAND1, m_NOT.Process(get(in,2)) );
        bitset inputAND2 = 0;
        add( inputAND2, get(in,1) );
        add( inputAND2, get(in,2) );
        bitset inputOR = 0;
        add( inputOR, m_AND.Process( inputAND1 ) );
        add( inputOR, m_AND.Process( inputAND2 ) );
        return m_OR.Process( inputOR );
    }

};

#endif
