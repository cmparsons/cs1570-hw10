// Programmer: Christian Parsons
// Section: E
// Filename: bully.h
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains the Bully class defintion.

#ifndef BULLY_H
#define BULLY_H

#include <fstream>
#include <string>
using namespace std;

class Tailor;
class Town;

const char BULLY = 'B'; //representation of a bully
const short MIN_PUNCH_POWER = 30; //range of bully's punch power
const short MAX_PUNCH_POWER = 50;
const short PUNCH_PROBABILITY = 80; //bully's probability to punch the tailor
const short PUNCH = 10; //amount tailor's health is reduced by after punch

const short NUM_BULLY_NAMES = 4; //number of possible names for bullies
const short MAX_MESSAGES = 10; //number of messages in message.dat

class Bully
{
private:
  char m_name[NAME_MAX];
  short m_punch_power;
  short m_punch_probability;

public:
  // Description: Default constructor for the Bully class.
  // pre: None
  // post: Bully's name is assigned from a name in bullies.dat. Bully's
  //       punch power is random value from MIN_PUNCH_POWER to MAX_PUNCH_POWER.
  //       Bully's m_punch_probability = PUNCH_PROBABILITY.
  Bully();

  // Description: Simulate a bully punching a tailor.
  // pre: None
  // post: Tailor's health is reduced by PUNCH, money is reduced by a
  //       percent of bully's punch power, and location is in a random spot in
  //       in the town. Returns true to calling function.
  void punch(Tailor & nerd, Town & town) const;

  // Description: Print out a random threatening message.
  // pre: message.dat must exist in directory
  //      MAX_MESSAGES should equal number of messages in message.dat
  //      length of every message in file < MAX_CHARACTERS
  // post: Prints out a threatening message on the screen from message.dat.
  void threaten() const;

  // Description: Get the Bully's name.
  // pre: None
  // post: The name of the Bully is returned.
  string get_name() const {return m_name;}

  // Description: Get the Bully'y punch probability.
  // pre: None
  // post: The Bully's punch probability is returned.
  short get_punch_prob() const {return m_punch_probability;}
};
#endif
