// Programmer: Christian Parsons
// Section: E
// Filename: general.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains general functions HW10.

#include "town.h"
#include "tailor.h"
#include "general.h"
#include "point.h"
#include "phantom_pants.h"
#include "bully.h"

int percent_probability()
{
  return random(100, 1);
}

void print_final_results(const Tailor & tailor, const bool killed,
  const long step, const Phantom_Pants pants[])
{
  cout << "\n\nFINAL RESULTS:\n";
  cout << "-------------------------------" << endl;

  //print steps tailor took during simulation
  cout << "Steps: " << step << "\n\n";

  //print any phantom pants alive in town
  for(int i = 0; i < MAX_PHANTOM_PANTS; i++)
    if(pants[i].get_location() != UNSPAWNED)
      cout << pants[i];

  cout << "\nCause of end: ";

  //print simulation results
  if(killed)
    cout << "Died from phantom pants!!!!" << endl;
  else if(tailor.get_health() == DEAD && !killed)
    cout << "Hit by too many bullies!!!" << endl;
  else if(tailor.get_pants() == SOLD_ALL)
    cout << "Sold all the pants!!!!" << endl;
  else
    cout << "Reached max steps of " << MAX_STEPS << endl;

  //print tailor's status at end of simulation
  cout << tailor << endl;
  return;
}

void color_town(const char & object)
{
  switch(object)
  {
    case HOUSE:
      cout << "\e[93m" << object << "\e[0m";
      break;
    case BULLY:
      cout << "\e[1;31m" << object << "\e[0m";
      break;
    case WALL:
      cout << "\e[1;34m" << object << "\e[0m";
      break;
    case PHANTOM_PANTS:
      cout << "\e[0;32m" << object << "\e[0m";
      break;
    default:
      cout << object;
  }
  return;
}
