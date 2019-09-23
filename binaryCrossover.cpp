/**
@file binaryCrossover.cpp
@author Christenson, Mark
*/

#include "binaryCrossover.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <math.h>

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

int BinaryCrossover::binToHex(int _input){
    int input = _input;
    int returnInt = 0;
    int i = 0;
    while (input > 0){
        if (input % 10 == 1){
            returnInt += pow(2, i);
        }
        input = input/10;
        i++;
    }
    return returnInt;
}

int BinaryCrossover::strToInt(string _input){
    stringstream intStr;
    int returnInt;
    intStr << _input;
    intStr >> returnInt;
    return returnInt;
}

string BinaryCrossover::hexToBinStr(int _input){
    return binStr(CHROMOSOMELENGTH, toBinary(_input));
}

string BinaryCrossover::binStr(int _length, int _input){
    stringstream intStr;
    intStr << (_input);
    string input;
    intStr >> input;
    if (input.length()<_length){
        string newStr;
        for (int i = input.length(); i < _length; i++){
            newStr += "0";
        }
        newStr += input;
        input = newStr;
    }

    return input;
}

int BinaryCrossover::toBinary(int _input){
    int input = _input;
    int i = 0;
    while (input >= pow(2,i)){
        i++;
    }

    int n = 0;
    int m = 0;
    int returnInt = 0;

    while (input > 0 && i >=0){
        n = pow(2,i);
        if(input/n == 1){
            m = pow(10, i);
            if(m % 9 == 0)  //I'm not sure why, but this program does not like
                            //4's and it shorts me one decimal value and leaves it with a multiple of nine
            {
                m++;
            }
            returnInt += m;
            input -= n;
        }
        i--;
    }

    return returnInt;
}
