#ifndef FA_H
#define FA_H

#include "HA.h"
#include "../Basic/XOR.h"

class FA : public Gate {

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
        IO inputHA1 = { in[0], in[1] };
        IO outputHA1 = m_HA.Process( inputHA1 );
        
        IO inputHA2 = { outputHA1[0], in[2] };
        IO outputHA2 = m_HA.Process( inputHA2 );
        
        IO inputXOR = { outputHA1[1], outputHA2[1] };
        IO output = { outputHA2[0], m_XOR.Process(inputXOR)[0] };
        return output;
    }

};

#endif
