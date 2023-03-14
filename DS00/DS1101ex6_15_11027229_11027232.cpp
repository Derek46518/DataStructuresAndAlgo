// C++ 11
// 11027229 & 11027232的小作品 
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
// Node 的 struct 
struct Node {
	int hp; // 生命值 
	vector<int> index; // 該生命值對應到的 index 
	Node * left; // 左節點 
	Node * right; // 右節點 
	Node * parent; // 父節點 
};

// 二元搜尋樹的class 
class BST {
	// 公開 
	public:
		// 建構子 
		BST(){
			head = NULL;
			
			
		}
		// 準備把資料放進樹裡面 
		input(vector<vector<string> > d) {
			data = d; // 把從main讀到的資料放入data裡面 
			
			// 逐一放入樹中 
			for(int i = 0 ; i < data.size(); i++) {
				append(i);
			}
		}
		
		// 透過index放入樹中
		void append(int index) {
			// 樹的一開始 
			if(head == NULL) {
				head = new Node;
				head -> hp = atoi(data[index][3].c_str()) ;
				head -> index.push_back(index);
				head -> right = NULL;
				head -> left = NULL;
				head -> parent = NULL;
				return;
			}
			// 開始往子節點放 
			innerAppend(head,index);
		}
		
		// 是不是空的 
		bool isEmpty(){
			if(head==NULL) return true;
			else return false;
		}
		
		// 刪除全部 
		void deleteAll(){
			delete_tree(head);
			head = NULL;
		}
		// 算出有幾層 
		int getLayer() {
			return height(head);
		}
		
		// 若有一筆資料被刪除，節點上的 index 要更新 
		void minusIndex(Node * current, int i){
			if( current == NULL) return; 
			if(current -> right!= NULL) minusIndex(current -> right,i);
			for(int & dataa : current -> index ){
				if(dataa>i) dataa--;
			}
			if(current -> left != NULL) minusIndex(current -> left,i);
		}
		
		// 刪掉最大的值 
		int deleteLargest(){
			// 將current設定到頭的位置 
			Node * current = head;
			if (head == NULL) return INT_MIN;
			int n;
			// 移到最右邊 
			while(current -> right != NULL) current = current -> right;
			// 取得最右邊的最大的元素 
			n = current -> index[0];
			current->index.erase(current->index.begin());
			// 更新index 
			minusIndex(head,n);
			// 把該資料刪了 
			data.erase(data.begin()+n);
			// 如果該節點上面沒資料 代表可以刪了 
			if(current -> index.size()==0){
				// 如果節點是頭 
				if(current == head){
					// 如果左邊沒東西 代表只剩下頭了 因此這棵樹已經沒了 
					if(head -> left ==NULL){
						head = NULL;
						return n;
					}
					// 將頭設成頭的左邊 並且刪除掉原本的頭 
					head = head -> left;
					head -> parent = NULL; 
					delete current;
					return n;
				}
				// 如果現在這個節點的左邊不是NULL的話 
				if(current -> left != NULL){
					// 將上一個節點的右邊設成現在的左邊 
					current -> parent -> right = current -> left;
					// 更新左節點的父節點 
					current -> left -> parent = current -> parent;
					// 刪除該節點 
					delete current;
					return n;
				}
				// 否則該節點就可以刪除了 
				else {
					// 斷開連結 
					current -> parent -> right = NULL;
					// 刪除 
					delete current;
					
					return n;
				}
			}

			return n;
			
		}
		
		// debug 用的 印出所有資料 
		void printAll(Node * current){
			if( current == NULL) return; 
			if(current -> right!= NULL) printAll(current -> right);
			for(int dataa : current -> index ){
				printf("%s\t%s\n",data[dataa][0].c_str(),data[dataa][3].c_str());
			}
			if(current -> left != NULL) printAll(current -> left);
		}
		
		// 找比門檻高的數字 
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
		
		// 內部走訪每個節點 
		void innerTravel(Node * current, int h, int & nodes,vector<vector<string> > & answer){
			// 如果是NULL 就直接RETURN 
			if(current == NULL) return;
			nodes++;
			
			// 先遞迴到最右邊 
			if(current -> right != NULL){
				innerTravel(current-> right, h, nodes,answer);
			}
			
			// 如果大於等於門檻的話 就是想要的 
			if(current -> hp >= h){
				for(int indexx: current -> index){
					answer.push_back(data[indexx]);
				}
			}
			
			// 如果現在的 hp 小於等於門檻，沒有往左節點帶的必要 因此直接return 
			if(current -> hp <= h) return;
			
			// 如果左邊不等於NULL 再往左邊帶 
			if(current -> left != NULL){
				innerTravel(current-> left, h, nodes,answer);
			}
			// 好習慣記得養成 
			return;
		}
		
		// 內部Append
		void innerAppend(Node * current, int index) {
			// 如果大於的話 
			if(atoi(data[index][3].c_str())>current->hp) {
				// 如果左節點不等於 NULL 往左邊 
				if(current -> right != NULL) {
					innerAppend(current -> right, index);
				} 
				// 否則就新增一個節點 
				else {
					current -> right = new Node;
					current -> right -> hp = atoi(data[index][3].c_str());
					current -> right -> index.push_back(index);
					current -> right -> right = NULL;
					current -> right -> left = NULL;
					current -> right -> parent = current;
				}
			} 
			// 如果相等的話 就 PUSH BACK 
			else if (atoi(data[index][3].c_str())==current->hp){
				current -> index.push_back(index);
			} 
			// 如果小於的話 跟上面的有點類似 
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
		// 計算高度 
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
	int first, last; //記錄第一個位置和第二個
	int i = 0; // 計數
	vector<string> answer; // 答案
	last = str.find(b); // 先去尋找在哪個位置要分割
	first = 0;// 一開始
	// 當last還沒跑到結束的位置
	while (last != string::npos) {
		// 如果間距不等於0
		if (last - first != 0) {
			answer.push_back(str.substr(first, last - first)); // 把substring推入answer
		}
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
bool readData(vector<vector<string> > & data,vector<vector<string> > & data2, string dataName) {
	data.clear();
	data2.clear();
	// 把檔案名稱搞定
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
	// 排掉前一行
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
// 印出資料 
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
	printf("請輸入:\n0:退出\n1:建立二元搜尋樹\n2:單一欄位搜尋\n3:刪除單一資料\n");
	int n = getInt();
	string fileName;
	BST tree;
	int t ;
	while(n!=0) {
		switch(n) {
			case 1:
				printf("請輸入檔案名稱\n");
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
				printf("輸入錯誤 請重新輸入\n");
		}
		printf("請輸入:\n0:退出\n1:建立二元搜尋樹\n2:單一欄位搜尋\n3:刪除單一資料\n");
		n = getInt(); // 重新取數字
	}
	return 0; // 好習慣記得養成
}
