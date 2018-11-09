//
//  Test.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 07/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Test.hpp"

Test::~Test() {
    file.flush();
    file.close();
    
    delete [] times.first;
    delete [] times.second;
    
    delete [] multiplications.first;
    delete [] multiplications.second;
    
    delete [] additions.first;
    delete [] additions.second;
    
    delete radix2;
    delete fht;
}

Test::Test(const string& path, const int minOrder, const int maxOrder, bool checkOutput) : path(path), min2Order(minOrder), max2Order(maxOrder), checkOutput(checkOutput) {
    
    file = ofstream(path + "output.csv");
    
    times.first = new chrono::microseconds[max2Order - min2Order];
    times.second = new chrono::microseconds[max2Order - min2Order];
    
    multiplications.first = new long[max2Order - min2Order];
    additions.first = new long[max2Order - min2Order];
    
    multiplications.second = new long[max2Order - min2Order];
    additions.second = new long[max2Order - min2Order];

    radix2 = new Radix2(path + "radix2", 0);
    fht = new Hartley(path + "fht", 0);
}

bool Test::runTest() {
    
    for (int i = min2Order; i <= max2Order; ++i) {
        long sampleSize = (long)exp2(i);
        
        radix2 = new Radix2(path + "radix2", sampleSize);
        radix2->prepareData();
        radix2->computeFourier();
        
        times.first[i] = radix2->getTimeTaken();
        additions.first[i] = radix2->getAdditions();
        multiplications.first[i] = radix2->getMultiplications();
        
        
        fht = new Hartley(path + "fht", sampleSize);
        fht->prepareData();
        fht->computeFourier();
        
        times.second[i] = fht->getTimeTaken();
        additions.second[i] = fht->getAdditions();
        multiplications.second[i] = fht-> getMultiplications();
        
        if (checkOutput) {
            complex<double>* r2Output = radix2->getOutput();
            complex<double>* fhtOutput = fht->getOutput();
            for (long i = 0; i < sampleSize; ++i) {
                if (!compareDoubles(abs(r2Output[i]), abs(fhtOutput[i]))) {
                    return false;
                }
            }
        }
        delete fht;
        delete radix2;
        
        
    }
    
    return true;
}
                    
bool Test::compareComplex(complex<double> A, complex<double> B) {
    
    return compareDoubles(A.real(), B.real()) && compareDoubles(A.imag(), B.imag());
    
}

bool Test::compareDoubles(double A, double B)
{
    double diff = A - B;
    return (diff < epsilon) && (-diff < epsilon);
}

