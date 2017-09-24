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
  vector<ND*> tmp;
  
  //Create Vector of size 128
  tmp.resize(128);

  //Set Vector Values to NULL
  for(vector<ND*>::iterator it = tmp.begin(); it != tmp.end(); it++)
  		tmp.insert(it, NULL);

	//Keeps track of the total time to insert into ND
	double timeSinceStart = 0;
	ND Damper;
  //Loop through EventList
  for(EventList::iterator it = el->begin(); it != el->end(); it++){
  	//Current event in the iteration
	
	Event * event = it;
	//Converts time and adds it to timeSinceStart
	timeSinceStart += (event->time/480.0);

 	//Encountered On Event
  	if(event->key == 'O'){	
      //Create ND
	  ND note = new ND();
	  //Stores time relative to total time
	  note.start = timeSinceStart;
	  //value of pitch
	  note.pitch = event->v1;
	  //value of volume
	  note.volume = event->v2;
	  //Add key to note
	  note.key = 'N';
	  //Store note based off pitch(index)
	  tmp[note.pitch]->note;




  	}
    //Enocountered OFF Event
    if(event->key == 'F'){
		//Get from ND tmp vector
		ND* note;
		note->tmp[event->pitch];
      // Set stop time
		note->stop = timeSinceStart;
      //Insert into ND
		nd.insert(std::pair<double, ND*>(note->start, *note));
		//Set location in temp vector to NULL
		tmp[event->pitch] = NULL;
    }

    //DamperDown Event
    if(event->key == 'D' && event->v1 == 1){
		 damper = new ND();
		 damper.key = 'D';
		 damper.start = timeSinceStart;
    }

    //DamperUp Event 
	if(event->key == 'D' && event->v1 == 0){
		damper.stop = timeSinceStart;
		nd.insert(std::pair<double, ND*>(damper.start, *damper));
		damper = NULL;
		//test
	}
  }
}

void CS302_Midi::nd_to_el()
{
  el = new EventList;
}
