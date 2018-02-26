#define ROUND
#define DEBUG

#include <iostream>

#include "Clock.h"
#include "Memory/RAM64.h"
#include "Memory/PC.h"

#define LIMIT 100

long cycles = 0;    

RAM64 m_RAM64;
PC m_PC;

void setup() {
    
    Clock::SetSpeed(0);
    
    BUS inputPC = m_PC.CreateInputBUS();
    inputPC[PC::I] = ZeroIO();
    inputPC[PC::L] = FilledIO(1);
    inputPC[PC::N] = ZeroIO();
    inputPC[PC::R] = NumToIO(cycles==50);
    m_PC.ProcessBUS( inputPC );
    
    for( unsigned i = 0; i < RAM64::SIZE; ++i ) {
        BUS input = m_RAM64.CreateInputBUS();
        input[RAM64::I] = NumToIO(i);
        input[RAM64::A] = NumToIO(i);
        input[RAM64::L] = NumToIO(1);
        BUS out = m_RAM64.ProcessBUS( input );
//         std::cout << "Loading " << IOToNum(input[RAM64::I]) << " to addr " << IOToNum(input[RAM64::A]) << std::endl;
    }
    
    m_RAM64.PrintRAM();
}



void loop() {
    
    BUS input = m_RAM64.CreateInputBUS();
    input[RAM64::I] = NumToIO(cycles);
    input[RAM64::A] = NumToIO(cycles%RAM64::SIZE);
    input[RAM64::L] = NumToIO(/*cycles%10==*/0);
    bool ld = ( cycles%100==0 );
    
    BUS inputPC = m_PC.CreateInputBUS();
    inputPC[PC::I] = ZeroIO();
    inputPC[PC::L] = ZeroIO();
    inputPC[PC::N] = FilledIO(cycles%10==0);
    inputPC[PC::R] = FilledIO(cycles==50);
    
    std::cout << IOToNum(m_PC.ProcessBUS(inputPC)[PC::O]) << " -> ";
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
