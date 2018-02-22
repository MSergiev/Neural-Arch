#ifndef MUX8WAY_H
#define MUX8WAY_H

#include "MUX.h"
#include "MUX4WAY.h"

class MUX8WAY : public Gate {
	
private:
    
	MUX m_MUX;
	MUX4WAY m_MUX4WAY;

public: 

	// Constructor
	MUX8WAY() : Gate("MUX8WAY",11,1,"ABCDEFGHSSS","O") {}

	// Destuctor
	~MUX8WAY() {}

    // Processing method
	virtual inline IO Process( IO in ) {
        IO inputMUX4WAY1 = { in[0], in[1], in[2], in[3], in[8], in[9] };
        IO inputMUX4WAY2 = { in[4], in[5], in[6], in[7], in[8], in[9] };
        IO inputMUX = { m_MUX4WAY.Process(inputMUX4WAY1)[0], m_MUX4WAY.Process(inputMUX4WAY2)[0], in[10] };
        return m_MUX.Process( inputMUX );
    }

};

#endif
