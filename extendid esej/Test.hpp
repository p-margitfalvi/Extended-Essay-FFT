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
    
public:
    
    ofstream file;
    const int min2Order = 10;
    const int max2Order = 20;
    const bool checkOutput;
    const string path;
    long* times;
    
    Radix2* radix2;
    Hartley* fht;
    
    
    Test(const string& path, const int minOrder, const int maxOrder, const bool checkOutput);
    ~Test();
    bool runTest();
    long* getTimes() { return times; }
    void writeTimes();
    
};

#endif /* Test_hpp */
