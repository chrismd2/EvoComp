/**
@file itemChecker.cpp
@author Christenson, Mark
*/

#include "itemChecker.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

BinaryCrossover::BinaryCrossover(){
    CHROMOSOMELENGTH = CHROMOSOMELENGTH;
}
BinaryCrossover::BinaryCrossover(int _Length = 8){
    CHROMOSOMELENGTH = _Length;
}

string BinaryCrossover::crossover(string _a, string _b){
    int a = binToHex(strToInt(_a));
    int b = binToHex(strToInt(_b));
    int offspring;
    offspring = a|b;
    string offstring = hexToBinStr(offspring);
    return offstring;
}
