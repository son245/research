#include "point.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <stdlib.h>
#define TOP_SIDE                1
#define RIGHT_SIDE              2
#define BOTTOM_SIDE             3
#define LEFT_SIDE               4
using namespace std;

/************************************Point*******************************
 *
 * Point class. define a point in 2d, with x and y coordinates.
 * Able to calculate the distance between another point.
 * 
 ************************************************************************/

Point::Point()
{
    x = 0;
    y = 0;
}
/*
 * create a random point for the linear problem
 */
Point::Point (double x1, double x2,int type)
{
    if(type == 1)
    {
        setX((x2-x1) * ( (double)rand() / (double)RAND_MAX ) 
            +  x1);//need checking
        setY(0);             
    }
}
/*
 * create a random point for the square problem
 */
Point::Point (Point squareBL, double squareLength)
{
    unsigned int edge = rand()%4 + 1;
    //choose a random edge for the point
    //if point is in one of the horizontal edges
    if(edge == TOP_SIDE || edge == BOTTOM_SIDE)
    {
        setX((squareLength-1) * ( (double)rand() / (double)RAND_MAX ) 
        +  squareBL.getX());//need checking
        if(edge == TOP_SIDE)
        {
            setY(squareBL.getY() + squareLength);
        }
        else
        {
            setY(squareBL.getY());
        }
    }
    else 
    {
        setY((squareLength-1) * ( (double)rand() / (double)RAND_MAX )
        +  squareBL.getY());
        if(edge == RIGHT_SIDE)
        {
            setX(squareBL.getX() + squareLength);
        }
        else
        {
            setX(squareBL.getX());
        }

    }
}
Point::Point(double newX, double newY)
{
    x = newX;
    y = newY;
}
Point & Point::operator= (const Point & rhs)
{
    if(this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
    return *this;
}
double Point::getX()
{
    return x;
}
double Point::getY()
{
    return y;
}
void Point::setX(double newX)
{
    x = newX;
}
void Point::setY(double newY)
{
    y = newY;
}
double Point::distance(Point p)
{
    double xd = x - p.getX();
    double yd = y - p.getY();
    return sqrt(xd * xd + yd * yd);
}
void Point::showCoordnate()
{
    std::cout << "x: " << x << ", y: " << y << std::endl;
}





