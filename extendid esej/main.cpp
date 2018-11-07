//
//  main.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 18/09/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include <iostream>
#include "Test.hpp"


int main(int argc, const char * argv[]) {
    /*
    Radix2 r2("radix-2");
    
    r2.prepareData();
    r2.computeFourier();
    cout << "Algorithm " << r2.name << " took: " << r2.getTimeTaken().count() << "ms, " << r2.getMultiplications() << " multiplications and " << r2.getAdditions() << " additions.\n";
    //r2.displayOutput();
    r2.outputCSV();
    
    Hartley fht("fht");
    
    fht.prepareData();
    fht.computeFourier();
    cout << "Algorithm " << fht.name << " took: " << fht.getTimeTaken().count() << "ms, " << fht.getMultiplications() << " multiplications and " << fht.getAdditions() << " additions.\n";
    //fht.displayOutput();
    fht.outputCSV();
    */
    
    Test test("/Users/Palo/Documents/Programming/EE/extendid\ esej/data", 10, 20, true);
    cout << test.runTest() << "\n";
    return 0;
}
