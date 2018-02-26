#ifndef RAM64_H
#define RAM64_H

#include "RAM8.h"

class RAM64 : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte A = 1;    // Address
    static const byte L = 2;    // Load bit
    
    static const byte A1 = ARCH-1;    // Address bit
    static const byte A2 = ARCH-2;    // Address bit
    static const byte A3 = ARCH-3;    // Address bit    
    static const byte A4 = ARCH-4;    // Address bit
    static const byte A5 = ARCH-5;    // Address bit
    static const byte A6 = ARCH-6;    // Address bit
    
    static const byte O = 0;    // Output
    
    static const byte SIZE = 64; //RAM size
    
private:
    
    DMUX8WAY m_DMUX;
    RAM8 m_RAM8[8];
    MUX8WAY m_MUX;
    
public: 

    // Constructor
    RAM64() : Gate("RAM64",3,1,"IAL","O") {}

    // Destuctor
    ~RAM64() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // DMUX loading bit
        IO inputDMUX = m_DMUX.CreateInputIO();
        inputDMUX[DMUX8WAY::I] = in[L][ARCH-1];
        inputDMUX[DMUX8WAY::S1] = in[A][A6];
        inputDMUX[DMUX8WAY::S2] = in[A][A5];
        inputDMUX[DMUX8WAY::S3] = in[A][A4];
        IO outputDMUX = m_DMUX.Process( inputDMUX );
        
        // Create RAM8 inputs
        BUS inputRAM8[8];
        for( byte i = 0; i < 8; ++i ) {
            inputRAM8[i] = m_RAM8[i].CreateInputBUS();
            inputRAM8[i][RAM8::I] = in[I];
            inputRAM8[i][RAM8::L] = FilledIO(outputDMUX[i]);
            inputRAM8[i][RAM8::A] = ZeroIO();
            inputRAM8[i][RAM8::A][RAM8::A1] = in[A][A1];
            inputRAM8[i][RAM8::A][RAM8::A2] = in[A][A2];
            inputRAM8[i][RAM8::A][RAM8::A3] = in[A][A3];
#ifdef DEBUG
            if( outputDMUX[i] > 0.5 ) {
                IO ad = ZeroIO();
                ad[A1] = in[A][A4];
                ad[A2] = in[A][A5];
                ad[A3] = in[A][A6];
                std::cout << "RAM64 - Loading " << IOToNum(in[I]) << " to addr " << IOToNum(ad) << std::endl;
            }
#endif
        }
        
        // MUX registry outputs
        BUS inputMUX = m_MUX.CreateInputBUS();
        for( byte i = 0; i < 8; ++i ) {
            inputMUX[i] = m_RAM8[i].ProcessBUS(inputRAM8[i])[RAM8::O];
        }
        inputMUX[MUX8WAY::S1] = FilledIO( in[A][A4] );
        inputMUX[MUX8WAY::S2] = FilledIO( in[A][A5] );
        inputMUX[MUX8WAY::S3] = FilledIO( in[A][A6] );
        
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
            Bin(i,6);
            std::cout << " -> ";
            PrintIO(output);
            std::cout << " (" << IOToNum(output) << ")" << std::endl;
        }
        std::cout << "==========================\n";
    }

};

#endif
