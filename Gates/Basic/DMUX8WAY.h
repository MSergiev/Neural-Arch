#ifndef DMUX8WAY_H
#define DMUX8WAY_H

#include "DMUX.h"
#include "DMUX4WAY.h"

class DMUX8WAY : public Gate {

private:
    
    DMUX m_DMUX;
    DMUX4WAY m_DMUX4WAY;

public: 

    // Constructor
    DMUX8WAY() : Gate("DMUX8WAY",4,8,"ISSS","ABCDEFGH") {}

    // Destuctor
    ~DMUX8WAY() {}

    // Processing method
    virtual inline bitset Process( bitset in ) {
        bitset inputDMUX4WAY = 0;
        add( inputDMUX4WAY, get(in,3) );   // I
        add( inputDMUX4WAY, get(in,1) );   // S2
        add( inputDMUX4WAY, get(in,0) );   // S1
        bitset outputDMUX4WAY = m_DMUX4WAY.Process( inputDMUX4WAY );
        
        bitset inputDMUX1 = 0;
        add( inputDMUX1, get(outputDMUX4WAY,0) );  // DMUX1_A
        add( inputDMUX1, get(in,2) );   // S2
        bitset outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        bitset inputDMUX2 = 0;
        add( inputDMUX2, get(outputDMUX4WAY,1) );  // DMUX1_A
        add( inputDMUX2, get(in,2) );   // S2
        bitset outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        bitset inputDMUX3 = 0;
        add( inputDMUX3, get(outputDMUX4WAY,2) );  // DMUX1_A
        add( inputDMUX3, get(in,2) );   // S2
        bitset outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        bitset inputDMUX4 = 0;
        add( inputDMUX4, get(outputDMUX4WAY,3) );  // DMUX1_A
        add( inputDMUX4, get(in,2) );   // S2
        bitset outputDMUX4 = m_DMUX.Process( inputDMUX4 );
        
        bitset output = 0;
        add( output, get( outputDMUX4, 1) );
        add( output, get( outputDMUX3, 1) );
        add( output, get( outputDMUX2, 1) );
        add( output, get( outputDMUX1, 1) );
        add( output, get( outputDMUX4, 0) );
        add( output, get( outputDMUX3, 0) );
        add( output, get( outputDMUX2, 0) );
        add( output, get( outputDMUX1, 0) );
        return output;
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }

};

#endif
