/**
 * @file DS2ex2_11027229_11027105.cpp
 * @author Derek and Nier (11027229 11027205)
 * @brief This is the Data Stucture homework 2
 * About 2-3 Tree and AVL Tree implementation
 *
 * @version 1.0
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023
 * @warning please use C++ 11 to compile
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctype.h>
#include <algorithm>
using namespace std;

int main(){

    vector<string> a;
    a.push_back("國立清華大學");
    a.push_back("國立臺灣大學");
    a.push_back("國立成功\大學");
    a.push_back("國立中興大學");
    a.push_back("國立交通大學");
    a.push_back("國立中央大學");
    a.push_back("國立中山大學");
    a.push_back("國立臺灣海洋大學");
    a.push_back("國立中正大學");
    a.push_back("國立彰化師範大學");
    a.push_back("國立臺北大學");
    a.push_back("國立臺南大學");
    a.push_back("東海大學");
    a.push_back("輔仁大學");
    a.push_back("東吳大學");
    a.push_back("中原大學");
    a.push_back("淡江大學");
    a.push_back("中國文化大學");
    for( int i = 0 ; i < a.size() ; i ++ ) {
        for( int j = 0 ; j < a.size() ; j++) {
            if(a[i] > a[j])
                swap(a[i], a[j] );
        }
    }
    for( int j = 0 ; j < a.size() ; j++) {
        cout << a[j] << endl;
    }
}
