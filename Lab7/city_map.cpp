/*Audaris Blades
 * Lab 7
 * Dijkstra's Algorithm
 */

#include "city_map.h"
#include <map>
#include <vector>

City_Map::City_Map(){
    Intersection *IS;
    City_Map() *c = new City_Map;
    c->all.clear();

    double input;
    while(cin >> input){
        IS = new Intersection;
        IS->street = input;
        cin >> input;
        IS->avenue = input;
        cin >> input;
        IS->x = input;
        cin >> input;
        IS->y = input;
        cin >> input;
        IS->green[0] = input;
        cin >> input;
        IS->green[1] = input;
        c->all.push_back(&IS);
    }

}

double City_Map::Dijkstra(int avg_best_worst){
    return 0;
}
