#include <iostream>
#include <sstream>
#include <cstdlib>
/**
@file TBD
@author Christenson, Mark
*/

#include <string>
#include <math.h>

using namespace std;

int CHROMOSOMELENGTH = 8;

/**
crossover crosses two binary strings together
@pre
@post
*/
string crossover(string, string);
/**
binTester is designed to test the binary functions
@pre None
@post None
*/
void binTester();

// the rest could be considered helper functions....
int toBinary(int);
string binStr(int, int);
string hexToBinStr(int);
int strToInt(string);
int binToHex(int);

main(){
    binTester();
}

void binTester() {
    cout << "hello world\n";
    int a = 6;      //0110
    int b = 12;     //1100
    int c = a&b;    //0100
    cout << toBinary(a) << " AND " << toBinary(b) << " = " << toBinary(c)<< endl;      //4
    for(int i = 321; i <= 321; i++){
        cout << i << ": " << toBinary(i) << endl;// " - " << pow(10, toBinary(i)) << endl;
    }

    string someStrA = hexToBinStr(a);
    string someStrB = hexToBinStr(b);
    cout << someStrA << endl;
    cout << strToInt(someStrA) << endl;

    cout << binToHex(strToInt(someStrA)) << endl;
    string offspring;
    offspring = crossover(someStrA, someStrB);;
    cout << offspring << endl;
}

string crossover(string _a, string _b){
    int a = binToHex(strToInt(_a));
    int b = binToHex(strToInt(_b));
    int offspring;
    offspring = a|b;
    string offstring = hexToBinStr(offspring);
    return offstring;
}

int binToHex(int _input){
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

int strToInt(string _input){
    stringstream intStr;
    int returnInt;
    intStr << _input;
    intStr >> returnInt;
    return returnInt;
}

string hexToBinStr(int _input){
    return binStr(CHROMOSOMELENGTH, toBinary(_input));
}

string binStr(int _length, int _input){
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

int toBinary(int _input){
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
