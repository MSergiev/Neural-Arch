#ifndef XOR_H
#define XOR_H

#include "NAND.h"
#include "OR.h"
#include "AND.h"

class XOR  : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output

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
        // Perform NAND and OR
        IO inputAND = m_AND.CreateInputIO();
        inputAND[AND::A] = m_NAND.Process(in)[NAND::O];
        inputAND[AND::B] = m_OR.Process(in)[OR::O];
        
        // Perform AND
        IO output( OUTPUTS, 0 );
        output[O] = m_AND.Process( inputAND )[AND::O];
        return output;
    }

};

#endif
