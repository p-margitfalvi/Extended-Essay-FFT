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
    
protected:
    long sampleCount = (long)exp2(20);
    std::chrono::milliseconds timeTaken;
    double sampleDeltaT = 1;
    double sampleFrequency = sampleCount / sampleDeltaT;
    double frequencyResolution = sampleFrequency / sampleCount;
    long multiplications = 0;
    long additions = 0;
    
    static const int frequencyCount = 5;
    const double freq[frequencyCount] = { 2, 5, 11, 17, 29};
    void generateSamples();
    void generateRandomSamples();
    double randomDouble(int min, int max);

    
public:
    string name;
    ofstream file;
    
    complex<double>* samples;
    complex<double>* output;
    
    FFT(const string &name, const long sampleCount);
    ~FFT();
    
    void setSampleCount(const long sampleCount);
    void displayOutput();
    void outputCSV();
    void insertSamples(complex<double>* data);
    std::chrono::milliseconds getTimeTaken() { return timeTaken; }
    long getAdditions() { return additions; }
    long getMultiplications() { return multiplications; }
    complex<double>* getOutput() { return output; }
};


#endif /* FFT_hpp */
