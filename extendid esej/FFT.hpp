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
#include <vector>

using namespace std;

class FFT {
    
protected:
    string name;
    ofstream file;
    
    vector<complex<double>> samples;
    vector<complex<double>> output;
    
    long sampleCount = (long)exp2(20);
    clock_t timeTaken;
    double sampleDeltaT = 1;
    double sampleFrequency = sampleCount / sampleDeltaT;
    double frequencyResolution = sampleFrequency / sampleCount;
    long multiplications = 0;
    long additions = 0;
    
    static const int frequencyCount = 5;
    const double freq[frequencyCount] = { 2, 5, 11, 17, 29};
    void generateSamples();

    
public:
    
    FFT(const string &name, const long sampleCount);
    ~FFT();
    
    void displayOutput();
    void outputCSV();
    void insertSamples(const vector<complex<double>>& data) { samples = data; }
    clock_t getTimeTaken() { return timeTaken; }
    long getAdditions() { return additions; }
    long getMultiplications() { return multiplications; }
    vector<complex<double>> getOutput() { return output; }
};


#endif /* FFT_hpp */
