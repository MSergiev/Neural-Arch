#ifndef ALU_H
#define ALU_H

#include "ADDER.h"
#include "../Basic/MUX.h"
#include "../Basic/NOT.h"
#include "../Basic/AND.h"
#include "../Basic/OR8WAY.h"
#include "../Basic/OR.h"

class ALU : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte CI = 2;   // Control bit input
    
    static const byte O = 0;    // Output
    static const byte C = 1;    // Control bit output
    
    // Control bits
    static const byte ZA = 0;   // Zero A
    static const byte NA = 1;   // Negate A
    static const byte ZB = 2;   // Zero B
    static const byte NB = 3;   // Negate B
    static const byte FS = 4;   // AND/ADD selector
    static const byte NO = 5;   // Negate output
    
    static const byte ZO = 0;   // Output is zero
    static const byte NG = 1;   // Output is negative

private:

    // Gates
    ADDER m_ADDER;
    MUX m_MUX;
    NOT m_NOT;
    AND m_AND;
    OR8WAY m_OR8WAY;
    OR m_OR;

public: 

    // Constructor
    ALU() : Gate("ALU",3,2,"ABC","OC") {}

    // Destuctor
    ~ALU() {}

    // Processing method
    virtual inline IO Process( IO in ) { return in; }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // Perform input zeroing and negation
        ProcessInput( in[A], in[CI][ZA], in[CI][NA] );
        ProcessInput( in[B], in[CI][ZB], in[CI][NB] );

        // AND inputs
		BUS inputAND = m_AND.CreateInputBUS();
        inputAND[AND::A] = in[A];
        inputAND[AND::B] = in[B];
		IO outputAND = m_AND.ProcessBUS( inputAND )[AND::O];
        
        // ADD inputs
		BUS inputADD = m_ADDER.CreateInputBUS();
        inputADD[ADDER::A] = in[A];
        inputADD[ADDER::B] = in[B];
		IO outputADD = m_ADDER.ProcessBUS( inputADD )[ADDER::O];
        
        // Process selected operation
		BUS inputF = m_MUX.CreateInputBUS();
        inputF[MUX::A] = outputAND;
        inputF[MUX::B] = outputADD;
        inputF[MUX::S] = IO(ARCH,in[CI][FS]);
		IO outputOP = m_MUX.ProcessBUS( inputF )[MUX::O];

        // Perform output negation
        BUS inputNegO = m_NOT.CreateInputBUS();
        inputNegO[NOT::I] = outputOP;
		IO negatedOutputOP = m_NOT.ProcessBUS( inputNegO )[NOT::O];
		BUS inputNO = m_MUX.CreateInputBUS();
        inputNO[MUX::A] = outputOP;
        inputNO[MUX::B] = negatedOutputOP;
        inputNO[MUX::S] = IO(ARCH,in[CI][NO]);
        IO finalOut = m_MUX.ProcessBUS( inputNO )[MUX::O];

        // Calculate output control bits
        BUS inputOR8 = { IO(), IO() };
        for( unsigned char i = 0; i < 8; ++i ) {
            inputOR8[0].push_back( finalOut[i] );
            inputOR8[1].push_back( finalOut[i+8] );
        }
        BUS outputOR8 = { IO(), IO() };
        outputOR8[0] = m_OR8WAY.Process( inputOR8[0] );
        outputOR8[1] = m_OR8WAY.Process( inputOR8[1] );
		IO outBits(2, 0);
        outBits[ZO] = m_NOT.Process( m_OR.ProcessBUS(outputOR8)[OR::O] )[NOT::O];
        outBits[NG] = finalOut[0];
        
		BUS output = CreateOutputBUS();
        output[O] = finalOut;
        output[C] = outBits;
        return output; 
    }
    
private:
    
    void ProcessInput( IO& in, IOin zero, IOin negate ) {
        BUS inputZero = m_MUX.CreateInputBUS();
        inputZero[MUX::A] = in;
        inputZero[MUX::B] = ZeroIO();
        inputZero[MUX::S] = IO( ARCH,zero );
		in = m_MUX.ProcessBUS( inputZero )[MUX::O];
        
        BUS inputNegateIn = m_NOT.CreateInputBUS();
        inputNegateIn[NOT::I] = in;
        IO negatedIn = m_NOT.CreateOutputIO();
		negatedIn = m_NOT.ProcessBUS( inputNegateIn )[NOT::O];
        
		BUS inputNegate = m_MUX.CreateInputBUS();
        inputNegate[MUX::A] = in;
        inputNegate[MUX::B] = negatedIn;
        inputNegate[MUX::S] = IO( ARCH,negate );
		in = m_MUX.ProcessBUS( inputNegate )[MUX::O];
    }

};

#endif
