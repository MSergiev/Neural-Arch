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
#include "OR8WAY.h"
#include "MUX4WAY.h"
#include "DMUX4WAY.h"


void bin( bitset in, unsigned char size ) {
    
	char str[size+1];
	memset( str, 0, sizeof(str) );
	for( unsigned i = 0; i < size; ++i ) {
		str[size-i-1] = (in&1) + '0';
		in >>= 1;
	}
	std::cout << str;
    
}



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
	for( bitset i = 0; i < comb; ++i ) {
        bin(i, g->inputNum());
        std::cout << " -> ";
        bin(g->Process(i), g->outputNum());
		std::cout << std::endl;
        if(i > limit) break;
	}
	std::cout << std::endl;
    
}



void testBatch( Gate* g ) {

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
    test( &m_NAND );
    testBatch( &m_NAND );
    
    NOT m_NOT;
    test( &m_NOT );
    testBatch( &m_NOT );
    
    AND m_AND;
    test( &m_AND );
    testBatch( &m_AND );
    
    NOR m_NOR;
    test( &m_NOR );
    testBatch( &m_NOR );
    
    OR m_OR;
    test( &m_OR );
    testBatch( &m_OR );
    
    XOR m_XOR;
    test( &m_XOR );
    testBatch( &m_XOR );
    
    MUX m_MUX;
    test( &m_MUX );
    testBatch( &m_MUX );
    
    DMUX m_DMUX;
    test( &m_DMUX );
    testBatch( &m_DMUX );
    
    HA m_HA;
    test( &m_HA );
    testBatch( &m_HA );
    
    FA m_FA;
    test( &m_FA );
    testBatch( &m_FA );
    
    OR8WAY m_OR8WAY;
    test( &m_OR8WAY, 10 );
    testBatch( &m_OR8WAY );
    
    MUX4WAY m_MUX4WAY;
    test( &m_MUX4WAY );
    testBatch( &m_MUX4WAY );
    
    DMUX4WAY m_DMUX4WAY;
    test( &m_DMUX4WAY );
    testBatch( &m_DMUX4WAY );
    
    return 0;

}
