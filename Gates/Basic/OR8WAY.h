#ifndef OR8WAY_H
#define OR8WAY_H

#include "OR.h"

class OR8WAY : public Gate {

public:
    
    static const byte A = 0;    // Input A
    static const byte B = 1;    // Input B
    static const byte C = 2;    // Input C
    static const byte D = 3;    // Input D
    static const byte E = 4;    // Input E
    static const byte F = 5;    // Input F
    static const byte G = 6;    // Input G
    static const byte H = 7;    // Input H
    
    static const byte O = 0;    // Output

private:
    
    OR m_OR;

public: 

    // Constructor
    OR8WAY() : Gate("OR8WAY",8,1,"ABCDEFGH","O") {}

    // Destuctor
    ~OR8WAY() {}

    // Processing method
    virtual inline IO Process( IO in ) {
        
        IO output = CreateOutputIO();
        
        for( byte i = 0; i < INPUTS; ++i ) {        
            IO inputOR = m_OR.CreateInputIO();
            inputOR[OR::A] = (i == 0 ? in[0] : output[O]);
            inputOR[OR::B] = in[i];            
            output[O] = m_OR.Process( inputOR )[OR::O];
        }
        
        return output;
        
    }

};

#endif
