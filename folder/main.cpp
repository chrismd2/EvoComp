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


void mutator(string * , int , int , bag * , item * );
void chromosomeEvolution(string *, int, bag*, int, item*);
string chromosomeMaker(int);
void fixer(bag*, string*, int, int, item*);
void crossBagFixer(bag*, string*, int, int, item*);
void addItem(bag*, string*, int, int, item*);
void removeItem(bag*, string*, int, int, item*);

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

	//This if statement is to consume the period
	if(dataIn.peek() == '.'){
        getline(dataIn, str);
	}

	//This while loop is for weight
    while(dataIn.peek() != '.')
    {
        getline(dataIn, str);
        itemOptions[inCount].setW(bin.strToInt(str));
        if(itemOptions[inCount].getW() == 0){
            itemOptions[inCount].setW(0);
        }
        inCount++;
    }

	//This if statement is to consume the period
	if(dataIn.peek() == '.'){
        getline(dataIn, str);
	}
    inCount = 0;

    //This while loop is for value
    while(dataIn.peek() != EOF)
    {
        getline(dataIn, str);
        itemOptions[inCount].setV(bin.strToInt(str));
        if(itemOptions[inCount].getV() == 0){
            itemOptions[inCount].setV(1);
        }
        inCount++;
    }
    dataIn.close();

    inCount = 0;
    str = "";
    srand(time(NULL));

    string chromosome[totalBags] = "";

	int chrsIndex = 0;
	int knapsackIndex = 0;
	bool inABag = false;

	while(knapsackIndex == 0 && chromosome[knapsackIndex].length() < totalItems){
        if (itemOptions[chrsIndex].getW()<=(knapsacks[knapsackIndex].getBagMax() - knapsacks[knapsackIndex].getBagWeight())){
            knapsacks[knapsackIndex].setBagWeight(knapsacks[knapsackIndex].getBagWeight()+itemOptions[chrsIndex].getW());
            knapsacks[knapsackIndex].setBagValue(knapsacks[knapsackIndex].getBagValue()+itemOptions[chrsIndex].getV());
            chromosome[knapsackIndex] += '1';
        }

        else{
            chromosome[knapsackIndex] += '0';
        }
        chrsIndex++;
	}

	knapsackIndex++;
	chrsIndex = 0;

	bool isInBag = false;
	while(knapsackIndex < totalBags){
        while(chromosome[knapsackIndex].length()<totalItems){
            for(int i = 0; i < knapsackIndex; i++){
                if(chromosome[i][chrsIndex] == '1'){
                    isInBag = true;
                }
            }
            if (!isInBag && itemOptions[chrsIndex].getW()<=(knapsacks[knapsackIndex].getBagMax() - knapsacks[knapsackIndex].getBagWeight())){
                knapsacks[knapsackIndex].setBagWeight(knapsacks[knapsackIndex].getBagWeight()+itemOptions[chrsIndex].getW());
                knapsacks[knapsackIndex].setBagValue(knapsacks[knapsackIndex].getBagValue()+itemOptions[chrsIndex].getV());
                chromosome[knapsackIndex] += '1';
            }
            else{
                chromosome[knapsackIndex] += '0';
            }
            isInBag = false;
            chrsIndex++;
        }
        chrsIndex = 0;
        knapsackIndex++;
	}

	crossBagFixer(knapsacks, chromosome, totalBags, totalItems, itemOptions);

	cout << "BAG#\t\t\tCHROMOSOME\t\t\t\t\t\t\t\t VALUE\tWEIGHT\tMAX\n";
	for(int i = 0; i < totalBags; i++){
        cout << "KP " << i + 1 << ": " << chromosome[i] << " " << knapsacks[i].getBagValue() << "\t" << knapsacks[i].getBagWeight() << "\t" << knapsacks[i].getBagMax() << endl;// " " << chromosome[i].length() << " " << totalItems << endl;
	}
	cout << endl;

	int m,n;
	for(int i = 0; i < 10000; i++){
        m = rand()%totalBags;
        n = rand()%totalItems;
        removeItem(knapsacks, chromosome, m, n, itemOptions);
	}

	/*
	cout << "BAG#\t\t\tCHROMOSOME\t\t\t\t\t\t\t\t VALUE\tWEIGHT\tMAX\n";
	for(int i = 0; i < totalBags; i++){
        cout << "KP " << i + 1 << ": " << chromosome[i] << " " << knapsacks[i].getBagValue() << "\t" << knapsacks[i].getBagWeight() << "\t" << knapsacks[i].getBagMax() << endl;// " " << chromosome[i].length() << " " << totalItems << endl;
	}
	cout << endl;
*/
	for(int i = 0; i < 1000; i++){
        chromosomeEvolution(chromosome, totalItems, knapsacks, totalBags, itemOptions);
	}

	cout << "BAG#\t\t\tCHROMOSOME\t\t\t\t\t\t\t\t VALUE\tWEIGHT\tMAX\n";
	for(int i = 0; i < totalBags; i++){
        cout << "KP " << i + 1 << ": " << chromosome[i] << " " << knapsacks[i].getBagValue() << "\t" << knapsacks[i].getBagWeight() << "\t" << knapsacks[i].getBagMax() << endl;// " " << chromosome[i].length() << " " << totalItems << endl;
	}
	cout << endl;
