#ifndef NAND_H
#define NAND_H

#include "Gate.h"
#include "../../Neuron/Neuron.h"


class NAND : public Gate {

    static constexpr double WEIGHT = -8.74477;
    static constexpr double BIAS = 13.2027;

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
	virtual inline IO Process( IO in ) {
        double inputs[] = { in[0], in[1] };
		n.SetInputs( inputs );
		n.FeedForward();
        IO output = { n.GetOutput() };
        return output;
    }
    
};

#endif
