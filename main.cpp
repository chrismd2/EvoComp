#include <iostream>
#include <sstream>
#include <cstdlib>
/**
@file Main
@author Christenson, Mark
*/

#include <string>
#include <math.h>
#include "binaryCrossover.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void binTester();
int mutator(int );

main(){
    //binTester();
    srand(time(NULL));
    int setOfIterations[10];
    for(int i = 0; i<10; i++){
        setOfIterations[i] = mutator(10);
    }

    for(int i = 0; i<10; i++){
        cout << i+1 << ":\t" << setOfIterations[i] << endl;
    }
}

int mutator(int _bitCount){ /**< must have srand(time(NULL)); set*/
    if (true){
        int MAXBITS = 10;
            switch(_bitCount){
        case 10:
            break;
        case 0:
            _bitCount++;
            break;
        default:
            _bitCount = 10;
        }
    }

    BinaryCrossover bin(_bitCount);
    int a, b;
    int n = pow(2, _bitCount);
    int runCount = 0;
    a = 0;
    b = rand()%n;
    string strA = bin.hexToBinStr(a);
    string strB = bin.hexToBinStr(b);
    string bitStr = "";
    //cout << bin.crossover(strA, strB) << endl;
    for (int i = 0; i < _bitCount; i++){
        bitStr += "1";
    }
    //cout << runCount << ":" << strA << endl;
    while (strA != bitStr){
        strA = bin.crossover(strA, strB);
        a = bin.binToHex(bin.strToInt(strA));
        b = pow(2,((rand()%_bitCount-1)+1));
        b = a^b;
        strB = bin.hexToBinStr(b);
        runCount++;
        //cout << runCount << ":" << strA << endl;
    }

    return runCount;
}

void binTester() {
    BinaryCrossover bin;
    cout << "hello world\n";
    int a = 6;      //0110
    int b = 12;     //1100
    int c = a&b;    //0100
    cout << bin.toBinary(a) << " AND " << bin.toBinary(b) << " = " << bin.toBinary(c)<< endl;      //4
    for(int i = 321; i <= 321; i++){
        cout << i << ": " << bin.toBinary(i) << endl;// " - " << pow(10, toBinary(i)) << endl;
    }

    string someStrA = bin.hexToBinStr(a);
    string someStrB = bin.hexToBinStr(b);
    cout << someStrA << endl;
    cout << bin.strToInt(someStrA) << endl;

    cout << bin.binToHex(bin.strToInt(someStrA)) << endl;
    string offspring;
    offspring = bin.crossover(someStrA, someStrB);;
    cout << offspring << endl;
}