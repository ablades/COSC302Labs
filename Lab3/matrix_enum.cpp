/*Audaris Blades
Lab3
Matrix Enumeration*/

class Matrix{
	public:
		int W;
		int E;
		int P;
		vector<int> permutation;
		vector<int> Non_X;
		vector<int> E_ID;
		void Print();
		void Permute(int index);
		void Choose(int index);
};


void Matrix::Permute(int index){
	int i;
	int temp;
	//BaseCase
	//If we've reached the final possible permutation we print it
	if(index == permutation.size()){
		cout << permutation[0];

		for(i = 1; i < permutation.size(); i++)
			cout << " " << permutation[i];
		cout << endl;
		return;

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


int main(int argc, char *argv[3]){
	//Program name
	argv[0]
	//dimensions of matrix
	argv[1]
	//print format
	argv[2]
}