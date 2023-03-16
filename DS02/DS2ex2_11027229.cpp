#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<cmath>
#include<ctype.h>
#include<algorithm>
using namespace std;

// The Node of all Trees
struct Node {
	Node * parent; // The pointer pointed to the parent
	vector<string> data; // Use to save data
	vector<vector<int> > ids; // Use to save ids corresponding the data
	vector<Node *> children; // Use to save children corresponding the node
	int value; 
	Node * left; // left pointer
	Node * right; // right pointer
	// Constructor without any args
	Node() {
		parent = NULL;
	}
	// Constructor when AVL Tree
	Node(int val, int id,Node* par) {
		parent = par;
		value = val;
		vector<int> temp;
		temp.push_back(id);
		ids.push_back(temp);
		left = NULL;
		right = NULL;
	}
	// Constructor when 2-3 tree without parent
	Node(string value, int id) {
		parent = NULL;
		data.push_back(value);
		vector<int> temp;
		temp.push_back(id);
		ids.push_back(temp);
	}
	// Constructor when 2-3 tree with parent
	Node(string value, vector<int> id,Node * par) {
		parent = par;
		data.push_back(value);
		ids.push_back(id);
	}
};

// Virtual class
class Tree {
	public:
		virtual void insert(string value, int id) {}
		// 序號 、 學校名稱 、科系名稱、日夜別、等級別、上學年度畢業生數
		void printLine(vector<vector<string> > originData, int index) {
			cout << "["<< originData[index][11]<<"] " <<originData[index][1] <<", "<<originData[index][3]<<", "<<originData[index][4]<<", "<<originData[index][5]<<", "<<originData[index][8]<<"\n";
		}
	protected:
		Node* root;
};

/**
This class is used to construct 2-3 tree
The logic can be searched online

*/
class TwoThreeTree:public Tree {
	private:
		/**
		Sort the data and id by string value inside the node
		@param node : the node to sort
		*/
		void sort(Node * node) {
			for(int i = 0 ; i < node -> data.size(); i++) {
				for(int j = i; j < node-> data.size() ; j++) {
					if(node->data[i]>node->data[j]) {
						swap(node->data[i],node->data[j]);
						swap(node->ids[i],node->ids[j]);
					}
				}
			}
		}
		/**
		Sort children of a node
		@param node: the node to sort
		*/
		void sortChildren(Node * node) {
			for(int i = 0 ; i < node->children.size(); i++) {
				for(int j = i; j < node-> children.size() ; j++) {
					if(node->children[i]->data[0]>node->children[j]->data[0]) {
						iter_swap(node->children.begin()+i,node->children.begin()+j);
					}
				}
			}
		}
		
		/**
		Split the node into two parts, and push the middle data into parent
		@param current : The node that needs to split
		*/
		void split(Node * current) {
			// no need to split, return
			if(current==NULL || current -> data.size() <= 2) return;
			Node * parent = current -> parent; // Get Parent
			Node * left = new Node(current->data[0],current->ids[0],parent); // create new left node
			Node * right = new Node(current->data[2],current->ids[2],parent); // create new right node
			string middleValue = current->data[1]; // get middle value used to push up
			vector<int> middleIds = current->ids[1]; // get middle id used to push up
			// if is leaf
			if (parent!=NULL) {
				// get node position and save in n
				int n = parent -> children.size()-1; 
				while(current!=parent->children[n]) {
					n--;
				}
				// special case
				if(current->children.size()==4&&current->data.size()==3) {
					current->children[0]->parent = left;
					current->children[1]->parent = left;
					left->children.push_back(current->children[0]);
					left->children.push_back(current->children[1]);
					current->children[2]->parent = right;
					current->children[3]->parent = right;
					right->children.push_back(current->children[2]);
					right->children.push_back(current->children[3]);
				}
				// spliting
				parent->children.erase(parent->children.begin()+n);
				parent->data.push_back(middleValue);
				parent->ids.push_back(middleIds);
				sort(parent);
				parent->children.push_back(left);
				parent->children.push_back(right);
				sortChildren(parent);
			} 
			// if node is root
			else { 
				parent = new Node(middleValue,middleIds,NULL);
				root = parent;
				// need to split node
				if(current->children.size()!=0) {
					current->children[0]->parent = left;
					current->children[1]->parent = left;
					left->children.push_back(current->children[0]);
					left->children.push_back(current->children[1]);
					current->children[2]->parent = right;
					current->children[3]->parent = right;
					right->children.push_back(current->children[2]);
					right->children.push_back(current->children[3]);
				}
				left->parent = parent;
				right->parent = parent;
				parent->children.push_back(left);
				parent->children.push_back(right);
				sortChildren(parent);
			}
			if(parent->data.size()==3) split(parent);
		}
		
