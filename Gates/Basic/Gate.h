#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

// Instruction length
#define ARCH 16

typedef double IOin;
typedef std::vector<IOin> IO;
typedef std::vector<IO> BUS;
typedef unsigned char byte;


void Bin( unsigned in, byte size = ARCH ) {
    
	char str[size+1];
	memset( str, 0, sizeof(str) );
	for( unsigned i = 0; i < size; ++i ) {
		str[size-i-1] = (in&1) + '0';
		in >>= 1;
	}
	std::cout << str;
    
}

IO NumToIO( unsigned num, unsigned size = ARCH ) {
    
    IO out;
    for( unsigned i = 0; i < size; ++i ) {
        out.push_back( num&1 );
        num >>= 1;
    }
    std::reverse( out.begin(), out.end() );
    return out;
    
}

unsigned IOToNum( IO& in ) {
    
    unsigned out = 0;
    for( unsigned i = 0; i < in.size(); ++i ) {
        out <<= 1;
        out |= 1&((unsigned)std::round(in[i]));
    }
    return out;
    
}

void PrintIO( IO in ) {
    
    if( in.size() == 0 ) return; 
    for( unsigned i = 0; i < in.size(); ++i ) {
#ifdef ROUND
            std::cout << std::round(in[i]);
#else
            std::cout << in[i] << " ";
#endif
    }
    
}

void PrintBUS( BUS in, unsigned size = 0 ) {
    if( size == 0 ) size = in.size();
    if( in.size() == 0 ) return; 
    for( unsigned i = 0; i < size; ++i ) {
        PrintIO( in[i] );
        std::cout << " (" << IOToNum( in[i] )<<  ")" << std::endl;
    }
    
}
    
// Create filled IO
inline IO FilledIO( IOin val ) { 
    return IO(ARCH,val); 
}

// Create zero IO
inline IO ZeroIO() { 
    return FilledIO(0);
}
    
void ReverseIO( IO& in ) {
    std::reverse( in.begin(), in.end() );
}



class Gate {

protected:
    
    // Gate parameters
    char* ID;
    const byte INPUTS;
    const byte OUTPUTS;
    char* IN_PINOUT;
    char* OUT_PINOUT;
    
public: 

    // Constructor
    Gate( char const *id, 
          byte inputs, 
          byte outputs, 
          char const *in_pinout, 
          char const *out_pinout ) 
    : INPUTS(inputs),
    OUTPUTS(outputs) 
    {
        ID = new char[10];
        memcpy( ID, id, 10 );
        IN_PINOUT = new char[inputs];
        memcpy( IN_PINOUT, in_pinout, inputs+1 );
        OUT_PINOUT = new char[outputs];
        memcpy( OUT_PINOUT, out_pinout, outputs+1 );
    }
    
    // Destructor
    virtual ~Gate() {
        delete[] ID;
        delete[] IN_PINOUT;
        delete[] OUT_PINOUT;
    }
    
	// Gate ID
	inline char* GateID() const { return ID; }
	
	// Input num
	inline byte inputNum() const { return INPUTS; }

	// Output num
	inline byte outputNum() const { return OUTPUTS; }
	
	// Input pinout
	inline char* inputPinout() const { return IN_PINOUT; }
	
	// Output pinout
	inline char* outputPinout() const { return OUT_PINOUT; }
	
    
    // Create input IO instance
    inline IO CreateInputIO() { return IO( INPUTS, 0 ); }
    
    // Create output IO instance
    inline IO CreateOutputIO() { return IO( OUTPUTS, 0 ); }
    
    // Create input BUS instance
    inline BUS CreateInputBUS() { return BUS( INPUTS, ZeroIO() ); }
    
    // Create output BUS instance
    inline BUS CreateOutputBUS() { return BUS( OUTPUTS, ZeroIO() ); }
    
    // Processing method
    virtual IO Process( IO in ) = 0;
    
    // Parallel processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        BUS output = CreateOutputBUS();
        
        for( unsigned i = 0; i < ARCH; ++i ) {
            IO inputSerial = CreateInputIO();
            for( unsigned j = 0; j < INPUTS; ++j ) {
                inputSerial[j] = in[j][i];
            }
            IO outputSerial = Process(inputSerial);
            for( unsigned j = 0; j < OUTPUTS; ++j ) {
                output[j][i] = outputSerial[j];
            }
        }
        
        return output;
    }

};

#endif
