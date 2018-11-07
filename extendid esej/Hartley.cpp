//
//  Hartley.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Hartley.hpp"

Hartley::Hartley(const string &name) : FFT(name){
    prepareData();
}

Hartley::~Hartley() {
    delete [] xarray;
    delete [] sine;
    delete [] cosine;
}

double* Hartley::compute(double* xvector, double* xarray, double* cosine, double* sine, long length) {
    
    for (long i = 0; i < length; ++i) {
        xarray[i] = 0;
    }
    long log2length = (long)log2(length);
    long b_p = length / 2;
    long n_p = 2;
    long tss = length / 2;
    for (long pvar = 0; pvar < log2length; ++pvar) {
        long npp = n_p/2;
        long baset = 0;
        for (long bvar = 0; bvar < b_p; ++bvar) {
            long baseb = baset + npp;
            long basebb = baset + n_p;
            for (long nvar = 0; nvar < npp; ++nvar) {
                long t_f = nvar*tss;
                long nmn = (basebb - nvar) % basebb;
                if (pvar % 2 == 0) {
                    double xcs;
                    if (nvar == 0) {
                        xcs = xvector[baseb + nvar];
                    } else {
                        xcs = xvector[baseb + nvar]*cosine[t_f] + xvector[nmn]*sine[t_f];
                    }
                    xarray[baset + nvar] = xvector[baset + nvar] + xcs;
                    xarray[baseb + nvar] = xvector[baset + nvar] - xcs;
                } else {
                    double xcs;
                    if (nvar == 0) {
                        xcs = xarray[baseb + nvar];
                    } else {
                        xcs = xarray[baseb + nvar]*cosine[t_f] + xarray[nmn]*sine[t_f];
                    }
                    xvector[baset + nvar] = xarray[baset + nvar] + xcs;
                    xvector[baseb + nvar] = xarray[baset + nvar] - xcs;
                }
            }
            baset = baset + n_p;
        }
        b_p = b_p / 2;
        n_p = n_p*2;
        tss = tss / 2;
    }
    if ((log2length - 1) % 2 == 0) {
        return xarray;
    } else {
        return xvector;
    }
    
}

void Hartley::computeFourier() {
    
    digitReversal(H, sampleCount);
    double* result = compute(H, xarray, cosine, sine, sampleCount);
    
    for (long i = 0; i < sampleCount; ++i) {
        output[i] = complex<double>((result[i] + result[sampleCount - i])/2, (result[i] - result[sampleCount - i])/2);
    }
    
}

void Hartley::toReal() {
    for (long i = 0; i < sampleCount; ++i) {
        H[i] = samples[i].real();
    }
}

void Hartley::prepareData() {
    
    xarray = new double[sampleCount];
    sine = new double[sampleCount];
    cosine = new double[sampleCount];
    
    for (long i  = 0; i < sampleCount; ++i) {
        xarray[i] = 0;
        sine[i] = sin(2*M_PI*i/sampleCount);
        cosine[i] = cos(2*M_PI*i/sampleCount);
    }
    
}

void Hartley::generateSamples() {
    FFT::generateSamples();
    toReal();
}

void Hartley::swap(double* x, long i, long j) {
    double temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}

double* Hartley::digitReversal(double* array, long length) {
    int n1var;
    long log2length = (long)log2(length);
    if (log2length % 2 == 0) {
        n1var = (int)sqrt(length);
    } else {
        n1var = (int)sqrt(length/2);
    }
    
    long* reverse = new long[n1var];
    for (long i = 0; i < n1var; ++i) {
        reverse[i] = 0;
    }
    reverse[1] = length/2;
    for (long i = 0; i < n1var/2; ++i) {
        reverse[2*i] = reverse[i]/2;
        reverse[2*i + 1] = reverse[2*i] + reverse[1];
    }
    // Algorithm 1
    for (long i = 0; i < n1var - 1; ++i) {
        for (long j = i + 1; j < n1var; ++j) {
            long uvar = i + reverse[j];
            long vvar = j + reverse[i];
            swap(array, uvar, vvar);
            if (log2length % 2 == 1) {
                uvar = i + reverse[j] + n1var;
                vvar = j + reverse[i] + n1var;
                swap(array, uvar, vvar);
            }
        }
    }
    
    
    delete [] reverse;
    return array;
}
