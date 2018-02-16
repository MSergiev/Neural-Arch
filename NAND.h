#ifndef NAND_H
#define NAND_H

#include "Gate.h"
#include "Neuron.h"

static const double WEIGHT = -8.74477;
static const double BIAS = 13.2027;

class NAND : public Gate {
	
private:
    
	Neuron n;

public: 

	// Constructor
	NAND() : Gate("NAND",2,1,"AB","O"), n(INPUTS) {
		double weights[INPUTS] = { WEIGHT, WEIGHT };
		n.SetWeights( weights );
		n.SetBias( BIAS );	
	}

	// Destuctor
	~NAND() {}
	
    // Processing method
	virtual inline bitset Process( bitset in ) {
        double inputs[] = { (double)get(in,0), (double)get(in,1) };
		n.SetInputs( inputs );
		n.FeedForward();
        return (bitset)std::round(n.GetOutput());
    }
    
    // Multiway processing method
    virtual inline bitset Process( bitset* in ) { return 0; }
    
};

#endif
