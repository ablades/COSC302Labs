/*Audaris Blades
Lab3
Matrix Enumeration*/
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
class Matrix{
	public:
		int W; //Matrix Rows/Cols
		int E; // Extra NonZero entrires
		int P;
		vector<int> permutation;
		vector<int> Non_X;
		vector<int> E_ID;
		void Print();
		void Permute(int index);
		void Choose(int index);
};


void Matrix::Permute(int index){
	//BaseCase
	//If we've reached the final possible permutation we print it
	if(index == W){
		//Print permutation here
		//Clear and calculate
		Non_X.clear();
		for(int row = 0; row < permutation.size(); row++){
			for(int col = 0; col < W-1; col++){
				//if there isnt a value in that column we can add it!
				if(permutation[row] != col)
					Non_X.push_back(row * W + col);
			}
		}

		E_ID.clear();
		Choose(0);
	}

	//Creates all possible permutations
	for(int i = index; i < permutation.size(); i++){
		//swap current pointers
		swap(permutation[i], permutation[index]);
		//Permute on the swap
		Permute(index+1);
		//Return to orignal permutation so next permutation can be made based off original permutation
		swap(permutation[i], permutation[index]);
	}
}

void Matrix::Choose(int index){

	//Base Case 1
	//If all E's have been added print!
	if(E_ID.size() == E){
		Print();
		return;
	}

	//Base Case 2 If there are more E's than we can fit not possible so return!
	if(E_ID.size() > (Non_X.size() - index))
		return;
	//Then the location in Non_X is valid so add it
	E_ID.push_back(Non_X[index]);
	//Find Next Permutation
	Choose(index+1);
	//Reset
	E_ID.pop_back();
	//Find next permutation
	Choose(index+1);
}

void Matrix::Print(){
	//Print in normal format;
	if(P == 'x'){
		for(int row = 0; row < permutation.size(); row++){
			for(int col = 0; col < W-1; col++){
				
				if(permutation[col] == col)
					cout << 'X';
				else if(E_ID[col] == (row * W + col))
					cout << 'E';
				else
					cout << '.';
			}
			cout << endl;
		}
	}
	//Print in numerical format
	if(P == 'h'){
		int sum = 0;
		for(int row = 0; row < permutation.size(); row++){
			for(int col = 0; col < W-1; col++){
				if(permutation[col] == col)
					sum += 1 + col;
				else if(E_ID[col] == (row * W + col))
					sum += 1 + col;
			}
		cout << sum <<endl;
		sum = 0;
		}
	}
}


int main(int argc, char *argv[4]){
	if(argc != 4)
		cerr << "Wrong Input";
		Matrix M;
	//dimensions of matrix
	M.W = atoi(argv[1]);
	//Number of E's to be inserted into permutations
	M.E = atoi(argv[2]);
	//Print format of the permutations
	M.P = atoi(argv[3]);
	//changes the size of the permutation vector to match
	M.permutation.resize(M.W);
	//sets up intial permutation structure
	for(int i = 0; i < M.permutation.size(); i++)
		M.permutation[i] = i;
	//Begins the permutations
	M.Permute(0);

}