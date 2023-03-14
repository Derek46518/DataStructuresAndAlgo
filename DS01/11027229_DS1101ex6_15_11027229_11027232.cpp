// C++ 11
// 11027229 & 11027232���p�@�~ 
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
		// �غc�l 
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
		
		// �غc�l 
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
	int first, last; //�O���Ĥ@�Ӧ�m�M�ĤG��
	int i = 0; // �p��0
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
	// �}�lŪ�� �g�Jvector�� 
	int i = 0;
	while(getline(ifs,line)){
		temp = split(line,sp);
		temp.push_back(to_string(i));
		data.insert(temp);
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


int main() {
	printf("aaa\n");
}
