// C++ 11
// 11027229 ���p�@�~
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
struct Node {
	int hp; // �ͩR�� 
	vector<int> index; // �ӥͩR�ȹ����쪺 index 
	Node * left; // ���`�I 
	Node * right; // �k�`�I 
	Node * parent; // ���`�I 
};

// �G���j�M��class 
class BST {
	// ���} 
	public:
		// �غc�l 
		BST(){
			head = NULL;
		}
		// �ǳƧ��Ʃ�i��̭� 
		input(vector<string> dataa, int i) {
			data.push_back(dataa);
			append(i);
		}
		
		// �z�Lindex��J��
		void append(int index) {
			// �𪺤@�}�l 
			if(head == NULL) {
				head = new Node;
				head -> hp = atoi(data[index][8].c_str()) ;
				head -> index.push_back(index);
				head -> right = NULL;
				head -> left = NULL;
				head -> parent = NULL;
				return;
			}
			// �}�l���l�`�I�� 
			innerAppend(head,index);
		}
		
		// �O���O�Ū� 
		bool isEmpty(){
			if(head==NULL) return true;
			else return false;
		}
		
		// �R������ 
		void deleteAll(){
			delete_tree(head);
			head = NULL;
			data.clear();
		}
		// ��X���X�h 
		int getLayer() {
			return height(head);
		}
		
		// �Y���@����ƳQ�R���A�`�I�W�� index �n��s 
		void minusIndex(Node * current, int i){
			if( current == NULL) return; 
			if(current -> right!= NULL) minusIndex(current -> right,i);
			for(int & dataa : current -> index ){
				if(dataa>i) dataa--;
			}
			if(current -> left != NULL) minusIndex(current -> left,i);
		}
		
	
		
		// debug �Ϊ� �L�X�Ҧ���� 
		void printAll(Node * current){
			if( current == NULL) return; 
			if(current -> right!= NULL) printAll(current -> right);
			for(int dataa : current -> index ){
				printf("%s\t%s\n",data[dataa][0].c_str(),data[dataa][3].c_str());
			}
			if(current -> left != NULL) printAll(current -> left);
		}
		
		// �����e�����Ʀr 
		void travelHigher(int height){
			Node * current = head;
			int nodes = 0;
			vector<vector<string> > answer; 
			innerTravel(head,height,nodes,answer);
			int i = 1;
			printf("\t#\tName\tType 1\tTotal\tHP\tAttack\tDefense\n");
			for(vector<string> vec:answer){
				printf("[%d]\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n",i,vec[0].c_str(),vec[1].c_str(),vec[2].c_str(),vec[6].c_str(),vec[3].c_str(),vec[4].c_str(),vec[5].c_str());
				i++;
			}
			printf("Number of Visited Nodes : %d\n",nodes);
		}
	private:
		Node * head;
		// int layer;
		vector<vector<string> > data;
		
		// �������X�C�Ӹ`�I 
		void innerTravel(Node * current, int h, int & nodes,vector<vector<string> > & answer){
			// �p�G�ONULL �N����RETURN 
			if(current == NULL) return;
			nodes++;
			
			// �����j��̥k�� 
			if(current -> right != NULL){
				innerTravel(current-> right, h, nodes,answer);
			}
			
			// �p�G�j�󵥩���e���� �N�O�Q�n�� 
			if(current -> hp >= h){
				for(int indexx: current -> index){
					answer.push_back(data[indexx]);
				}
			}
			
			// �p�G�{�b�� hp �p�󵥩���e�A�S�������`�I�a�����n �]������return 
			if(current -> hp <= h) return;
			
			// �p�G���䤣����NULL �A������a 
			if(current -> left != NULL){
				innerTravel(current-> left, h, nodes,answer);
			}
			// �n�ߺD�O�o�i�� 
			return;
		}
		
		// ����Append
		void innerAppend(Node * current, int index) {
			// �p�G�j�󪺸� 
			if(atoi(data[index][8].c_str())>current->hp) {
				// �p�G���`�I������ NULL ������ 
				if(current -> right != NULL) {
					innerAppend(current -> right, index);
				} 
				// �_�h�N�s�W�@�Ӹ`�I 
				else {
					current -> right = new Node;
					current -> right -> hp = atoi(data[index][8].c_str());
					current -> right -> index.push_back(index);
					current -> right -> right = NULL;
					current -> right -> left = NULL;
					current -> right -> parent = current;
				}
			} 
			// �p�G�۵����� �N PUSH BACK 
			else if (atoi(data[index][8].c_str())==current->hp){
				current -> index.push_back(index);
			} 
			// �p�G�p�󪺸� ��W�������I���� 
			else  {
				if(current -> left != NULL) {
					innerAppend(current -> left, index);
				} else {
					current -> left = new Node;
					current -> left -> hp = atoi(data[index][8].c_str());
					current -> left -> index.push_back(index);
					current -> left -> right = NULL;
					current -> left -> left = NULL;
					current -> left -> parent = current;
				}
			} 
		}
		// �p�Ⱚ�� 
		int height(Node * root){
			if (root == NULL) {
    			return 0; 
  			}
  			int left = height(root->left);  
  			int right = height(root->right);  
  			return 1 + max(left, right);  
		}
		void delete_tree(Node* root) {
  			if (root == nullptr) {
    			return;  // base case: empty tree has nothing to delete
  			}
  			delete_tree(root->left);  // delete left subtree
  			delete_tree(root->right);  // delete right subtree
  			delete root;  // delete root node
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
bool readData(BST & data, string dataName) {
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
		data.input(temp,i);
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
	int t;
	string fileName;
	BST bst;
	while(n!=0) {
		switch(n) {
			case 1:
				bst.deleteAll();
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(bst,fileName)) break;
				printf("%d\n",bst.getLayer());
				break;
			case 2:
				printf("�п�J�H��\n");
				t = getInt();
				
				break;
			
			default:
				printf("��J���~ �Э��s��J\n");
		}
		printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n");
		n = getInt(); // ���s���Ʀr
	}
	return 0; // �n�ߺD�O�o�i��
}
