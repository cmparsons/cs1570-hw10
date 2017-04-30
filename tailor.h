// Programmer: Christian Parsons
// Section: E
// Filename: town.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains the Tailor class defintion.

#ifndef TAILOR_H
#define TAILOR_H

#include "general.h"
#include "town.h"
#include "phantom_pants.h"
#include <cstring>

class Bully;
class Phantom_Pants;

const short MIN_START_MONEY = 20; //range for tailor's starting funds
const short MAX_START_MONEY = 40;

const short MAX_HEALTH = 100; //range for tailor's health
const short DEAD = 0; //health value corresponding to a dead tailor

const short PANTS_START = 30; //number of pants tailor starts off with
const short SOLD_ALL = 0; //tailor sold all of his/her pants
const short PANTS_PROFIT = 10; //amount of money from selling pair of pants
const short SELL_PANTS_CHANCE = 70; //chance a house will exchange pants

const char DEFAULT_SYM = 'M'; //default representation for tailor in town

const int PRINT_TAILOR_Y = 18; //cooridnates to print tailor on screen
const int PRINT_TAILOR_X = 0;

class Tailor
{
private:
  char m_name[20];
  short m_money; //current funds
  char m_symbol; //representation on the town grid
  bool m_alive; //dead/alive status
  Point m_loc; //location (x, y) in town grid
  short m_health; //health points
  short m_pants; //number of pants left to sell

  // Description: Sell a pair of pants to a house.
  // pre: None
  // post: The point occupied by the house pants_to_exchange member is set to
  //       false. Tailor's m_money increases by PANTS_PROFIT and m_pants is
  //       decreased by one. A message is printed with location of house
  //       that exchanged pants.
  void sell_pants(Town & town, const Point & point);

public:
  // Description: Prints the Tailor's status on the screen.
  // pre: None
  // post: Prints a message on the screen displaying the Tailor's name, alive
  //       status, location in the town, money, pants left, and health.
  friend ostream & operator <<(ostream & out, const Tailor & foo);

  // Description: Constructor for the Tailor class.
  // pre: None
  // post: The Tailor's m_name and m_symbol are set to the passed arguments
  //       (DEFAULT_SYM by default). m_money is set to random value from
  //       MIN_START_MONEY to MAX_START_MONEY. m_alive set to true. m_health set
  //       to MAX_HEALTH. m_pants set to PANTS_START.
  Tailor(const char name[], char sym = DEFAULT_SYM);

  // Description: Place the Tailor in a random spot in the town.
  // pre: Town cannot be completely filled
  // post: The Tailor's x and y coordinates are updated to a random spot in the
  //       town. The Tailor's symbol has been placed in the town at its
  //       coordinates.
  void place_me(Town & town);

  // Description: Simulate the Tailor walking through the town.
  // pre: Town cannot be completely filled
  // post: Randomly chosen spot in town contain's Tailor's m_symbol, and
  //       Tailor's coordinates are the randomly chosen spot.
  void rand_walk(Town & town);

  // Description: Set Tailor's health.
  // pre: None
  // post: The Tailor's health member has been set to the passed argument. If
  //       Tailors health reaches 0, then m_alive is changed to false.
  void set_health(const short health);

  // Description: Set the Tailor's money member.
  // pre: None
  // post: The Tailor's money member has been set to the passed argument.
  void set_money(const short money);

  // Description: Get the Tailor's location member.
  // pre: None
  // post: The Tailor's m_loc member has been returned.
  Point get_location() const {return m_loc;}

  // Description: Get the Tailor's health member.
  // pre: None
  // post: The Tailor's health member has been returned.
  short get_health() const {return m_health;}

  // Description: Get the Tailor's money member.
  // pre: None
  // post: The Tailor's money member has been returned.
  float get_money() const {return m_money;}

  // Description: Get the Tailor's pants member.
  // pre: None
  // post: The Tailor's m_pants member has been returned.
  char get_pants() const {return m_pants;}

  // Description: Tailor interacts with houses or bullies.
  // pre: None
  // post: Chance of Tailor's money increasing by PANTS_PROFIT per adjacent
  //       house.
  //       Chance of Tailor of being placed in new spot in town w/ less money,
  //       and a pair of Phantom Pants is generated as result of being
  //       punched by a bully. Or message is output to screen by bully.
  void interact(Town & town, Bully Bullies[], Phantom_Pants evil_pants[]);

};

#endif
