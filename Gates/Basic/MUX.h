#ifndef MUX_H
#define MUX_H

#include "NOT.h"
#include "NAND.h"

class MUX : public Gate {
	
private:
    
	NOT m_NOT;
	NAND m_NAND;

public: 

	// Constructor
	MUX() : Gate("MUX",3,1,"ABS","O") {}

	// Destuctor
	~MUX() {}

    // Processing method
	virtual inline IO Process( IO in ) {
        IO inputNOT = { in[2] };
        IO inputNAND1 = { m_NOT.Process(inputNOT)[0], in[0] };        
        IO inputNAND2 = { in[2], in[1] };        
        IO inputNAND3 = { m_NAND.Process(inputNAND1)[0], m_NAND.Process(inputNAND2)[0] };
        IO output = m_NAND.Process( inputNAND3 );
        return output;
    }
};

#endif
