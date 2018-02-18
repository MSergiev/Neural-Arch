#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

// Ticking speed in milliseconds
#define SPEED 500

class Clock {

private:

	// Clock division coefficient
	const double MILLIS = CLOCKS_PER_SEC/1000;

	// Current value
	bool tick;

	// Clock cycles
	long cycles;

	// Real processor cycles
	clock_t realCycles;

public:

	// Constructor
	Clock() : tick(false), cycles(0), realCycles(0) {}

	// Destructor
	~Clock() {}

	// Ticking method
	inline void Tick() {
		if( (clock() - realCycles)/MILLIS >= SPEED ) {
			realCycles = clock();
			tick = !tick;
			cycles++;
		}
	}

	// Tick getter
	inline bool GetTick() {
		return tick;
	}

	// Cycle count getter
	inline long GetCycles() {
		return cycles;
	}

};

#endif
