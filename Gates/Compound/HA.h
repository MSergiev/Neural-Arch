#ifndef HA_H
#define HA_H

#include "../Basic/XOR.h"
#include "../Basic/AND.h"

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
	virtual inline IO Process( IO in ) {
        IO output = {  m_XOR.Process(in)[0], m_AND.Process(in)[0] };
        return output;
    }

};

#endif
