//
//  Test.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 07/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Test.hpp"

Test::~Test() {
    file.flush();
    file.close();
    delete times;
    delete radix2;
    delete fht;
}

Test::Test(const string& path, const int minOrder, const int maxOrder, bool checkOutput) : path(path), min2Order(minOrder), max2Order(maxOrder), checkOutput(checkOutput) {
    
    file = ofstream(path + "output.csv");
    
    times = new long[max2Order - min2Order];
    
    radix2 = new Radix2(path + "radix2");
    fht = new Hartley(path + "fht");
    
}

bool Test::runTest() {
    
    for (int i = min2Order; i <= max2Order; ++i) {
        long sampleSize = (long)exp2(i);
        
    }
    
    return false;
}

