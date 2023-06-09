/**
 * @file DS2ex3_11027205_11027229.cpp
 * @author Nier and Derek (11027205 11027229)
 * @brief This is the Data Stucture homework 3
 * About Quadratic Probing and Double Hash
 *
 * @version 1.0
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2023
 * @warning please use C++ 11 to compile
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
	char id[10] = {'\0'};
	char name[10] = {'\0'};
	unsigned char score[6];
	float avg;
};

struct Table
{
	int key = 0;
	char id[10] = {'\0'};
	char name[10] = {'\0'};
	float avg;
};

class File
{
public:
	// cheak string is number
	bool IsNumber(string filename)
	{
		for (int i = 0; i < filename.length(); i++)
		{
			if (filename[i] - '0' < 0 || filename[i] - '0' > 9)
				return false;
		} // for
		return true;
	} // bool IsNumber

	string GetData(string &str, string &temp)
	{
		temp = "\0";
		int i = 0;
		int size = str.length();
		// Marge Data ( include space )
		for (i = 0; str[i] != '\t' && str[i] != '\n' && str[i] != '\0'; i++)
			temp = temp + str[i];
		for (int j = i + 1; j < size; j++) // respell str
			str[j - i - 1] = str[j];
		for (int j = size - i - 1; j < size; j++) // str last word + \0
			str[j] = '\0';
		return temp;
	} // string GetData()

	// modify filename
	void Cheak_filename(string &filename)
	{
		bool hasPoint = false;
		// cheak filename is or not all int
		if (IsNumber(filename))
			filename = "input" + filename + ".txt";

		else
		{
			for (int i = 0; i < filename.length(); i++)
			{
				// filename has '.'
				if (filename[i] == '.')
				{
					hasPoint = true;
					break;
				} // if ( hasPoint == true )
			}	  // for

			// filename has not '.'
			if (!hasPoint)
				filename = filename + ".txt";
		} // else
	}	  // string Cheak_filename
};		  // class File

class Hash
{
public:
	bool is_prime(int n)
	{
		if (n <= 1)
			return false;
		for (int i = 2; i * i <= n; i++)
		{
			if (n % i == 0)
				return false;
		} // for
		return true;
	} // bool is_prime

	int prime(int num)
	{
		while (!is_prime(num))
		{
			num++;
		} // while
		return num;
	} // int prime

	string CreateBinName(string filename)
	{
		string binFilename = "\0";
		binFilename = filename;
		binFilename = binFilename.erase(binFilename.size() - 3, 3) + "bin";
		return binFilename;
	} // string CreateBinFile

	// convert text to binary
	void ConvertToBin(string filename, string binFilename)
	{
		Data data;
		File file;
		ifstream txtFile;
		ofstream newFile;
		newFile.open(binFilename.c_str(), fstream::out | fstream::binary);
		txtFile.open(filename.c_str());

		string line = "\0", temp = "\0";
		getline(txtFile, line);
		while (line != "\0")
		{
			// insert id
			strcpy(data.id, file.GetData(line, temp).c_str());
			// insert name
			strcpy(data.name, file.GetData(line, temp).c_str());
			// insert 6 score
			for (int i = 0; i < 6; i++)
			{
				data.score[i] = stoi(file.GetData(line, temp).c_str());
			} // for
			// insert avg
			data.avg = stof(file.GetData(line, temp).c_str());
			newFile.write((char *)&data, sizeof(data));

			line = "\0";
			getline(txtFile, line);
		} // while

		newFile.close();
		txtFile.close();
	} // void ConvertToBin()

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

	int CreateTable(int num)
	{
		bool isPrime = false;
		float tableSize = num;
		int count = 0;
		num = (int)ceil((double)num * 1.2);
		num = prime(num);
		return num;
	} // void CreateTable

	void InsertToTable(Table table[], vector<Data> &data, int key, int insertPos, int vecPos, int &existingData)
	{
		existingData += 1;
		table[insertPos].key = key;
		strcpy(table[insertPos].id, data[vecPos].id);
		strcpy(table[insertPos].name, data[vecPos].name);
		table[insertPos].avg = data[vecPos].avg;
	} // void InsertToTable

	float UnSuccessAvg(float unSuccessNum, Table table[], int tableSize)
	{
		/* @parem step : how many step i do
		   @parem quadraticNum : squares number
		   @parem insertPos : insert position
		*/
		int step = 0;
		int quadraticNum = 0, insertPos = 0;
		for (int i = 0; i < tableSize; i++)
		{
			insertPos = i;
			while (table[insertPos].id[0] != '\0')
			{
				// init insert position
				insertPos = i;

				step += 1;
				quadraticNum += 1;
				insertPos = (insertPos + (quadraticNum * quadraticNum)) % tableSize;
			} // while

			// update unSuccessNum
			unSuccessNum = unSuccessNum + step;
			// init
			step = 0;
			quadraticNum = 0;
		} // for

		unSuccessNum = unSuccessNum / tableSize;
		return unSuccessNum;
	} // float UnSuccess

	float SuccessAvg(float successNum, int existingData)
	{
		successNum = successNum / existingData;
		return successNum;
	} // float Success

	void Bulid(Table table[], vector<Data> &data, int tableSize) {}
	void WriteToTxt(Table table[], string fileName) {}
}; // class Hash

