/*Lab2
Audaris Blades
BuildingAdvertise.cpp
*/
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

class BuildingAdvertise{
	public:
		long getMaxArea(int h[], int n){
				int R[n];
				//Sentinal
				R[0] = 0;
				int j = 0;
				int m = sizeof(h);
				for(int i = 1; i < n-1; i++){
					R[i] = h[j];
					int s = (j + 1) % m;
					h[j] = ((h[j] ^ h[s]) + 13) % 835454957;
					j = s;
				}
				//Sentinal
				R[n] = 0;
			//Stores height in key and indices in R in vals
			multimap<int,int> mm;
			for(int i = 0; i < sizeof(R);i++){
				mm.insert(pair<int,int>(R[i]), i);
			}
		};

};

int main(){};