#ifndef MUX4WAY_H
#define MUX4WAY_H

#include "MUX.h"

class MUX4WAY : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte C = 2;    // Input C
    static const byte D = 3;    // Input D
    static const byte S1 = 4;   // Selection bit 1
    static const byte S2 = 5;   // Selection bit 2
    
    static const byte O = 0;    // Output
    
private:
    
	MUX m_MUX;

public: 

	// Constructor
	MUX4WAY() : Gate("MUX4WAY",6,1,"ABCDSS","O") {}

	// Destuctor
	~MUX4WAY() {}

    // Processing method
	virtual inline IO Process( IO in ) {
        // MUX inputs A and B
        IO inputMUX1 = m_MUX.CreateInputIO();
        inputMUX1[MUX::A] = in[A];
        inputMUX1[MUX::B] = in[B];
        inputMUX1[MUX::S] = in[S1];
        
        // MUX inputs B and C
        IO inputMUX2 = m_MUX.CreateInputIO();
        inputMUX2[MUX::A] = in[C];
        inputMUX2[MUX::B] = in[D];
        inputMUX2[MUX::S] = in[S1];
        
        // MUX previout MUX outputs
        IO inputMUX3 = m_MUX.CreateInputIO();
        inputMUX3[MUX::A] = m_MUX.Process(inputMUX1)[MUX::O];
        inputMUX3[MUX::B] = m_MUX.Process(inputMUX2)[MUX::O];
        inputMUX3[MUX::S] = in[S2];
        
        IO output = CreateOutputIO();
        output[O] = m_MUX.Process( inputMUX3 )[MUX::O];
        return output;
    }

};

#endif
