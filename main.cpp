#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "WorkersJobsChrs.h"

using namespace std;

int main(){
    srand(NULL);

    int jobs = 9;       ///< keep at one digit
    int cycles = 50;
    int orders = 9;     ///< keep at one digit
    int workers = 9;    ///< keep at one digit
    int speed = 10;

    int jobCycles[jobs];
    int jobOrders[jobs];
    int workerSpeeds[workers];

    for(int i = 0; i < jobs; i++){
        jobCycles[i] = 0;
        jobOrders[i] = 0;
    }

    for(int i = 0; i < workers; i++){
        workerSpeeds[i] = 0;
    }

    if(true){
        WorkersJobsChrs chrs;
        chrs.getData(jobs, cycles, orders, workers, speed, jobCycles, jobOrders, workerSpeeds);
    }

    int index = 0;
    int currentWorker = rand()%workers;
    int assignments[jobs][workers];
    int remainingWork;

    for(int i = 0; i < jobs; i++){
        //cout << i << ": " << jobOrders[i] << endl;
        for(int j = 0; j < workers; j++){
            assignments[i][j] = 0;
        }
    }
    //cout << endl;
    while(index<jobs){

        int tooManyLoops = workers;
        remainingWork = jobOrders[index];

        while(assignments[index][currentWorker]>0 && tooManyLoops >=0){
            currentWorker = rand()%workers;
            tooManyLoops--;
        }

        if (true){
            assignments[index][currentWorker] = rand()%remainingWork;
            remainingWork-=assignments[index][currentWorker];
        }

        while(remainingWork > 0){
            currentWorker = rand()%workers;
            assignments[index][currentWorker] += 1;
            remainingWork--;
        }

        if(remainingWork == 0){
            index++;
        }
    }
    for(int i = 0; i < jobs; i++){
        for(int j = 0; j < workers; j++){
            cout    << "Worker " << j+1 << "'s assignments to job " << i+1 << ": "
                    << assignments[i][j] << "/" << jobOrders[i]<< endl;
        }
        cout << endl;
    }
/*
*/
    WorkersJobsChrs chrs;
    string outStr = "";
    for(int i = 0; i < jobs; i++){
        for(int j = 0; j < workers; j++){
            if(chrs.digitCounter(j)<chrs.digitCounter(jobs)){
                for(int n = 0; n < chrs.digitCounter(jobs)-chrs.digitCounter(j); n++)//notintegers...
                {
                    outStr+="0";
                }
            }
            outStr+= chrs.intToString(j);
            if(chrs.digitCounter(i)<chrs.digitCounter(workers)){
                for(int n = 0; n < chrs.digitCounter(workers)-chrs.digitCounter(i); n++)//notintegers...
                {
                    outStr+="0";
                }
            }
            outStr+= chrs.intToString(i);
            if(assignments[i][j]  == 0){
                outStr += "0";
            }
            if(assignments[i][j]!=0){
                outStr+= chrs.intToString(assignments[i][j]);
            }
        }
    }
/*
*/
    int workerLength = chrs.digitCounter(jobs) + chrs.digitCounter(workers) + chrs.digitCounter(orders);

    for(int i = 0; i< workers; i++){
        cout <<"Worker " << i << " speed: " << workerSpeeds[i] << endl;
    }
    cout << endl << outStr << endl;

    int info[workers*jobs][3];
    for(int i = 0; i < workers*jobs; i++){
        string str = "";
        index = 0;
        for(int k = 0; k < chrs.digitCounter(workers); k++){
            //cout << outStr[k+i*workerLength];
            str +=outStr[k+i*workerLength];
        }
        string s = str;
        str = "";
        for(int j = 1; j <= chrs.digitCounter(workers); j ++){
            str += s[chrs.digitCounter(workers)-j];
        }
        index = chrs.stringToInt(str);
        info[i][0] = workerSpeeds[index];
        //cout << endl;

        str = "";
        index = 0;
        for(int k = 0; k < chrs.digitCounter(jobs); k++){
            //cout << outStr[k+i*workerLength + chrs.digitCounter(workers)];
            str += outStr[k+i*workerLength + chrs.digitCounter(workers)];
        }
        s = str;
        str = "";
        for(int j = 1; j <= chrs.digitCounter(workers); j ++){
            str += s[chrs.digitCounter(workers)-j];
        }
        index = chrs.stringToInt(str);
        info[i][1] = jobCycles[index];
        //cout << endl;

        str = "";
        for(int k = 0; k < chrs.digitCounter(orders); k++){
            //cout << outStr[k+i*workerLength + chrs.digitCounter(workers) + chrs.digitCounter(jobs)];
            str += outStr[k+i*workerLength + chrs.digitCounter(workers) + chrs.digitCounter(jobs)];
        }
        s = str;
        str = "";
        for(int j = 1; j <= chrs.digitCounter(workers); j ++){
            str += s[chrs.digitCounter(workers)-j];
        }
        index = chrs.stringToInt(str);
        info[i][2] = index;


/*
        cout << info[i][0] << "\t" << info[i][1] << "\t"  << info[i][2] << endl;

    int info[workers*jobs][3];
    for(int i = 0; i < workers*jobs; i++){
        for(int j = 0; j < workerLength; j++){
            string str = "";
            index = 0;
            for(int k = 0; k < chrs.digitCounter(workers); k++){
                int tenPow = pow(10, chrs.digitCounter(workers) - k);
                str += outStr[k+i*workerLength];
                index += tenPow * chrs.stringToInt(str);
                info[i][0] = workerSpeeds[index];
            }
            cout << "Speed of worker " << index << ": " << workerSpeeds[index] << endl;

            str = "";
            index = 0;
            for(int k = 0; k < chrs.digitCounter(jobs); k++){
                int tenPow = pow(10, chrs.digitCounter(workers) - k);
                str += outStr[k+i*workerLength+chrs.digitCounter(workers)];
                index += tenPow * chrs.stringToInt(str);
                info[i][1] = jobCycles[index];
            }
            cout << "Cycles for job " << index << ": " << jobCycles[index] << endl;


            str = "";
            for(int k = 0; k < chrs.digitCounter(orders); k++){
                int tenPow = pow(10, chrs.digitCounter(workers) - k);
                str += outStr[k+i*workerLength+chrs.digitCounter(jobs)+chrs.digitCounter(workers)];
                //index += tenPow * chrs.stringToInt(str);
                info[i][2] = index;
            }
            cout << "Orders for job " << index << ": " << jobOrders[index] << endl << endl;

        }

        cout    << info[i][0] << " " << info[i][1] << " "  << info[i][2] << " = "
                << info[i][0]*info[i][1]*info[i][2] << endl;
*/
    }
    cout << endl;

    int allWorkerTimes[workers];
    for(int i = 0; i < workers; i++){
        allWorkerTimes[i] = 0;
    }

    for(int i = 0; i < jobs*workers-1; i++){
        for(int j = 0; j < workers; j++){
            allWorkerTimes[j] += info[i][0]*info[i][1]*info[i][2];
/*
            cout << i << ": " << info[i][0]<< " " <<info[i][1]<< " " <<info[i][2] << " = "
                 << info[i][0]*info[i][1]*info[i][2] << endl;
            cout << "Worker " << j << ": " << allWorkerTimes[j] << endl;
*/
            i++;
        }
        i--;
        //cout << endl;
    }

    int greatest = 0;
    for(int i = 0; i < workers; i++){
        cout << "Worker " << i << " time: " << allWorkerTimes[i] << endl;
        if (i == 0 || allWorkerTimes[i] > allWorkerTimes[greatest]){
            greatest = i;
        }
    }
    cout << "\nWorker " << greatest << "'s time is " << allWorkerTimes[greatest] << endl;
    cout << endl;
/*
    int workerTimes[workers];
    for(int i = 0; i < workers; i++){
        workerTimes[i] = 0;
    }

    for(int i = 0; i < outStr.length(); i+=workerLength){
        workerTimes[chrs.stringToInt(outStr[i])]    += workerSpeeds[chrs.stringToInt(outStr[i])]
                                                    *  jobCycles[chrs.stringToInt(outStr[i+1])]
                                                    *  chrs.stringToInt(outStr[i+2]);
    }

    for(int i = 0; i < workers; i++){
        cout << i << ": " << workerTimes[i] << endl;
    }
*/
}
