#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class Ball{
	public:
		int val;
		int matched;
		Ball *low;
		Ball *high;
};


//Easy iteration over balls
//Stores all balls in first picture
map<int, Ball*> FBMAP;
//Stores all balls in second picture
map<int, Ball*> SBMAP;

long long countValidGuesses(vector<int>  FP, vector<int>  SP){

	//Add Balls from firstPicture to FBMap
	for(int i = 0; i < FP.size(); i++){
		//Set Ball attributes
		Ball *b;
		b->matched = 0;
		b->low = NULL;
		b->high = NULL;
		FBMAP.insert(make_pair(FP[i], b));
	}

	//Add Balls from secondPicture to SBMap
	for(int i = 0; i < SP.size(); i++){
		Ball *b;
		b->matched = 0;
		b->low = NULL;
		b->high = NULL;
		SBMAP.insert(make_pair(SP[i], b));
	}
	
	return 0;
};

long long cvg(int v){

	//Loop through FBMAP and assign high and low values
	for(map<int, Ball*>::iterator it = FBMAP.begin(); it!= FBMAP.end(); it++){
		//ball in current iteration
		Ball *b = it->second;
		//Find adjecent by v elements low and high
		b->low = ((FBMAP.find(b->val - v))->second);
		b->high = ((FBMAP.find(b->val + v))->second);
	}

	
};




int main(){
	return 0;
};
