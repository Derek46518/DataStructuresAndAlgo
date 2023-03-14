#include <iostream>

using namespace std;

class Node {
    public:
        string data;
        Node *left;
        Node *mid;
        Node *right;
        vector<int> ids;
        Node(string value,int id) {
            string = value;
            left = NULL;
            mid = NULL;
            right = NULL;
            ids.push_back(id);
        }
};

class TwoThreeTree {
    private:
        Node *root;
        void insert(Node *&p, string value, int id) {
        	
            if (p == NULL) {
                p = new Node(value,id);
            }
			 else if ( p->data==value){
			 	p->ids.push_back(id);
			 }
			
			 else if (p->left == NULL) {
                if (value < p->data) {
                    p->left = new Node(value,id);
                } else {
                    p->mid = new Node(value,id);
                }
            } else if (p->right == NULL) {
                if (value > p->data) {
                    p->right = new Node(value,id);
                } else if (value < p->left->data) {
                    Node *temp = p->left;
                    p->left = new Node(value,id);
                    p->right = temp->mid;
                    p->data = temp->data;
                    delete temp;
                } else {
                    Node *temp = p->mid;
                    p->mid = new Node(value,id);
                    p->right = temp->mid;
                    p->data = temp->data;
                    delete temp;
                }
            } else {
                if (value < p->left->data) {
                    insert(p->left, value,id);
                } else if (value > p->right->data) {
                    insert(p->right, value,id);
                } else {
                    insert(p->mid, value,id);
                }
                if (p->left != NULL && p->mid != NULL && p->right != NULL) {
                    Node *temp = new Node(p->data,id);
                    temp->left = p->left;
                    temp->mid = p->mid;
                    temp->right = p->right;
                    p->left = NULL;
                    p->mid = NULL;
                    p->right = NULL;
                    p->data = temp->mid->data;
                    if (temp->left->data < p->data) {
                        p->left = temp->left;
                        p->mid = temp->mid;
                    } else {
                        p->mid = temp->left;
                        p->right = temp->mid;
                    }
                    delete temp;
                }
            }
        }
        void inOrderTraversal(Node *p) {
            if (p != NULL) {
                inOrderTraversal(p->left);
                cout << p->data << " ";
                inOrderTraversal(p->mid);
                inOrderTraversal(p->right);
            }
        }
    public:
        TwoThreeTree() {
            root = NULL;
        }
        void insert(int value) {
            insert(root, value);
        }
        void print() {
            inOrderTraversal(root);
        }
};

// Ū��
bool readData(Heap & data, string dataName) {
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
	vector<string> temp1;
	string sp = "\t";
	// �}�lŪ�� �g�Jheap��
	int i = 1;
	while(getline(ifs,line)) {
		temp = split(line,sp);
		temp1.push_back(temp[8]);
		temp1.push_back(to_string(i));
		data.insert(temp1);
		temp1.clear();
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
	Deap deap;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(minHeap,fileName)) break;
				minHeap.printOut();
				minHeap.restore();
				break;
			case 2:
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(minMaxHeap,fileName)) break;
				minMaxHeap.printOut();
				minMaxHeap.restore();
				break;
			
			
			default:
				printf("��J���~ �Э��s��J\n");
		}
		printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n");
		n = getInt(); // ���s���Ʀr
	}
	return 0; // �n�ߺD�O�o�i��
}
