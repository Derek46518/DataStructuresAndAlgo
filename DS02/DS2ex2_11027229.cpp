#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<cmath>
#include<ctype.h>
#include<algorithm>
using namespace std;


struct Node {
	Node * parent;
	vector<string> data;
	vector<vector<int> > ids;
	vector<Node *> children;
	int value;
	Node * left;
	Node * right;
	Node() {
		parent = NULL;
	}
	Node(int val, int id,Node* par) {
		parent = par;
		value = val;
		vector<int> temp;
		temp.push_back(id);
		ids.push_back(temp);
		left = NULL;
		right = NULL;
	}
	Node(string value, int id) {
		parent = NULL;
		data.push_back(value);
		vector<int> temp;
		temp.push_back(id);
		ids.push_back(temp);
	}
	Node(string value, vector<int> id,Node * par) {
		parent = par;
		data.push_back(value);
		ids.push_back(id);
	}
};

class Tree {
	public:
		virtual void insert(string value, int id) {}
		// �Ǹ� �B �ǮզW�� �B��t�W�١B��]�O�B���ŧO�B�W�Ǧ~�ײ��~�ͼ�
		void printLine(vector<vector<string> > originData, int index) {
			cout << "["<< originData[index][11]<<"] " <<originData[index][1] <<", "<<originData[index][3]<<", "<<originData[index][4]<<", "<<originData[index][5]<<", "<<originData[index][8]<<"\n";
		}
	protected:
		Node* root;
};
class TwoThreeTree:public Tree {
	private:
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
		void sortChildren(Node * node) {
			for(int i = 0 ; i < node->children.size(); i++) {
				for(int j = i; j < node-> children.size() ; j++) {
					if(node->children[i]->data[0]>node->children[j]->data[0]) {
						iter_swap(node->children.begin()+i,node->children.begin()+j);
					}
				}
			}
		}
		void split(Node * current) {
			if(current==NULL || current -> data.size() <= 2) return;
			Node * parent = current -> parent;
			Node * left = new Node(current->data[0],current->ids[0],parent);
			Node * right = new Node(current->data[2],current->ids[2],parent);
			string middleValue = current->data[1];
			vector<int> middleIds = current->ids[1];
			if (parent!=NULL) {
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
				parent->children.erase(parent->children.begin()+n);
				parent->data.push_back(middleValue);
				parent->ids.push_back(middleIds);
				sort(parent);
				parent->children.push_back(left);
				parent->children.push_back(right);
				sortChildren(parent);
			} else {
				parent = new Node(middleValue,middleIds,NULL);
				root = parent;
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

		void insertIntoNode(Node * node, string value, int id) {
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


	public:
		TwoThreeTree() {
			root = NULL;
		}
		void restore(vector<vector<string> > & originData) {
			root = NULL;
			originData.clear();
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
	int first, last; //�O���Ĥ@�Ӧ�m�M�ĤG��
	int i = 0; // �p��0
	vector<string> answer; // ����
	last = str.find(b); // ���h�M��b���Ӧ�m�n����
	first = 0;// �@�}�l
	// ��last�٨S�]�쵲������m
	while (last != string::npos) {
		// ��substring���Janswer
		answer.push_back(str.substr(first, last - first));
		// first����last�[�W���ξ����j�p
		first = last + b.size();
		// �A�~��M��U�ӭn���Ϊ��I
		last = str.find(b, first);
		i++;
	}
	// �p�Gfirst����m���O�̫�@�Ӧr�� �N��first�᭱�����e����answer�̭�
	if (first != str.length()) {
		answer.push_back(str.substr(first));
	}
	// �^��answer
	return answer;
}

// �[�W�ɮצW�٫e��
string addPrefix(string add, string s) {
	stringstream ss;
	ss << add;
	ss << s;
	ss << ".txt";
	return ss.str();
}

// Ū��
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
	// �}�lŪ�� �g�Jheap��
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
// ���o�ϥΪ̿�J��int
int getInt() {
	// ��Ū���
	string s;
	getline(cin,s);
	int total = 0; // total
	int a; // �Ȧs���Ʀr
	if(s.length()==0) return -1; // �p�G�ϥΪ̪������Uenter �N�^��-1(����main�ɷ|���ϥΪ̿�J���~)
	// string to integer
	for(int i = 0 ; i < s.length(); i++) {
		total *= 10;
		a = s[i] - '0';
		if (a < 0 || a > 9) return -1; // �p�G���b�d�� �N�^��-1 (����main�ɷ|���ϥΪ̿�J���~)
		total += a;
	}
	return total; //�N�Ȧ^�Ǧ^�h
}
int main() {
	vector<vector<string> > data;
	printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n");
	int n = getInt();
	string fileName;
	TwoThreeTree twoThreeTree;
	AVLTree avlTree;
	vector<vector<string> > originData;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(twoThreeTree,originData,fileName,true)) break;
				twoThreeTree.printRoot(originData);
				twoThreeTree.restore(originData);
				break;
			case 2:
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(avlTree,originData,fileName,false)) break;
				avlTree.printRoot(originData);
				avlTree.restore(originData);
				break;
			default:
				printf("��J���~ �Э��s��J\n");
		}
		printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n");
		n = getInt(); // ���s���Ʀr
	}
	return 0; // �n�ߺD�O�o�i��
}