class QuadraticProbing : public Hash
{
public:
	string CreateQuaName(string filename)
	{
		string quaFilename = "\0";
		quaFilename = filename;
		quaFilename = quaFilename.erase(0, 4);
		quaFilename = "quadratic" + quaFilename;
		return quaFilename;
	} // string CreateBinFile

	void Bulid(Table table[], vector<Data> &data, int tableSize, float &successNum, int &existingData)
	{
		char chr = '\0';
		/* @parem key : hash value
		   @parem h2key : h2 function hash value
		   @parem quadraticNum : squares number
		   @parem insertPos : insert position
		   @parem successStep : count unSuccess step
		*/
		long long key = 0;
		int temp = 0;
		int quadraticNum = 0, insertPos = 0;
		float successStep = 0.0;
		for (int i = 0; i < data.size(); i++)
		{
			// id ascii multiplied
			key = data[i].id[0];
			for (int j = 1; data[i].id[j] != '\0'; j++)
			{
				temp = data[i].id[j];
				key = key * temp;
			} // for

			key = key % tableSize;

			// set insert position
			insertPos = key;

			// insert position has data
			while (table[insertPos].id[0] != '\0')
			{
				successStep += 1;
				// init insert position
				insertPos = key;
				// squares number + 1
				quadraticNum += 1;
				insertPos = (insertPos + (quadraticNum * quadraticNum)) % tableSize;
			} // while

			successStep += 1;
			successNum = successNum + successStep;

			// insert data do table
			InsertToTable(table, data, key, insertPos, i, existingData);

			// init
			quadraticNum = 0;
			successStep = 0.0;
		} //  for
	}	  // void Build

	void WriteToTxt(Table table[], string quaFilename, int tableSize)
	{
		ofstream newFile;
		newFile.open(quaFilename.c_str());
		newFile << "--- Hash table created by Quadratic probing ---\n";
		for (int i = 0; i < tableSize; i++)
		{
			newFile << "[" << i << "]\t";
			if (table[i].id[0] == '\0')
			{
				newFile << "\n";
			} // if

			else
			{
				newFile << table[i].key << ",\t";
				newFile << table[i].id << ",\t";
				newFile << table[i].name << ",   \t";
				newFile << table[i].avg << "\n";
			} // else
		}	  // for

		newFile << "-------------------------------------------------\n";
		newFile.close();
	} // void WriteToTxt()

}; // class QuadraticProbing

class DoubleHash : public Hash
{
public:
	string CreateDouName(string filename)
	{
		string douFilename = "\0";
		douFilename = filename;
		douFilename = douFilename.erase(0, 4);
		douFilename = "double" + douFilename;
		return douFilename;
	} // string CreateBinFile

	int HighStep(int num)
	{
		bool isPrime = false;
		int count = 0;
		num = num / 3 + 1;
		num = prime(num);
		return num;
	} // int HighStep

	void Bulid(Table table[], vector<Data> &data, int tableSize, float &successNum, int &existingData)
	{
		char chr = '\0';
		/* @parem key : hash value
		   @parem h2key : h2 function hash value
		   @parem successStep : count success step
		*/
		long long key = 0, h2key = 0;
		int temp = 0, insertPos = 0, highStep = 0;
		float successStep = 0.0;
		highStep = HighStep(data.size());

		for (int i = 0; i < data.size(); i++)
		{
			// id ascii multiplied
			key = data[i].id[0];
			for (int j = 1; data[i].id[j] != '\0'; j++)
			{
				temp = data[i].id[j];
				key = key * temp;
			} // for

			// set h2 hash value
			h2key = key;
			// set h1 hash value
			key = key % tableSize;
			// set insert position
			insertPos = key;
			h2key = highStep - (h2key % highStep);

			// ( h2 function ) collision
			while (table[insertPos].id[0] != '\0')
			{
				successStep += 1;
				insertPos = (insertPos + h2key) % tableSize;
			} // while ( h2 function )

			successStep += 1;
			successNum = successNum + successStep;
			// insert data do table
			InsertToTable(table, data, key, insertPos, i, existingData);
			// init
			successStep = 0.0;
		} // for
	}	  // void Bulid

