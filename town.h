// Programmer: Christian Parsons
// Section: E
// Filename: town.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains the Town class defintion.

#ifndef TOWN_H
#define TOWN_H

#include "general.h"
#include "point.h"

const short NUM_HOUSES = 40; //number of houses to place in town
const short NUM_BULLIES = 10; //number of bullies to place in town

const short MAX_SIZE = 25; //max dimension size for town
const short MIN_SIZE = 4; //minimum dimension size for town

const char EMPTY = ' '; //representation of a blank space in town grid
const char WALL = 'W'; //representation of a wall in the town grid
const char HOUSE = 'H'; //representation of a house

struct Loc
{
  char symbol;
  bool pants_to_exchange;
};

class Town
{
private:
  Loc town_grid[MAX_SIZE][MAX_SIZE];
  short town_size;
  short num_bullies;
  short num_houses;

  // Description: Clear the contents of the passed town grid.
  // pre: town_size <= MAX
  // post: Every member's symbol of town_grid is initialized to whitespace.
  //       Every member's pants_to_exchange member is initialized to false.
  void clear();

  // Description: Builds wall on the outer rows and columns of the town grid,
  //              builds houses in the town, and places bullies in the town.
  // pre: town_size <= MAX
  //      all members of town_grid should be initialized to whitespace
  // post: A WALL char is placed in every member of the first and last row and
  //       first and last column up to (not including) size of the passed
  //       town grid.
  void build();

public:
  // Description: Print the current town grid.
  // pre: town_size <= MAX
  // post: Prints the town grid and the contents in each member.
  friend ostream & operator <<(ostream & out, const Town & foo);

  // Description: Constructor for the Town class. Sets the size of the town,
  //              clears, and builds the town.
  // pre: number of bullies and houses should not exceed number of spaces in
  //      town_grid(minus outer rows and columns)
  //      4 < size <= MAX
  // post: The town_size is set to the passed size argument, or MAX by default.
  //       The outside rows and columns are set to 'W' for a wall, houses 'H'
  //       are placed in the town in clumps, and bullies 'B' are placed randomly
  //       within the town.
  Town(const short bullies, const short houses, const short size = MAX_SIZE);

  // Description: Get the size of the town.
  // pre: None
  // post: The Town's town_size member has been returned.
  short get_town_size() const {return town_size;}

  // Description: Check if point is surrounded on all sides in town.
  // pre: 1 <= m_x_coord <= town_size - 2
  //      1 <= m_y_coord <= town_size - 2
  // post: Returns true if all points adjacent(left, right, above, below) to
  //       Point are occupied. Otherwise, returns false.
  bool surrounded(const Point & point) const;

  // Description: Get the contents of the town in location (x, y).
  // pre: x < town_size and y < town_size
  // post: The char in the index of town_grid[x][y] is returned.
  char get_grid_content(const Point & p) const
  {return town_grid[p.get_y_coord()][p.get_x_coord()].symbol;}

  // Description: Checks if a space in town is occupied.
  // pre: None
  // post: Returns false if space is occupied by EMPTY character. Othwerwise,
  //       returns true.
  bool space_occupied(const Point & check_space) const;

  // Description: Place the passed symbol in the town grid.
  // pre: x_coord < town_size and y_coord < town_size
  // post: The passed symbol is placed in the town_grid at the passed x and y
  //       coordinate.
  void set_in_grid(const Point & point, const char sym);

  // Description: Clears the contents of the town_grid at the passed coordinates
  // pre: clear_x < town_size and clear_y < town_size
  // post: The contents of the town_grid at the passed coordinates is set to
  //       whitespace.
  void clear_grid_content(const Point & point);

  // Description: Finds an empty place in the town.
  // pre: None
  // post: A point that is empty is returned.
  Point get_empty_point() const;

  // Description: Set space in Town's pants_to_exchange to false.
  // pre: None
  // post: The pants_to_exchange member is set to false for the space in
  //       town passed.
  void bought_pants(const Point & house);

  // Description: Get space in Town's pants_to_exchange member.
  // pre: None
  // post: The space in the Town's pants_to_exchange member has been returned.
  bool get_pants_to_exchange(const Point & p) const
  {return town_grid[p.get_y_coord()][p.get_x_coord()].pants_to_exchange;}
};

#endif
