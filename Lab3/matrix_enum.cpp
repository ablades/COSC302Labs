/*Audaris Blades
Lab4
Matrix Enumeration - Calculate all permutations given arguments*/
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Matrix{
	public:
		int W;
		int E;
		char* P;
		vector<int> permutation;
		vector<int> Non_X;
		vector<int> E_ID;
		void Print();
		void Permute(int index);
		void Choose(int index);
};


void Matrix::Permute(int index){
	//Base Case - Final permutation reached.
	if(index == W){
		Non_X.clear();

		for(int row = 0; row < W; row++){
			for(int col = 0; col < W; col++){
				//Add Empty locations
				if(permutation[row] != col)
					Non_X.push_back(row * W + col);
			}
		}

		E_ID.clear();
		//Permutate on E's
		Choose(0);
	}

	for(int i = index; i < permutation.size(); i++){
		//swap current pointers
		swap(permutation[i], permutation[index]);
		//Permute on the swap
		Permute(index+1);
		//Return to orignal permutation
		swap(permutation[i], permutation[index]);
	}
}

void Matrix::Choose(int index){
	//Base Case 1 Maximum elements have been added
	if(E_ID.size() == E){
		Print();
		return;
	}

	//Base Case 2 Too many elements
	if(E - E_ID.size() > (Non_X.size() -  index)){
		return;
	}
	//Then the location in Non_X is valid so add it
	E_ID.push_back(Non_X[index]);

	//Find Next Permutation
	Choose(index + 1);
	//Reset
	E_ID.pop_back();
	//Find next permutation
	Choose(index + 1);
	
}

void Matrix::Print(){
	//Print in standard format
	if(*P == 'x'){
		for(int row = 0; row < W; row++){
			for(int col = 0; col < W; col++){
				
				if(permutation[row] == col)
					cout << 'X';
				else if(find(E_ID.begin(), E_ID.end(), (row * W + col)) != E_ID.end())
					cout << 'E';
				else
					cout << '.';
			}
			cout << endl;		
		}	
		cout << endl;
	}		

	//Print in numerical format
	if(*P == 'h'){
		int val = 0;
		for(int row = 0; row < W; row++){
			for(int col = 0; col < W; col++){
				//Is a X
				if(permutation[row] == col)
					val |= 1 << col;
				//Is an E
				else if(find(E_ID.begin(), E_ID.end(), (row * W + col)) != E_ID.end())
					val |= 1 << col;
			}
			cout << hex << val << endl; 	
			val = 0;		
		}	
		cout << endl;
	}
}


int main(int argc, char *argv[]){
	Matrix M;
	M.W = atoi(argv[1]);
	M.E = atoi(argv[2]);
	M.P = argv[3];

	//sets up intial permutation structure
	for(int i = 0; i < M.W; i++)
		M.permutation.push_back(i);

	M.Permute(0);
}