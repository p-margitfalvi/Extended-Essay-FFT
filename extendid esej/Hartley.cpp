//
//  Hartley.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Hartley.hpp"

Hartley::Hartley(const string &name) : FFT(name){
    return;
}

void Hartley::separate(double X[], const long length) {
    double* b;
    b = new double [length/2];
    
    for (long i = 0; i < length / 2; i++) {
        b[i] = X[2*i + 1];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i] = X[2*i];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i + length / 2] = b[i];
    }
    
    delete [] b;
}

void Hartley::compute(double X[], const long length) {
    if (length < 2) {
        return;
    } else {
        separate(X, length);
        
        compute(X, length / 2);
        compute(X + length / 2, length / 2);
        
        for(long i = 0; i < length/2; i++) {
            double e = X[i];
            double o = X[i + length/2];
            double z = X[length/2 - i];
            
            double arg = 2*M_PI*i/length;
            double w = o*cos(arg) + z*sin(arg);
            
            X[i] = e + w;
            X[i + length/2] = e - w;
        }
    }
    
}

void Hartley::computeFourier() {
    compute(H, sampleCount);
    for (int i = 0; i < sampleCount; ++i) {
        output[i] = complex<double>((H[i] + H[sampleCount - i])/2, (H[i] - H[sampleCount - i])/2);
    }

}

void Hartley::toReal() {
    for (long i = 0; i < sampleCount; ++i) {
        H[i] = samples[i].real();
    }
}

void Hartley::generateSamples() {
    FFT::generateSamples();
    toReal();
}
