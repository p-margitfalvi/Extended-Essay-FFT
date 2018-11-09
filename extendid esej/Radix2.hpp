//
//  Radix2.hpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#ifndef Radix2_hpp
#define Radix2_hpp

#include <stdio.h>
#include <time.h>
#include "FFT.hpp"

class Radix2: public FFT {
  
private:
    void separate(vector<complex<double>>::iterator X, const long length);
    void compute(vector<complex<double>>::iterator X, const long length);
    
    vector<vector<complex<double>>*> exponentialTable;
    
public:
    void computeFourier();
    void prepareData();

    Radix2(const string &name, const long sampleCount);
    ~Radix2();
};

#endif /* Radix2_hpp */
