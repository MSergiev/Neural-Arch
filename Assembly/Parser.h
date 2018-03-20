#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <vector>

#define STR_LIM 256

// Table typedef
typedef std::map<std::string, unsigned> Table;



class PARSER {
    
    // Special registry table
    static const Table regTable;
    // Operation table
    static const Table opTable;
    // Memory operation table
    static const Table mopTable;
    // Jump condition table
    static const Table jmpTable;
    // Destination table
    static const Table dstTable;
    
    // Variable table
    static Table varTable;
    static unsigned lastAddr;
    
    // Instructuion parts
    static const unsigned char AOP = 1;
    static const unsigned char AVAL = 15;
    
    static const unsigned char COP = 3;
    static const unsigned char CMEM = 1;
    static const unsigned char COPR = 6;
    static const unsigned char CDST = 3;
    static const unsigned char CJMP = 3;
    
    // Current line number
    static unsigned instNum;
    static unsigned lineNum;
    static bool multiComment;
    
    
public: 

    // Constructor
    PARSER() {}

    // Destuctor
    ~PARSER() {}
    
    // Load program file into PARSER 
    inline static void parse( const char* inFilename, const char* outFilename ) {
        
        varTable.clear();
        instNum = 0;
        lineNum = 1;
        multiComment = false;
        
        std::ifstream inFile( inFilename );
        std::ofstream outFile( outFilename );
        if( !inFile ) {
            std::cerr << "ERROR: " << inFilename << " does not exist!" << std::endl;
            return;
        }
        
        char line[STR_LIM];
        inFile.getline( line, sizeof(line) );
        
        
        while(1) {
            std::cout << "Line: [" << line << "]" << std::endl;
            trim( line );
            std::cout << "Trimmed: [" << line << "]" << std::endl;
            
            if( line[0] != 0 ) {
                // Label
                if( !ParseLabel( line ) ) {
                    // A instruction
                    if( SUBSTR( line, 2) == "LD" ) {
                        if( !ParseAInst( outFile, line ) ) return;
                    }
                    // C instruction
                    else {
                        if( !ParseCInst( outFile, line ) ) return;
                    }
                    outFile << '\n';
                    instNum++;
                }
            }
            
            if( inFile.eof() ) break;
            inFile.getline( line, sizeof(line) );
            lineNum++;
        }
        WriteHalt( outFile );
        std::cout << inFilename << " parsed" << std::endl;
        outFile.close();
        
    }

private:    // Parsers
    
    // A instruction parser
    inline static bool ParseAInst( std::ofstream& file, char* line ) {
        
        file << DTOC(0);
        unsigned val = 0;
        // Explicit address
        if( line[2] >= '0' and line[2] <= '9' ) {
            val = STOU( &line[2] );
        }
        // Special register
        else if( regTable.find( &line[2] ) != regTable.end() ) {
            val = regTable.at( &line[2] );
        }
        // Variable
        else {
            if( varTable.find( &line[2] ) == varTable.end() ) {
                varTable[&line[2]] = lastAddr;
                lastAddr++;
            }
            val = varTable[&line[2]];
        }
        WriteBinVal( file, val, AVAL );
        return true;
        
    }
    
    // C instruction parser
    inline static bool ParseCInst( std::ofstream& file, char* line ) {
        
        file << DTOC(1);
        file << DTOC(0);
        file << DTOC(1);
        
        // Get operation
        char opr[16];
        memset( opr, 0, sizeof(opr) );
        unsigned char idx = 0;
        while( line[idx] != ';' and line[idx] != '\n' and line[idx] != 0 ) {
            idx++;
        }
        memcpy( opr, line, idx );
        
        if( opTable.find( opr ) != opTable.end() ) {
            file << 0;
            WriteBinVal( file, opTable.at(opr), COPR );
        } else if( mopTable.find( opr ) != mopTable.end() ) {
            file << 1;
            WriteBinVal( file, mopTable.at(opr), COPR );
        } else {
            std::cerr << "Line " << lineNum << ": Invalid operation" << std::endl;
            return false;
        }
        
        // Get destination
        char dst[] = { line[4] };
        if( dstTable.find( dst ) != dstTable.end() ) {
            WriteBinVal( file, dstTable.at( dst ), CDST );
        } else {
            WriteBinVal( file, 0, CDST );
        }
        
        // Get jump condition
        if( line[idx] == ';' ) {
            if( jmpTable.find( &line[idx+1] ) != jmpTable.end() ) {
                WriteBinVal( file, jmpTable.at( &line[idx+1] ), CJMP );
            } else {
                std::cerr << "Line " << lineNum << ": Invalid jump condition" << std::endl;
                return false;
            }
        } else {
            WriteBinVal( file, 0, CJMP );
        }
        
        return true;
        
    }
    
