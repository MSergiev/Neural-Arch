#include "NAND.h"
#include "NOT.h"
#include "AND.h"
#include "NOR.h"
#include "OR.h"
#include "XOR.h"
#include "MUX.h"
#include "DMUX.h"
#include "HA.h"
#include "FA.h"


void bin( bitset in, unsigned char size ) {
	char str[size+1];
	memset( str, 0, sizeof(str) );
	for( unsigned i = 0; i < size; ++i ) {
		str[size-i-1] = (in&1) + '0';
		in >>= 1;
	}
	std::cout << str;
}



void test( Gate* g ) {
    std::cout << "/////////" << std::endl;
    std::cout << "   " << g->GateID() << std::endl;
    std::cout << "/////////" << std::endl << std::endl;
    std::cout << g->inputPinout() << "    " << g->outputPinout() << std::endl;
    for( unsigned char i = 0; i < (g->inputNum() + g->outputNum() + 4); ++i  ) {
        std::cout << "=";
    }
    std::cout << std::endl;
    
    unsigned char comb = std::pow(2,g->inputNum());
	for( bitset i = 0; i < comb; ++i ) {
        bin(i, g->inputNum());
        std::cout << " -> ";
        bin(g->Process(i), g->outputNum());
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



void testBatch( Gate* g ) {
    std::cout << "////////////////////" << std::endl;
    std::cout << "       " << g->GateID() << std::endl;
    std::cout << "////////////////////" << std::endl << std::endl;

    bitset input[g->inputNum()];
    for( unsigned char j = 0; j < g->inputNum(); ++j ) {
        std::cout << g->inputPinout()[j] << " = ";
        bin(input[j], ARCH);
        std::cout << std::endl;
    }
    
    for( unsigned char j = 0; j < ARCH+4; ++j  ) {
        std::cout << "=";
    }
    
    std::cout << std::endl;
    
    for( unsigned char j = 0; j < g->outputNum(); ++j ) {
        std::cout << g->outputPinout()[j] << " = ";
        bin( Batch(g, input), ARCH); 
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



int main() {
    
    NAND m_NAND;
    NOT m_NOT;
    AND m_AND;
    NOR m_NOR;
    OR m_OR;
    XOR m_XOR;
    MUX m_MUX;
    DMUX m_DMUX;
    HA m_HA;
    FA m_FA;
    
    test( &m_NAND );
    test( &m_NOT );
    test( &m_AND );
    test( &m_NOR );
    test( &m_OR );
    test( &m_XOR );
    test( &m_MUX );
    test( &m_DMUX );
    test( &m_HA );
    test( &m_FA );
    
    testBatch( &m_NAND );
    testBatch( &m_NOT );
    testBatch( &m_AND );
    testBatch( &m_NOR );
    testBatch( &m_OR );
    testBatch( &m_XOR );
    
    return 0;

}
