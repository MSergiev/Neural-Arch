#ifndef MUX8WAY_H
#define MUX8WAY_H

#include "MUX.h"
#include "MUX4WAY.h"

class MUX8WAY : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte C = 2;    // Input C
    static const byte D = 3;    // Input D
    static const byte E = 4;    // Input E
    static const byte F = 5;    // Input F
    static const byte G = 6;    // Input G
    static const byte H = 7;    // Input G
    static const byte S1 = 8;   // Selection bit 1
    static const byte S2 = 9;   // Selection bit 2
    static const byte S3 = 10;  // Selection bit 3
    
    static const byte O = 0;    // Output
    
private:
    
	MUX m_MUX;
	MUX4WAY m_MUX4WAY;

public: 

	// Constructor
	MUX8WAY() : Gate("MUX8WAY",11,1,"ABCDEFGHSSS","O") {}

	// Destuctor
	~MUX8WAY() {}

    // Processing method
	virtual inline IO Process( IO in ) {
        // MUX4WAY inputs A,B,C,D
        IO inputMUX4WAY1 = m_MUX4WAY.CreateInputIO();
        inputMUX4WAY1[MUX4WAY::A] = in[A];
        inputMUX4WAY1[MUX4WAY::B] = in[B];
        inputMUX4WAY1[MUX4WAY::C] = in[C];
        inputMUX4WAY1[MUX4WAY::D] = in[D];
        inputMUX4WAY1[MUX4WAY::S1] = in[S1];
        inputMUX4WAY1[MUX4WAY::S2] = in[S2];
        
        // MUX4WAY inputs E,F,G,H
        IO inputMUX4WAY2 = m_MUX4WAY.CreateInputIO();
        inputMUX4WAY2[MUX4WAY::A] = in[E];
        inputMUX4WAY2[MUX4WAY::B] = in[F];
        inputMUX4WAY2[MUX4WAY::C] = in[G];
        inputMUX4WAY2[MUX4WAY::D] = in[H];
        inputMUX4WAY2[MUX4WAY::S1] = in[S1];
        inputMUX4WAY2[MUX4WAY::S2] = in[S2];
        
        // MUX previous MUX4WAY outputs
        IO inputMUX = m_MUX.CreateInputIO();
        inputMUX[MUX::A] = m_MUX4WAY.Process(inputMUX4WAY1)[MUX4WAY::O];
        inputMUX[MUX::B] = m_MUX4WAY.Process(inputMUX4WAY2)[MUX4WAY::O];
        inputMUX[MUX::S] = in[S3];
        
        IO output = CreateOutputIO();
        output[O] = m_MUX.Process( inputMUX )[MUX::O];
        return output;
    }

    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) override {
        BUS output = { IO() };
        
        for( byte i = 0; i < ARCH; ++i ) {
            IO input = CreateInputIO();
            for( byte j = 0; j < 8; ++j ) {
                input[j] = in[j][i];
            }
            input[S1] = in[S1][0];
            input[S2] = in[S2][1];
            input[S3] = in[S3][2];
            output[O].push_back( Process(input)[O] );
        }
        
        return output;
    }
};

#endif
