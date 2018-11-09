//
//  FFT.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "FFT.hpp"



FFT::FFT(const string &name, const long sampleCount) : file(name + ".csv"), name(name), sampleCount(sampleCount) {
    samples.resize(sampleCount, complex<double>(0., 0.));
    output.reserve(sampleCount);
}

FFT::~FFT() {
    file.flush();
    file.close();
}

void FFT::setSampleCount(const long sampleCount) {
    this->sampleCount = sampleCount;
    sampleFrequency = sampleCount / sampleDeltaT;
    frequencyResolution = sampleFrequency / sampleCount;
}

void FFT::displayOutput() {
    printf("  n\tx[]\tX[]\tf\n");       // header line
    // loop to print values
    for(long i=0; i < sampleCount; i++) {
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

void FFT::generateSamples() {
    for(long i=0; i < sampleCount; i++) {
        // sum several known sinusoids into x[]
        for(int j=0; j < frequencyCount; j++) {
            //cout << sin( 2*M_PI*freq[j]*i/nSamples ) << "\n";
            samples[i] += sin(2*M_PI*freq[j]*i/sampleCount);
        }
        output.push_back(samples[i]);        // copy into X[] for FFT work & result
    }
    
}