/*
	*/
	return 0;
}


void chromosomeEvolution(string * _chromosome, int _totalItems, bag * knapsacks, int _totalBags, item* itemOptions){
    int bagNum = rand()%_totalBags;
    BinaryCrossover bin(_totalItems);
    string oldChrs[1] = _chromosome[bagNum];
    string newChrs[1] = bin.crossover(_chromosome[bagNum], chromosomeMaker(_totalItems));
    bag aBag[1];
    aBag[0].setBagMax(knapsacks[bagNum].getBagMax());

    for(int i = 0; i < _totalItems; i++){
        if(newChrs[0][i] == '1'){
            aBag[0].setBagValue(aBag[0].getBagValue() + itemOptions[i].getV());
            aBag[0].setBagWeight(aBag[0].getBagWeight() + itemOptions[i].getW());
            //cout << aBag[0].getBagWeight()<< " " << aBag[0].getBagValue() << endl;
        }
    }

    crossBagFixer(aBag, newChrs, 1, _totalItems,  itemOptions);

    if(knapsacks[bagNum].getBagValue() < aBag[0].getBagValue())
    {
        knapsacks[bagNum].setBagValue(aBag[0].getBagValue());
        knapsacks[bagNum].setBagWeight(aBag[0].getBagWeight());
        _chromosome[bagNum] = newChrs[0];
    }

    crossBagFixer(aBag, newChrs, 1, _totalItems,  itemOptions);
}

void addItem(bag * knapsacks, string * _chromosome, int _bagNum, int _itemNum, item* _itemOptions){
    if(_chromosome[_bagNum][_itemNum]=='0'){
        _chromosome[_bagNum][_itemNum]=='1';
        knapsacks[_bagNum].setBagWeight(knapsacks[_bagNum].getBagWeight()+_itemOptions[_itemNum].getW());
        knapsacks[_bagNum].setBagValue(knapsacks[_bagNum].getBagValue()+_itemOptions[_itemNum].getV());
    }
    else{//cout<<"\n\nItem is already in the bag.\n\n";
    }
}