    // Parse label
    inline static bool ParseLabel( char* line ) {
        
        if( line[0] != '(' ) return false;
        unsigned idx = 1;
        while( line[idx] != ')') {
            if( line[idx] == 0 ) {
                std::cerr << "Line " << lineNum << ": Unfinished label, missing ) " << std::endl;
                break;
            }
            idx++;
        }
        
        std::string label = SUBSTR( &line[1], idx );
        
        if( varTable.find( label ) != varTable.end() ) {
            std::cerr << "Line " << lineNum << ": Duplicate label definition" << std::endl;
        }
        
        varTable[label] = instNum+1;
        
        return true;
        
    }
    
    // Write binary value to file
    inline static void WriteBinVal( std::ofstream& file, unsigned val, unsigned len ) {
        
        for( unsigned i = 0; i < len; ++i ) {
            file << (val&1);
            val >>= 1;
        }
        
    }
    
    // Write halting instruction to file
    inline static void WriteHalt( std::ofstream& file ) {
        
        for( unsigned char i = 0; i < 16; ++i ) {
            file << (i < 2);
        }
        
    }
    
    // Trim line
    inline static void trim( char* line ) {
        
        char tmp[STR_LIM];
        memset( tmp, 0, sizeof(tmp) );
        unsigned idx = 0;
        for( unsigned i = 0; i < strlen(line); ++i ) {
            // End of line
            if( line[i] == '\n' or line[i] == 0 ) break;
            
            if( multiComment ) {
                if( line[i] == '*' and line[i+1] == '/' ) {
                    multiComment = false;
                    i++;
                }
                continue;
            }
            
            // Comment
            if( line[i] == '/') {
                if( line[i+1] == '/') break;
                else if( line[i+1] == '*') {
                    multiComment = true;
                    continue;
                }
                else {
                    std::cerr << "Line " << lineNum << ": Unknown symbol " << line[i] << std::endl;
                    return;
                }
            }
            
            // Blank symbold
            if( line[i] != ' ' and line[i] != '\t' ) {
                tmp[idx] = line[i];
                idx++;
            }
        }
        memcpy( line, tmp, sizeof(tmp) );
        
    }
    
    // Find memory bit
    inline static bool memoryBit( char* line ) {
        
        for( unsigned i = 0; i < strlen(line); ++i ) {
            if( line[i] == 'M' ) return true;
        }
        return false;
        
    }
    
private:    // Convertors
    
    // Char to digit 
    inline static unsigned char CTOD( char in ) {
        return in-'0';
    }
    
    // Digit to char
    inline static char DTOC( unsigned char in ) {
        return in+'0';
    }
    
    // String to unsigned
    inline static unsigned STOU( char* in ) {
        unsigned len = 0;
        while( in[len] >= '0' and in[len] <= '9' ) {
            len++;
        }
        
        unsigned out = 0;
        for( unsigned i = 0; i < len; ++i ) {
            out += CTOD(in[i]) * std::pow(10, len-1-i);
        }
        return out;
    }
    
    // Unsigned to binary
    inline static void UTOB( unsigned in, char* out ) {
        for( unsigned i = 0; i < 16; ++i ) {
            out[i] = in&1;
            in >>= 1;
        }
    }
    
    // Substring
    inline static std::string SUBSTR( char* str, unsigned len ) {
        char tmp[len];
        memcpy( tmp, str, len );
        return tmp;
    }
    
};





unsigned PARSER::lastAddr = 0;
unsigned PARSER::instNum = 0;
unsigned PARSER::lineNum = 0;
bool PARSER::multiComment = false;
Table PARSER::varTable;

