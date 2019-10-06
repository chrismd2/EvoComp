/**
@file WorkersJobsChrs.h
@author Christenson, Mark
*/

#ifndef WORKERSJOBSCHRS_H
#define WORKERSJOBSCHRS_H

#include <string>

using namespace std;

class WorkersJobsChrs {
private:
public:
    int digitCounter(int);
    string intToString(int);
    int stringToInt(string);
    int stringToInt(char);
    string OpenExsistingInstance(int _jobs, int _cycles, int _orders, int _workers, int _speed);
    void CreateRandomInstance(int _jobs, int _cycles, int _orders, int _workers, int _speed);
    void getData(int &jobs, int &cycles, int &orders, int &workers, int &speed, int *jobCycles, int *jobOrders, int *workerSpeeds);
};

#endif // WORKERSJOBSCHRS_H
