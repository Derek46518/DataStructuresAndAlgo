// C++ 11
// 11027229 & 11027232的小作品 
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class Heap{
	public:
		void insert(vector<string> data);
		void del();
		void heapify(int i);
};
class MinHeap:public Heap{
	public:
		MinHeap(){}
		// 建構子 
		MinHeap(vector<vector<string> > dataT){
			data = dataT;
		}
		
		void insert(vector<string> dataT){
			
		}
		
		void heapify(int i){
			
		}
	private:
		vector<vector<string> > data;
		
};

class MinMaxHeap:public Heap{
	public:
		
		// 建構子 
		MinMaxHeap(){
		}
		MinMaxHeap(vector<vector<string> > dataT){
			data = dataT;
		}
		
		void insert(vector<string> dataT){
			
		}
		
		void heapify(int i){
			
		}
	private:
		vector<vector<string> > data;
		
};

vector<string> split(string &str, string &b) {
	int first, last; //記錄第一個位置和第二個
	int i = 0; // 計數0
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
bool readData(Heap & data, string dataName) {
	if(dataName.size()==3) dataName = addPrefix("input",dataName);
	ifstream ifs;
	string line;
	ifs.open(dataName);
	
	if(!ifs.is_open()){
		printf("No file\n");
		return false;
	} 
	for(int i = 0 ; i < 3 ; i++){
		getline(ifs,line);
	}
	vector<string> temp;
	string sp = "\n";
	// 開始讀黨 寫入vector內 
	int i = 0;
	while(getline(ifs,line)){
		temp = split(line,sp);
		temp.push_back(to_string(i));
		data.insert(temp);
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


int main() {
	printf("aaa\n");
}
