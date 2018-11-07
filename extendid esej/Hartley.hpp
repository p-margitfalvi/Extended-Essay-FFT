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
#include "fht.h"


class Hartley: public FFT {
    
private:
    double H[sampleCount];
    
    double* compute(double* xvector, double* xarray, double* cosine, double* sine, long length);
    double* digitReversal(double* xarray, long length);
    void swap(double* x, long i, long j);
    void toReal();
    
public:
    Hartley(const string &name);
    
    void computeFourier();
    void generateSamples();
};

#endif /* Hartley_hpp */
