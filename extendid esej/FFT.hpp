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
    long sampleCount = (long)exp2(10);
    std::chrono::milliseconds timeTaken;
    double sampleDeltaT = 1;
    double sampleFrequency = sampleCount / sampleDeltaT;
    double frequencyResolution = sampleFrequency / sampleCount;
    long operationsTaken = 0;
    
    static const int frequencyCount = 5;
    const double freq[frequencyCount] = { 2, 5, 11, 17, 29};
    void generateSamples();
    
public:
    string name;
    ofstream file;
    
    complex<double>* samples;
    complex<double>* output;
    
    FFT(const string &name);
    ~FFT();
    
    void displayOutput();
    void outputCSV();
    void insertSamples(complex<double>* data);
    std::chrono::milliseconds getTimeTaken() { return timeTaken; }
};


#endif /* FFT_hpp */
