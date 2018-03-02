#ifndef PC_H
#define PC_H

#include "REG.h"
#include "../../Gates/Compound/ADDER.h"
#include "../../Gates/Basic/MUX.h"
#include "../../Gates/Basic/OR.h"

class PC : public Gate {
    
public:
    
    static const byte I = 0;    // Input
    static const byte L = 1;    // Load bit
    static const byte N = 2;    // Increment bit
    static const byte R = 3;    // Reset bit
    
    static const byte O = 0;    // Output
    
private:
    
    OR m_OR;
    MUX m_MUX;
    ADDER m_ADDER;
    REG m_REG;
    
public: 

    // Constructor
    PC() : Gate("PC",4,1,"ILNR","O") {}

    // Destuctor
    ~PC() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // Get current registry data
        BUS inputREG = m_REG.CreateInputBUS();
        inputREG[REG::I] = ZeroIO();
        inputREG[REG::L] = ZeroIO();
        IO outputREG = m_REG.ProcessBUS( inputREG )[REG::O];
        
        // Select input
        BUS inputMUX = m_MUX.CreateInputBUS();
        inputMUX[MUX::A] = outputREG;
        inputMUX[MUX::B] = in[I];
        inputMUX[MUX::S] = in[L];
        in[I] = m_MUX.ProcessBUS( inputMUX )[MUX::O];
        
        // Increment value
        BUS inputADD = m_ADDER.CreateInputBUS();
        inputADD[ADDER::A] = in[I];
        inputADD[ADDER::B] = NumToIO(in[N][0]);
        in[I] = m_ADDER.ProcessBUS( inputADD )[ADDER::O];
        
        // Zero input
        inputMUX[MUX::A] = in[I];
        inputMUX[MUX::B] = ZeroIO();
        inputMUX[MUX::S] = in[R];
        in[I] = m_MUX.ProcessBUS( inputMUX )[MUX::O];
        
        // Determine registry writing
        IO inputOR = m_OR.CreateInputIO();
        inputOR[OR::A] = in[L][0];
        inputOR[OR::B] = in[R][0];
        IO outputOR = m_OR.Process( inputOR );
        inputOR[OR::A] = outputOR[OR::O];
        inputOR[OR::B] = in[N][0];
        outputOR = m_OR.Process( inputOR );
        
        // Registry manipulation
        inputREG[REG::I] = in[I];
        inputREG[REG::L] = FilledIO(outputOR[OR::O]);
        
        BUS output = CreateOutputBUS();   
        output[O] = m_REG.ProcessBUS( inputREG )[REG::O];
        return output; 
    }

};

#endif