const Table PARSER::regTable = {
    { "SP",   0x0000 },
    { "LCL",  0x0001 },
    { "ARG",  0x0002 },
    { "THIS", 0x0003 },
    { "THAT", 0x0004 },
    { "R0",   0x0000 },
    { "R1",   0x0001 },
    { "R2",   0x0002 },
    { "R3",   0x0003 },
    { "R4",   0x0004 },
    { "R5",   0x0005 },
    { "R6",   0x0006 },
    { "R7",   0x0007 },
    { "R8",   0x0008 },
    { "R9",   0x0009 },
    { "R10",  0x0010 },
    { "R11",  0x0011 },
    { "R12",  0x0012 },
    { "R13",  0x0013 },
    { "R14",  0x0014 },
    { "R15",  0x0015 },
    { "SCR",  0x4000 },
    { "KBD",  0x6000 }
};

// const Table PARSER::opTable = {
//     { "FAL",    0b101010 },
//     { "TRU",    0b111111 },
//     { "NGO",    0b111010 },
//     { "IDDD",   0b001100 },
//     { "IDDA",   0b110000 },
//     { "INVD",   0b001101 },
//     { "INVA",   0b110001 },
//     { "NEGD",   0b001111 },
//     { "NEGA",   0b110011 },
//     { "INCD",   0b011111 },
//     { "INCA",   0b110111 },
//     { "DECD",   0b001110 },
//     { "DECA",   0b110010 },
//     { "ADDD,A", 0b000010 },
//     { "SUBD,A", 0b010011 },
//     { "SUBA,D", 0b000111 },
//     { "ANDD,A", 0b000000 },
//     { "ORRD,A", 0b010101 }
// };
// 
// const Table PARSER::mopTable = {
//     { "IDDM",   0b110000 },
//     { "INVM",   0b110001 },
//     { "NEGM",   0b110011 },
//     { "INCM",   0b110111 },
//     { "DECM",   0b110010 },
//     { "ADDD,M", 0b000010 },
//     { "SUBD,M", 0b010011 },
//     { "SUBM,D", 0b000111 },
//     { "ANDD,M", 0b000000 },
//     { "ORRD,M", 0b010101 }
// };
// 
// const Table PARSER::dstTable = {
//     { "M",   0b001 },
//     { "D",   0b010 },
//     { "MD",  0b011 },
//     { "A",   0b100 },
//     { "AM",  0b101 },
//     { "AD",  0b110 },
//     { "AMD", 0b111 }
// };
// 
// const Table PARSER::jmpTable = {
//     { "JGT", 0b001 },
//     { "JEQ", 0b010 },
//     { "JGE", 0b011 },
//     { "JLT", 0b100 },
//     { "JNE", 0b101 },
//     { "JLE", 0b110 },
//     { "JMP", 0b111 }
// };

const Table PARSER::opTable = {
    { "0",      0b000000 },
    { "FAL",    0b010101 },
    { "TRU",    0b111111 },
    { "NGO",    0b010111 },
    { "IDDD",   0b001100 },
    { "IDDA",   0b000011 },
    { "INVD",   0b101100 },
    { "INVA",   0b100011 },
    { "NEGD",   0b111100 },
    { "NEGA",   0b110011 },
    { "INCD",   0b111110 },
    { "INCA",   0b111011 },
    { "DECD",   0b011100 },
    { "DECA",   0b010011 },
    { "ADDD,A", 0b010000 },
    { "SUBD,A", 0b110010 },
    { "SUBA,D", 0b111000 },
    { "ANDD,A", 0b000000 },
    { "ORRD,A", 0b101010 }
};

const Table PARSER::mopTable = {
    { "0",      0b000000 },
    { "IDDM",   0b000011 },
    { "INVM",   0b100011 },
    { "NEGM",   0b110011 },
    { "INCM",   0b111011 },
    { "DECM",   0b010011 },
    { "ADDD,M", 0b010000 },
    { "SUBD,M", 0b110010 },
    { "SUBM,D", 0b111000 },
    { "ANDD,M", 0b000000 },
    { "ORRD,M", 0b101010 }
};

const Table PARSER::dstTable = {
    { "0",   0b000 },
    { "M",   0b100 },
    { "D",   0b010 },
    { "MD",  0b110 },
    { "A",   0b001 },
    { "AM",  0b101 },
    { "AD",  0b011 },
    { "AMD", 0b111 }
};

const Table PARSER::jmpTable = {
    { "0",   0b000 },
    { "JGT", 0b100 },
    { "JEQ", 0b010 },
    { "JGE", 0b110 },
    { "JLT", 0b001 },
    { "JNE", 0b101 },
    { "JLE", 0b011 },
    { "JMP", 0b111 }
};

#endif
