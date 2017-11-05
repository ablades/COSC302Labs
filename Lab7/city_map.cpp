/*Audaris Blades
 * Lab 7
 * Dijkstra's Algorithm
 */

#include "city_map.h"
#include <map>
#include <vector>
#include <iterator>

City_Map::City_Map(){
    Intersection *IS = new Intersection();
    City_Map *c = new City_Map;

    double input;
    int st, ave;
    int stmax, avemax;
    while(cin >> st){
        IS->street = st;
        cin >> ave;
        IS->avenue = ave;
        cin >> input;
        IS->x = input;
        cin >> input;
        IS->y = input;
        cin >> input;
        IS->green[0] = input;
        cin >> input;
        IS->green[1] = input;
        c->all.push_back(IS);

        //First Intersection
        if(st == 0 & ave == 0)
            c->first = IS;
        //Set Last intersection point
        if(st > stmax || ((stmax == st) && ave >= avemax)){
            stmax = st;
            avemax = ave;
            c->last = IS;
        }
        IS = new Intersection();
    }
    //set initial size of temp vector
    vector< vector<Intersection *> > tmp(stmax+1, vector<Intersection *>(avemax +1));

    //Store contents of all into temp in proper position
        for(list<Intersection *>::iterator itr = c->all.begin(); itr !=  c->all.end(); itr++)
            tmp[(*itr)->street][(*itr)->avenue] = *itr;

    for(int i = 0; i < stmax; i++)
        for(int j = 0; j < avemax; i++){
            //Look Up
            if(i > 0 && (j % 5 == 0 || j % 2 != 0 || j == avemax)){

            }
            //Look Down
            if(i < stmax && (j % 2 == 0 || j % 5 == 0 || j == avemax)){
                //create road segment

            }
            //Look left
            if( j > 0 && (i % 5 == 0)){}
            //Look right
            if( j < avemax && (i % 5 == 0)){}
        }



}

double City_Map::Dijkstra(int avg_best_worst){
    return 0;
}
