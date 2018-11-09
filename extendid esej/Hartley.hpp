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
    vector<double> H;
    vector<double> xarray;
    vector<double> sine;
    vector<double> cosine;
    
    vector<double>::iterator compute(vector<double>::iterator xvector, long length);
    vector<double> digitReversal(vector<double>& array, long length);
    void swap(vector<double>& x, long i, long j);
    void toReal();
    void generateSamples();
    
public:
    Hartley(const string &name, const long sampleCount);
    ~Hartley();
    
    void computeFourier();
    void prepareData();
};

#endif /* Hartley_hpp */
