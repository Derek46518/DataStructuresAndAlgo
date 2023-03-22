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
    a.push_back("��߲M�ؤj��");
    a.push_back("��߻O�W�j��");
    a.push_back("��ߦ��\\�j��");
    a.push_back("��ߤ����j��");
    a.push_back("��ߥ�q�j��");
    a.push_back("��ߤ����j��");
    a.push_back("��ߤ��s�j��");
    a.push_back("��߻O�W���v�j��");
    a.push_back("��ߤ����j��");
    a.push_back("��߹��Ʈv�d�j��");
    a.push_back("��߻O�_�j��");
    a.push_back("��߻O�n�j��");
    a.push_back("�F���j��");
    a.push_back("�����j��");
    a.push_back("�F�d�j��");
    a.push_back("����j��");
    a.push_back("�H���j��");
    a.push_back("�����Ƥj��");
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
