/*Audaris Blades
 * Lab 7
 * Dijkstra's Algorithm
 */

#include "city_map.h"
#include <map>
#include <vector>
#include <iterator>
#include <cmath>

City_Map::City_Map(){
   // cout << "HERE";
    Intersection *IS;

    double x, y, gStr, gAve;
    int st, ave;
    int count = 0;
    int strMax = 0;
    int aveMax = 0;

    //Read in data
    while(cin >> st){
        IS = new Intersection;
        cin >> ave >> x >> y >> gStr >> gAve;
        IS->street = st;
        IS->avenue = ave;
        IS->x = x;
        IS->y = y;
        IS->green[0] = gStr;
        IS->green[1] = gAve;
        IS->backedge = NULL;
        IS->best_time = -1;

        //First Intersection
        if(st == 0 & ave == 0)
            first = IS;
        //Set Last intersection point
        if(st > strMax || ((strMax == st) && ave > aveMax)){
            strMax = st;
            aveMax = ave;
            last = IS;
        }
        all.push_back(IS);
    }

    //set initial size of temp vector
    vector< vector<Intersection *> > tmp(strMax +1, vector<Intersection *>(aveMax+1));

    //Store contents of all into tmp in proper position
        for(list<Intersection *>::iterator itr = all.begin(); itr !=  all.end(); itr++){
         //   cout << (*itr)->street << " " << (*itr)->avenue;
            tmp[(*itr)->street][(*itr)->avenue] = *itr;
           // cout << endl;
        }

    //Creates edges in all possible directions
    Road_Segment* rs;
    for(int i = 0; i < tmp.size(); i++){
        for(int j = 0; j < tmp[i].size(); j++){
            //Look Up
            if(i > 0 && (j % 5 == 0 || j % 2 != 0 || j == aveMax)){
                rs = new Road_Segment();
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i-1][j];
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i-1][j]->x,2) + pow(tmp[i][j]->y - tmp[i-1][j]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
            //Look Down
            if(i < strMax && (j % 2 == 0 || j % 5 == 0 || j == aveMax)){
                rs = new Road_Segment;//create road segment
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i+1][j];
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i+1][j]->x,2) + pow(tmp[i][j]->y - tmp[i+1][j]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }

            //Look left
            if( j > 0 && (i % 5 == 0 || i % 2 != 0)){
                rs = new Road_Segment;
                rs->type = STREET;
                rs->number = i;
                rs->from = tmp[i][j];
                rs->to = tmp[i][j-1];
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i][j-1]->x,2) + pow(tmp[i][j]->y - tmp[i][j-1]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
            //Look right
            if( j < aveMax && (i % 5 == 0 || i % 2 == 0)){
                rs = new Road_Segment;
                rs->type = STREET;
                rs->number = i;
                rs->from = tmp[i][j];
                rs->to = tmp[i][j+1];
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i][j+1]->x,2) + pow(tmp[i][j]->y - tmp[i][j+1]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
       }
    }
}

double City_Map::Dijkstra(int avg_best_worst){
    bfsq.insert(make_pair(0, first));

    //Queue
    while(bfsq.size()){
        Intersection * IS;
        Road_Segment * rs;
        double curTime = 0;
        double travelTime =-1;

        IS = bfsq.begin()->second;
        curTime = bfsq.begin()->first;
        //Remove node from queue
        bfsq.erase(bfsq.begin());
        IS->best_time = curTime;

        //loop through adj list and check if visited
        for(list<class Road_Segment *>::iterator itr = IS->adj.begin(); itr != IS->adj.end(); itr++){
            rs = *itr;

            //If intersection has been visited it will have a best time
            if(rs->to->best_time != -1)
                continue;

            //Calculate time to node
            travelTime = rs->distance / 30 * 3600;


            if(travelTime < rs->to->best_time || rs->to->best_time == -1){

                //If the intersection is in the queue remove it
                for(multimap<double, Intersection *>::iterator itr = bfsq.begin(); itr != bfsq.end(); itr++)
                    if(itr->second == rs->to)
                        bfsq.erase(itr);

                rs->to->best_time = curTime + travelTime;
                rs->to->backedge = rs;
                rs->to->bfsq_ptr = bfsq.insert(make_pair(curTime + travelTime, rs->to));
            }
        }
    }
    double time = 0;
    //Start at last intersection


    //Traverse back edges from last node
    //While we are not at the first node
    Intersection * lastIS;
    lastIS = last;
    while(lastIS->backedge != NULL){
        //Assign it to next intersection
        path.push_front(lastIS->backedge);
        lastIS = lastIS->backedge->from;
    }

    for(list<class Road_Segment *>::iterator itr = path.begin(); itr != path.end(); itr++){
        time += (*itr)->from->best_time;
    }

    //Returns the total time
    return time;

}

