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

void clear_line(const int line_y, const int line_x)
{
  const int MAX_CHARACTERS = 102;

  move(line_y, line_x); //move cursor to coordinates

  //clear line by printing whitespaces
  for(int i = 0; i < MAX_CHARACTERS; i++)
    addch(' ');

  refresh();
  move(line_y, line_x); //move cursor back
  return;
}

int percent_probability()
{
  return random(100, 1);
}

void print_final_results(const Tailor & tailor, const bool killed,
  const long step, const Phantom_Pants pants[])
{
  int printy = PRINT_Y; //initialize y-component of print

  clear_line(printy, PRINT_X);
  mvprintw(printy, PRINT_X, "FINAL RESULTS:");
  mvprintw(printy += 1, PRINT_X, "-------------------------------");

  move(printy += 2, PRINT_X);
  printw("Steps: %d", step);

  move(printy += 2, PRINT_X);

  //print any phantom pants alive in town
  for(int i = 0; i < MAX_PHANTOM_PANTS; i++)
    if(pants[i].get_location() != UNSPAWNED)
    {
      clear_line(printy + i, PRINT_X);
      cout << pants[i];
      move(printy ++, PRINT_X);
    }

  mvprintw(printy += 2, PRINT_X, "Cause of end: ");

  //print simulation results
  if(killed)
    printw("Death by phantom pants!!!!");
  else if(tailor.get_health() == DEAD && !killed)
    printw("Hit by too many bullies!!!");
  else if(tailor.get_pants() == SOLD_ALL)
    printw("Sold all of the pants!!!!");
  else
    printw("Reached max steps.");

  //print tailor's status at end of simulation
  cout << tailor;

  refresh();
  return;
}

int color_town(const char & object)
{
  int color;

  switch(object)
  {
    case HOUSE:
      color = 1;
      break;
    case BULLY:
      color = 2;
      break;
    case WALL:
      color = 3;
      break;
    case PHANTOM_PANTS:
      color = 4;
      break;
    default:
      color = 5;
  }
  return color;
}
