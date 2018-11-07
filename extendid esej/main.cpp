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


int main(int argc, const char * argv[]) {
    
    Radix2 r2("r2");
    
    r2.generateSamples();
    r2.computeFourier();
    r2.displayOutput();
    r2.outputCSV();
    
    Hartley fht("hartley");
    
    fht.generateSamples();
    fht.computeTest();
    //fht.computeFourier();
    fht.displayOutput();
    fht.outputCSV();
    
    return 0;
}
