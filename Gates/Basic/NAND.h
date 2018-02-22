#ifndef NAND_H
#define NAND_H

#include "Gate.h"
#include "../../Neuron/Neuron.h"


class NAND : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    
    static const byte O = 0;    // Output
    
private:
    
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
        // Set neuron inputs
        double inputs[] = { in[A], in[B] };
		n.SetInputs( inputs );
		n.FeedForward();
        
        IO output = CreateOutputIO();
        output[O] = n.GetOutput();
        
        return output;
    }
    
};

#endif
