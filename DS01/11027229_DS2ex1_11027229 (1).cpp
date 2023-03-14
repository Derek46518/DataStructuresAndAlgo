// C++ 11
// 11027229 ���p�@�~
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<cmath>
#include<ctype.h>
#include<algorithm>
using namespace std;
// abstract class
// use to define stuff
class Heap {
	public:
		virtual void insert(vector<string> data) {}
		virtual void del() {}
		virtual void heapify(int i) {}
		void restore() {
			data.clear();
		}
		void printOut() {
			printf("<min heap>\n");
			printf("root: [%s] %s\n",data[0][1].c_str(),data[0][0].c_str());
			printf("bottom: [%s] %s\n",data[data.size()-1][1].c_str(),data[data.size()-1][0].c_str());
			int i = 0;
			while(left(i)<data.size()) i = left(i);
			printf("leftmost bottom: [%s] %s\n",data[i][1].c_str(),data[i][0].c_str());
			// data.clear();
		}

		/**
		* Get the parent of the index
		* @param index.
		* @return parent.
		*/
		int parent(int i) {
			return (i-1)/2;
		}
		/**
		* Get the left node of the index
		* @param index.
		* @return left.
		*/
		int left(int i) {
			return (2*i + 1);
		}
		/**
		* Get the right node of the index
		* @param index.
		* @return right.
		*/
		int right(int i) {
			return (2*i + 2);
		}

		/**
		* Get grandparent by index
		* @param index.
		*
		*/
		int grandparent(int i) {
			return parent(parent(i));
		}
		/**
		* Get layer by index
		* @param index.
		*
		*/
		int layer(int i) {
			return log2(i+1);
		}

	protected:
		vector<vector<string> > data;

		/**
		* Get the key to the specific index
		* @param index.
		* @return key.
		*/
		int key(int i) {
			string temp = data[i][0];
			temp.erase(remove_if(temp.begin(),temp.end(),static_cast<int(*)(int)>(&ispunct)),temp.end());
			temp.erase(remove(temp.begin(),temp.end(),','),temp.end());
			return stoi(temp);
		}

		/**
		* Swap two orders
		* @param index i and j.
		*
		*/
		void swap(int i, int j) {
			vector<string > temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}

		/**
		* Determine that the level is min or not
		* @param index.
		* @return boolean, true if is Min level.
		*/
		bool isMinLevel(int i) {
			return ( layer(i) % 2 == 0);
		}

};
// class of Min Heap
class MinHeap:public Heap {
	public:
		MinHeap() {}
		/**
		* Insert data into heap.
		* @param vector of strings.
		*
		*/
		void insert(vector<string> dataT) {
			data.push_back(dataT);
			int i = data.size()-1;
			while (i != 0 && key(parent(i)) > key(i)) {
				swap(i, parent(i));
				i = parent(i);
			}
		}
		void heapify(int i) {}

};

class MinMaxHeap:public Heap {
	public:
		MinMaxHeap() {}
		void insert(vector<string> dataT) {
			data.push_back(dataT);
			int index = data.size()-1;
			bubbleUp(index); // Bubble up every insert
		}
		
		/**
		* for debug uses
		* print out the heap structure of min-max heap
		* @param the original data
		*/
		void debug(vector<vector<string> > &originData){
			vector<string> temp ;
			for(int i = 0 ; i < data.size(); i++){
				temp = originData[stoi(data[i][1]) - 1];
				printf("[%s] %s, %s %s %s %s\n",temp[11].c_str(),temp[1].c_str(),temp[3].c_str(),temp[4].c_str(),temp[5].c_str(),temp[8].c_str());
			}
		}
		/**
		* print out the answer
		*/
		void printOut() {
			printf("<min-max heap>\n");
			printf("root: [%s] %s\n",data[0][1].c_str(),data[0][0].c_str());
			printf("bottom: [%s] %s\n",data[data.size()-1][1].c_str(),data[data.size()-1][0].c_str());
			int i = 0;
			while(left(i)<data.size()) i = left(i);
			printf("leftmost bottom: [%s] %s\n",data[i][1].c_str(),data[i][0].c_str());
			// data.clear();
		}
		/**
		* delete root and print out result
		* @param vector<vector<string> originalData
		* @warning originalData will change
		*/
		void deleteAndPrintOut( vector<vector<string> > & originData ) {
			if(data.empty()) return;
			vector<string> root = data[0];
			vector<string> last = data.back();
			data.pop_back();
			data[0] = last;
			
			minMaxHeapify(0);
			
			int index = stoi(root[1])-1;
			vector<string> temp = originData[index];
			printf("[%s] %s, %s %s %s %s\n",temp[11].c_str(),temp[1].c_str(),temp[3].c_str(),temp[4].c_str(),temp[5].c_str(),temp[8].c_str());
			originData.erase(originData.begin()+index);
			updateData(index);
		}