		// insert the data into node
		void insertIntoNode(Node * node, string value, int id) {
			// check if data is equal, if is equal, push id
			for(int i = 0 ; i< node->data.size(); i++) {
				if(value == node->data[i]) {
					// printf("equal\n");
					node->ids[i].push_back(id);
					return;
				}
			}

			node->data.push_back(value);
			vector<int> temp;
			temp.push_back(id);
			node->ids.push_back(temp);
			sort(node);
			if (node->data.size() == 3) {
				split(node);
			}
		}
		/**
		Find place to insert node
		@param current : Current Node
		@param value : the value to input
		*/
		Node * findInsertionNode(Node * current, string value) {
			if (current->children.size()==0) return current; // leaf node
			for(int i = 0 ; i < current->data.size(); i++) {
				if(value==current->data[i]) return current;
			}
			if(value<current->data[0]) return findInsertionNode(current->children[0],value);
			else if (current->data.size()==1) return findInsertionNode(current->children[1],value);
			else if (value<current->data[1]) return findInsertionNode(current->children[1],value);
			else return findInsertionNode(current->children[2],value);
		}
		
		/**
		Get the height of the tree
		@param node : current node
		*/
		int getHeight(Node* node) {
			if (node == NULL) {
				return 0;
			}
			int maxHeight = 0;
			for (int i = 0; i < node->children.size(); i++) {
				int height = getHeight(node->children[i]);
				if (height > maxHeight) {
					maxHeight = height;
				}
			}
			return maxHeight + 1;
		}
		
		void restore(Node * current){
			for(Node * a : current->children){
				restore(a);
			}
			
			delete current;
		}

	public:
		TwoThreeTree() {
			root = NULL;
		}
		void restore(vector<vector<string> > & originData) {
			restore(root);
			originData.clear();
			root = NULL;
		}
		int countNodes(Node * node) {
			if (node == NULL) {
				return 0;
			}
			int count = 1;
			for (int i = 0; i < node->children.size(); i++) {
				count += countNodes(node->children[i]);
			}
			return count;
		}
		
		void insert(string value, int id) {
			if (root == NULL) {
				root = new Node(value, id);
				return;
			}
			Node * node = findInsertionNode(root, value);
			insertIntoNode(node, value, id);
		}
		/**
		Print Root
		@param the original data
		*/
		void printRoot(vector<vector<string> > &originData ) {
			printf("Tree height = %d\n",getHeight(root));
			printf("Number of nodes = %d\n",countNodes(root));
			vector<int> first = root->ids[0];
			vector<int> second;
			if(root->ids.size()==2) second = root->ids[1];
			int firstId = 0;
			int secondId = 0;
			int i = 1;
			while(firstId<first.size()||secondId<second.size()) {
				cout << i<< ": ";
				if(firstId<first.size()&&secondId<second.size()) {
					if(first[firstId]<second[secondId]) {
						printLine(originData,first[firstId]);
						firstId++;
					} else {
						printLine(originData,second[secondId]);
						secondId++;
					}
				} else if(firstId<first.size()&&secondId>=second.size()) {
					printLine(originData,first[firstId]);
					firstId++;
				} else {
					printLine(originData,second[secondId]);
					secondId++;
				}
				i++;
			}
		}
};

/**
This class is to build AVLTree
Logic can be searched online
*/
class AVLTree:public Tree {
	public:
		AVLTree(){
			root = NULL;
		}
		void insert(string value,int id) {
			value.erase(remove_if(value.begin(),value.end(),static_cast<int(*)(int)>(&ispunct)),value.end());
			value.erase(remove(value.begin(),value.end(),','),value.end());
			root = insert(root,stoi(value),id,NULL);
		}
		
