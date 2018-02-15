#include "TrainableNeuron.h"

static const unsigned inputs = 2;
static const unsigned samples = 4;

static double input[samples][inputs] = {
	{0,0},
	{0,1},
	{1,0},
	{1,1}
};

static double target[samples] = {
	1,
	0,
	0,
	0
};

static const double learningRate = 0.2;
static const long long iterations = 50000;

int main() {

	TrainableNeuron n( inputs );

	n.SetLearningRate( learningRate );

	for( unsigned i = 0; i < iterations; ++i ) {
		for( unsigned j = 0; j < samples; ++j ) {
			n.SetInputs( input[j] );
			n.SetTarget( target[j] );
			n.FeedForward();
			n.Backpropagate();

			if(i == iterations-1) {
				std::cout << j << " -> " << std::round(n.GetOutput()) << std::endl;
			}
		}
	}
	
	std::cout << "W0 = " << n.weight[0] << std::endl;
	std::cout << "W1 = " << n.weight[1] << std::endl;
	std::cout << "Bias = " << n.bias << std::endl;
	std::cout << "Sum = " << n.sum << std::endl;

	return 0;

}
