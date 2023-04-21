#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>


using namespace std;
int main(){
    fstream in;
    string line,file;
    in.open("input1.txt",fstream::in);
    while(getline(in,line)){
        cout << line<<endl;
    }
    
}