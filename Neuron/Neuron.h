#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

class Neuron {

public:
	
	// Neuron data
	unsigned inputCount;
	double* input;
	double* weight;
	double bias;

	double sum;
	double output;

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

		output = sigmoid( sum );
	
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

private:

	// Sigmoid activation function
	static inline double sigmoid( double val ) {
		return 1/(1 + std::pow(M_E, -val));
	};

};

#endif
