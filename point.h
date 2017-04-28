// Programmer: Christian Parsons
// Section: E
// Filename: point.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains class defintion for Point.

#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Town;

const short UP = 0; //arbritary values corresponding to direction
const short DOWN = 1;
const short RIGHT = 2;
const short LEFT = 3;
const short NUM_DIRECTIONS = 4; //number of possible directions
const short DEFAULT = -1; //default coordinate

class Point
{
private:
  short m_x_coord; //x and y coordinates
  short m_y_coord;

public:
  // Description: Constructor for Point class.
  // Pre: None
  // Post: Sets x and y coordinate members to the passed values or (0, 0) by
  //       default.
  Point(const short x_coord = DEFAULT, const short y_coord = DEFAULT);

  // Description: Gets the Point's x_coord member.
  // pre: None
  // post: The Point's x_coord member is returned.
  short get_x_coord() const {return m_x_coord;}

  // Description: Gets the Point's y_coord member.
  // pre: None
  // post: The Point's y_coord member is returned.
  short get_y_coord() const {return m_y_coord;}

  // Description: Gets the coordinates of a point adjacent to current point.
  // pre: None
  // post: Returns a point that is one space above, below, right, or left of
  //       current point, depending on passed argument.
  Point get_adjacent(const short & direction) const;

  // Description: Overloaded assignment operator for Point class.
  // pre: None
  // post: Passed point's x_coord and y_coord have been assigned to the Point's
  //       x_coord and y_coord. The Point has been returned.
  Point & operator =(const Point & point);

  // Description: Overloaded equality operator for Point class.
  // pre: None
  // post: Returns true if point1's x and y coordinates equal point2's x and y
  //       coordinates.
  friend bool operator ==(const Point & point1, const Point & point2);

  // Description: Overloaded not-equal operator for Point class.
  // pre: None
  // post: Returns true if point1's x and y coordinates are not equal to
  //       point2's x and y coordinates.
  friend bool operator !=(const Point & point1, const Point & point2);

  // Description: Overloaded insertion operator for Point class.
  // pre: None
  // post: The cooridnates of the point in the format (x, y) have been printed
  //       on the screen.
  friend ostream & operator <<(ostream & out, const Point & point);
};

#endif
