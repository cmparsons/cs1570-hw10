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

Bully::Bully()
{
  //static so fin doesn't reset to beginning of file for each bully created
  static ifstream fin("bullies.dat");

  m_punch_probability = PUNCH_PROBABILITY;
  m_punch_power = random(MAX_PUNCH_POWER, MIN_PUNCH_POWER);

  fin >> m_name; //read in name from bullies.dat
}

bool Bully::punch(Tailor & nerd, Town & town) const
{
  //amount of money bully takes from the tailor
  short money_taken = nerd.get_money() * make_percent(m_punch_power);

  //update tailor's health after punch
  nerd.set_health(nerd.get_health() - PUNCH);

  //take tailor's money
  nerd.set_money(nerd.get_money() - money_taken);

  //bully's punch sends tailor to new spot in town
  nerd.place_me(town);

  cout << "PUNCHED by " << m_name  << "!" << endl;
  return true;
}

void Bully::threaten() const
{
  ifstream fin("message.dat");

  //line corresponding to message that will output on screen
  short line = random(MAX_MESSAGES - 1, 0);
  string message = "";

  //ignore all lines up to line that corresponds to message of interest
  for(int i = 0; i < line; i++)
    fin.ignore(MAX_CHARACTERS, '\n'); //should read up to delimiter

  getline(fin, message); //get the corresponding message

  //print out the message from the bully
  cout << m_name << ": " << message << endl;
  return;
}
