#define ROUND
#define DEBUG

#include <iostream>

#include "Clock.h"
#include "Memory/RAM16K.h"

#define LIMIT 100

long cycles = 0;    

RAM16K m_RAM16K;

void setup() {
    
    Clock::SetSpeed(0);
    
    for( unsigned i = 0; i < RAM16K::SIZE; ++i ) {
        BUS input = m_RAM16K.CreateInputBUS();
        input[RAM16K::I] = NumToIO(i);
        input[RAM16K::A] = NumToIO(i);
        input[RAM16K::L] = NumToIO(1);
        BUS out = m_RAM16K.ProcessBUS( input );
//         std::cout << "Loading " << IOToNum(input[RAM16K::I]) << " to addr " << IOToNum(input[RAM16K::A]) << std::endl;
    }
    
    m_RAM16K.PrintRAM();
}



void loop() {
    
    BUS input = m_RAM16K.CreateInputBUS();
    input[RAM16K::I] = NumToIO(cycles);
    input[RAM16K::A] = NumToIO(cycles%RAM16K::SIZE);
    input[RAM16K::L] = NumToIO(/*cycles%10==*/0);
    bool ld = ( cycles%100==0 );
    
    std::cout << cycles << " -> ";
    PrintBUS( m_RAM16K.ProcessBUS(input) );
//     m_RAM16K.PrintRAM();
    
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
