/*Audaris Blades
Lab2
Convert MIDI Event/Note Files
*/

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "cs302-midi.h"
using namespace std;

//EL is Full
//Map is empty
void CS302_Midi::el_to_nd()
{
  nd = new NDMap;
  
  //Indexed by pitch
  vector<ND*> tmp;
  
  //Create Vector of size 128
  tmp.resize(128);

  //Set Vector Values to NULL
  for(vector<ND*>::iterator it = tmp.begin(); it != tmp.end(); it++)
  		tmp.insert(it, NULL);

  //Loop through EventList
  for(list<Event *>::iterator it = EventList.begin(),it != EventList.end(); it++){
  	Event * event = it;

  	//Event is on
  	if(event->key == 'O'){

  	}
  }
}

void CS302_Midi::nd_to_el()
{
  el = new EventList;
}