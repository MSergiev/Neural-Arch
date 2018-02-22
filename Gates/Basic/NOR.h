#ifndef NOR_H
#define NOR_H

#include "AND.h"
#include "NOT.h"

class NOR : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output
    
private:
	AND m_AND;
	NOT m_NOT;

public: 

	// Constructor
	NOR() : Gate("NOR",2,1,"AB","O") {}

	// Destuctor
	~NOR() {}
	
    // Processing method
	virtual inline IO Process( IO in ) {
        // Negate input A
        IO inputNOT1 = m_NOT.CreateInputIO();
        inputNOT1[NOT::I] = in[A]; 
        
        // Negate input B
        IO inputNOT2 = m_NOT.CreateInputIO();
        inputNOT2[NOT::I] = in[B]; 
        
        // Perform AND
        IO inputAND = m_AND.CreateInputIO();
        inputAND[AND::A] = m_NOT.Process(inputNOT1)[NOT::O];
        inputAND[AND::B] = m_NOT.Process(inputNOT2)[NOT::O];
        
        IO output = CreateOutputIO();
        output[O] = m_AND.Process( inputAND )[AND::O];
        return output;
    }

};

#endif
