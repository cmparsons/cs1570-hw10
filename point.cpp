// Programmer: Christian Parsons
// Section: E
// Filename: point.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains functions for the Point class.

#include "general.h"
#include "point.h"
#include "town.h"

Point::Point(const short x_coord, const short y_coord)
{
  m_x_coord = x_coord;
  m_y_coord = y_coord;
}

Point & Point::operator =(const Point & point)
{
  m_x_coord = point.m_x_coord;
  m_y_coord = point.m_y_coord;
  return (*this);
}

Point Point::get_adjacent(const short direction) const
{
  //will hold coordinates of new point
  Point adjacent(m_x_coord, m_y_coord); //initialized to current point

  //update appropriate coordinate
  switch (direction)
  {
    case UP:
      adjacent.m_y_coord++;
      break;
    case DOWN:
      adjacent.m_y_coord--;
      break;
    case LEFT:
      adjacent.m_x_coord--;
      break;
    case RIGHT:
      adjacent.m_x_coord++;
      break;
  }
  return adjacent;
}