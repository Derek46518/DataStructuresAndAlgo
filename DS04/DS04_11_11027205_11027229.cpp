/**
 * @file DS04_11_11027205_11027229.cpp
 * @author Derek(11027229) and Nier(11027205)
 * @brief 
 * This is DS homework 4
 * About building Graph and BFS
 * @version 1.0
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2023
 * 
 * use -std=c++14 to compile
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
#include <set>
#include <iomanip>
#include <stack>
#include <random>
using namespace std;
/**
 * @brief struct of original data
 * 
 */
struct Data
{
    char putID[10] = {'\0'};
    char getID[10] = {'\0'};
    float weight;
};

/**
 * @brief The class of node
 * Every student ID is a node, store in currentID, the connection is recorded into pairs
 * 
 */
class Node{
    public:
        /**
         * @brief Construct a new Node object
         * 
         * @param id student id
         */
        Node(string id){
            currentID = id;
        }
        /**
         * @brief add pair in node
         * 
         * @param in neighbour node
         * @param weight the weight of the path
         */
        void addPair(Node * in, float weight){
            pairs.insert(make_pair(in,weight));
        }

        /**
         * @brief print out the neighbours of every node. For debug use.
         * 
         */
        void printNodes(){
            for(auto p : pairs){
                cout << p.first ->currentID << '\t' << p.second << '\t';
            }
            cout << '\n';
        }
        string currentID;
        struct compp{
    		bool operator() (const pair<Node*, float>& a, const pair<Node*, float>& b) const {
        		return a.first->currentID < b.first->currentID;
    		}
		};
        // vector<pair<Node *,float> > pairs;
        set<pair<Node *,float>, compp > pairs;
        
};

struct comp{
	bool operator() (const Node* nodeA, const Node* nodeB) const{
		return nodeA->currentID <nodeB->currentID;
	}
};

/**
 * @brief The class of a graph
 * This class is used to build graph and run BFS
 * Adjencency list : graph
 * 
 * 
 */
class Graph{
    public:
    
