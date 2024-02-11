#include "FitnessFunction.h"

double FitnessFunction::calculateFitness(Chromosome* chromosome,int numGenes){
     double fitness;
     double m=0;
     double n=numGenes;
     bool *gen=chromosome->getGenes();

     for(int x=0;x<numGenes;x++){
        if(gen[x]){
            m++;
        }
     }

     fitness=(m/n);
     return fitness;
}