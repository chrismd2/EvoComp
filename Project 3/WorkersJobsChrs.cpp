/**
@file WorkersJobsChrs.cpp
@author Christenson, Mark
*/

#include <math.h>
#include <iostream>
#include <string>
#include <fstream>

#include "WorkersJobsChrs.h"
#include "binaryCrossover.h"

using namespace std;

int WorkersJobsChrs::digitCounter(int _num){
	int b = 0;
	int c = pow(10, b);
	do{
        b++;
        c = pow(10, b);
	}while(_num/c>0);

    return b;
}

string WorkersJobsChrs::intToString(int _input){
    BinaryCrossover converter;
    string returnString = converter.binStr(digitCounter(_input), _input);
    return returnString;
}
int WorkersJobsChrs::stringToInt(string _input){
    BinaryCrossover converter;
    int returnInt = converter.strToInt(_input);
    return returnInt;
}
int WorkersJobsChrs::stringToInt(char _input){
    string str = "";
    str += _input;
    BinaryCrossover converter;
    int returnInt = converter.strToInt(str);
    return returnInt;
}

string WorkersJobsChrs::OpenExsistingInstance(int _jobs, int _cycles, int _orders, int _workers, int _speed){
    string fileName = "";
    WorkersJobsChrs stringConversion;
    fileName += stringConversion.intToString(_workers);
    fileName +="_";
    fileName += stringConversion.intToString(_speed);
    fileName +="_";
    fileName += stringConversion.intToString(_jobs);
    fileName +="_";
    fileName += stringConversion.intToString(_cycles);
    fileName +="_";
    fileName += stringConversion.intToString(_orders);
    fileName += ".txt";

    fstream file(fileName, ios::in);
    if(file.fail()){
        CreateRandomInstance(_jobs, _cycles, _orders, _workers, _speed);
    }

    file.close();

    return fileName;
}//end OpenExsistingInstance

void WorkersJobsChrs::CreateRandomInstance(int _jobs, int _cycles, int _orders, int _workers, int _speed){
    string fileName = "";
    WorkersJobsChrs stringConversion;
    fileName += stringConversion.intToString(_workers);
    fileName +="_";
    fileName += stringConversion.intToString(_speed);
    fileName +="_";
    fileName += stringConversion.intToString(_jobs);
    fileName +="_";
    fileName += stringConversion.intToString(_cycles);
    fileName +="_";
    fileName += stringConversion.intToString(_orders);
    fileName += ".txt";

    fstream file(fileName, ios::out);

    for (int i = 0; i < _jobs; i++){
        file<<(1+rand()%_cycles)<<endl;
    }

    file<<'$'<<endl;

    for (int i = 0; i < _jobs; i++){
        file<<(1+rand()%_orders)<<endl;
    }

    file<<'$'<<endl;

    for (int i = 0; i < _workers; i++){
        file<<(1+rand()%_speed)<<endl;
    }
    file.close();
}//end CreateRandomInstance

void WorkersJobsChrs::getData(int &jobs, int &cycles, int &orders, int &workers, int &speed, int *jobCycles, int *jobOrders, int *workerSpeeds){
    WorkersJobsChrs chrs;
    string outStr;
    int index = 0;
    BinaryCrossover bin;
    fstream file(chrs.OpenExsistingInstance(jobs, cycles, orders, workers, speed), ios::in);

    while(file.peek() != '$'){
        getline(file, outStr);
        jobCycles[index] = bin.strToInt(outStr);
        index++;
    }

    getline(file, outStr);
    index = 0;

    while(file.peek() != '$'){
        getline(file, outStr);
        jobOrders[index] = bin.strToInt(outStr);
        index++;
    }

    getline(file, outStr);
    index = 0;

    while(file.peek() != EOF){
        getline(file, outStr);
        workerSpeeds[index] = bin.strToInt(outStr);
        index++;
    }
    file.close();
}//end getData
