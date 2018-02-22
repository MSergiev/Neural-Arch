#ifndef AND_H
#define AND_H

#include "NAND.h"
#include "NOT.h"

class AND : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output
    
private:
    
	NAND m_NAND;
	NOT m_NOT;

public: 

	// Constructor
	AND() : Gate("AND",2,1,"AB","O") {}

	// Destuctor
	~AND() {}
	
    // Processing method
	virtual inline IO Process( IO in ) {
        // Perform NAND
        IO outputNAND = m_NAND.Process(in);
        
        // Negate NAND
        IO output = CreateOutputIO();
        output[O] = m_NOT.Process( outputNAND )[NOT::O];
        return output;
    }

};

#endif
