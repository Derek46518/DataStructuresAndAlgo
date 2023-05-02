/**
 * @file DS04_11_11027205_11027229.cpp
 * @author Derek(11027229) and Nier(11027205)
 * @brief ?™æ˜¯ä¸€?‹è¢«?åˆ°?„å?æ¡??¨ä?è§?±ºä½œæ¥­4
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
        
    private:
        
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
  // ?ˆè??´è?
  string s;
  getline(cin, s);
  int total = 0; // total
  int a;         // ?«å??„æ•¸å­?
  if (s.length() == 0)
    return -1; // å¦‚æ?ä½¿ç”¨?…ç›´?¥æ?ä¸‹enter å°±å???1(?·è?main?‚æ??±ä½¿?¨è€…è¼¸?¥éŒ¯èª?
  // string to integer
  for (int i = 0; i < s.length(); i++)
  {
    total *= 10;
    a = s[i] - '0';
    if (a < 0 || a > 9)
      return -1; // å¦‚æ?ä¸åœ¨ç¯„å???å°±å???1 (?·è?main?‚æ??±ä½¿?¨è€…è¼¸?¥éŒ¯èª?
    total += a;
  }
  return total; // å°‡å€¼å??³å???
}

int main()
{
    vector<Data> data;
    Graph graph;
    WriteToVec("pairs401.bin",data);
    for(Data d : data){
        cout << d.putID << ' ' << d.getID << ' ' << d.weight << '\n';
    }
    graph.createGraph(data);
    graph.printAll();
}
