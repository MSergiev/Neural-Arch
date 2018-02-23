#ifndef BIT_H
#define BIT_H

#include "DFF.h"

class BIT : public Gate {

public:
    
    static const byte I = 0;    // Input
    static const byte L = 1;    // Load bit
    
    static const byte O = 0;    // Output
    
private:
    
    DFF m_DFF;
    
public: 

    // Constructor
    BIT() : Gate("BIT",2,1,"IL","O") {}

    // Destuctor
    ~BIT() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        return m_DFF.Process( in );
    }

};

#endif
