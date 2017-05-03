// Programmer: Christian Parsons
// Section: E
// Filename: main.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains main function for program that will simulate a
//          tailor's entrepreneurial adventures.

/******************************
          USED NCURSES
******************************/

#include "town.h"
#include "tailor.h"
#include "general.h"
#include "bully.h"
#include "phantom_pants.h"
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
  //convert command line argument to long
  long delay = atol(argv[1]);

  srand(time(NULL)); //seed the RNG

  //set up the town and all characters involved with the simulation
  Town Springfield(NUM_BULLIES, NUM_HOUSES, 17);
  Tailor Milhouse("Milhouse");
  Bully Thugs[NUM_BULLY_NAMES];
  Phantom_Pants Evil_Pants[MAX_PHANTOM_PANTS];

  //variables to track the simulation
  long step = 1; //track number of steps taken by Milhouse
  bool killed = false; //determine if Milhouse was killed by Phantom Pants
  short health = Milhouse.get_health(); //track health per step
  short pants_left = Milhouse.get_pants(); //track pants inventory
  int j = 0; //traverse thru phantom pants

  Milhouse.place_me(Springfield);
  cout << Springfield;

  /*
  Simulation loops until:
    -Milhouse dies from a pair of phantom pants
    -Milhouse's health drops to 0 as a result of being hit by bullies
    -Milhouse sold all of his pants
    -Simulation reaches MAX_STEPS: 1000
  */
  while(step < MAX_STEPS && !killed && pants_left > SOLD_ALL && health > DEAD)
  {
    //Milhouse takes a step in the town
    Milhouse.rand_walk(Springfield);
    cout << Springfield;

    //simulate moves for every pair of phantom pants in town
    //loops until every spawned pants moves or one pair kills Milhouse
    j = 0;
    while(j < MAX_PHANTOM_PANTS && !killed)
    {
      //if there are phantom pants in town, chase and/or kill Milhouse
      if(Evil_Pants[j].get_location() != UNSPAWNED)
      {
        //chance that the phantom pants won't move
        if(percent_probability() <= PHANTOM_PANTS_STEP_PROB)
        {
          killed = Evil_Pants[j].chase(Milhouse, Springfield);
          cout << Springfield;
        }
      }
      j++;
    }
    //Milhouse interacts with the town if he's not dead
    if(!killed)
    {
      Milhouse.interact(Springfield, Thugs, Evil_Pants);
      cout << Springfield;
    }
    //check Milhouse's condition
    health = Milhouse.get_health();
    pants_left = Milhouse.get_pants();

    cout << Milhouse;
    usleep(delay);
    step++;
  }
  refresh();

  //collect and present stats of the simulation
  print_final_results(Milhouse, killed, step, Evil_Pants);
  getch(); //wait to return back to normal terminal
  endwin(); //return to terminal window
  return 0;
}
