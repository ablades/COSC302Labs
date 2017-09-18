#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;
class Ball{
	public:
		int val;
		int matched;
		Ball *low;
		Ball *high;
		bool isFP;
		bool inChain;
};

class OneDimensionalBalls{
	public:
		//Easy iteration over balls
		//Stores all balls in first picture
		map<int, Ball*> FPMAP;
		//Stores all balls in second picture
		map<int, Ball*> SPMAP;
	

		long countValidGuesses(vector<int>  firstPicture, vector<int>  secondPicture){
			long rv = 0;
			//reset maps
			FPMAP.clear();
			SPMAP.clear();
			//Set ball attributes. Add to firstmap
			for(int i = 0; i < firstPicture.size(); i++){
				
				Ball *b =  new Ball();
				b->matched = 0;
				b->val = firstPicture[i];
				b->low = NULL;
				b->high = NULL;
				b->isFP = true;
				b->inChain = false;
				FPMAP.insert(make_pair(b->val, b));
				//cout << FPMAP.
			}

			//Set ball attributes. Add to secondmap.
			for(int i = 0; i < secondPicture.size(); i++){
				Ball *b = new Ball();
				b->matched = 0;
				b->val = secondPicture[i];
				b->low = NULL;
				b->high = NULL;
				b->isFP = false;
				b->inChain = false;
				SPMAP.insert(make_pair(b->val, b));
			}	
			
			//Sort potential Velocity values for the set
			set<int> pVelcocities;
			for(int i = 0; i < secondPicture.size(); i++){
				int vel = secondPicture[i] - firstPicture[0];
				vel = abs(vel);
				
				if(vel != 0)
					pVelcocities.insert(vel);
			}

			for(set<int>::iterator it = pVelcocities.begin(); it != pVelcocities.end(); it++)
				rv += cvg(*it);

			return rv;

		};

		long long cvg(int v){
			//cout << "hello";
			long rv = 0;
			//Set Ball Pointers in FP
			for(map<int, Ball*>::iterator it = FPMAP.begin(); it!= FPMAP.end(); it++){
				//ball in current iteration
				Ball *b = it->second;
				//cout << b->val;
				map<int, Ball*>::iterator lowIt = SPMAP.find(b->val - v);
				map<int, Ball*>::iterator highIt = SPMAP.find(b->val + v);
				//If there is an adjecent ball set its pointer
				if(lowIt != FPMAP.end())
					b->low = lowIt->second;
				else
					b->low = NULL;

				if(highIt != FPMAP.end())
					b->high = highIt->second;
				else 
					b->low = NULL;
				
			}

			//Set Ball Pointers in SP
			for(map<int, Ball*>::iterator it = SPMAP.begin(); it!= SPMAP.end(); it++){
				//ball in current iteration
				Ball *b = it->second;
				map<int, Ball*>::iterator lowIt = FPMAP.find(b->val - v);
				map<int, Ball*>::iterator highIt = FPMAP.find(b->val + v);

				//If there is an adjecent ball set its pointer
				if(lowIt != SPMAP.end())
					b->low = lowIt->second;
				else
					b->low = NULL;

				if(highIt != SPMAP.end())
					b->high = highIt->second;
				else
					b->high = NULL;
			}

			//Check Map for No Matches
			bool pMatch = false;

			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;
				//There are no matches if there are no pointers!
				if(b->low != NULL || b->high != NULL)
					pMatch = true;
			}

			if(pMatch == false)
				return rv;

				//Check all balls in FP again If any ball has 1 low or high only one way to match 
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;
				//There are no matches if there are no pointers!
				//Exclusive or check
				if((b->low == NULL) ^ (b->high == NULL)){
					b->matched = 1;
					//temp pointer points to child ball to change values;
					Ball *childBall = (b->low != NULL) ? (childBall = b->low) : (childBall = b->high);
					childBall->matched = 1;

					//set proper high/lowpointer
					if(childBall->val < b->val){
						childBall->low = NULL;
						b->high = NULL;
						if(b->low != NULL){
							b->low->high = NULL;
							b->low = NULL;
						}
					}
					else{
						childBall->high = NULL;
						b->low = NULL;
						if(b->high != NULL){
							b->high->low = NULL;
							b->high = NULL;
						}
					}
				}
			}

			//Check for balls without match
			bool allMatched = true;
			//Check for
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;

				if((b->matched == 0) && (b->high == NULL) && (b->low == NULL)){
					//cout << "no matches remaining";
					return rv;
				}
				
				
				if(b->matched == 0){
					allMatched = false;
				}

			}

			if(allMatched)
				return rv++;

			
			
			//Count the length of the chains
			//long rv = 0;

			for(map<int, Ball*>::iterator it = FPMAP.begin(); it != FPMAP.end(); it++){
				Ball *b = it->second;
				if((b->matched == 0) && (b->low != NULL || b->high != NULL))
					rv++;
			}
			return rv;

		};


};
