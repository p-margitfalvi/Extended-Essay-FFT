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
#include <time.h>
#include "FFT.hpp"

class Hartley: public FFT {
    
private:
    double* H;
    double* xarray;
    double* sine;
    double* cosine;
    
    double* compute(double* xvector, double* xarray, double* cosine, double* sine, long length);
    double* digitReversal(double* xarray, long length);
    void swap(double* x, long i, long j);
    void toReal();
    void generateSamples();
    
public:
    Hartley(const string &name, long sampleCount);
    ~Hartley();
    
    void computeFourier();
    void prepareData();
};

#endif /* Hartley_hpp */
