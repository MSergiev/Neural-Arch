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
	virtual inline IO Process( IO in ) {
        IO inputAND;
        inputAND.push_back( m_NAND.Process(in)[0] );
        inputAND.push_back( m_OR.Process(in)[0] );
        return m_AND.Process( inputAND );
    }

};

#endif
