// C++ 11
// 11027229 & 11027232���p�@�~ 
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
// Node �� struct 
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
		input(vector<vector<string> > d) {
			data = d; // ��qmainŪ�쪺��Ʃ�Jdata�̭� 
			
			// �v�@��J�� 
			for(int i = 0 ; i < data.size(); i++) {
				append(i);
			}
		}
		
		// �z�Lindex��J��
		void append(int index) {
			// �𪺤@�}�l 
			if(head == NULL) {
				head = new Node;
				head -> hp = atoi(data[index][3].c_str()) ;
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
		
		// �R���̤j���� 
		int deleteLargest(){
			// �Ncurrent�]�w���Y����m 
			Node * current = head;
			if (head == NULL) return INT_MIN;
			int n;
			// ����̥k�� 
			while(current -> right != NULL) current = current -> right;
			// ���o�̥k�䪺�̤j������ 
			n = current -> index[0];
			current->index.erase(current->index.begin());
			// ��sindex 
			minusIndex(head,n);
			// ��Ӹ�ƧR�F 
			data.erase(data.begin()+n);
			// �p�G�Ӹ`�I�W���S��� �N��i�H�R�F 
			if(current -> index.size()==0){
				// �p�G�`�I�O�Y 
				if(current == head){
					// �p�G����S�F�� �N��u�ѤU�Y�F �]���o�ʾ�w�g�S�F 
					if(head -> left ==NULL){
						head = NULL;
						return n;
					}
					// �N�Y�]���Y������ �åB�R�����쥻���Y 
					head = head -> left;
					head -> parent = NULL; 
					delete current;
					return n;
				}
				// �p�G�{�b�o�Ӹ`�I�����䤣�ONULL���� 
				if(current -> left != NULL){
					// �N�W�@�Ӹ`�I���k��]���{�b������ 
					current -> parent -> right = current -> left;
					// ��s���`�I�����`�I 
					current -> left -> parent = current -> parent;
					// �R���Ӹ`�I 
					delete current;
					return n;
				}
				// �_�h�Ӹ`�I�N�i�H�R���F 
				else {
					// �_�}�s�� 
					current -> parent -> right = NULL;
					// �R�� 
					delete current;
					
					return n;
				}
			}

			return n;
			
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
			if(atoi(data[index][3].c_str())>current->hp) {
				// �p�G���`�I������ NULL ������ 
				if(current -> right != NULL) {
					innerAppend(current -> right, index);
				} 
				// �_�h�N�s�W�@�Ӹ`�I 
				else {
					current -> right = new Node;
					current -> right -> hp = atoi(data[index][3].c_str());
					current -> right -> index.push_back(index);
					current -> right -> right = NULL;
					current -> right -> left = NULL;
					current -> right -> parent = current;
				}
			} 
			// �p�G�۵����� �N PUSH BACK 
			else if (atoi(data[index][3].c_str())==current->hp){
				current -> index.push_back(index);
			} 
			// �p�G�p�󪺸� ��W�������I���� 
			else  {
				if(current -> left != NULL) {
					innerAppend(current -> left, index);
				} else {
					current -> left = new Node;
					current -> left -> hp = atoi(data[index][3].c_str());
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
	int i = 0; // �p��
	vector<string> answer; // ����
	last = str.find(b); // ���h�M��b���Ӧ�m�n����
	first = 0;// �@�}�l
	// ��last�٨S�]�쵲������m
	while (last != string::npos) {
		// �p�G���Z������0
		if (last - first != 0) {
			answer.push_back(str.substr(first, last - first)); // ��substring���Janswer
		}
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
bool readData(vector<vector<string> > & data,vector<vector<string> > & data2, string dataName) {
	data.clear();
	data2.clear();
	// ���ɮצW�ٷd�w
	if( ! ( dataName.size()>5  &&  dataName.substr(dataName.size()-4) == ".txt" ) ) dataName = addPrefix("input",dataName);
	ifstream ifs;
	ifs.open(dataName);
	if(!ifs.is_open()) {
		printf("File Not Found\n");
		printf("Please Enter File Name again\n");
		return false;
	}
	string line;
	string sp = "\t";
	// �Ʊ��e�@��
	getline(ifs,line);
	vector<string> temp ;
	vector<string> temp1;
	while(getline(ifs,line)) {
		
		temp = split(line,sp);
		data2.push_back(temp);
		temp1.push_back(temp[0]);
		temp1.push_back(temp[1]);
		temp1.push_back(temp[2]);
		if(temp.size()==13){
			temp1.push_back(temp[5]);
			temp1.push_back(temp[6]);
			temp1.push_back(temp[7]);
			temp1.push_back(temp[4]);
		}
		else{
			temp1.push_back(temp[4]);
			temp1.push_back(temp[5]);
			temp1.push_back(temp[6]);
			temp1.push_back(temp[3]);
		}
		data.push_back(temp1);
		temp1.clear();
		temp.clear();
	}
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
// �L�X��� 
void printOut(vector<vector<string> > data){
	printf("\t#\tName\tType 1\tHP\tAttack\tDefense\n");
	int i = 1;
	for(vector<string> vec : data){
		printf("[%d]\t",i);
		printf("%s\t%s\t%s\t%s\t%s\t%s\t",vec[0].c_str(),vec[1].c_str(),vec[2].c_str(),vec[3].c_str(),vec[4].c_str(),vec[5].c_str());
		printf("\n");
		i++;
	}
}
int main() {
	vector<vector<string> >data;
	vector<vector<string> > data2; 
	printf("�п�J:\n0:�h�X\n1:�إߤG���j�M��\n2:��@���j�M\n3:�R����@���\n");
	int n = getInt();
	string fileName;
	BST tree;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				tree.deleteAll();
				if(!readData(data,data2,fileName)) break;
				tree.input(data);
				printOut(data);
				printf("HP tree height : %d\n",tree.getLayer());
				break;
			case 2:
				if(tree.isEmpty()){
					printf("Please finish mission 1 first\n");
					break;
				}
				printf("Please input threshold\n");
				t = getInt();
				tree.travelHigher(t);
				break;
			case 3:
				if(tree.isEmpty()){
					printf("Please finish mission 1 first\n");
					break;
				}
				t = tree.deleteLargest();
				
				printf("#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp. Atk\tSp. Def\tSpeed\tGeneration\tLegendary\n");
				if(data2[t].size()==13){
					cout << data2[t][0] << "\t" << data2[t][1] << "\t" << data2[t][2] << "\t" << data2[t][3] << "\t" << data2[t][4] << "\t" ;
					cout << data2[t][5] << "\t" << data2[t][6] << "\t" << data2[t][7] << "\t" << data2[t][8] << "\t" <<data2[t][9] << "\t" ;
					cout <<data2[t][10] << "\t" <<data2[t][11] << "\t" <<data2[t][12] << "\t" <<"\n";
				}
				else{
					cout << data2[t][0] << "\t" << data2[t][1] << "\t" << data2[t][2] << "\t" << " " << "\t" << data2[t][3] << "\t" << data2[t][4] << "\t" << data2[t][5] << "\t"<< data2[t][6] << "\t" <<data2[t][7] << "\t" <<data2[t][8] << "\t" <<data2[t][9] << "\t" <<data2[t][10] << "\t" <<data2[t][11] << "\t" <<"\n";
				}
				data2.erase(data2.begin()+t);
				data.erase(data.begin()+t);
				printf("Height of tree : %d\n",tree.getLayer());
				break;
			default:
				printf("��J���~ �Э��s��J\n");
		}
		printf("�п�J:\n0:�h�X\n1:�إߤG���j�M��\n2:��@���j�M\n3:�R����@���\n");
		n = getInt(); // ���s���Ʀr
	}
	return 0; // �n�ߺD�O�o�i��
}
