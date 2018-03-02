#ifndef RAM4K_H
#define RAM4K_H

#include "RAM512.h"

class RAM4K : public Gate {

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
    
    static const byte O = 0;    // Output
    
    static const unsigned SIZE = 4096; //RAM size
    
private:
    
    DMUX8WAY m_DMUX;
    RAM512 m_RAM512[8];
    MUX8WAY m_MUX;
    
public: 

    // Constructor
    RAM4K() : Gate("RAM4K",3,1,"IAL","O") {}

    // Destuctor
    ~RAM4K() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // DMUX loading bit
        IO inputDMUX = m_DMUX.CreateInputIO();
        inputDMUX[DMUX8WAY::I] = in[L][0];
        inputDMUX[DMUX8WAY::S1] = in[A][A12];
        inputDMUX[DMUX8WAY::S2] = in[A][A11];
        inputDMUX[DMUX8WAY::S3] = in[A][A10];
        IO outputDMUX = m_DMUX.Process( inputDMUX );
        
        // Create RAM512 inputs
        BUS inputRAM512[8];
        for( byte i = 0; i < 8; ++i ) {
            inputRAM512[i] = m_RAM512[i].CreateInputBUS();
            inputRAM512[i][RAM512::I] = in[I];
            inputRAM512[i][RAM512::L] = FilledIO(outputDMUX[i]);
            inputRAM512[i][RAM512::A] = ZeroIO();
            inputRAM512[i][RAM512::A][RAM512::A1] = in[A][A1];
            inputRAM512[i][RAM512::A][RAM512::A2] = in[A][A2];
            inputRAM512[i][RAM512::A][RAM512::A3] = in[A][A3];
            inputRAM512[i][RAM512::A][RAM512::A4] = in[A][A4];
            inputRAM512[i][RAM512::A][RAM512::A5] = in[A][A5];
            inputRAM512[i][RAM512::A][RAM512::A6] = in[A][A6];
            inputRAM512[i][RAM512::A][RAM512::A7] = in[A][A7];
            inputRAM512[i][RAM512::A][RAM512::A8] = in[A][A8];
            inputRAM512[i][RAM512::A][RAM512::A9] = in[A][A9];
#ifdef DEBUG
            if( outputDMUX[i] > 0.5 ) {
                IO ad = ZeroIO();
                ad[A1] = in[A][A10];
                ad[A2] = in[A][A11];
                ad[A3] = in[A][A12];
                std::cout << "RAM4K - Loading " << IOToNum(in[I]) << " to addr " << IOToNum(ad) << std::endl;
            }
#endif
        }
        
        // MUX registry outputs
        BUS inputMUX = m_MUX.CreateInputBUS();
        for( byte i = 0; i < 8; ++i ) {
            inputMUX[i] = m_RAM512[i].ProcessBUS(inputRAM512[i])[RAM512::O];
        }
        inputMUX[MUX8WAY::S1] = FilledIO( in[A][A10] );
        inputMUX[MUX8WAY::S2] = FilledIO( in[A][A11] );
        inputMUX[MUX8WAY::S3] = FilledIO( in[A][A12] );
        
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
