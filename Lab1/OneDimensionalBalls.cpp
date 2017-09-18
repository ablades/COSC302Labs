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
		~OneDimensionalBalls(){
			for(map<int, Ball*>::iterator it = FPMAP.begin(); it!= FPMAP.end(); it++)
				delete it->second;

			for(map<int, Ball*>::iterator it = SPMAP.begin(); it!= SPMAP.end(); it++)
				delete it->second;

		};

		long countValidGuesses(vector<int>  firstPicture, vector<int>  secondPicture){
			long rv = 0;
			//Add Balls from firstPicture to FPMAP
			FPMAP.clear();
			SPMAP.clear();
			for(int i = 0; i < firstPicture.size(); i++){
				//Set Ball attributes
				Ball *b =  new Ball();
				b->matched = 0;
				b->val = firstPicture[i];
				b->low = NULL;
				b->high = NULL;
				b->isFP = true;
				b->inChain = false;
				FPMAP.insert(make_pair(b->val, b));
			}

			//Add Balls from secondPicture to SPMAP
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
				if(vel > 0)
					pVelcocities.insert(vel);
			}

			for(set<int>::iterator it = pVelcocities.begin(); it != pVelcocities.end(); it++)
				rv += cvg(*it);

			return rv;

		};

		long long cvg(int v){
			cout << "hello";
			//Set Ball Pointers in FP
			for(map<int, Ball*>::iterator it = FPMAP.begin(); it!= FPMAP.end(); it++){
				//ball in current iteration
				Ball *b = it->second;
				map<int, Ball*>::iterator lowIt = SPMAP.find(b->val - v);
				map<int, Ball*>::iterator highIt = SPMAP.find(b->val + v);
				//If there is an adjecent ball set its pointer
				if(lowIt != FPMAP.end())
					b->low = lowIt->second;

				if(highIt != FPMAP.end())
					b->high = highIt->second;
				
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

				if(highIt != SPMAP.end())
					b->high = highIt->second;
			}

			//Check Map for No Matches
			bool pMatch  = false;
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;
				//There are no matches if there are no pointers!
				if(b->low != NULL || b->high != NULL){
					pMatch = true;
					break;
				}
			}

			if(!pMatch)
				return 0;

				//Check all balls in FP again If any ball has 1 low or high only one way to match 
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;
				//There are no matches if there are no pointers!
				//Exclusive or check
				if((b->low == NULL) != (b->high == NULL)){
					b->matched = 1;
					//temp pointer points to child ball to change values;
					Ball *childBall = (b->low != NULL) ? (childBall = b->low) : (childBall = b->high);
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

			//Check for balls without match
			bool allMatched = true;
			//Check for
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;

				if((b->matched == 0) && (b->high == NULL) && (b->low == NULL)){
					cout << "no matches remaining";
					return 0;
				}
				
				
				if(b->matched == 0){
					allMatched = false;
					break;
				}

			}

			if(allMatched)
				return 1;
			long rv = 0;

			for_each(FPMAP.begin(), FPMAP.end(), [&] (std::pair<int, Ball*> pair) {
				if(pair.second->matched == 0 && pair.second->low != NULL || pair.second->high != NULL) {
					cout << "Ball in chain\n";
					rv++;
				}
			});
			//Count the length of the chains
			//long rv = 0;

			/*for(map<int, Ball*>::iterator it = FPMAP.begin(); it != FPMAP.end(); it++){
				Ball *b = it->second;
				long chainCount = 0;
				while(b->high != NULL && b->inChain == false){
					
					if(b->isFP == true){
						chainCount++;
						b->inChain = true;
					}

					b = b->high;
				}

				if(chainCount != 0){
					rv += 1;
					rv *= chainCount;
				}
			}*/
			return rv;

		};


};
