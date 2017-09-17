#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

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
map<int Ball*> SBMAP

long countValidGuesses(vector<int>  FP, vector<int>  SP){
	
	//Add Balls from firstPicture to FBMap
	for(int i = 0; i < FP.size(); i++){
		//Set Ball attributes
		Ball cBall;
		cBall.matched = 0;
		cBall.low->NULL;
		cBall.high->NULL;
		FBMAP.insert(make_pair(FP[i], &cBall);
	}

	//Add Balls from secondPicture to SBMap
	for(int i = 0; i < SP.size(); i++){
		Ball cBall;
		SBMAP.insert(make_pair(SP[i], &cBall);
	}

	
};
