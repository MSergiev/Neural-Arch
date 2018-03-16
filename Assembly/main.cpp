#define DEBUG
#define ROUND

#include <iostream>

#include "Parser.h"

static char IN[] = "Test.asm";
static char OUT[] = "ROM.txt";

int main( int argc, const char* argv[] ) {
    
//     if( argc < 3 ) {
//         std::cerr << "ERROR: expected 2 arguments, provided " << (argc-1) << std::endl;
//         std::cerr << "Usage: parse [INPUT] [OUTPUT]" << std::endl;
//         return -1;
//     }
    
    if( argc == 1 ) PARSER::parse( IN, OUT );
    else if( argc == 2 ) PARSER::parse( argv[1], OUT );
    else PARSER::parse( argv[1], argv[2] );

	return 0;
}
