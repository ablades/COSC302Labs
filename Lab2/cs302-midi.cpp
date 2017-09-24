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
	ND *note = NULL;
	Event *event = NULL;
	ND *damper = NULL;
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

	enum eventType {OFF, ON, DU , DD};
  	el = new EventList;
  	//Temp map to store contents of nd
	map<int, multimap <int, Event *> > mtmp;
  	for(NDMap::iterator ndit = nd->begin(); ndit != nd->end(); ndit++){
		ND *note = NULL;
		note = ndit->second;

		Event *onEvent = NULL;
		Event *offEvent = NULL;
		//Dealing with a note
		//every note must have an on/off event
		if(note->key == 'N'){
			//Create On Event
			Event* onEvent = NULL;
			onEvent = new Event;
			onEvent->key = 'O';
			onEvent->v2 = note->volume;
			onEvent->v1 = note->pitch;
			onEvent->time = rint(note->stop * 480);
			mtmp[onEvent->time].insert(std::pair<int, Event *>(ON, onEvent));
			//Create Off Event
			Event* offEvent = NULL;
			offEvent = new Event;
			offEvent->key = 'F';
			offEvent->v1 = note->pitch;
			offEvent->time = rint(note->stop * 480);
			mtmp[offEvent->time].insert(std::pair<int, Event *>(OFF, offEvent));
			//Fill in information
		}
		//Dealing with a damper
		if(note->key == 'D'){
			//Create new DamperDown
			Event* dd = NULL;
			dd = new Event;
			dd->key = 'D';
			dd->v1 = 1;
			dd->time = rint(note->start * 480);
			mtmp[dd->time].insert(std::pair<int, Event *>(DD, dd));
			//Create new DamperUp
			Event* du = NULL;
			du = new Event;
			du->key = 'D';
			du->v1 = 0;
			dd->time = rint(note->stop * 480);
			//Fill in info
			mtmp[dd->time].insert(std::pair<int, Event *>(DU, du));

		}
	}

	//MAP IS SORTED BY THE TIME IN WHICH EVENTS OCCUR ABSOLUTELY
	//Iterates through the map
	for(std::map<int, multimap<int, Event*> >::iterator mit = mtmp.begin(); mit != mtmp.end(); mit++){
		//Creates reference to the multimap at each time
		multimap<int, Event*> mm = mit->second;
		//Iterates through the Multimap starting from second unit
		bool timeSet = false;
		for(std::multimap<int, Event*>::iterator mmit = mm.begin(); mmit != mm.end(); mit++){
			Event *event = NULL;
			event = mmit->second;
			
			//set time of inital event if iterator
			if(timeSet == false && (mit--) != mtmp.end()){
				//The current absolute time
				int currentTime = mit->first;
				int previousTime = (mit--)->first;
				event->time = currentTime - previousTime;
				timeSet = true;
			}

			//Events in same map occur at same time
			event->time = 0;
			//Convert the time
			
			//Push to EL

		}
	}
}
