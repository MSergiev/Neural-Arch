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
    virtual inline IO Process( IO in ) {
        IO inputDMUX4WAY = { in[0], in[2], in[3] };
//         add( inputDMUX4WAY, get(in,3) );   // I
//         add( inputDMUX4WAY, get(in,1) );   // S2
//         add( inputDMUX4WAY, get(in,0) );   // S1
        IO outputDMUX4WAY = m_DMUX4WAY.Process( inputDMUX4WAY );
        
        IO inputDMUX1 = { outputDMUX4WAY[0], in[1] };
//         add( inputDMUX1, get(outputDMUX4WAY,0) );  // DMUX1_A
//         add( inputDMUX1, get(in,2) );   // S2
        IO outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        IO inputDMUX2 = { outputDMUX4WAY[1], in[1] };
//         add( inputDMUX2, get(outputDMUX4WAY,1) );  // DMUX1_A
//         add( inputDMUX2, get(in,2) );   // S2
        IO outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        IO inputDMUX3 = { outputDMUX4WAY[2], in[1] };
//         add( inputDMUX3, get(outputDMUX4WAY,2) );  // DMUX1_A
//         add( inputDMUX3, get(in,2) );   // S2
        IO outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        IO inputDMUX4 = { outputDMUX4WAY[3], in[1] };
//         add( inputDMUX4, get(outputDMUX4WAY,3) );  // DMUX1_A
//         add( inputDMUX4, get(in,2) );   // S2
        IO outputDMUX4 = m_DMUX.Process( inputDMUX4 );
        
        IO output = { 
            outputDMUX1[0], 
            outputDMUX2[0], 
            outputDMUX3[0], 
            outputDMUX4[0], 
            outputDMUX1[1], 
            outputDMUX2[1], 
            outputDMUX3[1], 
            outputDMUX4[1],  
        };
//         add( output, get( outputDMUX4, 1) );
//         add( output, get( outputDMUX3, 1) );
//         add( output, get( outputDMUX2, 1) );
//         add( output, get( outputDMUX1, 1) );
//         add( output, get( outputDMUX4, 0) );
//         add( output, get( outputDMUX3, 0) );
//         add( output, get( outputDMUX2, 0) );
//         add( output, get( outputDMUX1, 0) );
        return output;
    }

};

#endif
