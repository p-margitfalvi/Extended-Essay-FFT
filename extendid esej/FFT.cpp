//
//  FFT.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "FFT.hpp"


<<<<<<< HEAD
FFT::FFT(const string &name, const long sampleCount) : file(name + ".csv"), name(name), sampleCount(sampleCount) {
=======
FFT::FFT(const string &name, long sampleCount) : file(name + ".csv"), name(name), sampleCount(sampleCount) {
>>>>>>> 1f35b6f90e5b5d9b3c381770d416a0d28acf1f25
    samples = new complex<double>[sampleCount];
    output = new complex<double>[sampleCount];
}

FFT::~FFT() {
    file.flush();
    file.close();
    delete [] samples;
    delete [] output;
}

void FFT::setSampleCount(const long sampleCount) {
    this->sampleCount = sampleCount;
    sampleFrequency = sampleCount / sampleDeltaT;
    frequencyResolution = sampleFrequency / sampleCount;
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

void FFT::generateRandomSamples() {
    for (long i = 0; i < sampleCount; ++i) {
        samples[i] = randomDouble(-500, 500);
    }
}

double FFT::randomDouble(int min, int max) {
    return (double)(random() % (max - min)) + min;
}



void FFT::generateSamples() {
    
    for(long i=0; i < sampleCount; i++) {
        samples[i] = complex<double>(0.,0.);
        // sum several known sinusoids into x[]
        for(int j=0; j < frequencyCount; j++) {
            //cout << sin( 2*M_PI*freq[j]*i/nSamples ) << "\n";
            samples[i] += sin( 2*M_PI*freq[j]*i/sampleCount );
        }
        output[i] = samples[i];        // copy into X[] for FFT work & result
    }
    
}
