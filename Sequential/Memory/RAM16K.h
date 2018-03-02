#ifndef RAM16K_H
#define RAM16K_H

#include "RAM4K.h"

class RAM16K : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte A = 1;    // Address
    static const byte L = 2;    // Load bit
    
    static const byte A1 = 0;    // Address bit
    static const byte A2 = 1;    // Address bit
    static const byte A3 = 2;    // Address bit    
    static const byte A4 = 3;    // Address bit
    static const byte A5 = 4;    // Address bit
    static const byte A6 = 5;    // Address bit
    static const byte A7 = 6;    // Address bit
    static const byte A8 = 7;    // Address bit
    static const byte A9 = 8;    // Address bit  
    static const byte A10 = 9;   // Address bit
    static const byte A11 = 10;  // Address bit
    static const byte A12 = 11;  // Address bit  
    static const byte A13 = 12;  // Address bit
    static const byte A14 = 13;  // Address bit
    static const byte A15 = 14;  // Address bit    
    
    static const byte O = 0;    // Output
    
    static const unsigned SIZE = 16384; //RAM size
    
private:
    
    DMUX8WAY m_DMUX;
    RAM4K m_RAM4K[8];
    MUX8WAY m_MUX;
    
public: 

    // Constructor
    RAM16K() : Gate("RAM16K",3,1,"IAL","O") {}

    // Destuctor
    ~RAM16K() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // DMUX loading bit
        IO inputDMUX = m_DMUX.CreateInputIO();
        inputDMUX[DMUX8WAY::I] = in[L][0];
        inputDMUX[DMUX8WAY::S1] = in[A][A15];
        inputDMUX[DMUX8WAY::S2] = in[A][A14];
        inputDMUX[DMUX8WAY::S3] = in[A][A13];
        IO outputDMUX = m_DMUX.Process( inputDMUX );
        
        // Create RAM4K inputs
        BUS inputRAM4K[8];
        for( byte i = 0; i < 8; ++i ) {
            inputRAM4K[i] = m_RAM4K[i].CreateInputBUS();
            inputRAM4K[i][RAM4K::I] = in[I];
            inputRAM4K[i][RAM4K::L] = FilledIO(outputDMUX[i]);
            inputRAM4K[i][RAM4K::A] = ZeroIO();
            inputRAM4K[i][RAM4K::A][RAM4K::A1] = in[A][A1];
            inputRAM4K[i][RAM4K::A][RAM4K::A2] = in[A][A2];
            inputRAM4K[i][RAM4K::A][RAM4K::A3] = in[A][A3];
            inputRAM4K[i][RAM4K::A][RAM4K::A4] = in[A][A4];
            inputRAM4K[i][RAM4K::A][RAM4K::A5] = in[A][A5];
            inputRAM4K[i][RAM4K::A][RAM4K::A6] = in[A][A6];
            inputRAM4K[i][RAM4K::A][RAM4K::A7] = in[A][A7];
            inputRAM4K[i][RAM4K::A][RAM4K::A8] = in[A][A8];
            inputRAM4K[i][RAM4K::A][RAM4K::A9] = in[A][A9];
            inputRAM4K[i][RAM4K::A][RAM4K::A10] = in[A][A10];
            inputRAM4K[i][RAM4K::A][RAM4K::A11] = in[A][A11];
            inputRAM4K[i][RAM4K::A][RAM4K::A12] = in[A][A12];
#ifdef DEBUG
            if( outputDMUX[i] > 0.5 ) {
                IO ad = ZeroIO();
                ad[A1] = in[A][A10];
                ad[A2] = in[A][A11];
                ad[A3] = in[A][A12];
                std::cout << "RAM16K - Loading " << IOToNum(in[I]) << " to addr " << IOToNum(ad) << std::endl;
            }
#endif
        }
        
        // MUX registry outputs
        BUS inputMUX = m_MUX.CreateInputBUS();
        for( byte i = 0; i < 8; ++i ) {
            inputMUX[i] = m_RAM4K[i].ProcessBUS(inputRAM4K[i])[RAM4K::O];
        }
        inputMUX[MUX8WAY::S1] = FilledIO( in[A][A13] );
        inputMUX[MUX8WAY::S2] = FilledIO( in[A][A14] );
        inputMUX[MUX8WAY::S3] = FilledIO( in[A][A15] );
        
        BUS output = CreateOutputBUS();
        output[O] = m_MUX.ProcessBUS( inputMUX )[MUX8WAY::O];
        return output; 
    }
    
    // Dump registry contents
    inline void PrintRAM() {
        std::cout << "\n==========================\n";
        std::cout <<"Registry:\n";
        for( unsigned i = 0; i < SIZE; ++i ) {
            BUS input = CreateInputBUS();
            input[I] = ZeroIO();
            input[A] = NumToIO(i);
            input[L] = ZeroIO();
            IO output = ProcessBUS(input)[O];
            std::cout << "A: ";
            Bin(i,12);
            std::cout << " -> ";
            PrintIO(output);
            std::cout << " (" << IOToNum(output) << ")" << std::endl;
        }
        std::cout << "==========================\n";
    }

};

#endif
