#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "WorkersJobsChrs.h"

using namespace std;

void randomizeData(int workers, int speed, int *workerSpeeds,
                   int jobs, int cycles, int *jobCycles, int orders, int *jobOrders,
                   int  *assignments);

int getWorst(string *chromosomes, int countChrs,
             int jobs, int workers, int orders,
             int *workerSpeeds, int *jobCycles, int *allWorkerTimes);

int bestFitness(string *chromosomes, int countChrs,
             int jobs, int workers, int orders,
             int *workerSpeeds, int *jobCycles, int *allWorkerTimes);

void replaceWorst(  string *chromosomes, int countChrs, string newChrs,
                    int jobs, int workers, int orders,
                    int *workerSpeeds, int *jobCycles, int *allWorkerTimes);

int main(){
    srand(NULL);

    int jobs = 5;       ///< keep at one digit
    int cycles = 50;
    int orders = 3;     ///< keep at one digit
    int workers = 2;    ///< keep at one digit
    int speed = 10;

    int jobCycles[jobs];
    int jobOrders[jobs];
    int workerSpeeds[workers];

    int assignments[jobs][workers];
    int allWorkerTimes[workers];

    WorkersJobsChrs chrs;

    int countChrs = 9;
    string chromosomes[countChrs];

    for(int i = 0; i < countChrs; i++){
        randomizeData(workers, speed, workerSpeeds, jobs, cycles, jobCycles, orders, jobOrders, (int *)assignments);
        chromosomes[i] = chrs.chromosomeMaker(jobs, workers, (int *)assignments);
        chrs.processData(jobs, workers, orders, chromosomes[i], workerSpeeds, jobCycles, allWorkerTimes);
        cout << chrs.getFitness(workers, allWorkerTimes) << endl;
    }
    cout << endl;

    string offspring;

    int lastFitness = 0;
    int tripped = 0;
    while (bestFitness(chromosomes, countChrs, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes) != lastFitness || tripped < 10){
        lastFitness = bestFitness(chromosomes, countChrs, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes);
        offspring = chrs.crossOver(chromosomes, countChrs, workers*jobs);
        chrs.processData(jobs, workers, orders, offspring, workerSpeeds, jobCycles, allWorkerTimes);
        //cout << chrs.getFitness(workers, allWorkerTimes) << endl;

        int worst = getWorst(chromosomes, countChrs, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes);
        chrs.processData(jobs, workers, orders, chromosomes[worst], workerSpeeds, jobCycles, allWorkerTimes);

        replaceWorst(chromosomes, countChrs, offspring, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes);
        if (bestFitness(chromosomes, countChrs, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes) == lastFitness){
            tripped++;
        }
    }

    for(int i = 0; i < countChrs; i++){
        chrs.processData(jobs, workers, orders, chromosomes[i], workerSpeeds, jobCycles, allWorkerTimes);
        cout << chrs.getFitness(workers, allWorkerTimes) << endl;
    }

    //cout << bestFitness(chromosomes, countChrs, jobs, workers, orders, workerSpeeds, jobCycles, allWorkerTimes);

    return 0;
}
int bestFitness( string *chromosomes, int countChrs,
                 int jobs, int workers, int orders,
                 int *workerSpeeds, int *jobCycles, int *allWorkerTimes) {
    int best;
    int lastBestFitness = 9999999;
    WorkersJobsChrs chrs;
    for(int i = 0; i < countChrs; i++){
        chrs.processData(jobs, workers, orders, chromosomes[i], workerSpeeds, jobCycles, allWorkerTimes);
        //cout << chrs.getFitness(workers, allWorkerTimes) << endl;
        if (lastBestFitness > chrs.getFitness(workers, allWorkerTimes)){
            best = i;
            lastBestFitness = chrs.getFitness(workers, allWorkerTimes);
        }
    }

    return lastBestFitness;
}

void replaceWorst(  string *chromosomes, int countChrs, string newChrs,
                    int jobs, int workers, int orders,
                    int *workerSpeeds, int *jobCycles, int *allWorkerTimes){
    int worst = getWorst(chromosomes, countChrs, jobs, workers, orders,
                         workerSpeeds, jobCycles, allWorkerTimes);

    WorkersJobsChrs chrs;
    chrs.processData(jobs, workers, orders, chromosomes[worst], workerSpeeds, jobCycles, allWorkerTimes);
    int worstFitness = chrs.getFitness(workers, allWorkerTimes);

    chrs.processData(jobs, workers, orders, newChrs, workerSpeeds, jobCycles, allWorkerTimes);
    if(chrs.getFitness(workers, allWorkerTimes) < worstFitness){
        chromosomes[worst] = newChrs;
    }
}

int getWorst(string *chromosomes, int countChrs,
             int jobs, int workers, int orders,
             int *workerSpeeds, int *jobCycles, int *allWorkerTimes){
    int worst;
    int lastWorstFitness = 0;
    WorkersJobsChrs chrs;
    for(int i = 0; i < countChrs; i++){
        chrs.processData(jobs, workers, orders, chromosomes[i], workerSpeeds, jobCycles, allWorkerTimes);
        //cout << chrs.getFitness(workers, allWorkerTimes) << endl;
        if (lastWorstFitness < chrs.getFitness(workers, allWorkerTimes)){
            worst = i;
            lastWorstFitness = chrs.getFitness(workers, allWorkerTimes);
        }
    }

    return worst;
}

void randomizeData(int workers, int speed, int *workerSpeeds, int jobs, int cycles, int *jobCycles, int orders, int *jobOrders, int  *assignments){
    int remainingWork;
    int index = 0;
    int currentWorker = rand()%workers;

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

    for(int i = 0; i < jobs; i++){
        for(int j = 0; j < workers; j++){
            *((assignments+i*workers) + j) = 0;
        }
    }

    while(index<jobs){

        int tooManyLoops = workers;
        remainingWork = jobOrders[index];

        while(*((assignments+index*workers) + currentWorker) >0 && tooManyLoops >=0){
            currentWorker = rand()%workers;
            tooManyLoops--;
        }

        if (true){
            *((assignments+index*workers) + currentWorker) = rand()%remainingWork;
            remainingWork -= *((assignments+index*workers) + currentWorker);
        }

        while(remainingWork > 0){
            currentWorker = rand()%workers;
            *((assignments+index*workers) + currentWorker) += 1;
            remainingWork--;
        }

        if(remainingWork == 0){
            index++;
        }
    }
}
