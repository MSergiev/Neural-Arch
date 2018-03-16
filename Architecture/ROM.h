#ifndef ROM_H
#define ROM_H

#include <fstream>
#include "../Gates/Basic/Gate.h"
#include "../Sequential/Memory/RAM64.h"


class ROM : public Gate {
    
public:
    
    static const byte I = 0;    // Address input
    
    static const byte O = 0;    // Address output
    
    char FILENAME[256];   // Program filename
    
private:
    
    RAM64 m_ROM;
    
public: 

    // Constructor
    ROM( ) : Gate("ROM",1,1,"I","O"), FILENAME( "ROM.txt" ) {}

    // Destuctor
    ~ROM() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        BUS input = m_ROM.CreateInputBUS();
        input[RAM64::I] = ZeroIO();
        input[RAM64::A] = in[I];
        input[RAM64::L] = ZeroIO();
        return m_ROM.ProcessBUS( input ); 
    }

    // Load program file
    inline bool LoadFile( const char* filename ) {
        std::cout << "Loading file " << filename << " into ROM" << std::endl;
        memset( FILENAME, 0, 256 );
        memcpy( FILENAME, filename, strlen(filename) );
        return LoadROM();
    }
    
private:
    
    // Load program file into ROM 
    inline bool LoadROM() {
        
        std::ifstream file( FILENAME );
        if( !file ){
            std::cerr << "ERROR: " << FILENAME << " does not exist!" << std::endl;
            return false;
        }
        
        unsigned addr = 0;
        char line[256];
        file.getline( line, sizeof(line) );
        
        BUS inputROM = m_ROM.CreateInputBUS();
        inputROM[RAM64::L] = FilledIO(1);
        
        while(1){
            if( line[0] == 0 ) break;
#ifdef DEBUG
            std::cout << "Instruction: " << line << std::endl;
#endif
            for( byte i = 0; i < ARCH; ++i ) {
                if( line[i] != '0' and line[i] != '1' ) {
                    std::cout << "Parser error at line " << (int)i << std::endl;
                    std::cout << "Erroneous symbol: " << line[i] << " (" << (int)line[i] << ")" << std::endl;
                    return false;
                }
                inputROM[RAM64::I][i] = (line[i] - '0');
            }
            inputROM[RAM64::A] = NumToIO(addr);
            
            m_ROM.ProcessBUS( inputROM );
            
            addr++;
            if( file.eof() or addr >= m_ROM.SIZE ) break;
            file.getline( line, sizeof(line) );
        }
        std::cout << FILENAME << " loaded" << std::endl;
        return true;
    }
};

#endif
