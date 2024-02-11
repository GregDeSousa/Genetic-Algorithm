main: main.o Chromosome.h Chromosome.o FitnessFunction.h FitnessFunction.o GA.h GA.o RandomGenerator.h RandomGenerator.o
	g++ -std=c++98 -pedantic main.o Chromosome.o FitnessFunction.o GA.o RandomGenerator.o -o main

main.o: main.cpp
	g++ -std=c++98 -pedantic -c -g main.cpp 

Chromosome.o: Chromosome.h Chromosome.cpp
	g++ -std=c++98 -pedantic -c -g Chromosome.cpp

FitnessFunction.o: FitnessFunction.h FitnessFunction.cpp
	g++ -std=c++98 -pedantic -c -g FitnessFunction.cpp

GA.o: GA.h GA.cpp
	g++ -std=c++98 -pedantic -c -g GA.cpp

RandomGenerator.o: RandomGenerator.h RandomGenerator.cpp
	g++  -std=c++98 -pedantic -c -g RandomGenerator.cpp

run:
	./main

clean:
	rm *.o main