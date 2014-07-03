#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include "point.h"
#include <vector>
/*******************************Chromosome****************************
 *
 * Chromosome class. define a point in 2d, with x and y coordinates.
 * Able to calculate the distance between another point.
 * 
 *********************************************************************/
class Chromosome
{
private:
    std::vector<Point> c;
    double fitness; 
public:
    Chromosome();
    Chromosome(double x1, double x2, double x3, double x4, double x5);
    /*
     * insert a point into the Chromosome
     * @param: point x
     */
    void insertLocation(Point x);
    /*
     * Create a full chromosome using the input - for the square problem
     * @param: numberOfPoint the number of points wanted
     * @param: squareCorner the Point location of the bottom left corner of the 
     *         assigning square
     * @param: length the length of the square
     */
    Chromosome(unsigned int numberOfPoint, Point squareCorner, unsigned int length);
    /*
     * Create a full chromosome using the input - for the linear problem
     * @param: numberOfPoint the number of points wanted
     * @param: double x1 the lower boundary of the interval
     * @param: double x2 the upper boundary of the interval
     */
    Chromosome(unsigned int numberOfPoint, double x1, double x2);
    Chromosome & operator= (const Chromosome & rhs);    /*
     * Find the fitness of the current Chromosome
     */
    void setFitness();
    /*
     * Show all the point of the current Chromosome
     * Just for testing
     */
    void showAllPoint();
    /*
     * find the size of the Chromosome
     */
    int getSize();
    /*
     * return the fitness of the Chromosome
     */
    double getFitness();
    /*
     * return a point at the index
     */
    Point getPoint(int index);
    /*
     * set a point to an index
     */
    void setPoint(int index, Point p);
};
#endif
