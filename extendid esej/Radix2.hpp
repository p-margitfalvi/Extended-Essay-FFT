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
#include "FFT.hpp"

class Radix2: public FFT {
  
private:
    void separate(complex<double>* X, const long length);
    
public:
    void compute(complex<double>* X, const long length=sampleCount);
    Radix2(const string &name);
    
};

#endif /* Radix2_hpp */
