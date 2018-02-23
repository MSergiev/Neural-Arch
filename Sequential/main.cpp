#define ROUND

#include <iostream>

#include "Clock.h"
#include "Memory/RAM64.h"

#define LIMIT 100

long cycles = 0;    

RAM64 m_RAM64;

void setup() {
    
    Clock::SetSpeed(0);
    
    for( unsigned i = 0; i < 64; ++i ) {
        BUS input = m_RAM64.CreateInputBUS();
        input[RAM64::I] = NumToIO(i);
        input[RAM64::A] = NumToIO(i);
        input[RAM64::L] = NumToIO(1);
        BUS out = m_RAM64.ProcessBUS( input );
        std::cout << "Loading " << IOToNum(input[RAM64::I]) << " to addr " << IOToNum(input[RAM64::A]) << std::endl;
    }
    
    m_RAM64.PrintRAM();
}



void loop() {
    
    BUS input = m_RAM64.CreateInputBUS();
    input[RAM64::I] = NumToIO(cycles);
    input[RAM64::A] = NumToIO(cycles%64);
    input[RAM64::L] = NumToIO(/*cycles%10==*/0);
    bool ld = ( cycles%100==0 );
    
    std::cout << cycles << " -> ";
    PrintBUS( m_RAM64.ProcessBUS(input) );
//     m_RAM64.PrintRAM();
    
}















int main() {
    
    setup();

	while( cycles < LIMIT ) {
		Clock::Tick();
        
		if( Clock::GetCycles() > cycles ) {
			cycles = Clock::GetCycles();   
            loop();
		}
		
	}

	return 0;
}
