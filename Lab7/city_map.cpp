/*Audaris Blades
 * Lab 7
 * Dijkstra's Algorithm
 */

#include "city_map.h"
#include <map>
#include <vector>
#include <iterator>

City_Map::City_Map(){
   // cout << "HERE";
    Intersection *IS;

    double x, y, gStr, gAve;
    int st, ave;
    int count = 0;
    int stmax, avemax;
    while(cin >> st){
        {
       // cout << count++;
        IS = new Intersection;
        //cout << "HERE";
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
    }
    //set initial size of temp vector
    vector< vector<Intersection *> > tmp(stmax +1, vector<Intersection *>(avemax+1));

    //Store contents of all into temp in proper position
        for(list<Intersection *>::iterator itr = all.begin(); itr !=  all.end(); itr++)
            tmp[(*itr)->street][(*itr)->avenue] = *itr;

    Road_Segment* rs;
    for(int i = 0; i < stmax; i++){
        for(int j = 0; j < avemax; i++){
            //Look Up
            if(i > 0 && (j % 5 == 0 || j % 2 != 0 || j == avemax)){
                rs = new Road_Segment;
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i-1][j];

                tmp[i][j]->adj.push_back(rs);
            }
            //Look Down
            if(i < stmax && (j % 2 == 0 || j % 5 == 0 || j == avemax)){
                rs = new Road_Segment;//create road segment
                rs->type = AVENUE;
                rs->number = j;
                rs->from = tmp[i][j];
                rs->to = tmp[i+1][j];

                tmp[i][j]->adj.push_back(rs);
            }
            //Look left
            if( j > 0 && (i % 5 == 0 || i % 2 != 0)){
                rs = new Road_Segment;
                rs->type = STREET;
                rs->number = i;
                rs->from = tmp[i][j];
                rs->to = tmp[i-1][j];

                tmp[i][j]->adj.push_back(rs);
            }
            //Look right
            if( j < avemax && (i % 5 == 0 || i % 2 == 0)){
                rs = new Road_Segment;
                rs->type = STREET;
                rs->number = i;
                rs->from = tmp[i][j];
                rs->to = tmp[i][j+1];

                tmp[i][j]->adj.push_back(rs);
            }
        }
    }


}

double City_Map::Dijkstra(int avg_best_worst){
    return 0;
}
