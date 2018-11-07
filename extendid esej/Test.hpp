//
//  Test.hpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 07/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>
#include <fstream>
#include "Radix2.hpp"
#include "Hartley.hpp"

using namespace std;

class Test {
    
private:
    
    ofstream file;
    
    // A constant for the comparision of 2 doubles
    constexpr static const double epsilon = 0.2;
    
    // Smallest and largest sample size to test, in the form of 2^n
    const int min2Order = 10;
    const int max2Order = 20;
    
    // Whether to check if the two algorithms produce the same output
    const bool checkOutput;
    
    // Where to store the resultant data
    const string path;
    
    // Arrays storing the benchmarks, .first is radix2, .second is fht
    pair<chrono::microseconds*, chrono::microseconds*> times;
    pair<long*, long*> multiplications;
    pair<long*, long*> additions;
    
    // The algorithm classes
    Radix2* radix2;
    Hartley* fht;
    
    // A function to compare 2 doubles
    bool compareDoubles (double A, double B);
    bool compareComplex(complex<double> A, complex<double> B);
    
public:

    Test(const string& path, const int minOrder, const int maxOrder, const bool checkOutput);
    ~Test();
    bool runTest();
    //long* getTimes() { return times; }
    // Writes the data into a file
    void writeData();
    
};

#endif /* Test_hpp */
