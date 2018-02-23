#ifndef SSDFF_H
#define SSDFF_H

#include "../../Gates/Basic/Gate.h"
#include "../../Neuron/Neuron.h"


class SSDFF : public Gate {
    
    static constexpr double WEIGHT = 1;
    static constexpr double BIAS = -2;
    
    static const byte I = 0;    // Input
    static const byte L = 1;    // Load bit
    
    static const byte O = 0;    // Output
    
private:
    
    Neuron n;
    IO oldIn;
    
public: 

    // Constructor
    SSDFF() : Gate("SSDFF",2,1,"IL","O"), n(1) {
        double weight = WEIGHT;
        n.SetWeights( &weight );
        n.SetBias( BIAS );
        oldIn = { 0, 0 };
    }

    // Destuctor
    ~SSDFF() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        if( oldIn[L] ) {
            n.SetBias( oldIn[I] ? -BIAS : BIAS );
        }
        double input = (double)oldIn[I];
        oldIn = in;
        n.SetInputs( &input );
        n.FeedForward();
        
        IO output = CreateOutputIO();
        output[O] = n.GetOutput();
        return output;
    }

};

#endif
