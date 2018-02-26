#ifndef RAM8_H
#define RAM8_H

#include "../../Gates/Basic/DMUX8WAY.h"
#include "REG.h"
#include "../../Gates/Basic/MUX8WAY.h"

class RAM8 : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte A = 1;    // Address
    static const byte L = 2;    // Load bit
    
    static const byte A1 = ARCH-1;    // Address bit
    static const byte A2 = ARCH-2;    // Address bit
    static const byte A3 = ARCH-3;    // Address bit
    
    static const byte O = 0;    // Output
    
    static const byte SIZE = 8; //RAM size
    
private:
    
    DMUX8WAY m_DMUX;
    REG m_REG[8];
    MUX8WAY m_MUX;
    
public: 

    // Constructor
    RAM8() : Gate("RAM8",3,1,"IAL","O") {}

    // Destuctor
    ~RAM8() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return (*m_REG).Process( in );
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // DMUX loading bit
        IO inputDMUX = m_DMUX.CreateInputIO();
        inputDMUX[DMUX8WAY::I] = in[L][ARCH-1];
        inputDMUX[DMUX8WAY::S1] = in[A][A3];
        inputDMUX[DMUX8WAY::S2] = in[A][A2];
        inputDMUX[DMUX8WAY::S3] = in[A][A1];
        IO outputDMUX = m_DMUX.Process( inputDMUX );
        
        // Create registry inputs
        BUS inputREG[8];
        for( byte i = 0; i < 8; ++i ) {
            inputREG[i] = m_REG[i].CreateInputBUS();
            inputREG[i][REG::I] = in[I];
            inputREG[i][REG::L] = FilledIO(outputDMUX[i]);
#ifdef DEBUG
            if( outputDMUX[i] > 0.5 ) {
                std::cout << "RAM8 - Loading " << IOToNum(in[I]) << " to addr " << (int)i << std::endl;
            }
#endif
        }
        
        // MUX registry outputs
        BUS inputMUX = m_MUX.CreateInputBUS();
        for( byte i = 0; i < 8; ++i ) {
            inputMUX[i] = m_REG[i].ProcessBUS(inputREG[i])[REG::O];
        }
        inputMUX[MUX8WAY::S1] = FilledIO( in[A][A1] );
        inputMUX[MUX8WAY::S2] = FilledIO( in[A][A2] );
        inputMUX[MUX8WAY::S3] = FilledIO( in[A][A3] );
        
        BUS output = CreateOutputBUS();
        output[O] = m_MUX.ProcessBUS( inputMUX )[MUX8WAY::O];
        return output; 
    }
    
    // Dump registry contents
    inline void PrintRAM() {
        std::cout << "\n==========================\n";
        std::cout <<"Registry:\n";
        for( byte i = 0; i < SIZE; ++i ) {
            BUS input = CreateInputBUS();
            input[I] = ZeroIO();
            input[A] = NumToIO(i);
            input[L] = ZeroIO();
            IO output = ProcessBUS(input)[O];
            std::cout << "A: ";
            Bin(i,3);
            std::cout << " -> ";
            PrintIO(output);
            std::cout << " (" << IOToNum(output) << ")" << std::endl;
        }
        std::cout << "==========================\n";
    }

};

#endif
