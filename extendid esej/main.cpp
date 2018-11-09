//
//  main.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 18/09/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include <iostream>
<<<<<<< HEAD
#include "Radix2.hpp"
#include "Hartley.hpp"
#include "Test.hpp"
#include <fstream>
#include <random>


int main(int argc, const char * argv[]) {
    long sampleCount = 512;
    const int minOrder = 3;
    const int maxOrder = 20;
    const int steps = maxOrder - minOrder + 1;
    const bool checkAlgorithms = true;
    ofstream file("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/output.csv");
    ofstream randomFile("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/randomOutput.csv");
    pair<long[steps], long[steps]> additions;
    pair<long[steps], long[steps]> multiplications;
    pair<long[steps], long[steps]> times;
    for (int i = minOrder; i <= maxOrder; ++i) {
    
        int idx = i - minOrder;
        sampleCount *= 2;
        
        
        
        Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/radix-2/" + to_string(idx), sampleCount);
        
        r2.prepareData();
        r2.computeFourier();
        
        times.first[idx] = r2.getTimeTaken().count();
        additions.first[idx] = r2.getAdditions();
        multiplications.first[idx] = r2.getMultiplications();
        
        auto r2Data = r2.getOutput();
        
        //r2.outputCSV();
        
        Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/fht/" + to_string(idx), sampleCount);
        
        fht.prepareData();
        fht.computeFourier();
        
        times.second[idx] = fht.getTimeTaken().count();
        additions.second[idx] = fht.getAdditions();
        multiplications.second[idx] = fht.getMultiplications();
        
        auto fhtData = fht.getOutput();
        
        //fht.outputCSV();
        if (checkAlgorithms) {
            for (long i = 0; i < sampleCount; ++i) {
                if(!Test::compareDoubles(abs(r2Data[i]), abs(fhtData[i]))) {
                    cout << "u suck :(\n";
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
=======
#include "Test.hpp"


int main(int argc, const char * argv[]) {
    /*
    Radix2 r2("radix-2");
>>>>>>> 1f35b6f90e5b5d9b3c381770d416a0d28acf1f25
    
    
<<<<<<< HEAD
    for (int i = minOrder; i <= maxOrder; ++i) {
        
        int idx = i - minOrder;
        sampleCount *= 2;
        
        
        
        Radix2 r2("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/randomRadix-2/" + to_string(idx), sampleCount);
        
        r2.prepareData();
        r2.computeFourier();
        
        times.first[idx] = r2.getTimeTaken().count();
        additions.first[idx] = r2.getAdditions();
        multiplications.first[idx] = r2.getMultiplications();
        
        auto r2Data = r2.getOutput();
        
        //r2.outputCSV();
        
        Hartley fht("/Users/Palo/Documents/Programming/EE/extendid\ esej/data/randomFht/" + to_string(idx), sampleCount);
        
        fht.prepareData();
        fht.computeFourier();
        
        times.second[idx] = fht.getTimeTaken().count();
        additions.second[idx] = fht.getAdditions();
        multiplications.second[idx] = fht.getMultiplications();
        
        auto fhtData = fht.getOutput();
        
        //fht.outputCSV();
        if (checkAlgorithms) {
            for (long i = 0; i < sampleCount; ++i) {
                if(!Test::compareDoubles(abs(r2Data[i]), abs(fhtData[i]))) {
                    cout << "u suck :(\n";
                }
            }
        }
    }
    randomFile << "#radix2\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << i << ";" << (long)exp2(i + minOrder) << ";" << times.first[i] << ";" << multiplications.first[i] << ";" << additions.first[i] << "\n";
    }
    file << "\n\n\n#fht\n";
    for(int i = 0; i < steps; ++i) {
        randomFile << i << ";" << (long)exp2(i + minOrder) << ";" << times.second[i] << ";" << multiplications.second[i] << ";" << additions.second[i] << "\n";
    }
=======
    Hartley fht("fht");
    
    fht.prepareData();
    fht.computeFourier();
    cout << "Algorithm " << fht.name << " took: " << fht.getTimeTaken().count() << "ms, " << fht.getMultiplications() << " multiplications and " << fht.getAdditions() << " additions.\n";
    //fht.displayOutput();
    fht.outputCSV();
    */
>>>>>>> 1f35b6f90e5b5d9b3c381770d416a0d28acf1f25
    
    Test test("/Users/Palo/Documents/Programming/EE/extendid\ esej/data", 10, 20, true);
    cout << test.runTest() << "\n";
    return 0;
}
