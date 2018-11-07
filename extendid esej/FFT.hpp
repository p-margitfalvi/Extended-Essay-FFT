//
//  FFT.hpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#ifndef FFT_hpp
#define FFT_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

class FFT {
    
public:
    ofstream file;
    
    static const long sampleCount = 128;
    constexpr static const double sampleDeltaT = 1;
    constexpr static const double sampleFrequency = sampleCount / sampleDeltaT;
    constexpr static const double frequencyResolution = sampleFrequency / sampleCount;
    
    static const int frequencyCount = 5;
    const double freq[frequencyCount] = { 2, 5, 11, 17, 29};
    
    complex<double> samples[sampleCount];
    complex<double> output[sampleCount];
    
    FFT(const string &name);
    ~FFT();
    
    void displayOutput();
    void outputCSV();
    void generateSamples();
};


#endif /* FFT_hpp */
