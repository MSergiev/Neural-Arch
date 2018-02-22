#ifndef DMUX4WAY_H
#define DMUX4WAY_H

#include "DMUX.h"

class DMUX4WAY : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte S1 = 1;   // Selection bit 1
    static const byte S2 = 2;   // Selection bit 2
    
    static const byte A = 0;    // Output A
    static const byte B = 1;    // Output B
    static const byte C = 2;    // Output C
    static const byte D = 3;    // Output D
    
private:
    
	DMUX m_DMUX;

public: 

    // Constructor
    DMUX4WAY() : Gate("DMUX4WAY",3,4,"ISS","ABCD") {}

    // Destuctor
    ~DMUX4WAY() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        // DMUX input and S2
        IO inputDMUX1 = m_DMUX.CreateInputIO();
        inputDMUX1[DMUX::I] = in[I];
        inputDMUX1[DMUX::S] = in[S2];
        IO outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        // DMUX first DMUX output A and S1
        IO inputDMUX2 = m_DMUX.CreateInputIO();
        inputDMUX2[DMUX::I] = outputDMUX1[DMUX::A];
        inputDMUX2[DMUX::S] = in[S1];
        IO outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        // DMUX first DMUX output B and S1
        IO inputDMUX3 = m_DMUX.CreateInputIO();
        inputDMUX3[DMUX::I] = outputDMUX1[DMUX::B];
        inputDMUX3[DMUX::S] = in[S1];
        IO outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        IO output = CreateOutputIO();
        output[A] = outputDMUX2[DMUX::A]; 
        output[B] = outputDMUX3[DMUX::A]; 
        output[C] = outputDMUX2[DMUX::B]; 
        output[D] = outputDMUX3[DMUX::B];
        return output;
    }

};

#endif
