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
    
    void separate(double* X, const long length);
    void separate(complex<double>* X, const long length);
    void compute(double* X, const long length);
    void pseudoversion(double* a, const long length, double* x);
    void discrete();
    void discreteHalved();
    void toReal();
    double* pyTransform(double* xvector, double* xarray, double* cosine, double* sine, long length, long log2length);
    double* digitReversal(double* xarray, long length, long log2length);
    void hartleyShift(double* c, const long length);
    void swap(double* x, long i, long j);
    
public:
    Hartley(const string &name);
    
    void computeFourier();
    void computeTest();
    void computeDiscrete();
    void computeDiscreteHalved();
    void computePseudo();
    void generateSamples();
};

#endif /* Hartley_hpp */
