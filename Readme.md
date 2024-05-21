# Genetic Algorithm (GA) Implementation

This repository contains an implementation of a Genetic Algorithm (GA) in C++. The GA is used to evolve a population of chromosomes towards an optimal solution for a given fitness function.

## Files

- `GA.h` - Header file for the GA class.
- `GA.cpp` - Implementation of the GA class.
- `Chromosome.h` - Header file for the Chromosome class.
- `Chromosome.cpp` - Implementation of the Chromosome class.
- `FitnessFunction.h` - Header file for the FitnessFunction class.
- `FitnessFunction.cpp` - Implementation of the FitnessFunction class.
- `RandomGenerator.h` - Header file for the RandomGenerator class.
- `RandomGenerator.cpp` - Implementation of the RandomGenerator class.

## Class Descriptions

### GA Class

The `GA` class handles the genetic algorithm operations, including population initialization, selection, crossover, mutation, and evaluation of fitness.

#### Constructors

- `GA(int populationSize, RandomGenerator* rand, int numGenes, int selectionSize)`

  Initializes the GA with a specified population size, random generator, number of genes per chromosome, and selection size.

- `GA(GA* geneticAlgorithm)`

  Copy constructor that creates a deep copy of an existing GA.

#### Destructor

- `~GA()`

  Cleans up dynamically allocated memory for the population.

#### Methods

- `Chromosome** run(FitnessFunction* fitnessFunction)`

  Runs one generation of the GA, performing selection, crossover, and mutation.

- `double** run(FitnessFunction* fitnessFunction, int numGenerations)`

  Runs the GA for a specified number of generations and returns the results.

- `Chromosome** selection(FitnessFunction* fitnessFunction)`

  Selects the best chromosomes based on the fitness function.

- `Chromosome** inverseSelection(FitnessFunction* fitnessFunction)`

  Selects the worst chromosomes based on the fitness function.

- `Chromosome** crossOver(Chromosome* c1, Chromosome* c2)`

  Performs crossover between two chromosomes.

- `Chromosome* mutate(Chromosome* c1)`

  Mutates a chromosome.

- `double calculateAvgAccuracy(FitnessFunction* fitnessFunction)`

  Calculates the average fitness of the population.

- `double calculateStd(FitnessFunction* fitnessFunction)`

  Calculates the standard deviation of the fitness of the population.

- `double calculateVariance()`

  Calculates the variance in the population.

- `void setPopulation(Chromosome** p)`

  Sets the population to a new set of chromosomes.

## Usage

To use this GA implementation, you can use the makefile after cloning the repository and it will show the variance and standard deviation of a randomly generated gene pool.
