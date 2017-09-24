/*Audaris Blades
Lab3
Data Manipulation
Convert EventFiles<->Note Files
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

	//Keeps track of the total time to insert into ND
	double timeSinceStart = 0; 

	//Temp pointers
	vector<ND*> tmp(128);
	ND *note = NULL;
	Event *event = NULL;
	ND *damper = NULL;

	for(EventList::iterator it = el->begin(); it != el->end(); it++){
		event = *it;
		timeSinceStart += (event->time/480.0);

	 	//Encountered On Event
	  	if(event->key == 'O'){	
			note = new ND;
		  	//Stores time relative to total time
			note->start = timeSinceStart;
			note->pitch = event->v1;
			note->volume = event->v2;
			note->key = 'N';
			//Store note based off pitch(index)
			tmp[note->pitch] = note;
	  	}

	    //Encountered OFF Event
	    if(event->key == 'F'){
			note = tmp[event->v1];
			note->stop = timeSinceStart;
			nd->insert(std::pair<double, ND*>(note->start, note));
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
		}
	}
}

void CS302_Midi::nd_to_el()
{

	enum eventType {OFF, DU, DD, ON};

  	el = new EventList;

  	//Temp pointers
	map<int, multimap<int, Event *> >tmp;
	ND *note = NULL;
	Event* onEvent = NULL;
	Event* offEvent = NULL;
	Event* dd = NULL;
	Event* du = NULL;

  	for(NDMap::iterator ndit = nd->begin(); ndit != nd->end(); ndit++){
		note = ndit->second;

		if(note->key == 'N'){
			//Create On Event
			onEvent = new Event;
			onEvent->key = 'O';
			onEvent->v2 = note->volume;
			onEvent->v1 = note->pitch;
			onEvent->time = rint(note->start*480);
			tmp[onEvent->time].insert(pair<int, Event *>(ON,onEvent));

			//Create Off Event
			offEvent = new Event;
			offEvent->key = 'F';
			offEvent->v1 = note->pitch;
			offEvent->time = rint(note->stop*480);
			tmp[offEvent->time].insert(pair<int, Event *>(OFF,offEvent));
		}

		//Dealing with a damper
		if(note->key == 'D'){
			//Create DamperDown
			dd = new Event;
			dd->key = 'D';
			dd->v1 = 1;
			dd->time = rint(note->start*480);
			tmp[dd->time].insert(pair<int, Event *>(DD, dd));

			//Create DamperUp
			du = new Event;
			du->key = 'D';
			du->v1 = 0;
			du->time = rint(note->stop*480);
			tmp[du->time].insert(pair<int, Event *>(DU, du));
		}
	}

	Event *event = NULL;
	bool timeSet = false;
	int previousTime = 0;
	
	for(std::map<int, multimap<int, Event *> >::iterator mit = tmp.begin(); mit != tmp.end(); mit++){
		timeSet = false;
		for(std::multimap<int, Event*>::iterator mmit = mit->second.begin(); mmit != mit->second.end(); mmit++){
			event = NULL;
			event = mmit->second;
			
			//set time of first in map
			if(timeSet == false ){
				int currentTime = mit->first;
				event->time = currentTime - previousTime;
				timeSet = true;
				previousTime = currentTime;
			}
			else
				event->time = 0;

			el->push_back(event);
		}
	}
}
