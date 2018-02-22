#ifndef ALU_H
#define ALU_H

#include "ADDER.h"
#include "../Basic/MUX.h"
#include "../Basic/NOT.h"
#include "../Basic/AND.h"
#include "../Basic/OR8WAY.h"
#include "../Basic/OR.h"

// Control bit positions
#define ZA 0	// Zero input A
#define NA 1	// Negate input A
#define ZB 2	// Zero input B
#define NB 3	// Negate input B
#define F  4	// AND/ADD function switch
#define NO 5	// Negate output

#define ZO 0	// Output is zero
#define NG 1	// Output is negative

// Inputs
#define IN_A 0 // Input A
#define IN_B 1 // Input B
#define IN_CONT 2   // Control bits

// Outputs
#define OUT 0 // Output
#define OUT_CONT 1 // Output control bits

class ALU : public Gate {

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
        IO inputA = in[IN_A];
		BUS inputZA = { inputA, IO(ARCH,0), IO(ARCH,in[IN_CONT][ZA]) };
		inputA = m_MUX.ProcessBUS( inputZA )[0];
		BUS inputNegA = { inputA, {in[IN_CONT][NA]} } ;
		IO negA = m_NOT.ProcessBUS( inputNegA )[0];
		BUS inputNA = { inputA, negA, IO(ARCH,in[IN_CONT][NA]) };
		inputA = m_MUX.ProcessBUS( inputNA )[0];
        
        IO inputB = in[IN_B];
		BUS inputZB = { inputB, IO(ARCH,0), IO(ARCH,in[IN_CONT][ZB]) };
		inputB = m_MUX.ProcessBUS( inputZB )[0];
		BUS inputNegB = { inputB, {in[IN_CONT][NB]} };
		IO negB = m_NOT.ProcessBUS( inputNegB )[0];
		BUS inputNB = { inputB, negB, IO(ARCH,in[IN_CONT][NB]) };
		inputB = m_MUX.ProcessBUS( inputNB )[0];

		BUS inputAND = { inputA, inputB };
		IO outputAND = m_AND.ProcessBUS( inputAND )[0];
		BUS inputADD = { inputA, inputB };
		IO outputADD = m_ADDER.ProcessBUS( inputADD )[0];
		BUS inputF = { outputAND, outputADD, IO(ARCH,in[IN_CONT][F]) };
		IO outputOP = m_MUX.ProcessBUS( inputF )[0];

        BUS inputNegO = { outputOP };
		IO outputNegO = m_NOT.ProcessBUS( inputNegO )[0];
		BUS inputNO = { outputOP, outputNegO, IO(ARCH,in[IN_CONT][NO]) };
        IO finalOut = m_MUX.ProcessBUS( inputNO )[0];

        BUS inputOR8 = { IO(), IO() };
        for( unsigned char i = 0; i < 8; ++i ) {
            inputOR8[0].push_back( finalOut[i] );
            inputOR8[1].push_back( finalOut[i+8] );
        }
        BUS outputOR8 = { IO(), IO() };
        outputOR8[0] = m_OR8WAY.Process( inputOR8[0] );
        outputOR8[1] = m_OR8WAY.Process( inputOR8[1] );
		IO outBits = { m_NOT.Process( m_OR.ProcessBUS(outputOR8)[0] )[0], finalOut[ARCH-1] };
        
		BUS output = { finalOut, outBits };
        return output; 
    }

};

#endif
