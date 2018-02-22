#ifndef OR_H
#define OR_H

#include "NOR.h"
#include "NOT.h"

class OR : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output
	
private:
	NOR m_NOR;
	NOT m_NOT;

public: 

	// Constructor
	OR() : Gate("OR",2,1,"AB","O") {}

	// Destuctor
	~OR() {}
	
    // Processing method
	virtual inline IO Process( IO in ) {
        // Perform NOR
        IO inputNOT = m_NOT.CreateInputIO();
        inputNOT[NOT::I] = m_NOR.Process(in)[NOR::O];
        
        // Negate NOR
        IO output = CreateOutputIO();
        output[O] = m_NOT.Process( inputNOT )[NOT::O];
        return output;
    }
    
};

#endif
