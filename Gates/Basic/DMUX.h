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
	virtual inline IO Process( IO in ) {        
        IO inputNOT = { in[1] };
        IO inputAND = { in[0], m_NOT.Process(inputNOT)[0] };        
        IO output = { m_AND.Process(inputAND)[0], m_AND.Process(in)[0] };
        return output;
    }

};

#endif
