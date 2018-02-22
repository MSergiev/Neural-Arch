#ifndef FA_H
#define FA_H

#include "HA.h"
#include "../Basic/XOR.h"

class FA : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte CI = 2;   // Carry input
    
    static const byte O = 0;    // Output
    static const byte C = 1;    // Carry

private:

	HA m_HA;
	XOR m_XOR;

public: 

	// Constructor
	FA() : Gate("FA",3,2,"ABC","RC") {}

	// Destuctor
	~FA() {}

	// Processing method
	virtual inline IO Process( IO in ) {
        // Add inputs A and B
        IO inputHA1 = m_HA.CreateInputIO();
        inputHA1[HA::A] = in[A];
        inputHA1[HA::B] = in[B];
        IO outputHA1 = m_HA.Process( inputHA1 );
        
        // Add HA result and carry in bit
        IO inputHA2 = m_HA.CreateInputIO();
        inputHA2[HA::A] = outputHA1[HA::O];
        inputHA2[HA::B] = in[CI];
        IO outputHA2 = m_HA.Process( inputHA2 );
        
        // XOR previous additions to calculate carry out bit
        IO inputXOR = m_XOR.CreateInputIO();
        inputXOR[XOR::A] = outputHA1[HA::C];
        inputXOR[XOR::B] = outputHA2[HA::C];
        
        IO output = CreateOutputIO();
        output[O] = outputHA2[HA::O];
        output[C] = m_XOR.Process(inputXOR)[XOR::O];
        return output;
    }

};

#endif
