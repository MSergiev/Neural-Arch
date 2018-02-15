#ifndef XOR_H
#define XOR_H

#include "NAND.h"
#include "OR.h"
#include "AND.h"

class XOR  : public Gate {
	
private:
	NAND m_NAND;
	OR m_OR;
	AND m_AND;

public: 

	// Constructor
	XOR() : Gate("XOR",2,1,"AB","O") {}

	// Destuctor
	~XOR() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputAND = 0;
        add( inputAND, m_NAND.Process(in) );
        add( inputAND, m_OR.Process(in) );
        return m_AND.Process( inputAND );
    }

};

#endif
