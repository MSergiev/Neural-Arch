#ifndef CPU_H
#define CPU_H

#include "../Sequential/Memory/PC.h"
#include "../Sequential/Memory/REG.h"
#include "../Gates/Basic/MUX.h"
#include "../Gates/Basic/NOT.h"
#include "../Gates/Basic/AND.h"
#include "../Gates/Basic/NAND.h"
#include "../Gates/Basic/OR.h"
#include "../Gates/Compound/ALU.h"


class CPU : public Gate {
    
public:
    
    static const byte I = 0;    // Instruction input
    static const byte M = 1;    // Mempory input
    static const byte R = 2;    // Reset bit
    
    static const byte O = 0;    // Output
    static const byte L = 1;    // Memory load bit
    static const byte A = 2;    // Memory address
    static const byte P = 3;    // Next instruction address
    
    // Instruction composition
    static const byte OPC = 0,      OPC_LEN = 1;    // Opcode
    static const byte UNUSED = 1,   UNUSED_LEN = 2; // Unused bits
    static const byte MEM = 3,      MEM_LEN = 1;    // Input/Reg selector
    static const byte CONT = 4,     CONT_LEN = 6;   // Control bits
    static const byte DEST = 10,    DEST_LEN = 3;   // Destination
    static const byte D_ADDR = 10,  D_ADDR_LEN = 1;   // Destination - address register
    static const byte D_DATA = 11,  D_DATA_LEN = 1;   // Destination - data register
    static const byte D_OUT = 12,   D_OUT_LEN = 1;   // Destination - output
    static const byte JUMP = 13,    JUMP_LEN = 3;   // Jump
    static const byte J_N = 13,     J_N_LEN = 1;   // Negative jump
    static const byte J_Z = 14,     J_Z_LEN = 1;   // Zero jump
    static const byte J_P = 15,     J_P_LEN = 1;   // Positive jump
    
private:
    
    MUX m_MUX;
    NOT m_NOT;
    OR m_OR;
    AND m_AND;
    NAND m_NAND;
    ALU m_ALU;
    PC m_PC;
    REG m_ADDR;
    REG m_DATA;
    
    IO m_ALUOut;
    
public: 

    // Constructor
    CPU() : Gate("CPU",3,4,"IMR","OLAP") {
        m_ALUOut = ZeroIO();
    }

    // Destuctor
    ~CPU() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
#ifdef DEBUG
        std::cout << "==================================" << std::endl;
        std::cout << "In:" << std::endl;
        PrintInputBUS(in);
        std::cout << std::endl;
#endif
        
        BUS inputMUX = m_MUX.CreateInputBUS();
        IO val = SubIO( in[I], 1, ARCH-1 );
        val.push_back(0);
        inputMUX[MUX::A] = m_ALUOut;
        inputMUX[MUX::B] = val;
        inputMUX[MUX::S] = FilledIO(m_NOT.Process( FilledIO(in[I][OPC]) )[NOT::O]);
        BUS outputMUX = m_MUX.ProcessBUS( inputMUX );
        
#ifdef DEBUG
        std::cout << "MUX In:" << std::endl;
        m_MUX.PrintInputBUS(inputMUX);
        std::cout << std::endl;
        std::cout << "MUX Out:" << std::endl;
        m_MUX.PrintOutputBUS(outputMUX);
        std::cout << std::endl;
#endif
        
        IO inputOR = { in[I][D_ADDR], m_NOT.Process( FilledIO(in[I][OPC]) )[0] };
        BUS inputADDR = m_ADDR.CreateInputBUS();
        inputADDR[REG::I] = outputMUX[MUX::O];
        inputADDR[REG::L] = FilledIO( m_OR.Process( inputOR )[OR::O] );
        BUS outputADDR = m_ADDR.ProcessBUS( inputADDR );
        
#ifdef DEBUG
        std::cout << "ADDR In:" << std::endl;
        m_ADDR.PrintInputBUS(inputADDR);
        std::cout << std::endl;        
        std::cout << "ADDR Out:" << std::endl;
        m_ADDR.PrintOutputBUS(outputADDR);
        std::cout << std::endl;
#endif
        
