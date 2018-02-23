#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

class Clock {

private:

    // Clock division coefficient
    static constexpr double MILLIS = CLOCKS_PER_SEC/1000;

    // Current value
    static bool tick;

    // Clock cycles
    static long cycles;

    // Real processor cycles
    static clock_t realCycles;
    
    // Ticking speed in milliseconds
    static unsigned speed;

public:

    // Ticking method
    static inline void Tick() {
        if( (clock() - realCycles)/MILLIS >= speed ) {
            realCycles = clock();
            tick = !tick;
            cycles += tick;
        }
    }

    // Tick getter
    static inline bool GetTick() {
        return tick;
    }

    // Cycle count getter
    static inline long GetCycles() {
        return cycles;
    }

    // Speed setter
    static inline void SetSpeed( unsigned speed ) {
        Clock::speed = speed;
    }

};

bool Clock::tick = false;
long Clock::cycles = 0;
clock_t Clock::realCycles = 0;
unsigned Clock::speed = 0;

#endif
