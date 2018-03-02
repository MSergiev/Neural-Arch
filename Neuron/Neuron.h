#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

enum ActFunction {
    STEP,
    SIGMOID
};

class Neuron {

public:
	
	// Neuron data
	unsigned inputCount;
	double* input;
	double* weight;
	double bias;

	double sum;
	double output;
    
    ActFunction func;

public:

	// Constructor
	Neuron( unsigned inputCount = 0 ) {
		
		this->inputCount = inputCount;
		input = new double[inputCount];
		weight = new double[inputCount];

		std::srand( time(0) );
		
		for( unsigned i = 0; i < inputCount; ++i ) {
			input[i] = 0;
			weight[i] = 0.5;
		}
		bias = 1;
        
        func = SIGMOID;

	};

	// Destructor
	virtual ~Neuron() {
		
		delete[] input;
		delete[] weight;	
	
	};

public:

	// Calculate neuron output
	inline void FeedForward() {
		
		sum = 0.0;
		for( unsigned i = 0; i < inputCount; ++i ) {
			sum += input[i]*weight[i];
		}	
		sum += bias;

        switch( func ) {
            case SIGMOID:   output = sigmoid( sum );    break;
            case STEP:      output = step( sum );       break;
        }
	
	};

	// Set neuron inputs
	inline void SetInputs( double* input ) {
		for( unsigned i = 0; i < inputCount; ++i ) {
			this->input[i] = input[i];
		}
	}

	// Set neuron weigths
	inline void SetWeights( double* weight ) {
		for( unsigned i = 0; i < inputCount; ++i ) {
			this->weight[i] = weight[i];
		}	
	}

	// Set neuron bias
	inline void SetBias( double bias ) {
		this->bias = bias;	
	}
	
	// Get neuron bias
	inline double GetBias() {
		return bias;
	}

	// Get neuron output
	inline double GetOutput() {
		return output;
	}
	
	// Set activation function
	inline void SetActivation( ActFunction f ) {
        func = f;
    }
    
	// Get activation function
	inline ActFunction GetActivation() {
        return func;
    }

private:

	// Sigmoid activation function
	static inline double sigmoid( double val ) {
		return 1/(1 + std::pow(M_E, -val));
	};

	// Step activation function
	static inline double step( double val ) {
		return (val > 0);
	};

};

#endif
