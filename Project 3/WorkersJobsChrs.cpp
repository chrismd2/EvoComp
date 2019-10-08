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

string WorkersJobsChrs::crossOver(string *chromosomes, int countChrs, int lengthChrs){
    string returnString = "";
    int point = rand()%lengthChrs;
    for(int i = 0; i < countChrs; i++){
        for(int j = point; j > 0; j--){
            returnString += chromosomes[i][point - j];
        }
        int n = rand()%(lengthChrs - point);
        point += n;
    }
    return returnString;
}

int WorkersJobsChrs::getFitness(int workers, int *allWorkerTimes){
    int greatest = 0;
    for(int i = 0; i < workers; i++){
        //cout << "Worker " << i << " time: " << allWorkerTimes[i] << endl;
        if (i == 0 || allWorkerTimes[i] > allWorkerTimes[greatest]){
            greatest = i;
        }
    }

    return allWorkerTimes[greatest];
}

void WorkersJobsChrs::processData(int jobs, int workers, int orders, string chromosome,
                                  int *workerSpeeds, int *jobCycles, int *allWorkerTimes){
    int workerLength = digitCounter(jobs) + digitCounter(workers) + digitCounter(orders);
    string outStr = chromosome;

    int info[workers*jobs][3];
    int index;
    for(int i = 0; i < workers*jobs; i++){
        string str = "";
        index = 0;
        for(int k = 0; k < digitCounter(workers); k++){
            str +=outStr[k+i*workerLength];
        }
        string s = str;
        str = "";
        for(int j = 1; j <= digitCounter(workers); j ++){
            str += s[digitCounter(workers)-j];
        }
        index = stringToInt(str);
        info[i][0] = workerSpeeds[index];

        str = "";
        index = 0;
        for(int k = 0; k < digitCounter(jobs); k++){
            str += outStr[k+i*workerLength + digitCounter(workers)];
        }
        s = str;
        str = "";
        for(int j = 1; j <= digitCounter(workers); j ++){
            str += s[digitCounter(workers)-j];
        }
        index = stringToInt(str);
        info[i][1] = jobCycles[index];

        str = "";
        for(int k = 0; k < digitCounter(orders); k++){
            str += outStr[k+i*workerLength + digitCounter(workers) + digitCounter(jobs)];
        }
        s = str;
        str = "";
        for(int j = 1; j <= digitCounter(workers); j ++){
            str += s[digitCounter(workers)-j];
        }
        index = stringToInt(str);
        info[i][2] = index;
    }

    for(int i = 0; i < workers; i++){
        allWorkerTimes[i] = 0;
    }

    for(int i = 0; i < jobs*workers-1; i++){
        for(int j = 0; j < workers; j++){
            allWorkerTimes[j] += info[i][0]*info[i][1]*info[i][2];
            if(allWorkerTimes[j] == 0){
                //allWorkerTimes[j] = 99999;
            }
            i++;
        }
        i--;
    }
}

string WorkersJobsChrs::chromosomeMaker(int jobs, int workers, int *assignments){
    string outStr;
    for(int i = 0; i < jobs; i++){
        for(int j = 0; j < workers; j++){
            if(digitCounter(j)<digitCounter(jobs)){
                for(int n = 0; n < digitCounter(jobs)-digitCounter(j); n++)//notintegers...
                {
                    outStr+="0";
                }
            }
            outStr+= intToString(j);
            if(digitCounter(i)<digitCounter(workers)){
                for(int n = 0; n < digitCounter(workers)-digitCounter(i); n++)//notintegers...
                {
                    outStr+="0";
                }
            }
            outStr+= intToString(i);
            if(*((assignments+i*workers) + j)  == 0){
                outStr += "0";
            }
            if(*((assignments+i*workers) + j)!=0){
                outStr+= intToString(*((assignments+i*workers) + j));
            }
        }
    }
    return outStr;
}
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
