#ifndef GATE_H
#define GATE_H

#include <cstring>

typedef short bitset;

void add( bitset& in, bool val) { in = (in<<1)|val; }
bitset get( bitset& in, unsigned char idx ) { return (((1<<idx)&in)>>idx); }

// Instruction length
#define ARCH 16

class Gate {

protected:
    
    // Gate parameters
    char* ID;
    const unsigned char INPUTS;
    const unsigned char OUTPUTS;
    char* IN_PINOUT;
    char* OUT_PINOUT;
    
public: 

    // Constructor
    Gate( char const *id, 
          unsigned char inputs, 
          unsigned char outputs, 
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
    
	// Input num
	inline char* GateID() const { return ID; }
	
	// Input num
	inline unsigned char inputNum() const { return INPUTS; }

	// Output num
	inline unsigned char outputNum() const { return OUTPUTS; }
	
	// Input pinout
	inline char* inputPinout() const { return IN_PINOUT; }
	
	// Output pinout
	inline char* outputPinout() const { return OUT_PINOUT; }
    
    // Processing method
    virtual bitset Process( bitset in ) = 0;

};

// Batchrocessing method
inline bitset Batch( Gate* g, bitset* in ) {
    
    bitset output = 0;
    
    for( unsigned char i = 0; i < ARCH; ++i ) {
        bitset input = 0;
        for( unsigned char j = 0; j < g->inputNum(); ++j ) {
            add( input, get(in[j], ARCH-i-1) );
        }
        add( output, g->Process( input ) );
    }
    
    return output;
    
}

#endif
