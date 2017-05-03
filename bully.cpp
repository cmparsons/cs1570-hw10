// Programmer: Christian Parsons
// Section: E
// Filename: bully.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains functions for the Bully class.

#include "bully.h"
#include "general.h"
#include "tailor.h"
#include "town.h"

short Bully::bullies_made = 0;

Bully::Bully()
{
  //static so fin doesn't reset to beginning of file for each bully created
  static ifstream fin("bullies.dat");

  bullies_made++;
  m_punch_probability = PUNCH_PROBABILITY;
  m_punch_power = random(MAX_PUNCH_POWER, MIN_PUNCH_POWER);

  fin >> m_name; //read in name from bullies.dat

  //once all bullies in simulation have been constructd, close input file
  if(bullies_made == NUM_BULLY_NAMES)
    fin.close();

}

void Bully::punch(Tailor & nerd, Town & town) const
{
  //amount of money bully takes from the tailor
  short money_taken = nerd.get_money() * make_percent(m_punch_power);

  //update tailor's health after punch
  nerd.set_health(nerd.get_health() - PUNCH);

  //take tailor's money
  nerd.set_money(nerd.get_money() - money_taken);

  //bully's punch sends tailor to new spot in town
  nerd.place_me(town);

  clear_line(PRINT_Y, PRINT_X);
  printw("PUNCHED by %s!", m_name);
  refresh();
  return;
}

void Bully::threaten() const
{
  ifstream fin("message.dat");

  //line corresponding to message that will output on screen
  short line = random(MAX_MESSAGES, 0);
  char message[MAX_MESSAGE_CHARS];

  //last message received should be message output
  for(int i = 0; i < line; i++)
    fin.getline(message, MAX_MESSAGE_CHARS - 1); //get the corresponding message

  fin.close(); //close the file

  //print out the message from the bully
  clear_line(PRINT_Y, PRINT_X);
  move(PRINT_Y, PRINT_X);
  printw("%s:", m_name);
  printw(message);
  refresh();
  return;
}
