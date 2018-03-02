#ifndef RAM_H
#define RAM_H

#include "../Sequential/Memory/RAM16K.h"


class RAM : public Gate {
    
public:
    
    static const byte I = 0;    // Input
    static const byte A = 1;    // Address
    static const byte L = 2;    // Load bit
    
    static const byte O = 0;    // Address output
    
private:
    
    RAM16K m_RAM;
    
public: 

    // Constructor
    RAM() : Gate("RAM",3,1,"IAL","O") {}

    // Destuctor
    ~RAM() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return in;
    }
    
    // Multiway processing method
    virtual inline BUS ProcessBUS( BUS in ) {
        return m_RAM.ProcessBUS( in ); 
    }
    
};

#endif
