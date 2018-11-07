//
//  FFT.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "FFT.hpp"


FFT::FFT(const string &name) : file(name + ".csv"), name(name) {
    samples = new complex<double>[sampleCount];
    output = new complex<double>[sampleCount];
}

FFT::~FFT() {
    file.flush();
    file.close();
    delete [] samples;
    delete [] output;
}

void FFT::displayOutput() {
    printf("  n\tx[]\tX[]\tf\n");       // header line
    // loop to print values
    for(int i=0; i < sampleCount; i++) {
        printf("% 3d\t%+.3f\t%+.3f\t%g\n",
               i, samples[i].real(), abs(output[i]), i*frequencyResolution);
    }
}

void FFT::outputCSV() {
    
    for(int i=0; i < sampleCount; i++) {
        file << i << ";" << samples[i].real() << ";" << abs(output[i]) << ";" <<  i * frequencyResolution << "\n";
    }
    
    file.flush();
}

void FFT::insertSamples(complex<double>* data) {
    
}

void FFT::generateSamples() {
    
    for(int i=0; i < sampleCount; i++) {
        samples[i] = complex<double>(0.,0.);
        // sum several known sinusoids into x[]
        for(int j=0; j < frequencyCount; j++) {
            //cout << sin( 2*M_PI*freq[j]*i/nSamples ) << "\n";
            samples[i] += sin( 2*M_PI*freq[j]*i/sampleCount );
        }
        output[i] = samples[i];        // copy into X[] for FFT work & result
    }
    
}
