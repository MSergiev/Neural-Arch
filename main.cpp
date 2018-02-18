#include <iostream>

#include "Clock.h"
#include "Gates/Basic/DFF.h"

int main() {
	Clock c;

    DFF m_DFF;
    
	long cycles = 0;

	while( cycles < 10 ) {
		c.Tick();
		if( c.GetCycles() > cycles ) {
			cycles = c.GetCycles();
			std::cout << cycles << " " << c.GetTick() << std::endl;
            
            bitset inputDFF = 0;
            add( inputDFF, cycles<5 );
            add( inputDFF, c.GetTick() );
            std::cout << "DFF: " << m_DFF.Process(inputDFF) << std::endl;
		}
	}

	return 0;
}
