/*Audaris Blades
Lab3
Matrix Enumeration*/

class Matrix{
	public:
		int W;
		int E;
		int P;
		vector<int> Perm;
		vector<int> Non_X;
		vector<int> E_ID;
		void Print();
		void Permute(int index);
		void Choose(int index);
}