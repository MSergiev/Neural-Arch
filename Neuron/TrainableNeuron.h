#ifndef TRAINABLENEURON_H
#define TRAINABLENEURON_H

#include "Neuron.h"


class TrainableNeuron : public Neuron {

private:

	//Trainable neuron data
	double target;
	double learningRate;

public:

	// Constructor
	TrainableNeuron( unsigned inputCount = 0 )
    :Neuron(inputCount)	{}

	// Destructor
	virtual ~TrainableNeuron(){}

public:

	// Set target values
	inline void SetTarget( double target ) {
		this->target = target;
	}

	// Set learning rate
	inline void SetLearningRate( double learningRate ) {
		this->learningRate = learningRate;
	}

	// Backpropagation
	inline void Backpropagate() {
        
        // Output error	
        double error = (output - target);
        
        switch( func ) {
            case SIGMOID: {
                // Squared cost
                //double cost = error*error;
                // Cost derivative
                double dCost_dOutput = 2 * error;
                // Output derivative
                double dOutput_dSum = output * (1-output);
                // Sum partial derivatives
                double dSum_dWeight[inputCount];
                for( unsigned i = 0; i < inputCount; ++i ) {
                    dSum_dWeight[i] = input[i];
                }
                // Bias derivative
                double dSum_dBias = 1;
                
                // Total partial derivatives
                double dCost_dWeight[inputCount];
                for( unsigned i = 0; i < inputCount; ++i ) {
                    dCost_dWeight[i] = dCost_dOutput * dOutput_dSum * dSum_dWeight[i];
                }
                double dCost_dBias = dCost_dOutput * dOutput_dSum * dSum_dBias;
                
                // Modify neuron parameters
                for( unsigned i = 0; i < inputCount; ++i ) {
                    weight[i] -= learningRate * dCost_dWeight[i];
                }
                bias -= learningRate * dCost_dBias;
                break;
            }
            
            case STEP: {
                bias = target-0.5;
                break;
            }
        }

	}

};

#endif
