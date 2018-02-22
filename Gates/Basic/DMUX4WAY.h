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
    virtual inline IO Process( IO in ) {
        IO inputDMUX1 = { in[0], in[2] };
        IO outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        IO inputDMUX2 = { outputDMUX1[0], in[1] };
        IO outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        IO inputDMUX3 = { outputDMUX1[1], in[1] };
        IO outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        IO output = { 
            outputDMUX2[0], 
            outputDMUX3[0], 
            outputDMUX2[1], 
            outputDMUX3[1],  
        };
        return output;
    }

};

#endif
