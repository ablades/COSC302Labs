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
    int stmax = 0;
    int avemax = 0;

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

        //First Intersection
        if(st == 0 & ave == 0)
            first = IS;
        //Set Last intersection point
        if(st > stmax || ((stmax == st) && ave > avemax)){
            stmax = st;
            avemax = ave;
            last = IS;
        }
        all.push_back(IS);
    }

    //set initial size of temp vector
    vector< vector<Intersection *> > tmp(stmax +1, vector<Intersection *>(avemax+1));

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
            if(i > 0 && (j % 5 == 0 || j % 2 != 0 || j == avemax)){
                rs = new Road_Segment();
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i-1][j];
                rs->backedge = nullptr;
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i-1][j]->x,2) + pow(tmp[i][j]->y - tmp[i-1][j]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
            //Look Down
            if(i < stmax && (j % 2 == 0 || j % 5 == 0 || j == avemax)){
                rs = new Road_Segment;//create road segment
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i+1][j];
                rs->backedge = nullptr;
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
                rs->backedge = nullptr;
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i][j-1]->x,2) + pow(tmp[i][j]->y - tmp[i][j-1]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
            //Look right
            if( j < avemax && (i % 5 == 0 || i % 2 == 0)){
                rs = new Road_Segment;
                rs->type = STREET;
                rs->number = i;
                rs->from = tmp[i][j];
                rs->to = tmp[i][j+1];
                rs->backedge = nullptr;
                rs->distance = sqrt(pow(tmp[i][j]->x - tmp[i][j+1]->x,2) + pow(tmp[i][j]->y - tmp[i][j+1]->y, 2));
                tmp[i][j]->adj.push_back(rs);
            }
       }
    }
}

double City_Map::Dijkstra(int avg_best_worst){
    bfsq.insert(make_pair(0, *first));

    //Queue
    while(bfsq.size()){
        Intersection * IS;
        Road_Segment * rs;
        double travelTime;
        IS = bfsq.begin()->second;
        //Remove node from queue
        bfsq.erase(bfsq.begin());

        //loop through adj list and check if visited
        for(int i; i < IS->adj.size(); i++){
            rs = IS->adj[i];

            //If intersection has been visited it will have a backedge
            if(rs->to->backedge != nullptr)
                continue;

            //Calculate time to node
            travelTime = rs->distance / (30 * 3600);

            //Insert intersection with travelTime into queue
            bfsq.insert(make_pair(travelTime, rs->to));


            if(travelTime < rs->to->best_time || rs->to->best_time == -1){

                //has not been visited. remove from queue
                if(rs->to == -1)
                    bfsq.erase(rs->to.bfsq_ptr);

                rs->to->best_time = travelTime;
                rs->to.back_edge = rs;
                rs->to.bfsq_ptr = bfsq.insert(make_pair(travelTime, rs->to));
            }
        }
    }
    double time = 0;
    //Start at last intersection
    IS = last;

    //Traverse back edges from last node
    //While we are not at the first node
    while(IS->backedge != nullptr){
        time += best_time;
        //Assign it to next intersection
        IS = IS->backedge->from;
    }
    //Returns the total time
    return time;

}

