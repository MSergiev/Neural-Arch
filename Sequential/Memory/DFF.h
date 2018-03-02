#ifndef DFF_H
#define DFF_H

#include "../../Gates/Basic/Gate.h"
#include "../../Neuron/TrainableNeuron.h"

class DFF : public Gate {
    
    static constexpr double BIAS = 0;
    
    static constexpr double RATE = 14;
    
public:
    
    static const unsigned char I = 0;   // Input
    static const unsigned char L = 1;   // Load bit
    
    static const unsigned char O = 0;   // Output
    
private:
    
    TrainableNeuron n;
    
public: 

    // Constructor
    DFF() : Gate("DFF",2,1,"IL","O"), n(0) {
        n.SetBias( BIAS );
        n.SetLearningRate( RATE );
        n.SetActivation( STEP );
    }

    // Destuctor
    ~DFF() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        n.FeedForward();
        if( in[L] > 0.5 ) {
            n.SetTarget( in[I] );
        }
        n.Backpropagate();
        
        IO output = CreateOutputIO();
        output[O] = n.GetOutput();
        return output;
    }

};

#endif