		void printRoot(vector<vector<string> > & originData) {
			printf("Tree height = %d\n",height(root));
			printf("Number of nodes = %d\n",numNodes(root));
			int i = 1;
			// printLine(vector<vector<string> > originData, int index)
			for(int n: root->ids[0]) {
				printf("%d: ",i);
				printLine(originData,n);
				i++;
			}
		}
		void restore(vector<vector<string> > & originData) {
			root = NULL;
			originData.clear();
		}
	private:
		int numNodes(Node* cur){
			if(cur==NULL) return 0;
			else return 1+numNodes(cur->left)+numNodes(cur->right);
		}
		Node* insert(Node* node,int value,int id, Node* parent) {
			if(node==NULL) {
				return new Node(value,id,parent);
			}

			if(node->value==value) {
				node->ids[0].push_back(id);
				return node;
			}

			if(value<node->value) {
				node->left = insert(node->left,value,id,node);
			} 
			else {
				node->right = insert(node->right,value,id,node);
			}
			int balance = getBalance(node);

			if (balance > 1 && value < node->left->value) return rightRotate(node);
			if (balance < -1 && value > node->right->value) return leftRotate(node);
			// Left Right Case
			if (balance > 1 && value > node->left->value) {
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}

			// Right Left Case
			if (balance < -1 && value < node->right->value) {
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			
			return node;
		}
		// right rotate
		Node* rightRotate(Node * y) {
			Node *x = y->left;
			Node *T2 = x->right;
			// Perform rotation
			x->right = y;
			y->left = T2;
			// Return new root
			return x;

		}
		Node *leftRotate(Node *x) {
			Node *y = x->right;
			Node *T2 = y->left;

			// Perform rotation
			y->left = x;
			x->right = T2;

			// Return new root
			return y;
		}
		// Get Balance factor of node N
		int getBalance(Node *N) {
			if (N == NULL) return 0;
			return height(N->left) - height(N->right);
		}
		int height(Node* current) {
			if(current==NULL) return 0;
			else return 1+ max(height(current->left),height(current->right));
		}

};

vector<string> split(string &str, string &b) {
	int first, last; //記錄第一個位置和第二個
	int i = 0; // 計數0
	vector<string> answer; // 答案
	last = str.find(b); // 先去尋找在哪個位置要分割
	first = 0;// 一開始
	// 當last還沒跑到結束的位置
	while (last != string::npos) {
		// 把substring推入answer
		answer.push_back(str.substr(first, last - first));
		// first移到last加上分割器的大小
		first = last + b.size();
		// 再繼續尋找下個要分割的點
		last = str.find(b, first);
		i++;
	}
	// 如果first的位置不是最後一個字元 就把first後面的內容推到answer裡面
	if (first != str.length()) {
		answer.push_back(str.substr(first));
	}
	// 回傳answer
	return answer;
}

// 加上檔案名稱前綴
string addPrefix(string add, string s) {
	stringstream ss;
	ss << add;
	ss << s;
	ss << ".txt";
	return ss.str();
}

// 讀檔
bool readData(Tree & data, vector<vector<string> > & originData, string dataName,bool isTwoThree) {
	if(dataName.size()==3) dataName = addPrefix("input",dataName);
	ifstream ifs;
	string line;
	ifs.open(dataName);
	if(!ifs.is_open()) {
		printf("No file\n");
		return false;
	}
	for(int i = 0 ; i < 3 ; i++) {
		getline(ifs,line);
	}
	vector<string> temp;
	string sp = "\t";
	// 開始讀黨 寫入heap內
	int i = 0;
	while(getline(ifs,line)) {
		temp = split(line,sp);
		temp.push_back(to_string(i+1));
		
		if(isTwoThree)data.insert(temp[1],i);
		
		else data.insert(temp[8],i);
		
		originData.push_back(temp);
		i++;
	}
	ifs.close();
	return true;
}
// 取得使用者輸入的int
int getInt() {
	// 先讀整行
	string s;
	getline(cin,s);
	int total = 0; // total
	int a; // 暫存的數字
	if(s.length()==0) return -1; // 如果使用者直接按下enter 就回傳-1(執行main時會報使用者輸入錯誤)
	// string to integer
	for(int i = 0 ; i < s.length(); i++) {
		total *= 10;
		a = s[i] - '0';
		if (a < 0 || a > 9) return -1; // 如果不在範圍內 就回傳-1 (執行main時會報使用者輸入錯誤)
		total += a;
	}
	return total; //將值回傳回去
}
int main() {
	vector<vector<string> > data;
	printf("請輸入:\n0:退出\n1:建立23樹\n2:建立AVL Tree\n");
	int n = getInt();
	string fileName;
	TwoThreeTree twoThreeTree;
	AVLTree avlTree;
	vector<vector<string> > originData;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("請輸入檔案名稱\n");
				getline(cin,fileName);
				if(!readData(twoThreeTree,originData,fileName,true)) break;
				twoThreeTree.printRoot(originData);
				twoThreeTree.restore(originData);
				break;
			case 2:
				printf("請輸入檔案名稱\n");
				getline(cin,fileName);
				if(!readData(avlTree,originData,fileName,false)) break;
				avlTree.printRoot(originData);
				avlTree.restore(originData);
				break;
			default:
				printf("輸入錯誤 請重新輸入\n");
		}
		printf("請輸入:\n0:退出\n1:建立23樹\n2:建立AVL Tree\n");
		n = getInt(); // 重新取數字
	}
	return 0; // 好習慣記得養成
}
