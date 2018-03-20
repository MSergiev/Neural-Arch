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
    static const byte HALT = 1,     HALT_LEN = 1;   // System halt bit
    static const byte UNUSED = 2,   UNUSED_LEN = 1; // Unused bits
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
    
    bool halt;  // System halt flag
    
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
    CPU() : Gate("CPU",3,4,"IMR","OLAP"), halt(false) {
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
        PrintInputBUS(in);
        std::cout << std::endl;
        decompose( in[I] );
        if( halt ) {
            std::cout << "CPU halted" << std::endl;
            std::cout << std::endl;
            std::cout << "==================================" << std::endl;
            return CreateOutputBUS();
        }
#endif
        halt = ( in[I][OPC] > 0.5 and in[I][HALT] > 0.5 );
        
        BUS inputMUX = m_MUX.CreateInputBUS();
        inputMUX[MUX::A] = m_ALUOut;
        inputMUX[MUX::B] = SubIO( in[I], 1, ARCH );
        inputMUX[MUX::S] = FilledIO(m_NOT.Process( FilledIO(in[I][OPC]) )[NOT::O]);
        BUS outputMUX = m_MUX.ProcessBUS( inputMUX );
        
#ifdef DEBUG
        m_MUX.PrintInputBUS(inputMUX);
        std::cout << std::endl;
        m_MUX.PrintOutputBUS(outputMUX);
        std::cout << std::endl;
#endif
        
        IO inputOR = { in[I][D_ADDR], m_NOT.Process( FilledIO(in[I][OPC]) )[0] };
        BUS inputADDR = m_ADDR.CreateInputBUS();
        inputADDR[REG::I] = outputMUX[MUX::O];
        inputADDR[REG::L] = FilledIO( m_OR.Process( inputOR )[OR::O] );
        BUS outputADDR = m_ADDR.ProcessBUS( inputADDR );
        
#ifdef DEBUG
        std::cout << "ADDR ";
        m_ADDR.PrintInputBUS(inputADDR);
        std::cout << std::endl;
        std::cout << "ADDR ";
        m_ADDR.PrintOutputBUS(outputADDR);
        std::cout << std::endl;
#endif
        
        inputMUX[MUX::A] = outputADDR[REG::O];
        inputMUX[MUX::B] = in[M];
        inputMUX[MUX::S] = FilledIO( in[I][MEM] );
        outputMUX = m_MUX.ProcessBUS( inputMUX );
        
#ifdef DEBUG
        m_MUX.PrintInputBUS(inputMUX);
        std::cout << std::endl;
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
        m_ALU.PrintInputBUS(inputALU);
        std::cout << std::endl;
        m_ALU.PrintOutputBUS(outputALU);
        std::cout << std::endl;
#endif
        
        inputDATA = m_DATA.CreateInputBUS();
        inputDATA[REG::I] = m_ALUOut;
        inputDATA[REG::L] = FilledIO( in[I][D_DATA] );
        outputDATA = m_DATA.ProcessBUS( inputDATA );
        
#ifdef DEBUG
        std::cout << "DATA ";
        m_DATA.PrintInputBUS(inputDATA);
        std::cout << std::endl;
        std::cout << "DATA ";
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
        inputPC[PC::L] = FilledIO( outputPJUMP[AND::O] );
        inputPC[PC::N] = FilledIO( 1/*m_NOT.Process( outputPJUMP )[NOT::O]*/ );
        inputPC[PC::R] = in[R];
        BUS outputPC = m_PC.ProcessBUS( inputPC );
        
#ifdef DEBUG
        m_PC.PrintInputBUS(inputPC);
        std::cout << std::endl;
        m_PC.PrintOutputBUS(outputPC);
        std::cout << std::endl;
#endif
        
        BUS output = CreateOutputBUS();
        output[O] = m_ALUOut;
        output[L] = FilledIO( in[I][D_OUT] );
        output[A] = outputADDR[REG::O];
        output[P] = outputPC[PC::O];
        
#ifdef DEBUG
        PrintOutputBUS(output);
        std::cout << std::endl;
        std::cout << "==================================" << std::endl;
#endif
        return output; 
    }
    
    // Instruction decomposer
    void decompose( IO inst ) {
        
        if( inst[OPC] <= 0.5 ) {
            // A instruction
            std::cout << "A INST" << std::endl;
            std::cout << "VAL: ";
//             ReverseIO( inst );
//             inst.pop_back();
//             ReverseIO( inst );
            inst = SubIO( inst, 1, ARCH );
            PrintIO( inst );
            std::cout << " (" << IOToNum( inst ) << ")" << std::endl;
            std::cout << std::endl;
        }
        // C instruction
        else {
            std::cout << "C INST" << std::endl;
            std::cout << "LD: " << (inst[MEM] ? "RAM" : "ADDR") << std::endl;
            PrintOperation( inst );
            PrintDest( inst );
            PrintJump( inst );
            std::cout << std::endl;
        }
        
    }

    // Print operation
    void PrintOperation( IO in ) {
        std::cout << "OP: ";
        in = SubIO( in, CONT, CONT_LEN );
        ReverseIO( in );
        switch( IOToNum( in ) ) {
            case 0b101010: std::cout << (in[MEM] ? "" : "0") << std::endl;      break;
            case 0b111111: std::cout << (in[MEM] ? "" : "1") << std::endl;      break;
            case 0b111010: std::cout << (in[MEM] ? "" : "-1") << std::endl;     break;
            case 0b001100: std::cout << (in[MEM] ? "" : "D") << std::endl;      break;
            case 0b110000: std::cout << (in[MEM] ? "M" : "A") << std::endl;     break;
            case 0b001101: std::cout << (in[MEM] ? "" : "!D") << std::endl;     break;
            case 0b110001: std::cout << (in[MEM] ? "!M" : "!A") << std::endl;   break;
            case 0b001111: std::cout << (in[MEM] ? "" : "-D") << std::endl;     break;
            case 0b110011: std::cout << (in[MEM] ? "-M" : "-A") << std::endl;   break;
            case 0b011111: std::cout << (in[MEM] ? "" : "D+1") << std::endl;    break;
            case 0b110111: std::cout << (in[MEM] ? "M+1" : "A+1") << std::endl; break;
            case 0b001110: std::cout << (in[MEM] ? "" : "D-1") << std::endl;    break;
            case 0b110010: std::cout << (in[MEM] ? "M-1" : "A-1") << std::endl; break;
            case 0b000010: std::cout << (in[MEM] ? "D+M" : "D+A") << std::endl; break;
            case 0b010011: std::cout << (in[MEM] ? "D-M" : "D-A") << std::endl; break;
            case 0b000111: std::cout << (in[MEM] ? "M-D" : "A-D") << std::endl; break;
            case 0b000000: std::cout << (in[MEM] ? "D&M" : "D&A") << std::endl; break;
            case 0b010101: std::cout << (in[MEM] ? "D|M" : "D|A") << std::endl; break;
        }
    }
    
    // Print destination
    void PrintDest( IO in ) {
        std::cout << "DEST: ";
        if( in[D_ADDR] ) std::cout << "ADDR ";
        if( in[D_DATA] ) std::cout << "DATA ";
        if( in[D_OUT] ) std::cout << "OUT ";
        std::cout << std::endl;
    }
    
    // Print jump condition
    void PrintJump( IO in ) {
        std::cout << "JUMP: ";
        in = SubIO( in, JUMP, JUMP_LEN );
        ReverseIO( in );
        switch( IOToNum( in ) ) {
            case 0b000: std::cout << "NULL" << std::endl;      break;
            case 0b001: std::cout << "OUT > 0" << std::endl;      break;
            case 0b010: std::cout << "OUT == 0" << std::endl;     break;
            case 0b011: std::cout << "OUT >= 0" << std::endl;      break;
            case 0b100: std::cout << "OUT < 0" << std::endl;     break;
            case 0b101: std::cout << "OUT != 0" << std::endl;     break;
            case 0b110: std::cout << "OUT <= 0" << std::endl;     break;
            case 0b111: std::cout << "*" << std::endl;     break;
        }
    }
    
};

#endif
