//Determining the location of n point in edges of a square so that the
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
#define MUTATION_RATE           0.005
//random float number between 0 and 1
#define RANDOM_NUM				((float)rand()/(RAND_MAX+1)+1)
#define POPULATION_CAP          100
using namespace std;

/**********************************Mutate*******************************
 *mutate a single child to further vary the population
 ***********************************************************************/
void mutate(Chromosome & offspring, Point squareBL, double squareLength)
{
    for(int i = 0; i < offspring.getSize(); i++)
    {
        if(RANDOM_NUM < MUTATION_RATE)
        {
            Point temp(squareBL,squareLength);
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
}


/*********************************Roulete Wheel Selection***********************
 *
 * return the index of the selected chromosome using roulete wheel selection method
 *
 *******************************************************************************/
int rouleteWheel(double totalFitness, vector<Chromosome> & population )
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
    unsigned int number;
    unsigned int square_length;
    double bottom_left_x;
    double bottom_left_y;
    cout << "Insert the number of points: " << endl;
    cin >> number;
    cout << "Insert the legnth of the square: "<< endl;
    cin >> square_length;
    cout << "Insert the x and y coordinates of the bottom left corner: " << endl;
    cin >> bottom_left_x;
    cin >> bottom_left_y;
    Point bottom_left_corner(bottom_left_x, bottom_left_y);
    //set the random seed generator to current time.

    srand((int)time(NULL));

    Chromosome save;
    double saveHighestFitness;

    /*************************initialize the new population ***********************/
    vector<Chromosome> population;
    int i = 0;

    //totalFitness will be use in roulete selection
    long double totalFitness = 0;
    while(population.size() < POPULATION_CAP)
    {
        Chromosome newChromosome(number, bottom_left_corner, square_length);
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
            mutate(offspring1,bottom_left_corner,square_length);
            mutate(offspring2,bottom_left_corner,square_length);
            offspring1.setFitness();
            offspring2.setFitness();
            temp_population.push_back(offspring1);
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

        //copy back to population
        i = 0;
        while(i < population.size())
        {
            population[i] = temp_population[i];
            i++;   
        }
        //remove all from temp
        temp_population.clear();
        cout << "Highest: " << saveHighestFitness << endl;
    }while(generation < 100000);// the number rof generation safely to reach the maximum
    //i am trying to determine this number using the linear problem

	return 0;

}