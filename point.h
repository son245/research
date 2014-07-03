
#ifndef POINT_H
#define POINT_H

/************************************Point*******************************
 *
 * Point class. define a point in 2d, with x and y coordinates.
 * Able to calculate the distance between another point.
 * 
 ************************************************************************/
class Point{
private: 
    double x;
    double y;
public:
    Point();
    Point(double newX, double newY);
    Point & operator= (const Point & rhs);
    double getX();
    double getY();
    void setX(double newX);
    void setY(double newY);
    double distance(Point p);
    void showCoordnate();
    Point(double x1, double x2,int type);
    Point (Point squareBL, double squareLength);
};

/****************************randomPoint******************************
 *
 *create a random point that is in an edge of the square
 *
 *********************************************************************/

#endif