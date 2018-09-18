//
//  main.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 18/09/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include <iostream>
#include <complex>

using namespace std;

void separate(complex<double>* a, int n) {
    complex<double>* b = new complex<double>[n/2];
    for(int i = 0; i < n/2; i++) {
        b[i] = a[2*i + 1];
    }
    for (int i = 0; i < n/2; i++) {
        a[i] = a[2*i];
    }
    for (int i = 0; i < n/2; i++) {
        a[i + n/2] = b[i];
    }
    delete [] b;
}

void fft(complex<double>* X, int n) {
    if (n < 2) {
        return;
    } else {
        separate(X, n);
        
        fft(X, n/2);
        fft(X + n/2, n/2);
        
        for(int i = 0; i < n/2; i++) {
            complex<double> e = X[i];
            complex<double> o = X[i + n/2];
            complex<double> w = exp(complex<double>(0, -2*M_PI*i/n));
            
            X[i] = e + w * o;
            X[i + n/2] = e - w * o;
        }
    }
}

int main(int argc, const char * argv[]) {
    const int nSamples = 64;
    double nSeconds = 1.0;                      // total time for sampling
    double sampleRate = nSamples / nSeconds;    // n Hz = n / second
    double freqResolution = sampleRate / nSamples; // freq step in FFT result
    complex<double> x[nSamples];                // storage for sample data
    complex<double> X[nSamples];                // storage for FFT answer
    const int nFreqs = 5;
    double freq[nFreqs] = { 2, 5, 11, 17, 29 }; // known freqs for testing
    
    // generate samples for testing
    for(int i=0; i<nSamples; i++) {
        x[i] = complex<double>(0.,0.);
        // sum several known sinusoids into x[]
        for(int j=0; j<nFreqs; j++)
            x[i] += sin( 2*M_PI*freq[j]*i/nSamples );
        X[i] = x[i];        // copy into X[] for FFT work & result
    }
    // compute fft for this data
    fft(X,nSamples);
    
    printf("  n\tx[]\tX[]\tf\n");       // header line
    // loop to print values
    for(int i=0; i<nSamples; i++) {
        printf("% 3d\t%+.3f\t%+.3f\t%g\n",
               i, x[i].real(), abs(X[i]), i*freqResolution );
    }
    return 0;
}
