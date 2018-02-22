#ifndef DMUX8WAY_H
#define DMUX8WAY_H

#include "DMUX.h"
#include "DMUX4WAY.h"

class DMUX8WAY : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte S1 = 1;   // Selection bit 1
    static const byte S2 = 2;   // Selection bit 2
    static const byte S3 = 3;   // Selection bit 3
    
    static const byte A = 0;    // Output A
    static const byte B = 1;    // Output B
    static const byte C = 2;    // Output C
    static const byte D = 3;    // Output D
    static const byte E = 4;    // Output E
    static const byte F = 5;    // Output F
    static const byte G = 6;    // Output G
    static const byte H = 7;    // Output H

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
        // DMUX4WAY input and S2 and S3
        IO inputDMUX4WAY = m_DMUX4WAY.CreateInputIO();
        inputDMUX4WAY[DMUX4WAY::I] = in[I];
        inputDMUX4WAY[DMUX4WAY::S1] = in[S2];
        inputDMUX4WAY[DMUX4WAY::S2] = in[S3];
        IO outputDMUX4WAY = m_DMUX4WAY.Process( inputDMUX4WAY );
        
        // DMUX DMUX4WAY output A and S1
        IO inputDMUX1 = m_DMUX.CreateInputIO();
        inputDMUX1[DMUX::I] = outputDMUX4WAY[DMUX4WAY::A];
        inputDMUX1[DMUX::S] = in[S1];
        IO outputDMUX1 = m_DMUX.Process( inputDMUX1 );
        
        // DMUX DMUX4WAY output B and S1
        IO inputDMUX2 = m_DMUX.CreateInputIO();
        inputDMUX2[DMUX::I] = outputDMUX4WAY[DMUX4WAY::B];
        inputDMUX2[DMUX::S] = in[S1];
        IO outputDMUX2 = m_DMUX.Process( inputDMUX2 );
        
        // DMUX DMUX4WAY output C and S1
        IO inputDMUX3 = m_DMUX.CreateInputIO();
        inputDMUX3[DMUX::I] = outputDMUX4WAY[DMUX4WAY::C];
        inputDMUX3[DMUX::S] = in[S1];
        IO outputDMUX3 = m_DMUX.Process( inputDMUX3 );
        
        // DMUX DMUX4WAY output D and S1
        IO inputDMUX4 = m_DMUX.CreateInputIO();
        inputDMUX4[DMUX::I] = outputDMUX4WAY[DMUX4WAY::D];
        inputDMUX4[DMUX::S] = in[S1];
        IO outputDMUX4 = m_DMUX.Process( inputDMUX4 );
        
        IO output = CreateOutputIO();
        output[A] = outputDMUX1[0];
        output[B] = outputDMUX2[0]; 
        output[C] = outputDMUX3[0]; 
        output[D] = outputDMUX4[0]; 
        output[E] = outputDMUX1[1]; 
        output[F] = outputDMUX2[1]; 
        output[G] = outputDMUX3[1]; 
        output[H] = outputDMUX4[1]; 
        return output;
    }

};

#endif
