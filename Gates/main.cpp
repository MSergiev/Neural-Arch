#define ROUND


#include "Basic/NAND.h"
#include "Basic/NOT.h"
#include "Basic/AND.h"
#include "Basic/NOR.h"
#include "Basic/OR.h"
#include "Basic/OR8WAY.h"
#include "Basic/XOR.h"
#include "Basic/MUX.h"
#include "Basic/MUX4WAY.h"
#include "Basic/MUX8WAY.h"
#include "Basic/DMUX.h"
#include "Basic/DMUX4WAY.h"
#include "Basic/DMUX8WAY.h"
#include "Compound/HA.h"
#include "Compound/FA.h"
#include "Compound/ADDER.h"
#include "Compound/ALU.h"



void test( Gate* g, unsigned limit = 64 ) {
    
    std::cout << "////////////////////" << std::endl;
    std::cout << "       " << g->GateID() << std::endl;
    std::cout << "////////////////////" << std::endl << std::endl;
    
    std::cout << g->inputPinout() << "    " << g->outputPinout() << std::endl;
    for( unsigned char i = 0; i < (g->inputNum() + g->outputNum() + 4); ++i  ) {
        std::cout << "=";
    }
    std::cout << std::endl;
    
    unsigned comb = std::pow(2,g->inputNum());
	for( unsigned i = 0; i < comb; ++i ) {
        IO input = NumToIO( i, g->inputNum() );
        PrintIO( input );
        std::cout << " -> ";
        PrintIO( g->Process(input) );
		std::cout << std::endl;
        if(i > limit) break;
	}
	std::cout << std::endl;
    
}

void testParallel( Gate* g ) {
    
    BUS input;
    input.push_back( NumToIO(0b00001111) );
    input.push_back( NumToIO(0b01010011) );
    input.push_back( NumToIO(0b11111111) );
    
    PrintBUS( input, g->inputNum() );
    for( unsigned char j = 0; j < ARCH+4; ++j  ) {
        std::cout << "=";
    }
    std::cout << std::endl;
    PrintBUS( g->ProcessBUS(input), g->outputNum() );
    std::cout << std::endl;
    
}



int main() {
    
    NAND m_NAND;
    test( &m_NAND );
    testParallel( &m_NAND );
    
    NOT m_NOT;
    test( &m_NOT );
    testParallel( &m_NOT );
    
    AND m_AND;
    test( &m_AND );
    testParallel( &m_AND );
    
    NOR m_NOR;
    test( &m_NOR );
    testParallel( &m_NOR );
    
    OR m_OR;
    test( &m_OR );
    testParallel( &m_OR );
    
    OR8WAY m_OR8WAY;
    test( &m_OR8WAY, 10 );
    
    XOR m_XOR;
    test( &m_XOR );
    testParallel( &m_XOR );
    
    MUX m_MUX;
    test( &m_MUX );
    testParallel( &m_MUX );
    
    MUX4WAY m_MUX4WAY;
    test( &m_MUX4WAY );
    
    MUX8WAY m_MUX8WAY;
    test( &m_MUX8WAY );
    
    DMUX m_DMUX;
    test( &m_DMUX );

    DMUX4WAY m_DMUX4WAY;
    test( &m_DMUX4WAY );
    
    DMUX8WAY m_DMUX8WAY;
    test( &m_DMUX8WAY );
    
    HA m_HA;
    test( &m_HA );
    
    FA m_FA;
    test( &m_FA );
    testParallel( &m_FA );
    
    ADDER m_ADDER;
    test( &m_ADDER );
    testParallel( &m_ADDER );

    ALU m_ALU;
    test( &m_ALU );
    testParallel( &m_ALU );
    
    return 0;

}
