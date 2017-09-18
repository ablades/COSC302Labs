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

	//Loop through FBMAP and assign high and low values to elements in SB
	for(map<int, Ball*>::iterator it = FBMAP.begin(); it!= FBMAP.end(); it++){
		//ball in current iteration
		Ball *b = it->second;
		//Find adjecent by v elements low and high
		b->low = ((SBMAP.find(b->val - v))->second);
		b->high = ((SBMAP.find(b->val + v))->second);
	}

	//Loop through FSBMAP and assign high and low values to elements in FB
	for(map<int, Ball*>::iterator it = SBMAP.begin(); it!= SBMAP.end(); it++){
		//ball in current iteration
		Ball *b = it->second;
		//Find adjecent by v elements low and high
		b->low = ((FBMAP.find(b->val - v))->second);
		b->high = ((FBMAP.find(b->val + v))->second);
	}

	//Check all balls in FP If no valid low or high pointer return zero (no guesses)
	for(map<int, Ball*>::iterator it = FBMAP.begin();it != FBMAP.end();it++){
		Ball *b = it->second;
		//There are no matches if there are no pointers!
		if(b->low == NULL && b->high == NULL)
			return 0;

	}	//Check all balls in FP again If any ball has 1 low or high only one way to match 
	for(map<int, Ball*>::iterator it = FBMAP.begin();it != FBMAP.end();it++){
		Ball *b = it->second;
		//There are no matches if there are no pointers!
		//Exclusive or check
		if((b->low == NULL) != (b->high == NULL)){
			b->matched = 1;
			//temp pointer points to child ball to change values;
			Ball *childBall;
			if(b->low != NULL)
				childBall = b->low;
			else
				childBall = b->high;

			childBall->matched = 1;

			//set proper high/lowpointer
			if(childBall->val < b->val)
				childBall->low = NULL;
			else
				childBall->high = NULL;

			//Dereference the childBall
			childBall = NULL;



		}
	}

	//set matched filed that it point to in sb to 1 set appropriate low and high to null for each ball

};




int main(){
	return 0;
};
