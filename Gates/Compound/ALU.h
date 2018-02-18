#ifndef ALU_H
#define ALU_H

#include "ADDER.h"
#include "../Basic/MUX.h"
#include "../Basic/NOT.h"
#include "../Basic/AND.h"
#include "../Basic/OR8WAY.h"

// Control bit positions
#define ZA 5	// Zero input A
#define NA 4	// Negate input A
#define ZB 3	// Zero input B
#define NB 2	// Negate input B
#define F  1	// AND/ADD function switch
#define NO 0	// Negate output

#define ZO 1	// Output is zero
#define NG 0	// Output is negative

class ALU : public Gate {

private:

    // Control bitset (ZA,NA,ZB,NB,F,NO)
    bitset control;
    
    // Output control bitset (ZO,NG)
    bitset outBits;

    // Gates
    ADDER m_ADDER;
    MUX m_MUX;
    NOT m_NOT;
    AND m_AND;
    OR8WAY m_OR8WAY;

public: 

    // Constructor
    ALU() : Gate("ALU",2,1,"AB","O"), control(0) {}

    // Destuctor
    ~ALU() {}

    // Processing method
    virtual inline bitset Process( bitset in ) { return in; }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset inputA = in[0];
		bitset inputZA[] = {inputA, 0, get(control, ZA)};
		inputA = m_MUX.Process(inputZA);
		bitset inputNegA[] = {inputA, get(control, NA)};
		bitset negA = m_NOT.Process(inputNegA);	
		bitset inputNA[] = {inputA, negA, get(control, NA)};
		inputA = m_MUX.Process(inputNA);
        
        bitset inputB = in[1];
		bitset inputZB[] = {inputB, 0, get(control, ZB)};
		inputB = m_MUX.Process(inputZB);
		bitset inputNegB[] = {inputB, get(control, NB)};
		bitset negB = m_NOT.Process(inputNegB);	
		bitset inputNB[] = {inputB, negB, get(control, NB)};
		inputB = m_MUX.Process(inputNB);

		bitset inputAND[] = {inputA, inputB};
		bitset outputAND = m_AND.Process(inputAND);
		bitset inputADD[] = {inputA, inputB};
		bitset outputADD = m_ADDER.Process(inputADD);
		bitset inputF[] = {outputAND, outputADD, get(control, 1)};
		bitset output = m_MUX.Process(inputF);

		bitset negOutput = m_NOT.Process(&output);
		bitset inputNO[] = {output, negOutput, get(control, 0)};
		output = m_MUX.Process(inputNO);

		outBits = 0;
		add( outBits, m_NOT.Process( m_OR8WAY.Process(output) ) );
	    add( outBits, get(output, ARCH-1) );	

        return output; 
        
    }
    
    // Control bitset setter
    void SetControlBits( bitset in ) {
        control = in;
    }
    
    // Output control bits getter
    bitset GetOutputBits() {
        return outBits;
    }

};

#endif
