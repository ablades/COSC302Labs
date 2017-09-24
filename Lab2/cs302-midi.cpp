/*Audaris Blades
Lab3
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


//EL is Full
//Map is empty
void CS302_Midi::el_to_nd()
{
  nd = new NDMap;
  
  //Holds Note Damper Events
  //Indexed by pitch
  vector<ND*> tmp(128);
  
  //Create Vector of size 128
  ND* note = NULL;
  Event *event = NULL;
  ND* damper = NULL;
  //Set Vector Values to NULL

	//Keeps track of the total time to insert into ND
	double timeSinceStart = 0;

  //Loop through EventList
  for(EventList::iterator it = el->begin(); it != el->end(); it++){
  	//Current event in the iteration
	
	 event = *it;
	//Converts time and adds it to timeSinceStart
	timeSinceStart += (event->time/480.0);

 	//Encountered On Event
  	if(event->key == 'O'){	
      //Create ND
	  
	  note = new ND;
	  //Stores time relative to total time
	  note->start = timeSinceStart;
	  //value of pitch
	  note->pitch = event->v1;
	  //value of volume
	  note->volume = event->v2;
	  //Add key to note
	  note->key = 'N';
	  //Store note based off pitch(index)
	  tmp[note->pitch] = note;




  	}
    //Enocountered OFF Event
    if(event->key == 'F'){
		//Get from ND tmp vec
		note = tmp[event->v1];
      // Set stop time
		note->stop = timeSinceStart;
      //Insert into ND
		nd->insert(std::pair<double, ND*>(note->start, note));
		//Set location in temp vector to NULL
		tmp[event->v1] = NULL;
    }

    //DamperDown Event
    if(event->key == 'D' && event->v1 == 1){
		 
		 damper = new ND;
		 damper->key = 'D';
		 damper->start = timeSinceStart;
		 tmp[0] = damper;
    }

    //DamperUp Event 
	if(event->key == 'D' && event->v1 == 0){
		damper = tmp[0];
		damper->stop = timeSinceStart;
		nd->insert(std::pair<double, ND*>(damper->start, damper));
		//damper = NULL;
		//test
	}
  }
}

void CS302_Midi::nd_to_el()
{
  el = new EventList;
}
