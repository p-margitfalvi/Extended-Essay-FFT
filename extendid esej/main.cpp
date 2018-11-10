//
//  main.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 18/09/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include <iostream>
#include "Radix2.hpp"
#include "Hartley.hpp"
#include <fstream>
#include <random>


double epsilon = 0.8;

bool compareDoubles(double A, double B) {
    double diff = A - B;
    return (diff < epsilon) && (-diff < epsilon);
}

double randomDouble(int min, int max) {
    return (double)(random() % (max - min)) + min;
}

// Sine wave data set
int main(int argc, const char * argv[]) {
    
    vector<double> dvector;
    vector<complex<double>> cvector;
    
    const int minOrder = 3;
    const int maxOrder = 23;
    
    const int minRandomAmplitude = -500;
    const int maxRandomAmplitude = 500;
    
    long sampleCount = (long)exp2(minOrder - 1);
    const int steps = maxOrder - minOrder + 1;
    // Whether to compare the outputs of the two algorithms
    const bool checkAlgorithms = false;
    
    ofstream file("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/output.csv");
    ofstream randomFile("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/randomOutput.csv");
    
    pair<long[steps], long[steps]> additions;
    pair<long[steps], long[steps]> multiplications;
    pair<clock_t[steps], clock_t[steps]> times;
    
    for (int i = minOrder; i <= maxOrder; ++i) {
        int idx = i - minOrder;
        sampleCount *= 2;
        
        Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/fht/" + to_string(idx), sampleCount);
        
        fht.prepareData();
        fht.computeFourier();
        
        times.second[idx] = fht.getTimeTaken();
        additions.second[idx] = fht.getAdditions();
        multiplications.second[idx] = fht.getMultiplications();
        
        auto fhtData = fht.getOutput();
        
        Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/radix-2/" + to_string(idx), sampleCount);
        
        r2.prepareData();
        r2.computeFourier();
    
        
        times.first[idx] = r2.getTimeTaken();
        additions.first[idx] = r2.getAdditions();
        multiplications.first[idx] = r2.getMultiplications();
        
        auto r2Data = r2.getOutput();
        
        if (times.second[0] > 100) {
            cout << "error, sample coun: " << sampleCount;
            return 0;
        }
        
        //r2.outputCSV();
        
        //fht.outputCSV();
        if (checkAlgorithms) {
            for (long i = 0; i < sampleCount; ++i) {
                if(!compareDoubles(abs(r2Data[i]), abs(fhtData[i]))) {
                    cout << "u suck :(\nFailed at sample count: " << sampleCount << "\n";
                }
            }
        }
    }
    
    file << "#radix2\n";
    for(int i = 0; i < steps; ++i) {
        file << i << ";" << (long)exp2(i + minOrder) << ";" << times.first[i] << ";" << multiplications.first[i] << ";" << additions.first[i] << "\n";
    }
    
    file << "\n\n\n#fht\n";
    for(int i = 0; i < steps; ++i) {
        file << i << ";" << (long)exp2(i + minOrder) << ";" << times.second[i] << ";" << multiplications.second[i] << ";" << additions.second[i] << "\n";
    }
    
    
    vector<complex<double>> randomSet;
    sampleCount = (long)exp2(minOrder - 1);
    // Random data set
    for (int i = minOrder; i <= maxOrder; ++i) {
        
        int idx = i - minOrder;
        sampleCount *= 2;
        
        randomSet.resize(sampleCount, complex<double>(0, 0));
        for (long i = 0; i < sampleCount; ++i) {
            randomSet[i] = randomDouble(minRandomAmplitude, maxRandomAmplitude);
        }
        
        Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/random_fht/" + to_string(idx), sampleCount);
        
        fht.prepareData();
        fht.insertSamples(randomSet);
        fht.computeFourier();
        
        times.second[idx] = fht.getTimeTaken();
        additions.second[idx] = fht.getAdditions();
        multiplications.second[idx] = fht.getMultiplications();
        
        auto fhtData = fht.getOutput();
        
        Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/random_radix-2/" + to_string(idx), sampleCount);
        
        r2.prepareData();
        r2.insertSamples(randomSet);
        r2.computeFourier();
        
        times.first[idx] = r2.getTimeTaken();
        additions.first[idx] = r2.getAdditions();
        multiplications.first[idx] = r2.getMultiplications();
        
        auto r2Data = r2.getOutput();
        
        //r2.outputCSV();
        
        //fht.outputCSV();
        if (checkAlgorithms) {
            for (long i = 0; i < sampleCount; ++i) {
                if(!compareDoubles(abs(r2Data[i]), abs(fhtData[i]))) {
                    cout << "u suck :(\nFailed at sample count: " << sampleCount << "\n";
                    return 0;
                }
            }
        }
    }
    
    randomFile << "#radix2\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << i << ";" << (long)exp2(i + minOrder) << ";" << times.first[i] << ";" << multiplications.first[i] << ";" << additions.first[i] << "\n";
    }
    
    randomFile << "\n\n\n#fht\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << i << ";" << (long)exp2(i + minOrder) << ";" << times.second[i] << ";" << multiplications.second[i] << ";" << additions.second[i] << "\n";
    }
    
    return 0;
}
