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
	virtual inline bitset Process( bitset in ) {
        bitset outputNAND = m_NAND.Process(in);
        return m_NOT.Process( outputNAND );
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }
};

#endif
