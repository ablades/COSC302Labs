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

class OneDimensionalBalls{
	public:
		//Easy iteration over balls
		//Stores all balls in first picture
		map<int, Ball*> FPMAP;
		//Stores all balls in second picture
		map<int, Ball*> SPMAP;

		long long countValidGuesses(vector<int>  FP, vector<int>  SP){

			//Add Balls from firstPicture to FPMAP
			for(int i = 0; i < FP.size(); i++){
				//Set Ball attributes
				Ball *b;
				b->matched = 0;
				b->low = NULL;
				b->high = NULL;
				FPMAP.insert(make_pair(FP[i], b));
			}

			//Add Balls from secondPicture to SPMAP
			for(int i = 0; i < SP.size(); i++){
				Ball *b;
				b->matched = 0;
				b->low = NULL;
				b->high = NULL;
				SPMAP.insert(make_pair(SP[i], b));
			}	
			
			return 0;
		};

		long long cvg(int v){

			//Loop through FPMAP and assign high and low values to elements in SB
			for(map<int, Ball*>::iterator it = FPMAP.begin(); it!= FPMAP.end(); it++){
				//ball in current iteration
				Ball *b = it->second;
				map<int, Ball*>::iterator lowIt = SPMAP.find(b->val - v);
				map<int, Ball*>::iterator highIt = SPMAP.find(b->val - v);
				//If there is an adjecent ball set its pointer
				if(lowIt != FPMAP.end())
					b->low = lowIt->second;

				if(highIt != FPMAP.end())
					b->high = highIt->second;
				
			}

			//Loop through FSPMAP and assign high and low values to elements in FB
			for(map<int, Ball*>::iterator it = SPMAP.begin(); it!= SPMAP.end(); it++){
				//ball in current iteration
				Ball *b = it->second;
				map<int, Ball*>::iterator lowIt = FPMAP.find(b->val - v);
				map<int, Ball*>::iterator highIt = FPMAP.find(b->val - v);
				//If there is an adjecent ball set its pointer
				if(lowIt != SPMAP.end())
					b->low = lowIt->second;

				if(highIt != SPMAP.end())
					b->high = highIt->second;
			}

			//Check all balls in FP If no valid low or high pointer return zero (no guesses)
			for(map<int, Ball*>::iterator it = FPMAP.begin();it != FPMAP.end();it++){
				Ball *b = it->second;
				//There are no matches if there are no pointers!
				if(b->low == NULL && b->high == NULL)
					return 0;

			}	//Check all balls in FP again If any ball has 1 low or high only one way to match 
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

			//set matched filed that it point to in sb to 1 set appropriate low and high to null for each ball

		};


		int countChains(){


		};

};

int main(){

};