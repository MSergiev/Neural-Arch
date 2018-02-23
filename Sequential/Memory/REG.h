#ifndef REG_H
#define REG_H

#include "BIT.h"

class REG : public Gate {
    
public:
    
    static const byte I = 0;    // Input
    static const byte L = 1;    // Load bit
    
    static const byte O = 0;    // Output
    
private:
    
    BIT m_BIT[ARCH];
    
public: 

    // Constructor
    REG() : Gate("REG",2,1,"IL","O") {}

    // Destuctor
    ~REG() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return (*m_BIT).Process( in );
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        BUS output = CreateOutputBUS();
        
        for( byte i = 0; i < ARCH; ++i ) {
            IO input = (*m_BIT).CreateInputIO();
            input[BIT::I] = in[I][i];
            input[BIT::L] = in[L][ARCH-1];
            output[O][i] = m_BIT[i].Process(input)[BIT::O];
        }
        
        return output; 
    }

};

#endif
