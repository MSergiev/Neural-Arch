#ifndef OR8WAY_H
#define OR8WAY_H

#include "OR.h"

class OR8WAY : public Gate {

private:
    
    OR m_OR;

public: 

    // Constructor
    OR8WAY() : Gate("OR8WAY",8,1,"ABCDEFGH","O") {}

    // Destuctor
    ~OR8WAY() {}

    // Processing method
    virtual inline bitset Process( bitset in ) {
        
        bitset output = 0;
        
        for( unsigned char i = 0; i < 8; ++i ) {        
            bitset inputOR = 0;
            
            add( inputOR, get( (i == 0 ? in : output), 0 ) );
            add( inputOR, get( in, i ) );
            
            output = m_OR.Process( inputOR );
        }
        
        return output;
        
    }

};

#endif
