#define ROUND

#include <iostream>

#include "Clock.h"
#include "Memory/RAM512.h"

#define LIMIT 100

long cycles = 0;    

RAM512 m_RAM512;

void setup() {
    
    Clock::SetSpeed(0);
    
    for( unsigned i = 0; i < 512; ++i ) {
        BUS input = m_RAM512.CreateInputBUS();
        input[RAM512::I] = NumToIO(i);
        input[RAM512::A] = NumToIO(i);
        input[RAM512::L] = NumToIO(1);
        BUS out = m_RAM512.ProcessBUS( input );
//         std::cout << "Loading " << IOToNum(input[RAM512::I]) << " to addr " << IOToNum(input[RAM512::A]) << std::endl;
    }
    
    m_RAM512.PrintRAM();
}



void loop() {
    
    BUS input = m_RAM512.CreateInputBUS();
    input[RAM512::I] = NumToIO(cycles);
    input[RAM512::A] = NumToIO(cycles%512);
    input[RAM512::L] = NumToIO(/*cycles%10==*/0);
    bool ld = ( cycles%100==0 );
    
    std::cout << cycles << " -> ";
    PrintBUS( m_RAM512.ProcessBUS(input) );
//     m_RAM512.PrintRAM();
    
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
