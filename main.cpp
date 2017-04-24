// Programmer: Christian Parsons
// Section: E
// Filename: main.cpp
// Assignment: HW #10
// Due Date: 5/3/17
// Purpose: File contains main function for program that will simulate a
//          tailor's entrepreneurial adventures.

#include "town.h"
#include "tailor.h"
#include "general.h"
#include "bully.h"
#include "phantom_pants.h"

int main()
{
  //set up the simulation
  Town Springfield(NUM_BULLIES, NUM_HOUSES, 17);
  Tailor Milhouse("Milhouse");
  Bully Thugs[NUM_BULLY_NAMES];
  Phantom_Pants Evil_Pants[MAX_PHANTOM_PANTS];

  //variables to track the simulation
  long step = 1; //track number of steps taken by Milhouse
  bool killed = false; //determine if Milhouse was killed by Phantom Pants
  short health = Milhouse.get_health();
  short pants_left = Milhouse.get_pants();

  srand(time(NULL)); //seed the RNG

  Milhouse.place_me(Springfield);
  cout << Springfield;

  /*
  Simulation loops until:
    -Milhouse dies from a pair of phantom pants
    -Milhouse's health drops to 0 as a result of being hit by bullies
    -Milhouse sold all of his pants
    -Simulation reaches MAX_STEPS: 1000
  */
  while(step <= MAX_STEPS && !killed && pants_left > SOLD_ALL && health > DEAD)
  {
    cout << "\nStep: " << step << endl;
    cout << "-------------------------------\n";

    //Milhouse takes a step in the town
    Milhouse.rand_walk(Springfield);

    //simulate moves for every pair of phantom pants in town
    for(int j = 0; j < MAX_PHANTOM_PANTS; j++)
    {
      //if there are phantom pants in town, chase and/or kill Milhouse
      if(Evil_Pants[j].get_location() != UNSPAWNED)
      {
        //chance that the phantom pants won't move
        if(percent_probability() <= PHANTOM_PANTS_STEP_PROB)
          killed = Evil_Pants[j].chase(Milhouse, Springfield);

        cout << Evil_Pants[j];
      }
    }
    //Milhouse interacts with the town
    Milhouse.interact(Springfield, Thugs, Evil_Pants);

    cout << Springfield;

    //check Milhouse's condition
    health = Milhouse.get_health();
    pants_left = Milhouse.get_pants();
    step++;
  }

  //collect and present stats of the simulation
  print_final_results(Milhouse, killed);
  return 0;
}
