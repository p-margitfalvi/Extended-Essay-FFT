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
    delete [] radix2Times;
    delete [] fhtTimes;
    
    delete [] radix2Multiplications;
    delete [] radix2Additions;
    delete [] fhtMultiplications;
    delete [] fhtAdditions;
    
    delete radix2;
    delete fht;
}

Test::Test(const string& path, const int minOrder, const int maxOrder, bool checkOutput) : path(path), min2Order(minOrder), max2Order(maxOrder), checkOutput(checkOutput) {
    
    file = ofstream(path + "output.csv");
    
    radix2Times = new long[max2Order - min2Order];
    fhtTimes = new long[max2Order - min2Order];
    
    radix2Multiplications = new long[max2Order - min2Order];
    radix2Additions = new long[max2Order - min2Order];
    
    fhtMultiplications = new long[max2Order - min2Order];
    fhtAdditions = new long[max2Order - min2Order];
    
    radix2 = new Radix2(path + "radix2");
    fht = new Hartley(path + "fht");
    
}

bool Test::runTest() {
    
    for (int i = min2Order; i <= max2Order; ++i) {
        long sampleSize = (long)exp2(i);
        radix2->setSampleCount(sampleSize);
        radix2->prepareData();
        radix2->computeFourier();
        
        
    }
    
    return false;
}

