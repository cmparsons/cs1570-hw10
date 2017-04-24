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

Tailor::Tailor(const string name, const char sym)
{
  m_name = name;
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
  bool took_step = false;

  while(!took_step) //loop until tailor took a step in a blank space
  {
    //find a random direction to take a step
    new_location = m_loc.get_adjacent(random(NUM_DIRECTIONS, 0));

    //check if the location is occupied
    if(!town.space_occupied(new_location))
      took_step = true;
  }
  //clear contents of tailor's previous location
  town.clear_grid_content(m_loc);

  //set tailor's new coordinates and update town
  m_loc = new_location;
  town.set_in_grid(m_loc, m_symbol);
  return;
}

void Tailor::interact(Town & town, Bully bullies[], Phantom_Pants evil_pants[])
{
  Point adjacent;
  short direction = 0;

  //select which bully will interact with tailor(if applicable)
  short which_bully = random(NUM_BULLY_NAMES - 1, 0);
  Bully thug = bullies[which_bully];
  bool tailor_punched = false;

  static short phantom_pants_made = 0; //track number of phatom pants spawned

  //loops until every adjacent space is checked or tailor got punched by bully
  while(direction < NUM_DIRECTIONS && !tailor_punched)
  {
    //get an adjacent space to check
    adjacent = m_loc.get_adjacent(direction);

    //if space is a house, there might be possible exchange
    if(town.get_grid_content(adjacent) == HOUSE && percent_probability()
       <= SELL_PANTS_CHANCE && town.get_pants_to_exchange(adjacent))
    {
      sell_pants(town, adjacent);
    }
    //if space is a bully, uh-oh
    else if(town.get_grid_content(adjacent) == BULLY)
    {
      //see if tailor will be punched or threatened by bully
      if(percent_probability() <= thug.get_punch_prob())
      {
        tailor_punched = thug.punch(*this, town);

        //pair of phantom pants created
        if(phantom_pants_made < MAX_PHANTOM_PANTS)
        {
          evil_pants[phantom_pants_made].place_me(town);
          phantom_pants_made++;
        }
      }
      else
        thug.threaten();
    }
    direction++; //check next space
  }
  return;
}

void Tailor::sell_pants(Town & town, const Point & point)
{
  town.set_pants_to_exchange(false, point); //house now has no pants to exchange
  m_money += PANTS_PROFIT; //update tailor's money
  m_pants--;

  //print out the house where sale occurred
  cout << "Pants exchanged from: " << point << endl;
  return;
}

void Tailor::set_money(const float money)
{
  m_money = money;
  return;
}

void Tailor::set_health(const short health)
{
  m_health = health;

  if(m_health == DEAD) //if tailor has 0 heath points, they dead
    m_alive = false;
  return;
}
