#include <iostream>
using namespace std;
#include "GA.h"

	GA::GA(int populationSize, RandomGenerator* rand, int numGenes, int selectionSize){
             this->populationSize=populationSize;
             this->selectionSize=selectionSize;
             population = new Chromosome*[populationSize];

             for(int x=0; x<populationSize;x++){
                population[x]=new Chromosome(numGenes,rand);//is there is no variance this might be the culprit or mabye even the Random function itself
                //cout<<x+1<<":"<<population[x]->toString()<<endl;
             }
    }
    
    GA::GA(GA* geneticAlgorithm){
          populationSize=geneticAlgorithm->populationSize;
          selectionSize=geneticAlgorithm->selectionSize;
          population=new Chromosome* [populationSize];

          for(int x=0; x<populationSize;x++){
            population[x]=new Chromosome(geneticAlgorithm->population[x]);//Check if this copy contructor does actually do a deep copy
          }
    }
	GA::~GA(){
          for(int z=0;z<populationSize;z++){
               delete population[z];
          }
          delete[] population;
          population=NULL;
    }
	Chromosome** GA::run(FitnessFunction* fitnessFunction){
         Chromosome** winners=selection(fitnessFunction);
         Chromosome** losers=inverseSelection(fitnessFunction);
        /*for(int x=0;x<populationSize;x++){
        cout<<x<<": winners: "<<fitnessFunction->calculateFitness(winners[x],winners[x]->getNumGenes())<<"------"<<winners[x]->toString()<<endl;
        }
        cout<<endl;
       
       for(int x=0;x<populationSize;x++){
        cout<<x<<": losers: "<<fitnessFunction->calculateFitness(losers[x],losers[x]->getNumGenes())<<"------"<<winners[x]->toString()<<endl;
        }
        cout<<endl;*/
        
        Chromosome** offsprings=new Chromosome*[3*selectionSize];//
        Chromosome** P=new Chromosome*[this->populationSize];

        for(int i=0;i<(2*selectionSize);i++){
          Chromosome** nChromosomes=crossOver(winners[i],winners[i+1]);
          offsprings[i]=nChromosomes[0];
          offsprings[i+1]=nChromosomes[1];
          i++;
        }

        for(int y=0;y<selectionSize;y++){
          //cout<<"winnner: "<<winners[y+2*selectionSize]->toString()<<endl;
          offsprings[y+2*selectionSize]=mutate(winners[y+2*selectionSize]);
        }
      
        for(int j=0;j<populationSize;j++){
          P[j]=population[j];
        }
        
        Chromosome* dyingChromosomes;
        int u=0;
        for(int s=0;s<(3*selectionSize);s++){
           dyingChromosomes=losers[s];
           for(int p=0;p<populationSize;p++){
              if(P[p]==dyingChromosomes){               
               u=p;
              }
           }
           P[u]=offsprings[s];
        }
          /*for(int j=0;j<populationSize;j++){
               cout<<j<<" : "<<P[j]->toString()<<endl;
        
        }
       cout<<endl;*/        
       /*for(int j=0;j<populationSize;j++){///////USE 2d allocation and it
          delete winners[j];
          delete losers[j];
         }*/

         /*for(int y=0;y<3*selectionSize;y++){
          delete offsprings[y];
         }*/

        delete [] winners;
        winners=NULL;
        delete [] losers;
        losers=NULL;
        delete [] offsprings;
        offsprings=NULL;
         return P;
    }
	double** GA::run(FitnessFunction* fitnessFunction, int numGenerations){
       double** results = new double*[numGenerations];
        Chromosome** P;
       for(int r=0;r<numGenerations;r++){
           results[r]=new double[3];
       }

       for(int i=0;i<numGenerations;i++){
           P=run(fitnessFunction);
           population=P;
           /*for(int x=0; x<populationSize;x++){
           cout<<x<<" : "<<P[x]->toString()<<endl;
           }
           cout<<endl;*/
           results[i][0]=calculateAvgAccuracy(fitnessFunction);
           results[i][1]=calculateStd(fitnessFunction);
           results[i][2]=calculateVariance();
          
       }
       return results;
    }
	Chromosome** GA::selection(FitnessFunction* fitnessFunction){
      Chromosome** pop_copy=new Chromosome*[populationSize];
      for(int x=0;x<populationSize;x++){
        pop_copy[x]=population[x];
      }
      Chromosome* temp;
       for(int j=0;j<populationSize;j++){
        for(int y=0;y<populationSize-1;y++){
             int numG=pop_copy[y]->getNumGenes();
             int numG2=pop_copy[y+1]->getNumGenes();
            if((fitnessFunction->calculateFitness(pop_copy[y],numG))<(fitnessFunction->calculateFitness(pop_copy[y+1],numG2))){
                  temp=pop_copy[y+1];
                  pop_copy[y+1]=pop_copy[y];
                  pop_copy[y]=temp;

        }
      }
       }
      return pop_copy;
    }
	Chromosome** GA::inverseSelection(FitnessFunction* fitnessFunction){
      Chromosome** pop_copy=selection(fitnessFunction);
      Chromosome* temp;
     for(int u=0;u<(populationSize/2);u++){
        temp = pop_copy[u];
        pop_copy[u]=pop_copy[populationSize-1-u];
        pop_copy[populationSize-1-u]=temp;
      }
      
      return pop_copy;
    }
	Chromosome** GA::crossOver(Chromosome* c1, Chromosome* c2){
        Chromosome* copy_c1=new Chromosome(c1);
        Chromosome* copy_c2=new Chromosome(c2);
        Chromosome** cross=new Chromosome*[2];
        
        cross[0]=copy_c1->crossOver(c2);
        cross[1]=copy_c2->crossOver(c1);//////////////////////leak here
        return cross;
    }
	Chromosome* GA::mutate(Chromosome* c1){
        Chromosome* copy_c1=c1->mutate();
        return copy_c1;
    }
	double GA::calculateAvgAccuracy(FitnessFunction* fitnessFunction){
       double Avg=0;
       double TF=0;
       for(int y=0;y<populationSize;y++){
        int numG=population[y]->getNumGenes();
         TF=TF+fitnessFunction->calculateFitness(population[y],numG);
       }

       Avg=TF/populationSize;
       return Avg;
    }
	double GA::calculateStd(FitnessFunction* fitnessFunction){
       double STD;
       double Sum=0;
       double Avg=this->calculateAvgAccuracy(fitnessFunction);
       int numG;
       for(int x=0;x<populationSize;x++){
          numG=population[x]->getNumGenes();
          //cout<<((fitnessFunction->calculateFitness(this->population[x],numG)))<<"::"<<Avg<<endl;
          Sum+=pow(((fitnessFunction->calculateFitness(this->population[x],numG))-Avg),2);
       }
       STD=sqrt(Sum/populationSize);
       return STD;
    }
	double GA::calculateVariance(){
         double V=0;
         bool unique;
         double N_unique=1;
         int x,j;
         for(x=1;x<populationSize;x++){
            //unique=true;
            for(j=0;j<x;j++){
                if((population[x]->toString()==population[j]->toString())){
                         break;
                   }
             }
              if(x==j){
               N_unique++;
                   }
             }
           V=(N_unique/populationSize);
           return V;
  }
    
	void GA::setPopulation(Chromosome** p){
      Chromosome** copy=new Chromosome* [populationSize];
    
      for(int k=0;k<populationSize;k++){
        copy[k]=new Chromosome(p[k]);
      }
      for(int x=0;x<populationSize;x++){
        this->population[x]=copy[x];//////////////////////////////////leak here
      }


      delete[] copy;
      copy=NULL;

    }