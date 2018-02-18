#ifndef DMUX4WAY_H
#define DMUX4WAY_H

#include "DMUX.h"

class DMUX4WAY : public Gate {

private:
    
	DMUX m_DMUX;

public: 

    // Constructor
    DMUX4WAY() : Gate("DMUX4WAY",3,4,"ISS","ABCD") {}

    // Destuctor
    ~DMUX4WAY() {}

    // Processing method
    virtual inline bitset Process( bitset in ) {
        bitset inputDMUX1 = 0;
        add( inputDMUX1, get(in,2) );   // I
        add( inputDMUX1, get(in,0) );   // S1
        bitset outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        bitset inputDMUX2 = 0;
        add( inputDMUX2, get(outputDMUX1,0) );  // DMUX1_A
        add( inputDMUX2, get(in,1) );   // S2
        bitset outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        bitset inputDMUX3 = 0;
        add( inputDMUX3, get(outputDMUX1,1) );  // DMUX1_B
        add( inputDMUX3, get(in,1) );   // S2
        bitset outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        bitset output = 0;
        add( output, get( outputDMUX3, 1) );
        add( output, get( outputDMUX2, 1) );
        add( output, get( outputDMUX3, 0) );
        add( output, get( outputDMUX2, 0) );
        return output;
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
