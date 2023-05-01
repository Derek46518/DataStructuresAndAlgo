/**
 * @file DS04_11_11027205_11027229.cpp
 * @author Derek(11027229) and Nier(11027205)
 * @brief 這是一個被搞到的專案 用來解決作業4
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
        Node(string id,string put, float weight){
            currentID = put;
            pairs.push_back(make_pair(id,weight));
        }

        void addPair(string pairp, float weight){
            pair<string,float> temp = make_pair(pairp,weight);
            pairs.push_back(temp);
        }

        void sort(){
            std::sort(pairs.begin(), pairs.end());
        }
        
        void printPairID(){
            for(pair<string,float> p : pairs){
                cout << p.first << ' ' << p.second <<'\t';
            }
            cout << '\n';
        }
        string currentID;
        
    private:
        
        vector<pair<string,float> > pairs;
};



class Graph{
    public:
        void clear(){
            graph.clear();
        }
        
        bool findAndInsert(string getID, string putID, float weight){
            for(Node &node : graph){
                if(node.currentID==putID){
                    
                    node.addPair(getID,weight);
                    
                    return true;
                }
            }
            return false;
        }

        

        void sort(){
            std::sort(graph.begin(),graph.end(),[](const Node& s1, const Node& s2){return s1.currentID<s2.currentID;});
            for(Node node : graph){
                node.sort();
            }
        }
        void createGraph(vector<Data> data){
            for(Data d : data){
                if(!findAndInsert(d.getID,d.putID,d.weight)){
                    graph.push_back( Node(d.getID,d.putID,d.weight) );
                }
            }
        }
        void printAll(){
            for(Node n : graph){
                cout << n.currentID << '\n';
                n.printPairID();
            }
        }

    private:
        vector<Node> graph;
        
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
  // 先讀整行
  string s;
  getline(cin, s);
  int total = 0; // total
  int a;         // 暫存的數字
  if (s.length() == 0)
    return -1; // 如果使用者直接按下enter 就回傳-1(執行main時會報使用者輸入錯誤)
  // string to integer
  for (int i = 0; i < s.length(); i++)
  {
    total *= 10;
    a = s[i] - '0';
    if (a < 0 || a > 9)
      return -1; // 如果不在範圍內 就回傳-1 (執行main時會報使用者輸入錯誤)
    total += a;
  }
  return total; // 將值回傳回去
}

int main()
{
    vector<Data> data;
    Graph graph;
    WriteToVec("pairs401.bin",data);
    for(Data d : data){
        cout << d.getID << ' ' << d.putID << ' ' << d.weight << '\n';
    }
    graph.createGraph(data);
    graph.sort();
    graph.printAll();
}