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
       }
    }
}

double City_Map::Dijkstra(int avg_best_worst){
    first->best_time = 0;
    bfsq.insert(make_pair(0, first));
    bool flag = false;
    //Queue
    while(bfsq.size()){
        Intersection * IS;
        Road_Segment * rs;
       // int waitTime = 0;

        IS = bfsq.begin()->second;
      //  IS->bfsq_ptr = bfsq.begin();
        //Remove node from queue
        bfsq.erase(bfsq.begin());

     //   IS->best_time = 0;

        //loop through adj list
        for(list<class Road_Segment *>::iterator itr = IS->adj.begin(); itr != IS->adj.end(); itr++){
            rs = *itr;
            int red = rs->to->green[1];
            int green = rs->to->green[0];
            int smallestDelay;
            int waitTime = 0;
            double newTime = 0;

            //If intersection has been visited it will have a best time
            //cout << rs->to->best_time << "Best Time" << endl;
         //   if(rs->to->best_time != -1)
           //     continue;

           /* if(red < green)
                smallestDelay = red;
            else
                smallestDelay = green;*/


                //Average Case
          /*  if(avg_best_worst == 'A'){

                if(rs->type == STREET)
                    waitTime = pow(red,2)/(2*(green + red));
                else if(rs->type == AVENUE)
                    waitTime = pow(green, 2)/(2*(green + red));
            }
                //Worst Case
            if(avg_best_worst == 'W'){

                if(rs->type == STREET)
                    waitTime = rs->to->green[1];
                else if(rs->type == AVENUE)
                    waitTime = rs->to->green[0];
            }*/

            //cout << "Current Time" << curTime  << endl;





            //time to next intersection


                newTime += (rs->distance / 30 * 3600)  + IS->best_time + waitTime;
           // cout << "Travel Time" << travelTime <<endl;
            //Remove and add to path
            if(rs->to->best_time == -1 || newTime < rs->to->best_time ){
            /*&& waitTime <= smallestDelay*/
                if(rs->to->best_time == -1)
                    rs->to->best_time += 1;

                //If the best time is in the intersection remove it and insert next best time
              //  if(rs->to->best_time != -1){
                   for(multimap<double, Intersection *>::iterator it = bfsq.begin(); it != bfsq.end(); it++){
                        if(it->second == rs->to ){
                          //  cout << "Here";
                            bfsq.erase(it);
                        }
                    }


             //   cout << rs->to->best_time << endl;
                rs->to->best_time = newTime;
               // cout << rs->to->best_time << endl;
                rs->to->backedge = rs;
                bfsq.insert(make_pair(rs->to->best_time , rs->to));
            }
        }
    }

    double time = 0;
    //Start at last intersection


    //Traverse back edges from last node
    Road_Segment* p;
    p = last->backedge;

    while(p != NULL){
        path.push_front(p);
        p = p->from->backedge;
    }
   // cout << path.size();
    for(list<class Road_Segment *>::iterator itr = path.begin(); itr != path.end(); itr++){
        time += (*itr)->to->best_time;
    }

    //Returns the total time
    return time;

}

