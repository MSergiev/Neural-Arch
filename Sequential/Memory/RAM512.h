#ifndef RAM512_H
#define RAM512_H

#include "RAM64.h"

class RAM512 : public Gate {

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
    
    static const byte O = 0;    // Output
    
    static const unsigned SIZE = 512; //RAM size
    
private:
    
    DMUX8WAY m_DMUX;
    RAM64 m_RAM64[8];
    MUX8WAY m_MUX;
    
public: 

    // Constructor
    RAM512() : Gate("RAM512",3,1,"IAL","O") {}

    // Destuctor
    ~RAM512() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        // DMUX loading bit
        IO inputDMUX = m_DMUX.CreateInputIO();
        inputDMUX[DMUX8WAY::I] = in[L][0];
        inputDMUX[DMUX8WAY::S1] = in[A][A9];
        inputDMUX[DMUX8WAY::S2] = in[A][A8];
        inputDMUX[DMUX8WAY::S3] = in[A][A7];
        IO outputDMUX = m_DMUX.Process( inputDMUX );
        
        // Create RAM64 inputs
        BUS inputRAM64[8];
        for( byte i = 0; i < 8; ++i ) {
            inputRAM64[i] = m_RAM64[i].CreateInputBUS();
            inputRAM64[i][RAM64::I] = in[I];
            inputRAM64[i][RAM64::L] = FilledIO(outputDMUX[i]);
            inputRAM64[i][RAM64::A] = ZeroIO();
            inputRAM64[i][RAM64::A][RAM64::A1] = in[A][A1];
            inputRAM64[i][RAM64::A][RAM64::A2] = in[A][A2];
            inputRAM64[i][RAM64::A][RAM64::A3] = in[A][A3];
            inputRAM64[i][RAM64::A][RAM64::A4] = in[A][A4];
            inputRAM64[i][RAM64::A][RAM64::A5] = in[A][A5];
            inputRAM64[i][RAM64::A][RAM64::A6] = in[A][A6];
#ifdef DEBUG
            if( outputDMUX[i] > 0.5 ) {
                IO ad = ZeroIO();
                ad[A1] = in[A][A7];
                ad[A2] = in[A][A8];
                ad[A3] = in[A][A9];
                std::cout << "RAM512 - Loading " << IOToNum(in[I]) << " to addr " << IOToNum(ad) << std::endl;
            }
#endif
        }
        
        // MUX registry outputs
        BUS inputMUX = m_MUX.CreateInputBUS();
        for( byte i = 0; i < 8; ++i ) {
            inputMUX[i] = m_RAM64[i].ProcessBUS(inputRAM64[i])[RAM64::O];
        }
        inputMUX[MUX8WAY::S1] = FilledIO( in[A][A7] );
        inputMUX[MUX8WAY::S2] = FilledIO( in[A][A8] );
        inputMUX[MUX8WAY::S3] = FilledIO( in[A][A9] );
        
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
            Bin(i,9);
            std::cout << " -> ";
            PrintIO(output);
            std::cout << " (" << IOToNum(output) << ")" << std::endl;
        }
        std::cout << "==========================\n";
    }

};

#endif
