#ifndef AND_H
#define AND_H

#include "NAND.h"
#include "NOT.h"

class AND : public Gate {
	
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
        IO outputNAND = m_NAND.Process(in);
        return m_NOT.Process( outputNAND );
    }

};

#endif
