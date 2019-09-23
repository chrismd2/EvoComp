/**
@file binaryCrossover.cpp
@author Christenson, Mark
*/

#ifndef BINARYCROSSOVER_H
#ifndef BINARYCROSSOVER_H
#define BINARYCROSSOVER_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <math.h>

using namespace std;

class BinaryCrossover {
private:
    int CHROMOSOMELENGTH = 8;
public:
    /**
    Creates a binary cross over object
    @pre None
    @post A binary object will be instantiated to process numbers in
            such a manner the following functions are intended to
    */
    BinaryCrossover();
    /**
    Creates a binary cross over object with a stipulated chromosome length
    @pre an integer must be provided
    @post A binary object will be instantiated to process numbers in
            such a manner the following functions are intended to with the stipulated chromosome length
    */
    BinaryCrossover(int);

    /**
    crossover crosses two binary strings together
    @pre both must be strings representing binary numbers
    @post a string will be returned representing the result of using the OR operator on them
    */
    string crossover(string, string);

    // the rest could be considered helper functions....
    /**
    gives a binary representation of a hex number in hex
    @pre must be given an int
    @post a hex number is returned representing a binary number
    */
    int toBinary(int);
    /**
    converts an int to a string
    @pre must be given an int for length and must be given an int to process
    @post a string will be returned representing the provided int and will have
            leading 0 characters to fill the string length
    */
    string binStr(int, int);
    /**
    converts a hexadecimal integer to a binary string
    @pre must be given a hexadecimal integer
    @post a binary string is returned representing a binary number
    */
    string hexToBinStr(int);
    /**
    converts a string to an int
    @pre must be given a string
    @post a hex number is returned
    */
    int strToInt(string);
    /**
    converts a binary number to a hexadecimal
    @pre must be given an integer representing a binary number
    @post a hexadecimal number is returned
    */
    int binToHex(int);
};

#endif
