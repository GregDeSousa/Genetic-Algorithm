#include "RandomGenerator.h"
#include <cstdlib>

RandomGenerator::RandomGenerator(int Seed){
    srand(Seed);
    seed=Seed;
}

bool RandomGenerator::randomBool(){
    bool bin;
    if(rand()%2==0){
        bin=false;
    }else {
        bin=true;
    }
    return bin;
}

