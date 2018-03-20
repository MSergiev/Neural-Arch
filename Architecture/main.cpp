#define DEBUG
#define ROUND

#include <iostream>

#include "../Sequential/Clock.h"
#include "Computer.h"

#define LIMIT 100

long cycles = 0;    

COMPUTER m_PC;



void setup() {
    
    Clock::SetSpeed(0);
    
}



void loop() {
    
    std::cout << "\nCycle: " << cycles << std::endl;
    BUS input = m_PC.CreateInputBUS();
    input[COMPUTER::R] = ZeroIO();
    BUS out = m_PC.ProcessBUS( input );
    m_PC.PrintOutputBUS(out);
    std::cout << std::endl;
    
}















int main( int argc, const char* argv[] ) {
    
    setup();
    
    if( argc < 2 ) {
        if( !m_PC.LoadFile( "ROM.txt" ) ) return -1;
    }
    else {
        if( !m_PC.LoadFile( argv[1] ) ) return -1;
    }

	while( cycles < LIMIT ) {
		Clock::Tick();
        
		if( Clock::GetCycles() > cycles ) {
			cycles = Clock::GetCycles();   
            loop();
            
            if( !m_PC.IsActive() ) return 0;
		}
		
	}

	return 0;
}
