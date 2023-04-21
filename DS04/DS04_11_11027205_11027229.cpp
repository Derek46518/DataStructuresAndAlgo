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

using namespace std;

struct Data
{
    char putID[10] = {'\0'};
    char getID[10] = {'\0'};
    float weight;
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

int main()
{
    vector<Data> data;
    WriteToVec("pairs401.bin",data);
    for(Data d : data){
        cout << d.putID << '\n';
        cout << d.getID << '\n';
        cout << d.weight <<'\n';
    }
}