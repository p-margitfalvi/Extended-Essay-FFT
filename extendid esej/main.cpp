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

template <typename T>
struct comma_separator : std::numpunct<T>
{
    typename std::numpunct<T>::char_type do_decimal_point() const
    {
        return ',';
    }
};

template <typename T>
std::basic_ostream<T>& comma_sep(std::basic_ostream<T>& os)
{
    os.imbue(std::locale(std::locale(""), new comma_separator<T>));
    return os;
}

bool compareDoubles(double A, double B) {
    double diff = A - B;
    return (diff < epsilon) && (-diff < epsilon);
}

double randomDouble(int min, int max) {
    return (double)(random() % (max - min)) + min;
}


int main(int argc, const char * argv[]) {
    
    const int trialCount = 20;
    const int minOrder = 5;
    const int maxOrder = 25;
    
    const int minRandomAmplitude = -500;
    const int maxRandomAmplitude = 500;
    
    long sampleCount = (long)exp2(minOrder - 1);
    
    const int steps = maxOrder - minOrder + 1;
    // Whether to compare the outputs of the two algorithms
    const bool checkAlgorithms = false;
    // Whether to write every transformed wave into a separate csv file
    const bool outputAll = false;
    
    ofstream file("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/output.csv");
    ofstream randomFile("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/randomOutput.csv");
    
    pair<long[steps], long[steps]> additions;
    pair<long[steps], long[steps]> multiplications;
    pair<clock_t[steps], clock_t[steps]> times;
    
    file << comma_sep;
    randomFile << comma_sep;
    
    for (int i = minOrder; i <= maxOrder; ++i) {
        
        int idx = i - minOrder;
        sampleCount *= 2;
        
        for (int l = 0; l < trialCount; ++l) {
            
            Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/fht/" + to_string(i), sampleCount);
            
            fht.prepareData();
            fht.computeFourier();
            
            times.second[idx] = fht.getTimeTaken();
            additions.second[idx] = fht.getAdditions();
            multiplications.second[idx] = fht.getMultiplications();
            
            auto fhtData = fht.getOutput();
            
            Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/radix-2/" + to_string(i), sampleCount);
            
            r2.prepareData();
            r2.computeFourier();
            
            
            times.first[idx] += r2.getTimeTaken();
            additions.first[idx] = r2.getAdditions();
            multiplications.first[idx] = r2.getMultiplications();
            
            auto r2Data = r2.getOutput();
            
            if (outputAll) {
                r2.outputCSV();
                fht.outputCSV();
            }
            
            if (checkAlgorithms) {
                for (long j = 0; j < sampleCount; ++j) {
                    if(!compareDoubles(abs(r2Data[j]), abs(fhtData[j]))) {
                        cout << "Failed at sample count: " << sampleCount << "\n";
                    }
                }
            }
        }
    }
    
    file << "#radix2\n";
    for(int i = 0; i < steps; ++i) {
        file << fixed << i + 1 << ";" << (long)exp2(i + minOrder) << ";" << times.first[i] / (double)trialCount << ";" << multiplications.first[i] / (double)trialCount << ";" << additions.first[i] / (double)trialCount << "\n";
    }
    
    file << "\n\n\n#fht\n";
    for(int i = 0; i < steps; ++i) {
        file << fixed << i + 1 << ";" << (long)exp2(i + minOrder) << ";" << times.second[i] / (double)trialCount << ";" << multiplications.second[i] / (double)trialCount << ";" << additions.second[i] / (double)trialCount << "\n";
    }
    
    vector<complex<double>> randomSet;
    sampleCount = (long)exp2(minOrder - 1);
    // Random data set
    for (int i = minOrder; i <= maxOrder; ++i) {
        
        int idx = minOrder;
        sampleCount *= 2;
        
        for (int l = 0; l < trialCount; ++l) {
            
            randomSet.resize(sampleCount, complex<double>(0, 0));
            for (long m = 0; m < sampleCount; ++m) {
                randomSet[m] = randomDouble(minRandomAmplitude, maxRandomAmplitude);
            }
            
            Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/random_fht/" + to_string(i), sampleCount);
            
            fht.prepareData();
            fht.insertSamples(randomSet);
            fht.computeFourier();
            
            times.second[idx] = fht.getTimeTaken();
            additions.second[idx] = fht.getAdditions();
            multiplications.second[idx] = fht.getMultiplications();
            
            auto fhtData = fht.getOutput();
            
            Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/random_radix-2/" + to_string(i), sampleCount);
            
            r2.prepareData();
            r2.insertSamples(randomSet);
            r2.computeFourier();
            
            times.first[idx] = r2.getTimeTaken();
            additions.first[idx] = r2.getAdditions();
            multiplications.first[idx] = r2.getMultiplications();
            
            auto r2Data = r2.getOutput();
            
            if (outputAll) {
                r2.outputCSV();
                fht.outputCSV();
            }
            
            if (checkAlgorithms) {
                for (long j = 0; j < sampleCount; ++j) {
                    if(!compareDoubles(abs(r2Data[j]), abs(fhtData[j]))) {
                        cout << "Failed at sample count: " << sampleCount << "\n";
                        return 0;
                    }
                }
            }
        }
    }
    
    randomFile << "#radix2\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << fixed << i + 1 << ";" << (long)exp2(i + minOrder) << ";" << times.first[i] / (double)trialCount << ";" << multiplications.first[i] / (double)trialCount << ";" << additions.first[i] / (double)trialCount << "\n";
    }
    
    randomFile << "\n\n\n#fht\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << fixed << i + 1 << ";" << (long)exp2(i + minOrder) << ";" << times.second[i] / (double)trialCount << ";" << multiplications.second[i] / (double)trialCount << ";" << additions.second[i] / (double)trialCount << "\n";
    }
    
    return 0;
}
