#ifndef MUX8WAY_H
#define MUX8WAY_H

#include "MUX.h"
#include "MUX4WAY.h"

class MUX8WAY : public Gate {
	
private:
    
	MUX m_MUX;
	MUX4WAY m_MUX4WAY;

public: 

	// Constructor
	MUX8WAY() : Gate("MUX8WAY",11,1,"ABCDEFGHSSS","O") {}

	// Destuctor
	~MUX8WAY() {}

    // Processing method
	virtual inline bitset Process( bitset in ) {
        bitset inputMUX4WAY1 = 0;
        add( inputMUX4WAY1, get(in,10) );
        add( inputMUX4WAY1, get(in,9) );
        add( inputMUX4WAY1, get(in,8) );
        add( inputMUX4WAY1, get(in,7) );
        add( inputMUX4WAY1, get(in,1) );
        add( inputMUX4WAY1, get(in,0) );
        
        bitset inputMUX4WAY2 = 0;
        add( inputMUX4WAY2, get(in,6) );
        add( inputMUX4WAY2, get(in,5) );
        add( inputMUX4WAY2, get(in,4) );
        add( inputMUX4WAY2, get(in,3) );
        add( inputMUX4WAY2, get(in,1) );
        add( inputMUX4WAY2, get(in,0) );
        
        bitset inputMUX = 0;
        add( inputMUX, m_MUX4WAY.Process(inputMUX4WAY1) );
        add( inputMUX, m_MUX4WAY.Process(inputMUX4WAY2) );
        add( inputMUX, get(in,2) );
        
        return m_MUX.Process( inputMUX );
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
