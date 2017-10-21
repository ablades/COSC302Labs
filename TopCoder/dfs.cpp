nclude <string>
#include <vector>

using namespace std;

class Node{
		public:
					int pos;
							char val;
									Node *north;
											Node *south;
											        Node *east;
															Node *west;
																	bool visited = false;
};

class LandMines{
		public:
					vector<char> elements;
							int numClear(vector<string> layout);
									void createAdj(Node* cNode);
											int rows;
													int cols;
};
 
int LandMines::numClear(vector<string> layout){
	    stores string elements
		    cols = layout.size();
		        rows = layout[0].size();
		            for(int i = 0; i < layout.size(); i++){
							for(int j = 0; j <layout[i].size();j++)
										elements.push_back(layout[i][j]);
										    }
										        //Create initial Node with first element
										            Node *root = new Node();
										                root->pos = 0;
										                    root->val = elements[0];
		//								                        createAdj(root);
		//								                            
		//								                                //set links
		//								                                    
		//								                                        for(int i = 0; i < cols; i++){
		//																				for(int j = 0; j < rows; j++){
		//																							//Check North 
		//																							            //Check West
		//																							                        //Check South
		//																							                                    //Check East
		//																							                                                
		//																							                                                            
		//																							                                                                    }
		//																							                                                                        }
		//																							                                                                            return 0;
		//																							                                                                                
		//																							                                                                                }
		//																							                                                                                void LandMines::createAdj(Node *cNode){
		//																							                                                                                    //Create all connections between nodes
		//																																													//North Node
		//																																													     if(cNode->pos - cols > 0 && elements[cNode->pos - cols] != 'M'){
		//																																													             cNode->north = new Node();
		//																																													                     cNode->north->pos = cNode->pos - cols;
		//																																													                             cNode->north->val = elements[cNode->north->pos];
		//																																													                                     
		//																																													                                             createAdj(cNode->north);
		//																																													                                                 }
		//																																																												//South Node
		//																																																												     if(cNode->pos  + cols < elements.size() && elements[cNode->pos + cols] != 'M'){
		//																																																															cNode->south = new Node();
		//																																																															        cNode->south->pos = cNode->pos + cols;
		//																																																															                cNode->south->val = elements[cNode->south->pos];
		//																																																															                         
		//																																																																								createAdj(cNode->south);
		//																																																																								    }   
		//																																																																								            //West Node
		//																																																																								                if(cNode->pos - 1 > 0 && elements[cNode->pos - 1] != 'M'&& ((cNode->pos -1) % cols != 0)){
		//																																																																														cNode->west = new Node();
		//																																																																														        cNode->west->pos = cNode->pos - 1;
		//																																																																														                cNode->west->val = elements[cNode->west->pos];
		//																																																																														                        
		//																																																																														                                createAdj(cNode->west);
		//																																																																														                                    }
		//																																																																														                                        
		//																																																																														                                             //East Node
		//																																																																														                                                 if(cNode->pos + 1 < elements.size() && elements[cNode->pos + 1] != 'M' && ((cNode->pos + 1) % cols != rows)){
		//																																																																														                                                         cNode->east = new Node();
		//																																																																														                                                                 cNode->east->pos = cNode->pos + 1;
		//																																																																														                                                                         cNode->east->val = elements[cNode->east->pos];
		//																																																																														                                                                                 
		//																																																																														                                                                                         //Attempt to recurse on node
		//																																																																														                                                                                                 createAdj(cNode->east);
		//																																																																														                                                                                                     }
		//																																																																														                                                                                                     }