		bool isEmpty() {
			return data.size() == 0 ? true:false;
		}

		void heapify(int i) {}
	private:
		
		/**
		* update the index in data
		*/
		void updateData(int index) {
			for(int i = 0 ; i < data.size() ; i++) {
				if(stoi(data[i][1]) -1 >index) {
					data[i][1] = to_string( stoi(data[i][1]) -1 );
				}
			}
		}

		/**
		* re heapify heap
		* @param index
		*/
		void minMaxHeapify(int index) {
			if(index>=data.size()) return;
			int GrandChildIndex = findGrandChildIndex(index);
			if(GrandChildIndex!=-1){
				if(key(index)>key(GrandChildIndex)){
					swap(index,GrandChildIndex);
					if( key( parent(GrandChildIndex) )  < key(GrandChildIndex)){
						swap(parent(GrandChildIndex),GrandChildIndex);
					}
				}
				else{
					int smallest = findSmallestChild(index);
					if( key(index) > key(smallest) && smallest != -1){
						swap(index,smallest);
					}
					return;
				}
				
				minMaxHeapify(GrandChildIndex);
			}	
			else{
				int smallest = findSmallestChild(index);
				if(smallest != -1 && key(index) > key(smallest) ){
					swap(index,smallest);
				}
				return;
			}
			
		}
		
		/**
		* find the smallest children of index 
		* @param index
		* @return smallest children of index
		*/
		int findSmallestChild(int index){
			int firstChild = index * 2 + 1;
			if(firstChild>=data.size()) return -1;
			if(firstChild+1>=data.size()) return firstChild;
			else if (key(firstChild+1) <key(firstChild)) firstChild++;
			return firstChild;
		}
		
		/**
		* find smallest grand children of index
		* @param index
		* @return  smallest grand children of index
		*/
		int findGrandChildIndex(int index) {
			int firstChild = index * 4 + 3;
			if(firstChild>=data.size()) return -1;
			int lastChild = min((int)data.size() - 1, index * 4 + 6);
			
			int minMaxChildIndex = firstChild;
			if (firstChild <= lastChild) {
				for (int i = firstChild + 1; i <= lastChild; i++) {
					if ( key(i) < key(minMaxChildIndex) ) {
						minMaxChildIndex = i;
					}
				}
			}
			
			return minMaxChildIndex;
		}

		/**
		* Bubble up the index
		* @param index.
		*
		*/
		void bubbleUp(int i) {
			if(i==0) return;
			if(isMinLevel(i)) {
				if(key(i)>key(parent(i))) {
					swap(i,parent(i));
					bubbleUpMax(parent(i));
				} bubbleUpMin(i);
			} else {
				if(key(i)<key(parent(i))) {
					swap(i,parent(i));
					bubbleUpMin(parent(i));
				} bubbleUpMax(i);
			}
		}
		void bubbleUpMin(int i) {
			if (i <= 2) return;
			if (isMinLevel(grandparent(i)) && key(i) < key(grandparent(i))) {
				swap(i, grandparent(i));
				bubbleUpMin(grandparent(i));
			}
		}

		void bubbleUpMax(int i) {
			if (i <= 2) return;
			if (!isMinLevel(grandparent(i)) && key(i) > key(grandparent(i))) {
				swap(i, grandparent(i));
				bubbleUpMax(grandparent(i));
			}
		}
		// Utility function to get the index of the left child of a node
		int left_child(int i) {
			return 2 * i + 1;
		}

		// Utility function to get the index of the right child of a node
		int right_child(int i) {
			return 2 * i + 2;
		}



};

/**
* Class of Deap
* Extends Heap
*/
class Deap:public Heap {
	public:
		Deap() {}
		/**
		* insert data
		* @param vector of strings dataT
		*/
		void insert(vector<string> dataT) {
			if(data.size()==0) {
				vector<string> temp;
				data.push_back(temp);
			}
			data.push_back(dataT);
			int index = data.size()-1;
			reheap(index); // reheap every insertion
		}
		void del() {}
		void heapify(int i) {}

