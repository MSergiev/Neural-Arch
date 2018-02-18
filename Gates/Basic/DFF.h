#ifndef DFF_H
#define DFF_H

#include "AND.h"
#include "NOT.h"

class DFF  : public Gate {
	
private:
    
	AND m_AND;
    NOT m_NOT;
    bitset output;
    
public: 

	// Constructor
	DFF() : Gate("DFF",2,1,"DC","O") {}

	// Destuctor
	~DFF() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        output = m_AND.Process(in);
        
//         bitset inputNAND1 = 0;
//         add( inputNAND1, get(in,0) );
//         add( inputNAND1, get(in,1) );
//         bitset outputNAND1 = m_NAND.Process(inputNAND1);
//         
//         bitset inputNAND2 = 0;
//         add( inputNAND2, get(in,0) );
//         add( inputNAND2, m_NOT.Process(get(in,1)) );
//         bitset outputNAND2 = m_NAND.Process(inputNAND2);
//         
//         bitset output = 0;
        
        return output;
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset output = 0;
        
        for( unsigned char i = 0; i < ARCH; ++i ) {
            bitset input = 0;
            for( unsigned char j = 0; j < INPUTS; ++j ) {
                add( input, get(in[j], ARCH-i-1) );
            }
            add( output, Process(input) );
        }
        
        return output; 
        
    }

};

#endif
