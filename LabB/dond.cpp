/*Audaris Blades
 * Dice or No Dice
 * Calculates Probablity*/

#include <vector>

using namespace std;

double sum(vector<double> p){
    double s = 0;
    for(int i = 0; i < p.size(); i++)
        s += p[i];

    return s;
};

int main(int argc, char *argv[]){
    double sides, turns, lastRoll;
        if(argc != 4)
            exit(1);

        sides = argv[1];
        //number of rolls left
        turns = argv[2];
        //last roll
        lastRoll = argv[3];

    vector<double> prob(sides, 0);

    //Initialize vector
    for(int i = 0; i < sides; i++){
        //edge probability
        if(i == 0 || i == sides -1)
            prob[i] = (s-2/s);
        else
            prob[i] = (s-3/s); // has a greater and lower value
    }

    //All rolls are legal
    if(turns == 1){
        //Edge case
        if(lastRoll == 0 || lastRoll == sides - 1)
            cout << s-2/s << endl;
        else if(lastRoll == -1)
            cout << 1;
        else{
            cout << s-3/s << endl;
        }
    }


    if(turns > 1){

        if(lastRoll != -1){

            prob[lastRoll] = 0;
            if(lastRoll == 0)
                prob[1] = 0;
            else if(lastRoll == sides -1)
                prob[sides-1] = 0;
            else{
                prob[lastRoll - 1] = 0;
                prob[lastRoll + 1] = 0;
            }
        }

        //Multiplies the probablity vector by the turn number
        for(int i = 1; i < turns ;i++){
            for(int j = 0; j < prob.size(); j++)
                prob[j] *= (1/sides);
        }
    }




}

/*class Dice{
    double s;
    vector< vector <double > > cache;
    double rc(int t, int last);
};


int main(int argc, char *argv[]){
    int t,lr;
    Dice d;

    if(argc != 4)
        exit(1);

        d.s = argv[1];
        //number of rolls left
        t = argv[2];
        //last roll
        lr = argv[3];

    return rc(t, lr);
  //  }
}
//calculate probabilities
double Dice::rc(int t, int last) {
    long long sum = 0;
  //Check if we've called rc before with values
    if(cache[t][last] != -1)
        return cache[t][last];


    //Probablity for one role left
    //Store in cache

    if(last == -1 || last == 0){
        for(int i = 0; i < s; i++)
            sum += rc(t-1,i);

        return sum;
    }


}

