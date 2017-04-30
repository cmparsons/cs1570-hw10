// Programmer: Christian Parsons
// Section: E
// Filename: phantom_pants.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains the class defintion for Phantom_Pants.

#ifndef PHANTOM_PANTS_H
#define PHANTOM_PANTS_H

#include "point.h"
#include "general.h"

class Town;
class Tailor;

const char PHANTOM_PANTS = 'P'; //representation of Phantom Pants in town
const short MAX_PHANTOM_PANTS = 3; //max number of phantom pants allowed on grid
const short PHANTOM_PANTS_STEP_PROB = 25; //probability phantom pants will move

class Phantom_Pants
{
private:
  Point m_loc; //(x, y) location in town grid
  char m_symbol; //representation in town grid

  // Description: Checks if pants are next to tailor.
  // pre: None
  // post: If taior is in an adjacent space, returns true. Otherwise, returns
  //       false.
  bool next_to_tailor(const Tailor & victim) const;

  // Description: Phantom pants kill the tailor.
  // pre: None
  // post: The tailor's alive member is set to false and health is set to 0.
  void kill(Tailor & victim) const;

public:
  // Description: Constructor for the Phantom_Pants class.
  // pre: None
  // post: Sets m_loc to (-1, -1), by default and m_symbol to PHANTOM_PANTS.
  Phantom_Pants() : m_symbol(PHANTOM_PANTS) {}

  // Description: Overloaded extraction operator for Phantom_Pants class.
  // pre: None
  // post: Prints the location of the phantom pants.
  friend ostream & operator <<(ostream & out, const Phantom_Pants & pants);

  // Description: Gets the location of the phantom pants.
  // pre: None
  // post: Returns the Phantom Pants' m_loc member.
  Point get_location() const {return m_loc;}

  // Description: Places the Phantom_Pants in the town.
  // pre: None
  // post: m_loc is set to a random position in the town, and m_symbol is set in
  //       the town_grid at its coordinates.
  void place_me(Town & town);

  // Description: Chase the passed tailor and possibly kill.
  // pre: None
  // post: The phantom pants have moved one space closer to tailor by trying
  //       to reach its y-coordinate first, then its x-coordinate. Checks before
  //       and after moving if tailor is next to pants. If so, pants kills tailor
  //       and return true. Otherwise, returns false.
  bool chase(Tailor & victim, Town & town);
};

#endif
