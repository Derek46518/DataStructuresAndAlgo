/**
 * @file DS04_11_11027205_11027229.cpp
 * @author Derek(11027229) and Nier(11027205)
 * @brief 
 *
 * @version 1.0
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

struct Data
{
    char putID[10] = {'\0'};
    char getID[10] = {'\0'};
    float weight;
};

class Node{
    public:
        
        Node(string id){
            currentID = id;
        }

        void addPair(Node * in, float weight){
            pairs.push_back(make_pair(in,weight));
        }

        void sort(){
            std::sort(pairs.begin(),pairs.end(),[](const auto& n1, auto& n2){return n1.first->currentID <n2.first->currentID;});
        }
        
        void printNodes(){
            for(auto p : pairs){
                cout << p.first ->currentID << '\t' << p.second << '\t';
            }
            cout << '\n';
        }
        string currentID;
        vector<pair<Node *,float> > pairs;
};

class Graph{
    public:
        void clear(){
            graph.clear();
        }
        Node * find(string str){
            for(Node *n : graph){
                if (n->currentID==str) return n;
            }
            return NULL;
        }
        void writeFile(string fileName){
            size_t pos = fileName.find_last_of('.');            
            if (pos != std::string::npos) {
                // Replace the substring after the last '.' with "adj"
                fileName.replace(pos + 1, std::string::npos, "adjt");
            }
            ofstream ofs(fileName);
            ofs << "<<< There are " << graph.size() << " IDs in total. >>>"<<endl;
            int i = 1;
            int count = 0;
            for(Node * node : graph){
                if(i<10)ofs << "[  " << i <<"] "<<node->currentID<<":"<<endl;
                else if (i<100) ofs << "[ " << i <<"] "<<node->currentID<<":"<<endl;
                else ofs << "[" << i <<"] "<<node->currentID<<":"<<endl;
                int j = 1;
                for(pair<Node *,float> p : node ->pairs){
                    if (j<10)ofs << "\t( "<<j<<") "<<p.first->currentID<<", "<<p.second;
                    else ofs << "\t("<<j<<") "<<p.first->currentID<<", "<<p.second;
                    j++;
                    count ++;
                    if (j>1 && (j-1)%10==0)ofs<<endl;
                }
                ofs << endl;
                i++;
            }
            ofs << "<<< There are " << i-1 << " IDs in total. >>>\n";
            cout << "<<< There are " << i-1 << " IDs in total. >>>\n\n";
            cout << "<<< There are " << count << " nodes in total. >>>\n";
            ofs.close();
        }
        void createGraph(vector<Data> data){
            for(Data d : data){
                Node * firstPair = find(d.putID);
                Node * secondPair = find(d.getID);
                if(firstPair==NULL) {
                    firstPair = new Node(d.putID);
                    graph.push_back(firstPair);
                }
                if(secondPair==NULL) {
                    secondPair = new Node(d.getID);
                    graph.push_back(secondPair);
                }
                firstPair->addPair(secondPair,d.weight);
            }
            for(Node * n : graph){
                n->sort();
            }
            std::sort(graph.begin(),graph.end(),[](auto &g1, auto& g2){return g1->currentID<g2->currentID;});
        }
        void printAll(){
            for(Node * node : graph){
                cout << node ->currentID << '\n';
                node -> printNodes();
            }
        }
        void traverse(string fileName){
        	size_t pos = fileName.find_last_of('.');
            if (pos != std::string::npos) {
                // Replace the substring after the last '.' with "adj"
                fileName.replace(pos + 1, std::string::npos, "cntt");
            }
            ofstream ofs(fileName);
        	ofs << "<<< There are " << graph.size() << " IDs in total. >>>" << endl;
        	unordered_set<Node*> visit;
        	vector< std::pair<string, vector<Node*> > > list;
			queue<Node *> q;
			// int i = 1;
        	for(Node * node : graph){
        		// start travel
        		q.push(node);
        		innerTravel(node,visit,q);
        		// end travel
        		
        		visit.erase(node); // delete current
        		
        		vector<Node * > visited(visit.begin(),visit.end()); 
        		std::sort(visited.begin(),visited.end(),[](auto &g1, auto& g2){return g1->currentID<g2->currentID;});
        		list.push_back(make_pair(node->currentID,visited) ); // push back the visited list
        		visit.clear();
        		
			}
			std::stable_sort(list.begin(),list.end(),[](auto &g1, auto& g2){return g1.second.size()>g2.second.size();});
			int i = 1;
			for(pair<string, vector<Node*> >  a : list){
				if(i<10) ofs << "[  " << i << "] " << a.first<<"("<< a.second.size()<<"):\n";
        		else if(i<100) ofs << "[ " << i << "] " << a.first<<"("<< a.second.size() <<"):\n";
        		else ofs << "[" << i << "] " << a.first<<"("<< a.second.size()<<"):\n";
        		int j = 1;
        		for(Node * n : a.second){
        			if(j<10)ofs << "\t( " << j << ") " << n->currentID ;
        			else ofs << "\t(" << j << ") " << n->currentID ;
					if(j > 1 && j%10==0) ofs<<"\n"; 
        			j++;
				}
				ofs << "\n";
				i++;
			}

			cout << "<<< There are " << graph.size() << " IDs in total. >>>" << endl;
		}
		void innerTravel(Node* node, unordered_set<Node*>& visited, queue<Node*>& q) {
    		visited.insert(node);
    		while (!q.empty()) {
        		node = q.front();
        		q.pop();
        		for (auto& pair : node->pairs) {
            		if (visited.count(pair.first) == 0) {
                		visited.insert(pair.first);
                		q.push(pair.first);
            		}
        		}
    		}
		}
		
    private:
        vector<Node*> graph;
};

//  write binary to struct
void WriteToVec(string binFilename, vector<Data> &data)
{
    Data tempData;
    int stNo = 0;

    fstream binFile;
    binFile.open(binFilename.c_str(), fstream::in | fstream::binary);
    binFile.seekg(0, binFile.end);
    stNo = binFile.tellg() / sizeof(tempData);
    binFile.seekg(0, binFile.beg);

    // push binary data to vec
    for (int i = 0; i < stNo; i++)
    {
        binFile.read((char *)&tempData, sizeof(tempData));
        data.push_back(tempData);
    } // for

    binFile.close();
} // void WriteToVec



int getInt()
{
  string s;
  getline(cin, s);
  int total = 0; // total
  int a;         
  if (s.length() == 0)
    return -1; 
  // string to integer
  for (int i = 0; i < s.length(); i++)
  {
    total *= 10;
    a = s[i] - '0';
    if (a < 0 || a > 9)
      return -1; 
    total += a;
  }
  return total; 
}

string addPrefix(string add, string s)
{
  stringstream ss;
  ss << add;
  ss << s;
  ss << ".bin";
  return ss.str();
}

bool readData(Graph & graph,vector<Data> &data, string & fileName){
    if(fileName.size()==3)
        fileName = addPrefix("pairs",fileName);
    ifstream ifs;
    ifs.open(fileName);
    if(!ifs.is_open()){
        printf("No File\n");
        return false;
    }
    
    ifs.close();
    graph.clear();
    data.clear();
    WriteToVec(fileName,data);
    graph.createGraph(data);
    return true;
}

int main()
{

    vector<Data> data;
    Graph graph;
    string fileName;
    cout << "*** Graph data manipulation **\n* 0. QUIT                  *\n* 1. Build adjancency lists        *\n* 2. Compute connection counts        *\n* *************************************\n";
    int n = getInt();
    while(n!=0){
        switch(n){
            case 1:
            cout << "Please input file name :";
            getline(cin,fileName);
            if(!readData(graph,data,fileName)){
                break;
            }
            graph.writeFile(fileName);
            break;
            
            case 2 :
            	if(data.empty()){
            		cout << "Please do mission 1 first\n";
					break;
				}
				graph.traverse(fileName);
            break;
        }
        cout << "*** Graph data manipulation **\n* 0. QUIT                  *\n* 1. Build adjancency lists        *\n* 2. Compute connection counts        *\n* *************************************\n";
        n = getInt();
    }
   
}