		void printOut() {
			printf("<deap heap>\n");
			printf("top left: [%s] %s\n",data[1][1].c_str(),data[1][0].c_str());
			printf("top right: [%s] %s\n",data[2][1].c_str(),data[2][0].c_str());
			printf("bottom: [%s] %s\n",data[data.size()-1][1].c_str(),data[data.size()-1][0].c_str());
			int i = 0;
			while(left(i)<data.size()) i = left(i);
			printf("leftmost bottom: [%s] %s\n",data[i][1].c_str(),data[i][0].c_str());
			data.clear();
		}
		/**
		* For testing uses
		*/
		void test() {
			for(vector<string> temp : data) {
				cout << data.size()<<"\n";
			}
			printf("\n");
		}
	private:
		bool isRight(int i) {
			int currentLayer = layer(i);
			int nodes = pow(2,currentLayer)/2;
			i-= pow(2,currentLayer) - 1;
			return(i>=nodes);
		}
		/**
		* Reheap by the rules of Deap
		* @ param index
		*/
		void reheap(int index) {
			// �p�G�Omax�h
			if(isRight(index)) {
				int cor = index - pow(2,(layer(index)-1)); // count corresponding sibling
				// if data at index is smaller than corresbonding, swap and bubbleUpMin
				if(key(index)<key(cor)) {
					swap(index,cor);
					bubbleUpMin(cor);
				}

				bubbleUpMax(index);
			}
			// �p�G�Omin�h
			else {
				int cor = index + pow(2,(layer(index)-1)); // count corresponding sibling
				// if no sibling, find the parent of the node
				if(cor>data.size()-1) cor = parent(cor);
				// if data at index is bigger than corresbonding, swap and bubbleUpMin
				if(cor!=0 && key(index)>key(cor)) {
					swap(index,cor);
					bubbleUpMax(cor);
				}
				bubbleUpMin(index);
			}
		}

		// bubbleUp Every swap, build min heap
		void bubbleUpMin(int i) {
			if (i <=0) return;
			if (parent(i)>0 && key(i) < key(parent(i))) {
				swap(i, parent(i));
				bubbleUpMin(parent(i));
			}
		}
		// bubbleUp Every swap, build max heap
		void bubbleUpMax(int i) {
			if(i<=0) return;
			if (parent(i)>0 && key(i) > key(parent(i))) {
				swap(i, parent(i));
				bubbleUpMax(parent(i));
			}
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
bool readData(Heap & data, vector<vector<string> > & originData, string dataName) {
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
		temp.push_back(to_string(i));
		originData.push_back(temp);
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
	vector<vector<string> > originData;
	printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n3: Top-K minimums from min-max heap\n");
	int n = getInt();
	string fileName;
	MinHeap minHeap;
	MinMaxHeap minMaxHeap;
	Deap deap;
	int t ;
	
	while(n!=0) {
		switch(n) {
			
			case 1:
				minHeap.restore();
				originData.clear();
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(minHeap,originData,fileName)) break;
				minHeap.printOut();
				break;
			case 2:
				minMaxHeap.restore();
				originData.clear();
				printf("�п�J�ɮצW��\n");
				getline(cin,fileName);
				if(!readData(minMaxHeap,originData,fileName)) break;
				minMaxHeap.printOut();

				break;

			case 3:
				printf("�п�J�D�t���N\n");
				if(minMaxHeap.isEmpty()) {
					printf("Run case 2 first\n");
					break;
				}

				t = getInt();
				while(t<=0) {
					printf("Invalid Input\n");
				}
				
				for(int i = 0 ; i < t && !minMaxHeap.isEmpty() ; i++) {
					/*
					printf("============\n");
					minMaxHeap.debug(originData);
					printf("============\n");
					
					*/
					printf("Top %d",i+1);
					minMaxHeap.deleteAndPrintOut(originData);
				}

				break;
			default:
				printf("��J���~ �Э��s��J\n");
		}
		printf("�п�J:\n0:�h�X\n1:�إ�min heap\n2:�إ�min-max heap\n3: Top-K minimums from min-max heap\n");
		n = getInt(); // ���s���Ʀr
	}
	return 0; // �n�ߺD�O�o�i��
}
