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
    virtual inline IO Process( IO in ) {
        
        IO output;
        output.push_back(0);
        
        for( unsigned char i = 0; i < 8; ++i ) {        
            IO inputOR;
            
            inputOR.push_back( (i == 0 ? in[0] : output[0]) );
            inputOR.push_back( in[i] );
            
            output[0] = m_OR.Process( inputOR )[0];
        }
        
        return output;
        
    }

};

#endif
