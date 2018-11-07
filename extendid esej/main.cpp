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
    
    Radix2 r2("radix-2");
    
    r2.prepareData();
    r2.computeFourier();
    cout << "Algorithm " << r2.name << " took: " << r2.getTimeTaken().count() << "ms.\n";
    //r2.displayOutput();
    r2.outputCSV();
    
    Hartley fht("fht");
    
    fht.prepareData();
    fht.computeFourier();
    cout << "Algorithm " << fht.name << " took: " << fht.getTimeTaken().count() << "ms.\n";
    //fht.displayOutput();
    fht.outputCSV();
    
    return 0;
}
