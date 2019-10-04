/**
@file itemChecker.cpp
@author Christenson, Mark
*/

#ifndef ITEMCHECKER_H
#define ITEMCHECKER_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

class ItemChecker {
private:
    int CHROMOSOMELENGTH = 8;
public:
    /**
    Creates an itemChecker object
    @pre None
    @post A binary object will be instantiated to process numbers in
            such a manner the following functions are intended to
    */
    ItemChecker();

    /**
    Creates a binary cross over object
    @pre None
    @post A binary object will be instantiated to process numbers in
            such a manner the following functions are intended to
    */
    ItemChecker(int);
};

#endif

