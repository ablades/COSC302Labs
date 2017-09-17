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
		FBMAP.insert(make_pair(FP[i], &cBall));
	}

	//Add Balls from secondPicture to SBMap
	for(int i = 0; i < SP.size(); i++){
		Ball *b;
		b->matched = 0;
		b->low = NULL;
		b->.high = NULL;
		SBMAP.insert(make_pair(SP[i], &cBall));
	}
	
	return 0;
};

long long cvg(int v){

	//Loop through FBMAP
	for(map<int, Ball*>::iterator it = FBMAP.begin(); it! = FBMAP.end(); it++){
		//Find  int -val and int +val in the current map
		//set low and high accourdingly
		Ball* b;
		b->it.second;
		b->low = (it.find(b.val - v)->second);
		b->high = (it.find(b.val + v)->second);
	}
};


int main(){
	return 0;
}