        inputMUX[MUX::A] = outputADDR[REG::O];
        inputMUX[MUX::B] = in[M];
        inputMUX[MUX::S] = FilledIO( in[I][MEM] );
        outputMUX = m_MUX.ProcessBUS( inputMUX );
        
#ifdef DEBUG
        std::cout << "MUX In:" << std::endl;
        m_MUX.PrintInputBUS(inputMUX);
        std::cout << std::endl;
        std::cout << "MUX Out:" << std::endl;
        m_MUX.PrintOutputBUS(outputMUX);
        std::cout << std::endl;
#endif
        
        BUS inputDATA = m_DATA.CreateInputBUS();
        inputDATA[REG::I] = ZeroIO();
        inputDATA[REG::L] = ZeroIO();
        BUS outputDATA = m_DATA.ProcessBUS( inputDATA );
        
        BUS inputALU = m_ALU.CreateInputBUS();
        inputALU[ALU::A] = outputDATA[REG::O];
        inputALU[ALU::B] = outputMUX[MUX::O];
        inputALU[ALU::CI] = SubIO( in[I], CONT, CONT_LEN );
        BUS outputALU = m_ALU.ProcessBUS( inputALU );
        m_ALUOut = outputALU[ALU::O];
        
#ifdef DEBUG
        std::cout << "ALU In:" << std::endl;
        m_ALU.PrintInputBUS(inputALU);
        std::cout << std::endl;        
        std::cout << "ALU Out:" << std::endl;
        m_ALU.PrintOutputBUS(outputALU);
        std::cout << std::endl;
#endif
        
        inputDATA = m_DATA.CreateInputBUS();
        inputDATA[REG::I] = m_ALUOut;
        inputDATA[REG::L] = FilledIO( in[I][D_DATA] );
        outputDATA = m_DATA.ProcessBUS( inputDATA );
        
#ifdef DEBUG
        std::cout << "DATA In:" << std::endl;
        m_DATA.PrintInputBUS(inputDATA);
        std::cout << std::endl;        
        std::cout << "DATA Out:" << std::endl;
        m_DATA.PrintOutputBUS(outputDATA);
        std::cout << std::endl;
#endif
        
        IO inputNJUMP = m_AND.CreateInputIO();
        inputNJUMP[AND::A] = in[I][J_N];
        inputNJUMP[AND::B] = outputALU[ALU::C][ALU::NG];
        IO outputNJUMP = m_AND.Process( inputNJUMP );
        
        IO inputZJUMP = m_AND.CreateInputIO();
        inputZJUMP[AND::A] = in[I][J_Z];
        inputZJUMP[AND::B] = outputALU[ALU::C][ALU::ZO];
        IO outputZJUMP = m_AND.Process( inputZJUMP );
        
        IO inputPJUMP = m_AND.CreateInputIO();
        IO inputNAND = m_NAND.CreateInputIO();
        inputNAND[NAND::A] = outputALU[ALU::C][ALU::NG];
        inputNAND[NAND::B] = outputALU[ALU::C][ALU::ZO];
        inputPJUMP[AND::A] = in[I][J_P];
        inputPJUMP[AND::B] = m_NAND.Process( inputNAND )[NAND::O];
        IO outputPJUMP = m_AND.Process( inputPJUMP );
        
        BUS inputPC = m_PC.CreateInputBUS();
        inputPC[PC::I] = outputADDR[REG::O];
        inputPC[PC::L] = FilledIO(outputPJUMP[AND::O]);
        inputPC[PC::N] = FilledIO(1);
        inputPC[PC::R] = in[R];
        BUS outputPC = m_PC.ProcessBUS( inputPC );
        
#ifdef DEBUG
        std::cout << "PC In:" << std::endl;
        m_PC.PrintInputBUS(inputPC);
        std::cout << std::endl;
        std::cout << "PC Out:" << std::endl;
        m_PC.PrintOutputBUS(outputPC);
        std::cout << std::endl;
#endif
        
        BUS output = CreateOutputBUS();
        output[O] = m_ALUOut;
        output[L] = FilledIO( in[I][D_OUT] );
        output[A] = outputADDR[REG::O];
        output[P] = outputPC[PC::O];
        
#ifdef DEBUG
        std::cout << "Output:" << std::endl;
        PrintOutputBUS(output);
        std::cout << std::endl;
        std::cout << "==================================" << std::endl;
#endif
        return output; 
    }

};

#endif
