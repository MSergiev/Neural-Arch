#ifndef ALU_H
#define ALU_H

#include "ADDER.h"
#include "MUX.h"
#include "NOT.h"
#include "AND.h"
#include "OR.h"

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
    OR m_OR;

public: 

    // Constructor
    ALU() : Gate("ALU",2,1,"AB","O"), control(0) {}

    // Destuctor
    ~ALU() {}

    // Processing method
    virtual inline bitset Process( bitset in ) { return 0; }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) {
        
        bitset output = 0;
        
        bitset inputA = in[0]
        bitset inputB = in[1];
        
        bitset inputZeroA = get(control, 5);
        bitset outputZeroA = m_MUX.Process(inputZeroA);
        
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
