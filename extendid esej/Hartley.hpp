//
//  Hartley.hpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#ifndef Hartley_hpp
#define Hartley_hpp

#include <stdio.h>
#include "FFT.hpp"

class Hartley: public FFT {
    
private:
    double H[sampleCount];
    
    void separate(double X[], const long length);
    void compute(double X[], const long length);
    void toReal();
    
public:
    Hartley(const string &name);
    
    void computeFourier();
    void generateSamples();
};

#endif /* Hartley_hpp */