void removeItem(bag * knapsacks, string * _chromosome, int _bagNum, int _itemNum, item* _itemOptions){
    //_bagNum--;
    //_itemNum--;
    if(_chromosome[_bagNum][_itemNum]=='1'){
        //cout << "CHRS" << _chromosome[_bagNum] << " A" << _itemNum << endl;
        _chromosome[_bagNum][_itemNum]='0';
        // << "CHRS" << _chromosome[_bagNum] << " B" << endl;
        knapsacks[_bagNum].setBagWeight(knapsacks[_bagNum].getBagWeight()-_itemOptions[_itemNum].getW());
        knapsacks[_bagNum].setBagValue(knapsacks[_bagNum].getBagValue()-_itemOptions[_itemNum].getV());

    }
    else{//cout<<"\n\nItem is not in the bag.\n\n";
    }
}
void stringToBag(bag knapsacks, string _chromosome, int _totalItems, item* itemOptions){
    knapsacks.setBagValue(0);
    knapsacks.setBagWeight(0);
    for(int i = 0; i < _totalItems; i++){
        switch(_chromosome[i]){
        case '1':
            knapsacks.setBagValue(knapsacks.getBagWeight()+itemOptions[i].getV());
            knapsacks.setBagWeight(knapsacks.getBagWeight()+itemOptions[i].getW());
            break;
        }
    }
    cout << "In stringToBag\n";
}
void crossBagFixer(bag * knapsacks, string * _chromosome, int _totalBags, int _totalItems, item* itemOptions){
    for(int i = 0; i < _totalBags; i++){
        if(i > 0){
            for(int j = 0; j < _totalItems; j++){
                for(int k = 0; k < _totalBags; k++){
                    if(_chromosome[k][j] == '1'){
                        removeItem(knapsacks, _chromosome, i, j, itemOptions);
                    }
                }

                if(knapsacks[i].getBagWeight() < 0 || knapsacks[i].getBagValue()< 0){
                    cout << "\n\nLESS THAN ZERO\n\n";
                    knapsacks[i].setBagWeight(0);
                    knapsacks[i].setBagValue(0);
                    _chromosome[i] = "";
                    for(int j = 0; j< _totalItems; j++){
                        _chromosome[i] += '0';
                    }
                }
            }
        }

        int n = rand()%_totalItems;
        string chromosome = *_chromosome;
        bag aBag = *knapsacks;
        bool looped = false;
        while(knapsacks[i].getBagWeight()>knapsacks[i].getBagMax()){
            if(_chromosome[i][n] == '1'){
                    removeItem(knapsacks, _chromosome, i, n, itemOptions);
            }
/*    cout << bagNum+1    << ": " << aBag[0].getBagValue()
                        << " " << aBag[0].getBagWeight()
                        << " " << aBag[0].getBagMax() << endl;*/
            else{
                n--;
                if(n<0){
                    n = _totalItems;
                    if(looped){
                        cout << "LOOPED" << endl;
                        knapsacks[i].setBagWeight(0);
                        knapsacks[i].setBagValue(0);
                    }
                    looped = true;
                }
            }
        }
        //cout << _chromosome[i] << endl;

        /**/
    }
}

string chromosomeMaker(int _totalItems){
    int totalItems = _totalItems;
    BinaryCrossover bin;
	string chromosome = {};



    for(int i = 0; i < totalItems; i++){
        switch(rand()%2){
        case 0:
            chromosome += "0";
            break;
        case 1:
            chromosome += "1";
            break;
        }
    }

    return chromosome;
}

void mutator(string * _chromosome, int _totalBags, int _totalItems, bag * _knapsacks, item * _items){ /**< must have srand(time(NULL)); set*/
    int bagNum = rand()%_totalBags;
    int itemNum = rand()%_totalItems;
    string chromosome[_totalBags] = * _chromosome;
    int knapsacksValue = _knapsacks[bagNum].getBagValue();
    int knapsacksWeight = _knapsacks[bagNum].getBagWeight();

    switch(chromosome[bagNum][itemNum]){
    case '1':
        removeItem(_knapsacks, _chromosome, bagNum, itemNum, _items);
        break;
    case '0':
        addItem(_knapsacks, _chromosome, bagNum, itemNum, _items);
        break;
    }

    //fixer(knapsacks, chromosome, _totalBags, _totalItems, _items);

    if(knapsacksValue >= _knapsacks[bagNum].getBagValue()){
        //cout << _knapsacks[bagNum].getBagValue()<<endl;
        _knapsacks[bagNum].setBagValue(knapsacksValue);
        _knapsacks[bagNum].setBagWeight(knapsacksWeight);
        switch(chromosome[bagNum][itemNum]){
        case '1':
            chromosome[bagNum][itemNum] = '0';
            break;
        case '0':
            chromosome[bagNum][itemNum] = '1';
            break;
        }
    }
    /*
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
    }*/

    //return runCount;
}
