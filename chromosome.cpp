#include <iostream>
#include "point.h"
#include "chromosome.h"
#include <random>
#include <vector>

/*******************************Chromosome****************************
 *
 * Chromosome class. define a group of points in 2d, with x and y coordinates.
 * a full solution to the problem
 * 
 *********************************************************************/

Chromosome::Chromosome()
{
    fitness = 0;
}
Chromosome::Chromosome(double x1, double x2, double x3, double x4, double x5)
{
    c.push_back(Point(x1, 0));
    c.push_back(Point(x2, 0));
    c.push_back(Point(x3, 0));
    c.push_back(Point(x4, 0));
    c.push_back(Point(x5, 0));
    setFitness();
}

/*
 * insert a point into the Chromosome
 * @param: point x
 */
void Chromosome::insertLocation(Point x)
{
    c.push_back(x);
}
/*
 * Create a full chromosome using the input
 * @param: numberOfPoint the number of points wanted
 * @param: squareCorner the Point location of the bottom left corner of the 
 *         assigning square
 * @param: length the length of the square
 */
Chromosome::Chromosome(unsigned int numberOfPoint, double x1, double x2)
{
    unsigned int count = 0;
    while(count < numberOfPoint)
    {
        Point newPoint(x1,x2,1);
        insertLocation(newPoint);
        count++;
    }
    setFitness();
}
Chromosome::Chromosome(unsigned int numberOfPoint, Point squareCorner, unsigned int length)
{
    unsigned int count = 0;
    while(count < numberOfPoint)
    {
        Point newPoint(squareCorner,length);
        insertLocation(newPoint);
        count++;
    }
    setFitness();
}
Chromosome & Chromosome::operator= (const Chromosome & rhs)
{
    if(this != &rhs)
    {
        unsigned int i = 0;
        c.clear();
        while(i < rhs.c.size())
        {
            c.push_back(rhs.c.at(i));
            i++;
        }
    }
    return *this;
}
/*
 * Find the fitness of the current Chromosome
 */
void Chromosome::setFitness()
{
    unsigned int firstPoint = 0;
    unsigned int secondPoint = 1;
    double product = 1.0;
    double temp;
    while(firstPoint < c.size() - 1)
    {
        while(secondPoint < c.size())
        {
            temp = c[firstPoint].distance(c[secondPoint]);
            product *= temp;
            secondPoint++;
        }
        firstPoint++;
        secondPoint = firstPoint + 1;
    }
    fitness = product;
}
/*
 * Show all the point of the current Chromosome
 * Just for testing
 */
void Chromosome::showAllPoint()
{
    unsigned int i = 0;
    while(i < c.size())
    {
        std::cout << "x: " << c[i].getX() <<", y: " << c[i].getY()<< std::endl;
        i++;
    }
}
/*
 * find the size of the Chromosome
 */
int Chromosome::getSize()
{
    return c.size();
}
/*
 * return the fitness of the Chromosome
 */
double Chromosome::getFitness()
{
    return fitness;
}
/*
 * return a point at the index
 */
Point Chromosome::getPoint(int index)
{
    return c[index];
}
/*
 * set a point to an index
 */
void Chromosome::setPoint(int index, Point p)
{
    c[index] = p;
}