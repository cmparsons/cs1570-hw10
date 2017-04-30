// Programmer: Christian Parsons
// Section: E
// Filem_name: tailor.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains functions for the Tailor class.

#include "bully.h"
#include "town.h"
#include "tailor.h"
#include "general.h"
#include "phantom_pants.h"

ostream & operator <<(ostream & out, const Tailor & foo)
{
  clear_line(PRINT_TAILOR_Y, PRINT_TAILOR_X);
  
  printw("%s", foo.m_name);

  //display alive status
  if(foo.m_alive)
    printw(" is alive");
  else
    printw(" is dead");

  //diplay location in town
  printw(" in ");
  out << foo.m_loc;

  //display money, number of pants, and health
  printw(" with $%i,", foo.m_money);
  printw(" %i pants,", foo.m_pants);
  printw(" and health %i.", foo.m_health);
  refresh();
  return out;
}

Tailor::Tailor(const char name[], const char sym)
{
  strcpy(m_name, name);
  m_symbol = sym;
  m_money = random(MAX_START_MONEY, MIN_START_MONEY);
  m_alive = true;
  m_health = MAX_HEALTH;
  m_pants = PANTS_START;

  //will call Point's default constructor to initialize m_location
}

void Tailor::place_me(Town & town)
{
  Point new_location; //set to default of (-1, -1)

  //if already on grid, clear its previous location in town
  if(m_loc != new_location)
    town.clear_grid_content(m_loc);

  //get an empty space in the town to place the tailor
  new_location = town.get_empty_point();

  //update tailor's cooridnates and set in the town
  m_loc = new_location;
  town.set_in_grid(m_loc, m_symbol);
  return;
}

void Tailor::rand_walk(Town & town)
{
  Point new_location;
  bool occupied = true;
  bool surrounded = false;

  //loop until tailor took a step in a blank space or if surrounded
  while(occupied && !surrounded)
  {
    //find a random direction to take a step
    new_location = m_loc.get_adjacent(random(NUM_DIRECTIONS, 0));

    //check if the location is occupied
    occupied = town.space_occupied(new_location);

    //check if tailor is trapped
    surrounded = town.surrounded(m_loc);
  }

  //if not surrounded, update coordinates and town
  if(!surrounded)
  {
    //vacate tailor's previous location
    town.clear_grid_content(m_loc);

    //update tailor's coordinates
    m_loc = new_location;

    //set tailor's new coordinates and update town
    town.set_in_grid(m_loc, m_symbol);
  }
  return;
}

void Tailor::interact(Town & town, Bully bullies[], Phantom_Pants evil_pants[])
{
  Point adjacent;
  char adjacent_content;
  short direction = 0;
  bool keep_checking = true; //keep checking adjacent spaces

  //select which bully will interact with tailor(if applicable)
  short which_bully = random(NUM_BULLY_NAMES - 1, 0);
  Bully thug = bullies[which_bully];

  static short phantom_pants_made = 0; //track number of phantom pants made

  //loops until every adjacent space is checked or tailor got punched by bully
  while(direction < NUM_DIRECTIONS && keep_checking)
  {
    //get an adjacent space and check its contents
    adjacent = m_loc.get_adjacent(direction);
    adjacent_content = town.get_grid_content(adjacent);

    switch (adjacent_content)
    {
      case HOUSE:
        //possibilty of exchange with house that has pants to exchange
        if(percent_probability() <= SELL_PANTS_CHANCE
           && town.get_pants_to_exchange(adjacent))
        {
          sell_pants(town, adjacent);
        }
        break;
      case BULLY:
        //tailor might get punched
        if(percent_probability() <= thug.get_punch_prob())
        {
           thug.punch(*this, town);

          //create a pair of phantom pants
          if(phantom_pants_made < MAX_PHANTOM_PANTS)
          {
            evil_pants[phantom_pants_made].place_me(town);
            phantom_pants_made++;
            m_pants--;
          }
        }
        else
          thug.threaten();
        keep_checking = false; //stop interacting during this turn
        break;
    }
    direction++; //check next space
  }
  return;
}

void Tailor::sell_pants(Town & town, const Point & point)
{
  town.bought_pants(point); //house now has no pants to exchange
  m_money += PANTS_PROFIT; //update tailor's money and pants inventory
  m_pants--;

  //print out the house where sale occurred
  clear_line(PRINT_Y, PRINT_X);
  move(PRINT_Y, PRINT_X);
  printw("Pants exchanged from ");
  cout << point;
  refresh();
  return;
}

void Tailor::set_money(const short money)
{
  //to account for if money dipped below 0
  m_money = (money < 0) ? 0 : money;
  return;
}

void Tailor::set_health(const short health)
{
  //set health to passed value if non-negative or make 0
  m_health = (health >= DEAD) ? health : DEAD;

  //if tailor has 0 heath points, they dead
  m_alive = (m_health == DEAD) ? false : true;
  return;
}
