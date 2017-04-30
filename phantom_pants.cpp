// Programmer: Christian Parsons
// Section: E
// Filename: phantom_pants.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains functions for the Phantom_Pants class.

#include "phantom_pants.h"
#include "town.h"
#include "point.h"
#include "tailor.h"
#include "general.h"

ostream & operator <<(ostream & out, const Phantom_Pants & pants)
{
  printw("Phantom pants at ");
  out << pants.m_loc;
  return out;
}

void Phantom_Pants::place_me(Town & town)
{
  Point new_location; //set to default of (-1, -1)

  //get an empty space in the town to place the pants
  new_location = town.get_empty_point();

  //update pants' cooridnates and set in the town
  m_loc = new_location;
  town.set_in_grid(m_loc, m_symbol);
  return;
}

bool Phantom_Pants::chase(Tailor & victim, Town & town)
{
  //get Tailor's location in grid
  Point target = victim.get_location();
  short target_x = target.get_x_coord();
  short target_y = target.get_y_coord();

  short direction = 0; //direction pants will travel
  bool occupied = true; //check for an available space
  bool killed = false; //determine if tailor was killed
  Point new_location;
  bool surrounded = false;

  //check if pants are next to tailor before moving(prevent overlap)
  if(next_to_tailor(victim))
  {
    kill(victim);
    killed = true;
    return killed;
  }

  //if pants is not next to the tailor, chase the tailor
  if(m_loc.get_y_coord() != target_y) //try to get to tailor's y-coordinate
  {
    //find where tailor is respect to the pants
    direction = target_y - m_loc.get_y_coord();

    if(direction > 0) //tailor must be above phantom pants
      new_location = m_loc.get_adjacent(UP);

    else //tailor must be below phantom pants
      new_location = m_loc.get_adjacent(DOWN);
  }
  else //try to get to tailor's x-coordinate
  {
    //find where tailor is respect to the pants
    direction = target_x - m_loc.get_x_coord();

    if(direction > 0) //tailor must be to the right of phantom pants
      new_location = m_loc.get_adjacent(RIGHT);

    else //tailor must be to the left of phantom pants
      new_location = m_loc.get_adjacent(LEFT);
  }
  //check if desired space is filled
  occupied = town.space_occupied(new_location);

  while(occupied && !surrounded)
  {
    //get an adjacent spot
    new_location = m_loc.get_adjacent(random(NUM_DIRECTIONS - 1, 0));

    //find out if the spot is occupied
    occupied = town.space_occupied(new_location);

    //check if pants are trapped
    surrounded = town.surrounded(m_loc);
  }

  //if not surrounded, update coordinates and town
  if(!surrounded)
  {
    //clear contents of pants' previous location
    town.clear_grid_content(m_loc);

    //update pants coordinates
    m_loc = new_location;

    //set pants' new coordinates and update town
    town.set_in_grid(m_loc, m_symbol);
  }

  //check if tailor is next to pants after moving
  if(next_to_tailor(victim))
  {
    kill(victim);
    killed = true;
  }
  return killed;
}

bool Phantom_Pants::next_to_tailor(const Tailor & victim) const
{
  bool found_tailor = false;
  short direction = 0; //count number of directions checked
  Point adjacent;

  //loop until all adjacent spaces have been checked or found tailor in adjacent
  //space
  while(direction < NUM_DIRECTIONS && !found_tailor)
  {
    //get an adjacent space
    adjacent = m_loc.get_adjacent(direction);

    //check if tailor is in that space
    if(adjacent == victim.get_location())
      found_tailor = true;
    direction++;
  }
  return found_tailor;
}

void Phantom_Pants::kill(Tailor & victim) const
{
  victim.set_health(DEAD);
  return;
}
