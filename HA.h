#ifndef HA_H
#define HA_H

#include "XOR.h"
#include "AND.h"

class HA : public Gate {
	
private:

	XOR m_XOR;
	AND m_AND;

public: 

	// Constructor
	HA() : Gate("HA",2,2,"AB","RC") {}

	// Destuctor
	~HA() {}
	
	// Processing method
	virtual inline bitset Process( bitset in ) {
        bitset output = 0;
        add( output, m_XOR.Process(in) );
        add( output, m_AND.Process(in) );
        return output;
    }

};

#endif
