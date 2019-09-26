#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
/**
@file Main
@author Christenson, Mark; Smith, Daniel
*/

#include <string>
#include <math.h>
#include "binaryCrossover.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bag.h"

using namespace std;

void binTester();
int mutator(int );
string newCrossoverTester();

int main(){
    fstream dataIn("items.txt", ios::in);
    const int totalItems = 90;
    item itemOptions[totalItems];
    int inCount = 0;
    string str;
    BinaryCrossover bin;
	const int totalBags = 10;
	bag knapsacks[totalBags];

	while (dataIn.peek() != '.')
	{
		getline(dataIn, str);
		knapsacks[inCount].setBagMax(bin.strToInt(str));
		
		inCount++;
	}
	inCount = 0;

    while(dataIn.peek() != '.')
    {
        getline(dataIn, str);
        itemOptions[inCount].setW(bin.strToInt(str));
        if(itemOptions[inCount].getW() == 0){
            itemOptions[inCount].setW(0);
        }
        inCount++;
    }
    inCount = 0;
    while(dataIn.peek() != EOF)
    {
        getline(dataIn, str);
        itemOptions[inCount].setV(bin.strToInt(str));
        inCount++;
    }
    dataIn.close();

    inCount = 0;
    str = "";
    srand(time(NULL));

    for(int i = 0; i < totalItems; i++){
        //cout << chromosome[i];
        if(i == totalItems - 1){
            //cout << endl << i << endl;
        }
    }

    cout << "These UNIQUE strings are OR'ed together\n";
    string chromosome = newCrossoverTester();


    cout << "\nThese are all the items\n";
    while(inCount < totalItems){
        cout << itemOptions[inCount].getW() << " " << itemOptions[inCount].getV() << endl;
        inCount++;
    }

	for (int j = 0; j < totalBags; j++)
	{
		for (int i = 0; i < totalItems; i++) {
			if (chromosome[i] == '1' && knapsacks[j].getBagWeight() + itemOptions[i].getW() <= knapsacks[j].getBagMax()) {
				knapsacks[j].setBagWeight(knapsacks[j].getBagWeight() + itemOptions[i].getW());
				knapsacks[j].setBagValue(knapsacks[j].getBagValue() + itemOptions[i].getV());
			}
		}
		cout << "Bag Weight: " << knapsacks[j].getBagWeight() << "\nBag Value: " << knapsacks[j].getBagValue() << endl;
	}
/*
example run values
6720
10950
17280
*/
}

string newCrossoverTester(){
    int totalItems = 90;
    BinaryCrossover bin;
    stringstream intStr;
    long unsigned int bit = 0;
    const int chromosomeCount = 2;
	string chromosome[chromosomeCount] = {};


    for (int j = 0; j < chromosomeCount; j++)
    {
        for(int i = 0; i < totalItems; i++){
            switch(rand()%2){
            case 0:
                chromosome[j] += "0";
                break;
            case 1:
                chromosome[j] += "1";
                break;
            }
        }
    }
    cout << chromosome[0] << endl << chromosome[1] << endl;

    cout << bin.crossover(chromosome[0], chromosome[1]);

    return chromosome[0];
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
