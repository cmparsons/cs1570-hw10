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

void print_final_results(const Tailor & tailor, const bool killed)
{
  cout << "\n\nFINAL RESULTS:\n";
  cout << "-------------------------------" << endl;

  //print simulation results
  if(killed)
    cout << "Died from phantom pants!!!!" << endl;
  else if(tailor.get_health() == DEAD)
    cout << "Hit by too many bullies!!!" << endl;
  else if(tailor.get_pants() == 0)
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

bool operator ==(const Point & point1, const Point & point2)
{
  return (point1.m_x_coord == point2.m_x_coord
          && point1.m_y_coord == point2.m_y_coord);
}

bool operator !=(const Point & point1, const Point & point2)
{
  return !(point1 == point2);
}

ostream & operator <<(ostream & out, const Tailor & foo)
{
  out << foo.m_name; //diplay name

  //display alive status
  if(foo.m_alive)
    out << " is alive";
  else
    out << " is dead";

  //diplay location in town
  out << " in " << foo.m_loc;

  //display money, number of pants, and health
  out << " with $" << foo.m_money << ", "
      << foo.m_pants << " pants, "
      << "and health " << foo.m_health << ".\n";
  return out;
}

ostream & operator <<(ostream & out, const Town & town)
{
  //i = row, j = column
  for(int i = 0; i < town.town_size; i++)
  {
    for(int j = 0; j < town.town_size; j++) //print out row i
    {
      color_town(town.town_grid[i][j].symbol);
      out << " ";
    }
    out << "\n";
  }
  return out;
}

ostream & operator <<(ostream & out, const Point & point)
{
  out << "(" << point.m_x_coord + 1 << ", " << point.m_y_coord + 1 << ")";
  return out;
}

ostream & operator <<(ostream & out, const Phantom_Pants & pants)
{
  out << "Phantom pants at " << pants.m_loc << endl;
  return out;
}