	void WriteToTxt(Table table[], string douFilename, int tableSize)
	{
		ofstream newFile;
		newFile.open(douFilename.c_str());
		newFile << "--- Hash table created by Double hashing ---\n";
		for (int i = 0; i < tableSize; i++)
		{
			newFile << "[" << i << "]\t";
			if (table[i].id[0] == '\0')
			{
				newFile << "\n";
			} // if

			else
			{
				newFile << table[i].key << ",\t";
				newFile << table[i].id << ",\t";
				newFile << table[i].name << ",   \t";
				newFile << table[i].avg << "\n";
			} // else
		}	  // for

		newFile << "-------------------------------------------------\n";
		newFile.close();
	} // void WriteToTxt()
};	  // class DoubleHash

class Mission
{
public:
	bool is_prime(int n)
	{
		if (n <= 1)
			return false;
		for (int i = 2; i * i <= n; i++)
		{
			if (n % i == 0)
				return false;
		} // for
		return true;
	} // bool is_prime

	int prime(int num)
	{
		while (!is_prime(num))
		{
			num++;
		} // while
		return num;
	} // int prime
	int HighStep(int num)
	{
		bool isPrime = false;
		int count = 0;
		num = num / 3 + 1;
		num = prime(num);
		return num;
	} // int HighStep
	void Mission1()
	{
		File file;
		QuadraticProbing QP;
		vector<Data> data; // store binary data

		ifstream txtFile;
		ifstream binFile;
		string filename = "\0";
		string binFilename = "\0";
		string quaFilename = "\0";

		cout << "\nInput your files ( 301, input301.txt ) : ";
		cin >> filename;
		file.Cheak_filename(filename); // modify fileName
		txtFile.open(filename.c_str());

		if (txtFile.is_open())
		{
			binFilename = QP.CreateBinName(filename);
			binFile.open(binFilename.c_str());
			if (!binFile.is_open())
			{
				cout << "### " << binFilename << " does not exsit! ###\n";
				// convert text to binary
				QP.ConvertToBin(filename, binFilename);
				binFile.open(binFilename.c_str());
			} // if

			// write binary to vec
			QP.WriteToVec(binFilename, data);
			int tableSize = 0;
			// count table size
			tableSize = QP.CreateTable(data.size());
			// declare table
			Table table[tableSize];
			/* @ parem existingData : count insert to table data
			   @ parem unSuccessNum : count unSuccess insert
			   @ parem successNum : count success insert
			*/
			int existingData = 0;
			float unSuccessNum = 0.0000;
			float successNum = 0.0000;
			// bulid table
			QP.Bulid(table, data, tableSize, successNum, existingData);
			quaFilename = QP.CreateQuaName(filename);
			// wrire table to txt
			QP.WriteToTxt(table, quaFilename, tableSize);

			unSuccessNum = QP.UnSuccessAvg(unSuccessNum, table, tableSize);
			successNum = QP.SuccessAvg(successNum, existingData);

			cout << endl
				 << "Hash table has been successfully created by Quadratic probing";
			cout << endl
				 << "unsuccessful search: " << fixed << setprecision(4) << unSuccessNum << " comparisons on average";
			cout << endl
				 << "\nsuccessful search: " << fixed << setprecision(4) << successNum << " comparisons on average\n";

			findItem(table, data, 1, tableSize);
			binFile.close();
			txtFile.close();
		} // if

		else
			cout << "\n\n### " << filename << " does not exist! ###\n";
	} // void Mission1

