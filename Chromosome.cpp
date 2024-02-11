
#include "Chromosome.h"
#include <iostream>
using namespace std;

Chromosome::Chromosome(int numGenes,RandomGenerator* rand){//This works//////////////woahhhhh
       if(numGenes<0){
         this->numGenes=0;
        genes=new bool[0];
       }else if(numGenes>0){
       this->numGenes=numGenes;
        genes=new bool[numGenes];
          if(rand==NULL){
             for(int x=0;x<numGenes;x++){
               genes[x]=false;
           }
          }else{
           for(int x=0;x<numGenes;x++){
               genes[x]=rand->randomBool();
           }
          }
       }
}

Chromosome::Chromosome(Chromosome* chromosome){
        if(chromosome==NULL){
            this->numGenes=0;
            genes=new bool[0];
        }else{
        this->numGenes=chromosome->getNumGenes();
        genes=new bool[chromosome->getNumGenes()];//Different to Jival
        for(int x=0; x<chromosome->getNumGenes();x++){
            genes[x]=chromosome->genes[x];
        }
        }
}

Chromosome::Chromosome(bool* Genes, int numGenes){
         if(numGenes<0){
            this->numGenes=0;
            genes=new bool[0];
         }else{
         this->numGenes=numGenes;
        genes=new bool[numGenes];
        
        if(Genes==NULL){
           for(int x=0; x<numGenes; x++){
               genes[x]=false;
           }
           }else{
                for(int x=0; x<numGenes; x++){
               genes[x]=Genes[x];
           }
           }
         }
        
}

Chromosome::~Chromosome(){
        delete[] genes;
        genes=NULL;
}
double Chromosome::fitness(FitnessFunction* fitnessFunction, Chromosome* chromosome, int numGenes){
        double output;
        if(fitnessFunction==NULL || chromosome==NULL || numGenes<=0){
            return 0;
        }else{
            output=fitnessFunction->calculateFitness(chromosome,numGenes);
        }

        return output;
}

int Chromosome::getNumGenes(){
     return numGenes;
}

Chromosome* Chromosome::crossOver(Chromosome* c2){
        if(c2==NULL){
            Chromosome* copy=new Chromosome(this);
            return copy;
        }else{
        int crossOverPoint=floor(c2->numGenes/2);
        bool *nGenes=new bool[c2->numGenes];
       for(int z=0;z<crossOverPoint;z++){
         nGenes[z]=this->genes[z];
       }

       for(int x=crossOverPoint;x<numGenes;x++){
          nGenes[x]=c2->genes[x];
       }

       Chromosome* new_chrom=new Chromosome(nGenes, this->numGenes);
        delete[] nGenes;
            nGenes=NULL;
            return new_chrom;
        }
       
        
}

Chromosome* Chromosome::mutate(){//This works but see if deep copying is gonna be an issue
        bool* nGenes=new bool[this->numGenes];//This works but may cause issues if fitchfork runs -pedantic (POSSIBLE MEM LEAK)
        for(int j=0; j<numGenes;j++){
            nGenes[j]=!(genes[j]);
        }
        Chromosome* new_chrom=new Chromosome(nGenes, numGenes);
        delete nGenes;
        nGenes=NULL;
        return new_chrom;
}

std::string Chromosome::toString(){//This works
      std::string *Output=new std::string[this->numGenes];
      std::string OUT;
      if(numGenes==0){
        return "";
      }else{
        for(int y=0;y<numGenes;y++){
            if(genes[y]){
                Output[y]="1";
        }else if(!(genes[y])){
               Output[y]="0";
        }
        }
      }  

      for(int y=0;y<numGenes;y++){
          OUT.append(Output[y]);
      }
      delete[] Output;
      return OUT;
}

bool* Chromosome::getGenes(){
    return genes;
}