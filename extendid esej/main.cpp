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
#include "Test.hpp"


int main(int argc, const char * argv[]) {
    long sampleCount = 512;
    for (int i = 10; i <= 20; ++i) {
        
        sampleCount *= 2;
        Radix2 r2("radix-2", sampleCount);
        
        r2.prepareData();
        r2.computeFourier();
        cout << "Algorithm " << r2.name << " took: " << r2.getTimeTaken().count() << "ms, " << r2.getMultiplications() << " multiplications and " << r2.getAdditions() << " additions.\n";
        //r2.displayOutput();
        //r2.outputCSV();
        
        Hartley fht("fht", sampleCount);
        
        fht.prepareData();
        fht.computeFourier();
        cout << "Algorithm " << fht.name << " took: " << fht.getTimeTaken().count() << "ms, " << fht.getMultiplications() << " multiplications and " << fht.getAdditions() << " additions.\n";
        
        auto r2Data = r2.getOutput();
        auto fhtData = fht.getOutput();
        
        for (long i = 0; i < sampleCount; ++i) {
            if(!Test::compareDoubles(abs(r2Data[i]), abs(fhtData[i]))) {
                cout << "u suck :(\n";
            }
        }
    }
    
    //fht.displayOutput();
    //fht.outputCSV();
    
    return 0;
}
