#ifndef NOR_H
#define NOR_H

#include "AND.h"
#include "NOT.h"

class NOR : public Gate {
	
private:
	AND m_AND;
	NOT m_NOT;

public: 

	// Constructor
	NOR() : Gate("NOR",2,1,"AB","O") {}

	// Destuctor
	~NOR() {}
	
    // Processing method
	virtual inline IO Process( IO in ) {
        IO inputAND;
        
        for( unsigned char i = 0; i < 2; ++i ) {
            IO inputNOT;
            inputNOT.push_back( in[i] );
            inputAND.push_back( m_NOT.Process(inputNOT)[0] );
        }
        
        return m_AND.Process( inputAND );
    }

};

#endif
