// Programmer: Christian Parsons
// Section: E
// Filename: general.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains general functions and libraries for HW10.

#ifndef GENERAL_H
#define GENERAL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "point.h"
#include "tailor.h"
#include <ncurses.h>
using namespace std;

const short NAME_MAX = 20; //max characters for a name
const long MAX_STEPS = 1000; //max steps for simulation
const Point UNSPAWNED; //point not on the grid: coordinates (-1, -1)

const int PRINT_Y = 22; //coordinates to print updates from simulation
const int PRINT_X = 0;

void clear_line(const int line_y, const int line_x);

// Description: Gets value that corresponds to an object's color.
// pre: None
// post: House: yellow
//       Bully: red
//       Phantom Pants: green
//       Wall: blue
int color_town(const char & object);

// Description: Prints the final results of the simulation.
// pre: None
// post: The reason why the simulation ended has been printed on the screen,
//       and the tailor's status at the end.
void print_final_results(const Tailor & tailor, const bool killed,
  const long step, const Phantom_Pants pants[]);

// Description: Generates a vaule from 1-100.
// pre: None
// post: An integer from 1-100, inclusive, is returned.
int percent_probability();

// Description: Converts passed value into a percent.
// pre: None
// post: A value representing a percent is returned.
template <class T>
float make_percent(const T num)
{
  return (static_cast<float>(num) / 100);
}

// Description: Generates a random number within the bounds.
// pre: T and S must be defined for modulus, subraction, & addition operations.
// post: Returns a random value with bounds, lower <= x <= upper,
//       with the type T.
template <class T, class S>
T random(const T upper, const S lower)
{
  return (rand() % (upper - lower + 1) + lower);
}

#endif
