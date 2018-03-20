#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "ROM.h"
#include "RAM.h"


class COMPUTER : public Gate {
    
public:
    
//     static const byte I = 0;    // Input
    static const byte R = 0;    // Reset bit
    
    static const byte O = 0;    // Output
    
private:
    
    ROM m_ROM;
    CPU m_CPU;
    RAM m_RAM;
    
    BUS outputROM, outputCPU, outputRAM;
    
public: 

    // Constructor
    COMPUTER() : Gate("COMPUTER",1,1,"R","O") {
        outputROM = m_ROM.CreateOutputBUS();
        outputCPU = m_CPU.CreateOutputBUS();
        outputRAM = m_RAM.CreateOutputBUS();
    }

    // Destuctor
    ~COMPUTER() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        
        BUS inputROM = m_ROM.CreateInputBUS();
        inputROM[ROM::I] = outputCPU[CPU::P];
        outputROM = m_ROM.ProcessBUS( inputROM );
        
        BUS inputCPU = m_CPU.CreateInputBUS();
        inputCPU[CPU::I] = outputROM[ROM::O];
        inputCPU[CPU::M] = outputRAM[RAM::O];
        inputCPU[CPU::R] = in[R];
        outputCPU = m_CPU.ProcessBUS( inputCPU );
        
        BUS inputRAM = m_RAM.CreateInputBUS();
        inputRAM[RAM::I] = outputCPU[CPU::O];
        inputRAM[RAM::A] = outputCPU[CPU::A];
        inputRAM[RAM::L] = outputCPU[CPU::L];
        outputRAM = m_RAM.ProcessBUS( inputRAM );
        
        return outputCPU; 
        
    }
    
    // Load program file
    inline bool LoadFile( const char* filename ) {
        return m_ROM.LoadFile( filename );
    }
    
    // Get active status
    inline bool IsActive() {
        return !m_CPU.halt;
    }
};

#endif
