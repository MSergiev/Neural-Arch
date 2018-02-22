#ifndef MUX_H
#define MUX_H

#include "NOT.h"
#include "NAND.h"

class MUX : public Gate {

public:

    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte S = 2;    // Selection bit
    
    static const byte O = 0;    // Output
    
private:
    
	NOT m_NOT;
	NAND m_NAND;

public: 

	// Constructor
	MUX() : Gate("MUX",3,1,"ABS","O") {}

	// Destuctor
	~MUX() {}

    // Processing method
	virtual inline IO Process( IO in ) {
        // Negate selection bit
        IO inputNOT = m_NOT.CreateInputIO();
        inputNOT[NOT::I] = in[S];
        
        // NAND input A and negated S
        IO inputNAND1 = m_NAND.CreateInputIO();
        inputNAND1[NAND::A] = m_NOT.Process(inputNOT)[NOT::O];
        inputNAND1[NAND::B] = in[A];
        
        // NAND input B and S
        IO inputNAND2 = m_NAND.CreateInputIO();
        inputNAND2[NAND::A] = in[S];
        inputNAND2[NAND::B] = in[B];
        
        // NAND previous NAND outputs
        IO inputNAND3 = m_NAND.CreateInputIO();
        inputNAND3[NAND::A] = m_NAND.Process(inputNAND1)[NAND::O];
        inputNAND3[NAND::B] = m_NAND.Process(inputNAND2)[NAND::O];
        
        IO output = CreateOutputIO();
        output[O] = m_NAND.Process( inputNAND3 )[NAND::O];
        return output;
    }
};

#endif
