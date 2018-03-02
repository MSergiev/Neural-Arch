#define DEBUG
#define ROUND

#include <iostream>

#include "../Sequential/Clock.h"
#include "CPU.h"

#define LIMIT 100

long cycles = 0;    

CPU m_CPU;



void setup() {
    
    Clock::SetSpeed(0);
    
    
    BUS input = m_CPU.CreateInputBUS();
    
    input[CPU::I][CPU::OPC] = 0;
    input[CPU::I][CPU::UNUSED] = 0;
    input[CPU::I][CPU::UNUSED+1] = 0;
    input[CPU::I][CPU::MEM] = 0;
    input[CPU::I][CPU::CONT] = 0;
    input[CPU::I][CPU::CONT+1] = 0;
    input[CPU::I][CPU::CONT+2] = 0;
    input[CPU::I][CPU::CONT+3] = 0;
    input[CPU::I][CPU::CONT+4] = 0;
    input[CPU::I][CPU::CONT+5] = 0;
    input[CPU::I][CPU::D_ADDR] = 0;
    input[CPU::I][CPU::D_DATA] = 0;
    input[CPU::I][CPU::D_OUT] = 0;
    input[CPU::I][CPU::J_N] = 0;
    input[CPU::I][CPU::J_Z] = 0;
    input[CPU::I][CPU::J_P] = 0;
    
    input[CPU::M] = ZeroIO();
    input[CPU::R] = FilledIO(1);
    
    m_CPU.ProcessBUS( input );
    
    input[CPU::I] =
    IO{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // O V V V V V V V V V V V V V V V
    input[CPU::R] = ZeroIO();
    
    m_CPU.ProcessBUS( input );
    
    input[CPU::I] = IO{1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1};
    // O X X M C C C C C C D D D J J J
    input[CPU::R] = ZeroIO();
    
    BUS out = m_CPU.ProcessBUS( input );
    PrintBUS(out);
    std::cout << std::endl;
}



void loop() {
    
    BUS input = m_CPU.CreateInputBUS();
    
    input[CPU::I] = IO{1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,1};
    // O X X M C C C C C C D D D J J J
    input[CPU::M] = ZeroIO();
    input[CPU::R] = ZeroIO();
    
    std::cout << cycles << std::endl;
    BUS out = m_CPU.ProcessBUS( input );
//     PrintBUS(out);
    std::cout << std::endl;
    
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
