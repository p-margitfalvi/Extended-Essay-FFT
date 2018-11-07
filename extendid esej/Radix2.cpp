//
//  Radix2.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Radix2.hpp"

Radix2::Radix2(const string &name, const long sampleCount) : FFT(name, sampleCount) {
    return;
}

Radix2::~Radix2() {
    long log2length = (long)log2(sampleCount) + 1;
    delete [] exponentialTable;
}

void Radix2::separate(complex<double>* X, const long length) {
    complex<double>* b = new complex<double>[length/2];
    for(int i = 0; i < length/2; i++) {
        b[i] = X[2*i + 1];
    }
    for (int i = 0; i < length/2; i++) {
        X[i] = X[2*i];
    }
    for (int i = 0; i < length/2; i++) {
        X[i + length/2] = b[i];
    }
    delete [] b;
}

void Radix2::compute(complex<double>* X, const long length) {
    if (length < 2) {
        return;
    } else {
        separate(X, length);
        
        compute(X, length/2);
        compute(X + length/2, length/2);
        
        for(long i = 0; i < length/2; i++) {
            complex<double> e = X[i];
            complex<double> o = X[i + length/2];
            //complex<double> w = exp(complex<double>(0, -2*M_PI*i/length)); NOW USES TABLE CALCULATED VALUES
            complex<double> w = exponentialTable[(long)log2(length)][i];
            multiplications += 4;
            additions += 6;
            X[i] = e + w * o;
            X[i + length/2] = e - w * o;
        }
    }
}

// Initialise the exponential table with values and prepare the samples
void Radix2::prepareData() {
    long log2length = (long)log2(sampleCount) + 1;
    exponentialTable = new complex<double>*[log2length];
    for (long i = 1; i < log2length; ++i) {
        complex<double>* row = new complex<double>[(long)exp2(i - 1)];
        for (long j = 0; j < (long)exp2(i - 1); ++j) {
            row[j] = exp(complex<double>(0, -2*M_PI*j/exp2(i)));
        }
        exponentialTable[i] = row;
    }
    additions = 0;
    multiplications = 0;
    generateSamples();
}

void Radix2::computeFourier() {
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    compute(output, sampleCount);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    timeTaken = std::chrono::duration_cast<typeof(timeTaken)>(t2 - t1);
}
