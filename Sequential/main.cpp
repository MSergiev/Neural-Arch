#define ROUND

#include <iostream>

#include "Clock.h"
#include "Memory/RAM8.h"

#define LIMIT 100

long cycles = 0;    

RAM8 m_RAM8;

void setup() {
    
    Clock::SetSpeed(0);
    
//     for( byte i = 0; i < 8; ++i ) {
//         BUS input = m_RAM8.CreateInputBUS();
//         input[RAM8::I] = NumToIO(0);
//         input[RAM8::A] = NumToIO(i);
//         input[RAM8::L] = NumToIO(1);
// //         PrintBUS(input);
//         BUS out = m_RAM8.ProcessBUS( input );
// //         PrintBUS(out);
// //         std::cout << std::endl;
//     }
    
    m_RAM8.PrintRAM();
}



void loop() {
    
    BUS input = m_RAM8.CreateInputBUS();
    input[RAM8::I] = NumToIO(cycles);
    input[RAM8::A] = NumToIO(cycles%8);
    input[RAM8::L] = NumToIO(cycles%10==0);
    
//     { NumToIO(63-cycles), NumToIO(cycles%(RAM8::SIZE)), {(double)(cycles<7)} };

//     if( cycles%100 ) inp = !inp;
    bool ld = ( cycles%100==0 );
    
//     BUS in = m_REG.CreateInputBUS();
//     in[REG::I] = NumToIO(cycles);
//     in[REG::L] = NumToIO(ld);
    
    std::cout << cycles << " -> ";
    PrintBUS( m_RAM8.ProcessBUS(input) );
    m_RAM8.PrintRAM();
    
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