	void findItem(Table table[], vector<Data> &dataVec, int code, int tableSize)
	{
		string data;
		cout << "Input a student ID to search ([0] Quit):";
		cin >> data;
		long long int key, h2key;
		int temp;
		int insertPos = 0;
		int probes = 1;
		int quadraticNum = 0;
		int highStep = HighStep(tableSize);
		key = data[0];
		while (data != "0")
		{
			for (int j = 1; data[j] != '\0'; j++)
			{
				temp = data[j];
				key = key * temp;
			} // for

			switch (code)
			{

			case 1:
				key %= tableSize;
				while (table[insertPos].id[0] != '\0')
				{
					
					
					if (strcmp(data.c_str(), table[insertPos].id))
					{
						insertPos = key;
						quadraticNum += 1;
						probes += 1;
						insertPos = (insertPos + (quadraticNum * quadraticNum)) % tableSize;
						cout << insertPos << "\n";
					}
					else
					{
						cout << "{ " << table[insertPos].id << ", " << table[insertPos].name << ", " << table[insertPos].avg << " } "
							 << "is found after " << probes << " probes.\n";
						break;
					}
				}
				if (table[insertPos].id[0] == '\0')
				{
					cout << data << " is not found after " << probes << " probes.\n";
				}

				break;
			case 2:
				h2key = key;
				key = key % tableSize;
				insertPos = key;
				highStep = HighStep(dataVec.size());
				h2key = highStep - (h2key % highStep);
				cout << insertPos << '\n';
				while ( table[insertPos].id[0] != '\0' ) {
					
					if(strcmp(data.c_str(),table[insertPos].id)){
						probes+=1;
						insertPos = ( insertPos  + h2key ) % tableSize ;
						cout << insertPos << "\n";
					}
					else {
						cout << "{ " << table[insertPos].id << ", " << table[insertPos].name << ", " << table[insertPos].avg << " } "
							 << "is found after " << probes << " probes.\n";
						break;
					}
					
				} // while ( h2 function )
				if (table[insertPos].id[0] == '\0')
				{
					cout << data << " is not found after " << probes << " probes.\n";
				}
				break;
			}
			h2key = 0;
			highStep = HighStep(tableSize);
			insertPos = 0;
			probes = 1;
			quadraticNum = 0;
			cout << "Input a student ID to search ([0] Quit):";
			cin >> data;
			key = data[0];
		}

		
		
	}

	void Mission2()
	{
		File file;
		DoubleHash DH;
		vector<Data> data; // store binary data

		ifstream txtFile;
		ifstream binFile;
		string filename = "\0";
		string binFilename = "\0";
		string douFilename = "\0";

		cout << "\nInput your files ( 301, input301.txt ) : ";
		cin >> filename;
		file.Cheak_filename(filename); // modify fileName
		txtFile.open(filename.c_str());

		if (txtFile.is_open())
		{
			binFilename = DH.CreateBinName(filename);
			binFile.open(binFilename.c_str());
			if (!binFile.is_open())
			{
				cout << "### " << binFilename << " does not exsit! ###\n";
				// convert text to binary
				DH.ConvertToBin(filename, binFilename);
				binFile.open(binFilename.c_str());
			} // if

			// write binary to vec
			DH.WriteToVec(binFilename, data);
			int tableSize = 0;
			// count table size
			tableSize = DH.CreateTable(data.size());
			// declare table
			Table table[tableSize];
			/* @ parem existingData : count insert to table data
			   @ parem successNum : count success insert
			*/
			int existingData = 0;
			float successNum = 0.0000;
			// bulid table
			DH.Bulid(table, data, tableSize, successNum, existingData);
			douFilename = DH.CreateDouName(filename);
			// wrire table to txt
			DH.WriteToTxt(table, douFilename, tableSize);

			successNum = DH.SuccessAvg(successNum, existingData);

			cout << endl
				 << "Hash table has been successfully created by Double hashing";
			cout << endl
				 << "\nsuccessful search: " << successNum << fixed << setprecision(4) << " comparisons on average\n";
			findItem(table, data, 2, tableSize);
			binFile.close();
			txtFile.close();
		} // if

		else
			cout << "\n\n### " << filename << " does not exist! ###\n";
	} // void Mission2
};	  // class Mission

void Start()
{
	int command = 0;
	Mission mission;
	do
	{
		cout << "\n****** Hash Table ******";
		cout << "\n* 0. QUIT              *";
		cout << "\n* 1. Quadratic probing *";
		cout << "\n* 2. Double hashing    *";
		cout << "\n************************";
		cout << "\nInput your command ( 0, 1, 2 ) : ";
		cin >> command;
		switch (command)
		{
		case (0):
			cout << "\nexit";
			break;
		case (1):
			mission.Mission1();
			break;
		case (2):
			mission.Mission2();
			break;
		default:
			cout << "\n### Command does not exist! ###\n";
		}				   // switch
	} while (command > 0); // do while
} // void start()

int main()
{
	Start();
} // int main()
