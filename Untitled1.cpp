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

// 讀檔
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
	// 開始讀黨 寫入heap內
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
	printf("請輸入:\n0:退出\n1:建立min heap\n2:建立min-max heap\n");
	int n = getInt();
	string fileName;
	TwoThreeTree twoThreeTree;
	Deap deap;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("請輸入檔案名稱\n");
				getline(cin,fileName);
				if(!readData(minHeap,fileName)) break;
				minHeap.printOut();
				minHeap.restore();
				break;
			case 2:
				printf("請輸入檔案名稱\n");
				getline(cin,fileName);
				if(!readData(minMaxHeap,fileName)) break;
				minMaxHeap.printOut();
				minMaxHeap.restore();
				break;
			
			
			default:
				printf("輸入錯誤 請重新輸入\n");
		}
		printf("請輸入:\n0:退出\n1:建立min heap\n2:建立min-max heap\n");
		n = getInt(); // 重新取數字
	}
	return 0; // 好習慣記得養成
}
