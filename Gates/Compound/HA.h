#ifndef HA_H
#define HA_H

#include "../Basic/XOR.h"
#include "../Basic/AND.h"

class HA : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output
    static const byte C = 1;    // Carry
    
private:

	XOR m_XOR;
	AND m_AND;

public: 

	// Constructor
	HA() : Gate("HA",2,2,"AB","OC") {}

	// Destuctor
	~HA() {}
	
	// Processing method
	virtual inline IO Process( IO in ) {
        IO output = CreateOutputIO();
        output[O] = m_XOR.Process(in)[XOR::O];
        output[C] = m_AND.Process(in)[AND::O];
        return output;
    }

};

#endif
