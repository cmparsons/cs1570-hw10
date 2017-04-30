// Programmer: Christian Parsons
// Section: E
// Filename: town.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains functions for the Town class.

#include "town.h"
#include "general.h"
#include "tailor.h"
#include "point.h"
#include "bully.h"

void operator <<(ostream & out, const Town & town)
{
  int color;

  //i = row, j = column
  for(int i = 0; i < town.town_size; i++)
  {
    move(i , 0); //move cursor to beginning of every row
    for(int j = 0; j < town.town_size; j++) //print out row i
    {
      //get the color based on object in space
      color = color_town(town.town_grid[i][j].symbol);

      //print space with appropriate color
      attron(COLOR_PAIR(color));
      addch(town.town_grid[i][j].symbol);
      attroff(COLOR_PAIR(color));

      //print whitespace between each spot in town
      attron(COLOR_PAIR(6));
      addch(' ');
      attroff(COLOR_PAIR(6));
    }
  }
  refresh();
  return;
}

Town::Town(const short bullies, const short houses, const short size)
{
  initscr(); //initialize the screen
  curs_set(0); //don't show the cursor
  start_color(); //allow for colored output
  use_default_colors(); //keep background default terminal color

  //initialize color pairs
  //(color pair value, foreground, background)
  init_pair(HOUSE_COLOR, COLOR_YELLOW, COLOR_WHITE);
  init_pair(BULLY_COLOR, COLOR_RED, COLOR_WHITE);
  init_pair(WALL_COLOR, COLOR_BLUE, COLOR_WHITE);
  init_pair(PHANTOM_PANTS_COLOR, COLOR_GREEN, COLOR_WHITE);
  init_pair(DEFAULT_COLOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(SPACE_FORMAT, COLOR_WHITE, COLOR_WHITE);

  //valid passed size argument
  if(size >= MIN_SIZE && size <= MAX_SIZE)
    town_size = size;
  else
    town_size = MAX_SIZE;

  num_bullies = bullies;
  num_houses = houses;
  clear();
  build();
}

void Town::clear()
{
  for(int i = 0; i < town_size; i++) //i = row
    for(int j = 0; j < town_size; j++) //j = column
    {
      town_grid[i][j].symbol = EMPTY; //initialize each member to whitespace
      town_grid[i][j].pants_to_exchange = false; //member has pants to exchange
    }
  return;
}

void Town::build()
{
  bool placed = false; //determine if object was placed in town
  Point loc; //point in town where something will be placed

  //build the wall
  for(int i = 0; i < town_size; i++) //build wall in first row and column
  {
    town_grid[0][i].symbol = WALL; //first row
    town_grid[i][0].symbol = WALL; //first column
  }
  for(int j = 0; j < town_size; j++) //build wall in last row and column
  {
    town_grid[town_size - 1][j].symbol = WALL; //last row
    town_grid[j][town_size - 1].symbol = WALL; //last column
  }

  //find a starting point to build the first
  loc = get_empty_point();

  //places the houses in clumps
  for(int i = 0; i < num_houses; i++) //loop until all houses placed
  {
    //set house in grid and up its status of having pants to exchange
    set_in_grid(loc, HOUSE);
    town_grid[loc.get_y_coord()][loc.get_x_coord()].pants_to_exchange = true;

    placed = false;

    //find an adjacent spot to place next house or find a new starting point
    while(!placed)
    {
      //get the coordinates of a random space adjacent to the current space
      loc = loc.get_adjacent(random(NUM_DIRECTIONS, 0));

      //if space is unoccupied, will place house in space
      if(!space_occupied(loc))
        placed = true;
      //if no available spaces to place house, generate new starting point
      else if(surrounded(loc))
      {
        loc = get_empty_point();
        placed = true;
      }
    }
  }

  //place bullies in random places in town independent of each other
  for(int i = 0; i < num_bullies; i++)
  {
    loc = get_empty_point();
    set_in_grid(loc, BULLY);
  }
  return;
}

Point Town::get_empty_point() const
{
  bool found = false; //determine if an empty has been found
  short x_coord = 0;
  short y_coord = 0;

  while(!found)
  {
    x_coord = random(town_size - 1, 0);
    y_coord = random(town_size - 1, 0);

    //check if space is empty
    if(!space_occupied(Point(x_coord, y_coord)))
      found = true; //found an empty space
  }
  return Point(x_coord, y_coord);
}

bool Town::space_occupied(const Point & check_space) const
{
  //if space is empty, return false
  return (town_grid[check_space.get_y_coord()]
          [check_space.get_x_coord()].symbol != EMPTY);
}

void Town::set_in_grid(const Point & point, const char sym)
{
  town_grid[point.get_y_coord()][point.get_x_coord()].symbol = sym;
  return;
}

void Town::clear_grid_content(const Point & point)
{
  town_grid[point.get_y_coord()][point.get_x_coord()].symbol = EMPTY;
  return;
}

bool Town::surrounded(const Point & point) const
{
  Point adjacent;
  short direction = 0;
  bool occupied = true;

  while(occupied && direction < NUM_DIRECTIONS)
  {
    //get a point adjacent to the passed point
    adjacent = point.get_adjacent(direction);

    //check if space is occupied in that point
    occupied = space_occupied(adjacent);
    direction++;
  }
  return occupied;
}

void Town::bought_pants(const Point & house)
{
  town_grid[house.get_y_coord()][house.get_x_coord()].pants_to_exchange
  = false;
  return;
}
