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
	virtual inline IO Process( IO in ) {
        IO inputMUX1 = { in[0], in[1], in[4] };
        IO inputMUX2 = { in[2], in[3], in[4] };
        IO inputMUX3 = { m_MUX.Process(inputMUX1)[0], m_MUX.Process(inputMUX2)[0], in[5] };
        return m_MUX.Process( inputMUX3 );
    }

};

#endif
