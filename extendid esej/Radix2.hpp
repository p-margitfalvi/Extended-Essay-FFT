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
    void separate(complex<double>* X, const long length);
    void compute(complex<double>* X, const long length);
    
    complex<double>** exponentialTable;
    
public:
    void computeFourier();
    void prepareData();
<<<<<<< HEAD
    Radix2(const string &name, const long sampleCount);
=======
    Radix2(const string &name, long sampleCount);
>>>>>>> 1f35b6f90e5b5d9b3c381770d416a0d28acf1f25
    ~Radix2();
};

#endif /* Radix2_hpp */
