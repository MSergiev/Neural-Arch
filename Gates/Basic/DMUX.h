#ifndef DMUX_H
#define DMUX_H

#include "NOT.h"
#include "AND.h"

class DMUX : public Gate {

public:

    static const byte I = 0;    // Input
    static const byte S = 1;    // Selection bit
    
    static const byte A = 0;    // Output A
    static const byte B = 1;    // Output B
    
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
        // Negate selection bit
        IO inputNOT = m_NOT.CreateInputIO();
        inputNOT[NOT::I] = in[S];
        
        // AND input A and negated S
        IO inputAND = m_AND.CreateInputIO();
        inputAND[AND::A] = in[I];
        inputAND[AND::B] = m_NOT.Process(inputNOT)[NOT::O];    
        
        IO output = CreateOutputIO();
        output[A] = m_AND.Process(inputAND)[AND::O];
        output[B] = m_AND.Process(in)[AND::O];
        return output;
    }

};

#endif
