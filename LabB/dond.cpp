/*Audaris Blades
 * Dice or No Dice Calcuate the probablilty
*/
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

bool adj(int n, int m);

double dond(int sides, int rolls, int lastRoll, map <pair <int, int>, double> &cache) {

    double result = 0;

    pair <int, int> index(rolls, lastRoll);
    // Check the cache for value
    if(cache.count(index))
        return cache[index];

    // Base case.
    if (rolls == 0 || lastRoll == -1)
        return 1;



    // Sum of the probabilities
    for(int i = 0; i < sides; i++)
        if (!adj(i, lastRoll)){
            result += dond(sides, rolls - 1, i, cache);
           // cout << result << endl;
        }

    // Return prob
    return cache[index] = result / (double) sides;
}

int main(int argc, char** argv) {
    map <pair <int, int>, double> cache;
    int sides, rolls, lastRoll;

    //arg count check
    if (argc != 4)
        exit(-1);

    sides = atoi(argv[1]);
    rolls = atoi(argv[2]);
    lastRoll = atoi(argv[3]);
    cout << dond(sides, rolls, lastRoll, cache) << endl;

    return 0;
}

//Check adj
 bool adj(int n, int m) {
    return (n == m+1 || n == m || n+1 == m);
}