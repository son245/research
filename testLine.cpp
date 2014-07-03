//Determining the location of n point between an interval so that the
//product of all the gaps are the largest
//by Son Nguyen - Truman State University
//subpervised by Dr. Khang Tran-Truman State University


#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "chromosome.h"
#define CROSSOVER_RATE          0.6
#define MUTATION_RATE           0.025
//random float number between 0 and 1
#define RANDOM_NUM				((float)rand()/(RAND_MAX+1)+1)
#define POPULATION_CAP          100
#define PI                      3.14159265
using namespace std;
    

/**********************************Mutate*******************************
 *mutate a single child to further vary the population
 ***********************************************************************/
void mutate(Chromosome & offspring, double x1, double x2)
{
   for(int i = 0; i < offspring.getSize(); i++)
    {
        if(RANDOM_NUM < MUTATION_RATE)
        {
            Point temp(x1, x2,1);
            offspring.setPoint(i,temp);
        }
    }
}

/**********************************Cross Over****************************
 *the cross over between two child to further vary the population4
 ***********************************************************************/
void crossOver(Chromosome & offspring1, Chromosome & offspring2)
{
    if(RANDOM_NUM < CROSSOVER_RATE)
    {
        unsigned int random = rand()%2;
        if(random == 0)//1 point crossover
        {
            //create a random cross over point
            int crossover = (int) (RANDOM_NUM * (offspring1.getSize()-1));
            while(crossover < offspring1.getSize())
            {
                Point temp = offspring1.getPoint(crossover);
                offspring1.setPoint(crossover, offspring2.getPoint(crossover));
                offspring2.setPoint(crossover,temp);
                crossover++;
            }            
        }   
        else//2 points crossover
        {
            int crossover1 = (int) (RANDOM_NUM * (offspring1.getSize()-1));
            int crossover2;
            do
            {
                crossover2 = (int) (RANDOM_NUM * (offspring1.getSize()-1));
            }while(crossover1 == crossover2);
            if(crossover1 < crossover2)
            {
                while(crossover1 <= crossover2)
                {
                    Point temp = offspring1.getPoint(crossover1);
                    offspring1.setPoint(crossover1, offspring2.getPoint(crossover1));
                    offspring2.setPoint(crossover1,temp);
                    crossover1++;
                } 
            }
            else
            {
                while(crossover2 <= crossover1)
                {
                    Point temp = offspring1.getPoint(crossover2);
                    offspring1.setPoint(crossover2, offspring2.getPoint(crossover2));
                    offspring2.setPoint(crossover2,temp);
                    crossover2++;
                }
            }
        }
    }
}


/*********************************Roulete Wheel Selection***********************
 *
 * return the index of the selected chromosome using roulete wheel selection method
 *
 *******************************************************************************/
int rouleteWheel(double totalFitness, std::vector<Chromosome> & population )
{
    //generate a random number between 0 & total fitness count
    double slice = (double)(RANDOM_NUM * totalFitness);
    double fitnessSoFar = 0;
    for(unsigned int i = 0; i < population.size(); i++)
    {
        fitnessSoFar += population[i].getFitness();
        if(fitnessSoFar >= slice)
        {
            return i;
        }
    }
    return 0;
}

    

int main()
{
    double x1;
    double x2;
    unsigned int number;
    cout << "Insert x1: " << endl;
    cin >> x1;
    cout << "Insert x2: " << endl;
    cin >> x2;
    cout << "Insert number of points: " << endl;
    cin >> number;
    //set the random seed generator to current time.
    srand((int)time(NULL));
/*    Chromosome compare(0.990804,-0.995473,-0.0972469,
        0.660516, -0.667616) ; testing
*/    
Chromosome compare(1,0.65465367,0,-0.65465367,-1) ;//checking with the given answer(updated)
    cout << "Answer is: " << compare.getFitness() << endl;

    Chromosome save;
    double saveHighestFitness;


    /*************************initialize the new population ***********************/
    vector<Chromosome> population;
    int i = 0;

    //totalFitness will be use in roulete selection
    long double totalFitness = 0;
    while(population.size() < POPULATION_CAP)
    {
        Chromosome newChromosome(number, x1, x2);
        population.push_back(newChromosome);
        totalFitness += population[i].getFitness();
        i++;
    }

    //the beginning generation is 0
    unsigned int generation = 0;
    double highestFitness;
    double check;
    double highestFitnessIndex;
    /****************************starting the evolution************************/
    do
    {
        generation++;
        //temporary storage for the new population
        vector<Chromosome> temp_population;
        //repeat until the new population has the same chromosome as the old one
        while(temp_population.size() < population.size())
        {
            Chromosome offspring1 = population[rouleteWheel(totalFitness,population)];
            Chromosome offspring2 = population[rouleteWheel(totalFitness,population)];
            crossOver(offspring1,offspring2);
            mutate(offspring1,x1,x2);
            mutate(offspring2,x1,x2);
            offspring1.setFitness();
            offspring2.setFitness();
/*  testing cout << "offspring 1: " << endl;
            offspring1.showAllPoint();
            cout << "offspring 2: " << endl;
            offspring2.showAllPoint();
*/          temp_population.push_back(offspring1);
            temp_population.push_back(offspring2);
            //using clear method
        }
        //report new generation fitness 
        cout << "GENERATION: " << generation << endl;
        //find highest fitness
        highestFitness = 0;
        unsigned int i = 0;
        while(i < temp_population.size())
        {
            if(highestFitness < temp_population[i].getFitness())
            {
                highestFitness = temp_population[i].getFitness();
                highestFitnessIndex = i;
            }
            i++;
        }   
        //check if this fitness is the highest of all time, if it is then make a deep
        //copy of it to the memoir. 
        if(highestFitness > saveHighestFitness)
        {
            saveHighestFitness = highestFitness;
            save = temp_population[highestFitnessIndex];
        }
        cout << " and the generation highest fitness is: " << highestFitness << endl;
        temp_population[highestFitnessIndex].showAllPoint();//false statement
        //copy back to population
        i = 0;
        while(i < population.size())
        {
            population[i] = temp_population[i];
            i++;   
        }
        //remove all from temp
        temp_population.clear();
        cout << "compare: " << compare.getFitness() << " high: " << highestFitness << endl;   
        check = compare.getFitness() - highestFitness;
        cout << "Highest: " << saveHighestFitness << endl;    
    }while( check > 0.01);//key point in evolution, can change it to
    //while(generation < A_CONSTANT) when we have an efficent algorithm and
    //a good enough number of generation it take to the best solution


 /* testing  int count = 0;
    while(count < 50)
    {
        //0.5 -> 5
        cout << (6-1) * ( (double)rand() / (double)RAND_MAX ) << endl;
        count++;
    }*/
/*	Point a(1,2);
	Point b(3,2);
	cout << "the distance between a and b is: "<< b.distance(a)<< endl;
    a = b;a
    cout << " now the distance should be 0; " << b.distance(a) << endl;
 
    Chromosome ab;
    cout << " current size : " << ab.getSize() << endl;
    ab.insertLocation(a);
    cout << " current size : " << ab.getSize() << endl;
    ab.insertLocation(b);
    cout << " current size : " << ab.getSize() << endl; */   
	return 0;

}