        /**
         * @brief clear graph
         * 
         */
        void clear(){
            // graph.clear();
            graphIn.clear();
            
        }
        /**
         * @brief find the node corresponding the student ID.
         * 
         * @param str student ID
         * @return Node* the node corresponding the student ID.
         */
        Node * find(string str){
			auto it = std::find_if(graphIn.begin(), graphIn.end(), [&](Node* node) { return node->currentID == str; });
			if (it != graphIn.end()) {
    			return *it;
			} else {
    			return NULL;
			}
        }
        /**
         * @brief write .adj file. 
         * after building graph, sort the Adjencency List by ID, and write the graph into the file.
         * @param fileName 
         */
        void writeFile(string fileName){
        	/*
        	for(Node * n : graphIn){
                n->sort();
            }
            */
            // graph = vector<Node* >(graphIn.begin(),graphIn.end());
            // std::sort(graph.begin(),graph.end(),[](auto &g1, auto& g2){return g1->currentID<g2->currentID;});
            size_t pos = fileName.find_last_of('.');            
            if (pos != std::string::npos) {
                // Replace the substring after the last '.' with "adj"
                fileName.replace(pos + 1, std::string::npos, "adjt");
            }
            ofstream ofs(fileName);
            ofs << "<<< There are " << graphIn.size() << " IDs in total. >>>"<<endl;
            int i = 1;
            int count = 0;
            for(Node * node : graphIn){
            	ofs << "[" << setw(3) << i << "] "<< node->currentID<<":"<<endl;
                
                int j = 1;
                for(pair<Node *,float> p : node ->pairs){
                	ofs <<"\t("<<setw(2)<< j<<") " <<p.first->currentID<<", "<< setw(5) <<p.second;
                    
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

        /**
         * @brief build the Graph
         * 
         * @param data vector of original data
         */
        void createGraph(Data d){
            Node * firstPair = find(d.putID);
            Node * secondPair = find(d.getID);
            if(firstPair==NULL) {
                firstPair = new Node(d.putID);
                graphIn.insert(firstPair);
            }
            if(secondPair==NULL) {
                secondPair = new Node(d.getID);
                graphIn.insert(secondPair);
            }
            firstPair->addPair(secondPair,d.weight);
        }
        /**
         * @brief Print out the graph, for debug uses
         * 
         */
        void printAll(){
            for(Node * node : graphIn){
                cout << node ->currentID << '\n';
                node -> printNodes();
            }
        }

        /**
         * @brief travel the graph by BFS, and write the data into .cnt
         * 
         * @param fileName 
         */
        void traverse(string fileName){
            // create fileName
        	size_t pos = fileName.find_last_of('.');
            if (pos != std::string::npos) {
                // Replace the substring after the last '.' with "adj"
                fileName.replace(pos + 1, std::string::npos, "cnt");
            }
            // open file
            ofstream ofs(fileName);
        	ofs << "<<< There are " << graphIn.size() << " IDs in total. >>>" << endl; // write
        	unordered_set<Node*> visit; // store visited Node
        	
        	vector< std::pair<string, vector<Node*> > > list; // store all info
			queue<Node *> q; // store unvisited node
			
        	for(Node * node : graphIn){
        		// start travel
        		q.push(node);
        		innerTravel(node,visit,q);
        		// end travel
        		visit.erase(node); // delete current
        		vector<Node*> visited(visit.begin(),visit.end());
        		sort(visited.begin(),visited.end(),[](auto &g1, auto& g2){return g1->currentID<g2->currentID;});
        		list.push_back(make_pair(node->currentID,visited) ); // push back the visited list
        		visit.clear(); // clear data
        		
			}
			int i = 1;
			stable_sort(list.begin(),list.end(),[](auto &g1, auto& g2){return g1.second.size()>g2.second.size(); });
            // write data
			for(pair<string, vector<Node* > >  a : list){
				ofs << "["<< setw(3) << i <<"] " << a.first<<"("<<a.second.size()<<"):\n";  
				
        		int j = 1;
        		for(Node * n : a.second){
        			// if(j<10)ofs << "\t( " << j << ") " << n->currentID ;
        			// else ofs << "\t(" << j << ") " << n->currentID ;
        			ofs << "\t("<<setw(2)<<j<<") " << n->currentID;
					if(j > 1 && j%10==0) ofs<<"\n"; 
        			j++;
				}
				ofs << "\n";
				i++;
			}

			cout << "<<< There are " << graphIn.size() << " IDs in total. >>>" << endl;
		}
        /**
         * @brief inner traversal, using recursion
         * 
         * @param node current node
         * @param visited visited nodes
         * @param q the queue
         */
		void innerTravel(Node* node, unordered_set<Node* >& visited, queue<Node*>& q) {
    		visited.insert(node); // insert current node to visited
    		while (!q.empty()) {
                // get first node and pop
        		node = q.front();
        		q.pop();
                // get neighbours
        		for (auto& pair : node->pairs) {
                    // if not visited
            		if (visited.count(pair.first) == 0) {
                        // insert into visited, and insert into queue
                		visited.insert(pair.first);
                		q.push(pair.first);
            		}
        		}
    		}
		}
		bool isEmpty(){
			if(graphIn.size()==0) return true;
			return false;
		}
        void DFStraverse(string fileName,float d,string pre){
            // create fileName
        	size_t pos = fileName.find_last_of('.');
            if (pos != std::string::npos) {
                // Replace the substring after the last '.' with "adj"
                fileName.replace(pos + 1, std::string::npos, pre);
            }
            // open file
            ofstream ofs(fileName);
        	ofs << "<<< There are " << graphIn.size() << " IDs in total. >>>" << endl; // write
        	unordered_set<Node*> visit; // store visited Node
            stack<Node *> sk;
            vector< std::pair<string, vector<Node*> > > list; // store all info
            for(Node * n : graphIn){
                sk.push(n);
                innerDFStravel(n,visit,sk,d);
                vector<Node * > visited(visit.begin(),visit.end());
                sort(visited.begin(),visited.end(),[](auto &g1, auto& g2){return g1->currentID<g2->currentID;});
                list.push_back(make_pair(n->currentID,visited));
                visited.clear();
            }
            int i = 1;
			stable_sort(list.begin(),list.end(),[](auto &g1, auto& g2){return g1.second.size()>g2.second.size(); });
            // write data
			for(pair<string, vector<Node* > >  a : list){
				if (a.second.size()<=1) continue;
				ofs << "["<< setw(3) << i <<"] " << a.first<<"("<<a.second.size()<<"):\n";  
				
        		int j = 1;
        		for(Node * n : a.second){
        			
        			ofs << "\t("<<setw(2)<<j<<") " << n->currentID;
					if(j > 1 && j%10==0) ofs<<"\n"; 
        			j++;
				}
				ofs << "\n";
				i++;
			}

			cout << "<<< There are " << graphIn.size() << " IDs in total. >>>" << endl;
        }

        void innerDFStravel(Node* node, unordered_set<Node* >& visited, stack<Node*>& sk,float d){
            visited.insert(node); // insert current node to visited
    		while (!sk.empty()) {
                // get first node and pop
        		node = sk.top();
        		sk.pop();
                // get neighbours
        		for (auto& pair : node->pairs) {
                    // if not visited
            		if (pair.second>=d&&visited.count(pair.first) == 0) {
                		visited.insert(pair.first);
                		sk.push(pair.first);
            		}
        		}
    		}
        }
		
    private:
        // vector<Node*> graph;
        set<Node*, comp> graphIn;
};

/**
 * @brief Write binary file into vector
 * 
 * @param binFilename binary filename
 * @param data output vector
 */
void WriteToVec(string binFilename,Graph & graph)
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
        // data.push_back(tempData);
        graph.createGraph(tempData);
    } // for
    binFile.close();
} // void WriteToVec

/**
 * @brief Get the integer of user input
 * 
 * @return int user input
 */
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

/**
 * @brief add prefix to filename
 * 
 * @param add prefix
 * @param s current filename
 * @return string fixed filename
 */
string addPrefix(string add, string s)
{
  stringstream ss;
  ss << add;
  ss << s;
  ss << ".bin";
  return ss.str();
}

/**
 * @brief read the data by filename, and build graph
 * 
 * @param graph 
 * @param data the output data.
 * @param fileName the file to open
 * @return true if the file exist
 * @return false if the data doesn't exist
 */
bool readData(Graph & graph, string & fileName){
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
    WriteToVec(fileName,graph);
    return true;
}

int main()
{
    vector<Data> data;
    Graph graph;
    string fileName;
    cout << "*** Graph data manipulation **\n* 0. QUIT                  *\n* 1. Build adjancency lists        *\n* 2. Compute connection counts        *\n* *************************************\n";
    int n = getInt();
    float d;
    char ch;
    while(n!=0){
        switch(n){
            case 1:
            cout << "Please input file name :";
            getline(cin,fileName);
            if(!readData(graph,fileName)){
                break;
            }
            graph.writeFile(fileName);
            break;
            case 2 :
            	if(graph.isEmpty()){
            		cout << "Please do mission 1 first\n";
					break;
				}
				graph.traverse(fileName);
            break;
            case 3:
                if(graph.isEmpty()){
            		cout << "Please do mission 1 first\n";
					break;
				}
                cout << "Please enter number\n";
                
                cin >> d;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (d>0 && d <=1)graph.DFStraverse(fileName,d,"inf");
				else cout << "Wrong Number\n";
				break;
			case 4:
				if(graph.isEmpty()){
            		cout << "Please do mission 1 first\n";
					break;
				}
				d = rand() / (RAND_MAX + 1.);
				graph.DFStraverse(fileName,d,"pro");
				break;
        }
        cout << "*** Graph data manipulation **\n* 0. QUIT                  *\n* 1. Build adjancency lists        *\n* 2. Compute connection counts        *\n* *************************************\n";
        n = getInt();
    }
}
