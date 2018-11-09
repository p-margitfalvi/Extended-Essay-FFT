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

// Clears up the memory allocated by the exponential table
Radix2::~Radix2() {
    /*
    for (auto row : exponentialTable) {
        delete row;
    }*/
}

// Sorts the array in such an order that even-indexed elements are in the first half
// and odd-indexed elements in the second half
void Radix2::separate(vector<complex<double>>::iterator X, const long length) {
    vector<complex<double>> b(length / 2);
    // Move the odd-indexed elements into a temp array b
    for(long i = 0; i < length/2; i++) {
        b[i] = X[2*i + 1];
    }
    // Move even-indexed elements to the beginning
    for (long i = 0; i < length/2; i++) {
        X[i] = X[2*i];
    }
    // Move odd-indexed elements from temporary storage to the second half
    for (long i = 0; i < length/2; i++) {
        X[i + length/2] = b[i];
    }
}

// Recursively computes the radix-2 Cooley-Tukey FFT algorithm
void Radix2::compute(vector<complex<double>>::iterator X, const long length) {
    if (length < 2) {
        // The fourier transform of array of size 1 is equal to itself. Therefore, do nothing
        return;
    } else {
        // Sort the array into two halfs, the first one containing even-indexed elements,
        // the second half containing the odd-indexed ones
        separate(X, length);
        // Recursively perform the FFT on the two halves
        compute(X, length/2);
        compute(X + length/2, length/2);
        
        // Put the results of the two FFT's together
        for(long i = 0; i < length/2; i++) {
            complex<double> e = X[i];
            complex<double> o = X[i + length/2];
            complex<double> w = exp(complex<double>(0, -2*M_PI*i/length));
            long log2length = (long)log2(length);
            //complex<double> w = exponentialTable[log2length - 1]->at(i);
            multiplications += 4;
            additions += 6;
            X[i] = e + w * o;
            X[i + length/2] = e - w * o;
        }
    }
}

// Initialise the exponential table with values and prepare the samples and clear the arrays
void Radix2::prepareData() {
    long log2length = (long)log2(sampleCount) + 1;
    exponentialTable.resize(log2length, vector<complex<double>>());
    for (long i = 1; i < log2length; ++i) {
        //row->reserve((long)exp2(i - 1));
        for (long j = 0; j < (long)exp2(i - 1); ++j) {
            //row->push_back(exp(complex<double>(0, -2*M_PI*j/exp2(i))));
            exponentialTable[i].push_back(exp(complex<double>(0, -2*M_PI*j/exp2(i))));
        }
        //exponentialTable.push_back(row);
    }
    additions = 0;
    multiplications = 0;
    generateSamples();
}

// Computes the fourier transform and measures the time taken
void Radix2::computeFourier() {
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    compute(output.begin(), sampleCount);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    timeTaken = std::chrono::duration_cast<typeof(timeTaken)>(t2 - t1);
}
