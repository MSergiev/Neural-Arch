#ifndef OR_H
#define OR_H

#include "NOR.h"
#include "NOT.h"

class OR : public Gate {
	
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
        IO inputNOT = m_NOR.Process(in);
        return m_NOT.Process( inputNOT );
    }
    
};

#endif
