// ��T�G�A 11027205 ���v��

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Data {
	char id[10] = {'\0'} ;
	char name[10] = {'\0'};
	unsigned char score[6] ;
	float avg ;	
};

struct Table {
	int key = 0 ;
	char id[10] = {'\0'} ;
	char name[10] = {'\0'};
	float avg ;	
};

class File {
	public :

        // �T�{�ɦW�O�_���Ʀr 
		bool IsNumber( string filename ) {
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i]-'0' < 0 || filename[i]-'0' > 9 )
					return false;
			} // for
			return true ;
		} // bool IsNumber

        // ���X�ɮשһݪ����e �çR���w���Ϊ� Data 
		string CheakDataName( string &str, string &temp ) {
			temp = "\0" ;
			int i = 0 ;
			int size = str.length() ;
            // Marge Data ( include space )
			for( i=0; str[i] != '\t' && str[i] != '\n' && str[i] != '\0'; i++ )
				temp = temp + str[i] ;
			for( int j=i+1; j < size; j++ )    // respell str
				str[j-i-1] = str[j] ;
			for( int j=size-i-1; j<size; j++ ) // str last word + \0
				str[j] = '\0' ;
			return temp ;
		} // CheakDataName()

        // �ק��ɦW 
		void Cheak_filename( string &filename ) {
			bool hasPoint = false ;
            // �ɦW���O�Ʀr
			if ( IsNumber( filename ) ) 
				filename = "input" + filename + ".txt" ;

            // �ɦW�]�t�Ʀr�H�~���r�� 
			else {
				for ( int i = 0; i < filename.length(); i++ ) {
                    // �ɦW�]�t '.'
					if ( filename[i] == '.') {
						hasPoint = true ;
						break ;
					} // if ( hasPoint == true ) 
				} // for

                // �ɦW���]�t '.'
	  		    if ( !hasPoint )
		  		    filename = filename + ".txt" ;
			} // else
		} // string Cheak_filename
}; // class File

class Hash {
	public :
		
		bool is_prime(int n) {
    		if (n <= 1) {
        		return false;
    		}
    		for (int i = 2; i*i <= n; i++) {
        		if (n % i == 0) {
            		return false;
        		}
    		}
    		return true;
		}

		int prime( int num){
			while (!is_prime(num)) {
        		num++;
    		}
			return num;
		}

		string CreateBinName( string filename ) {
			string binFilename = "\0" ;
			binFilename = filename ;
			binFilename = binFilename.erase( binFilename.size()-3, 3 ) + "bin" ;
			return binFilename ;
		} // string CreateBinFile

		// convert text to binary
		void ConvertToBin( string filename, string binFilename ) {
			Data data ;
			File file ;
			ifstream txtFile  ;
			ofstream newFile ;
			newFile.open( binFilename.c_str(), fstream::out|fstream::binary ) ;
			txtFile.open( filename.c_str() ) ;

			string line =  "\0", temp = "\0" ;
			getline(txtFile, line) ; 
			while( line != "\0" ) {
				// insert id
				strcpy( data.id , file.CheakDataName( line, temp ).c_str() );
				// insert name
				strcpy( data.name , file.CheakDataName( line, temp ).c_str() );
				// insert 6 score
				for ( int i=0; i < 6; i++ ) {
					data.score[i] = stoi( file.CheakDataName( line, temp ).c_str() ) ;
				} // for
				// insert avg
				data.avg = stof( file.CheakDataName( line, temp ).c_str() ) ;
			    newFile.write( (char*)&data, sizeof(data) ) ;

				line = "\0" ;
				getline(txtFile, line) ; 
			} // while
			
			newFile.close() ;
			txtFile.close() ;
		} // void ConvertToBin()
		
		//  write binary to struct
		void WriteToVec( string binFilename, vector<Data> &data ) {
			Data tempData ;
			int stNo = 0 ;
			
			fstream binFile ;
			binFile.open( binFilename.c_str(), fstream::in|fstream::binary) ;
			binFile.seekg( 0, binFile.end ) ;
			stNo = binFile.tellg() / sizeof(tempData) ;
			binFile.seekg( 0, binFile.beg ) ;

			// push binary data to vec
			for ( int i=0 ; i < stNo ; i++ ) {
				binFile.read( (char*)&tempData, sizeof(tempData) ) ;
				data.push_back( tempData ) ;
			} // for

			binFile.close() ;
		} // void WriteToVec
		
		int CreateTable( int num ) {
			bool isPrime = false ;
			float tableSize = num ;
			int count = 0 ;
			
			
			
			num = (int)ceil((double)num*1.2);
			num = prime(num);
			/*
			// count prime num 
			while ( isPrime == false ) {
				count = 0 ;
				for ( int i = 1; i <= num/2; i++ ) {
					if ( num % i == 0 ) {
						count++ ; 
					} // if
					
					if ( count > 1 ) {
						count = 0 ;
						break ;
					} // if 
				} // for
				
				if ( count == 1 ) isPrime = true ;
				else num++ ;
			} // while
			*/
			return num ;
		} // void CreateTable
		
		void Bulid( Table table[], vector<Data> &data, int tableSize ) {}
		void WriteToTxt( Table table[], string fileName ) {}
}; // class Hash

class QuadraticProbing : public Hash {
	public :
		string CreateQuaName( string filename ) {
			string quaFilename = "\0" ;
			quaFilename = filename ;
			quaFilename = quaFilename.erase( 0, 4 )  ;
			quaFilename = "quadratic" + quaFilename ;
			return quaFilename ;
		} // string CreateBinFile
		
		void Bulid( Table table[], vector<Data> &data, int tableSize ) {
			char chr = '\0' ; 
			/* @parem key : �����
			   @parem h2key : h2 function �p��I���� 
			   @parem quadraticNum : �I����n���誺��
			   @parem insertPos : insert position
			*/
			int key = 0, temp = 0 ;
			int quadraticNum = 0, insertPos = 0 ; 
			for( int i=0; i < data.size(); i++ ) {
				// �Ǹ� ascii �ۭ� 
				key = data[i].id[0] ;
				for ( int j=1; data[i].id[j] != '\0'; j++ ) {
					temp = data[i].id[j] ;
					key = key * temp ;
					// ��p�Ʀr 
					
					key = key % tableSize ;
					
				} // for
				
				key = key % tableSize ;

				// set insert position
				insertPos = key ;
				
				// table��m�w�Q��mdata 
				while ( table[insertPos].id[0] != '\0' ) {
					// init insert position 
					insertPos = key ;
					// ����ƥ[ 1 (  �쥻�� 0 ) 
					quadraticNum++ ;
					insertPos = insertPos + ( quadraticNum*quadraticNum ) ;
					// �W�Ltable 
					if ( insertPos >= tableSize ) {
						insertPos = insertPos % tableSize ;
					} // if
				} // while
				
				// ��Jtable 
				table[insertPos].key = key ;
				strcpy( table[insertPos].id, data[i].id ) ;
				strcpy( table[insertPos].name, data[i].name ) ;
				table[insertPos].avg = data[i].avg ;
				
				// ��l�ƸI����m�P����� 
				insertPos = 0 ;
				quadraticNum = 0 ; 
			} //  for
		} // void Build
		
		void WriteToTxt( Table table[], string quaFilename, int tableSize ) {
			ofstream newFile ;
			newFile.open( quaFilename.c_str() ) ;
			newFile <<  "--- Hash table created by Quadratic probing ---\n" ;
			for ( int i=0; i < tableSize; i++ ) {
				newFile << "[" << i << "]\t" ;
				if ( table[i].id[0] == '\0' ) {
					newFile << "\n" ;
				} // if
				
				else {
					newFile << table[i].key  <<  ",\t" ;
					newFile << table[i].id   <<  ",\t" ;
					newFile << table[i].name <<  ",   \t" ;
					newFile << table[i].avg  <<  "\n" ;
				} // else
			} // for
			 
			newFile <<  "-------------------------------------------------\n" ;
			newFile.close() ;
		} // void WriteToTxt()

}; // class QuadraticProbing

class DoubleHash : public Hash{
	public :
		string CreateDouName( string filename ) {
			string douFilename = "\0" ;
			douFilename = filename ;
			douFilename = douFilename.erase( 0, 4 )  ;
			douFilename = "double" + douFilename ;
			return douFilename ;
		} // string CreateBinFile
		
		
		
		
		int HighStep( int num ) {
			bool isPrime = false ;
			float tableSize = num ;
			int count = 0 ;
			num = (int)ceil((double)num/3)+1;
			// count prime num 
			
			num = prime(num);
			return num ;
		} // int HighStep
		
		void Bulid( Table table[], vector<Data> &data, int tableSize ) {
			char chr = '\0' ; 
			/* @parem key : �����
			   @parem h2key : h2 function �����
			*/
			long long key = 0, h2key = 0 ;
			int  temp = 0,  insertPos = 0, highStep = 0 ;
			highStep = HighStep( data.size() ) ;
			
			for ( int i=0; i < data.size(); i++ ) {
				// �Ǹ� ascii �ۭ� 
				key = data[i].id[0] ;
				for ( int j=1; data[i].id[j] != '\0'; j++ ) {
					temp = data[i].id[j] ;
					key = key * temp ;
				} // for
				
				h2key = key ;
				key = key % tableSize ;
				
				
				// �]�w�I����m 
				insertPos = key ;
				cout << "name : " << data[i].name << " key : " << key << endl ;
				cout << "h2key : " << h2key << endl;
				// table��m�w�Q��mdata 
				if ( table[insertPos].id[0] != '\0' ) {
					h2key = highStep - ( h2key % highStep ) ;
					insertPos = key  + h2key ;
					
					cout << "highstep : " << highStep << endl;
					insertPos = insertPos % tableSize ;
					cout << "insertPos : " << insertPos << endl;	
						
					if ( table[insertPos].id[0] != '\0' ) {
						int cycle = 0 ;
						cycle = insertPos + ( tableSize - key ) ;
						cout << "insertPos : " << insertPos << endl ;
						while ( table[insertPos].id[0] != '\0' ) {
							insertPos = insertPos + cycle ;
							if ( insertPos >= tableSize )
								insertPos = insertPos % tableSize ;
						} // while
					} // if

					cout << "insertPos : " << insertPos << endl ; 
				} // if
				
				// ��Jtable 
				table[insertPos].key = key ;
				strcpy( table[insertPos].id, data[i].id ) ;
				strcpy( table[insertPos].name, data[i].name ) ;
				table[insertPos].avg = data[i].avg ;
				
				key = 0 ;
				h2key = 0 ;
				
			} // for

		} // void Bulid
		
		void WriteToTxt( Table table[], string douFilename, int tableSize ) {
			ofstream newFile ;
			newFile.open( douFilename.c_str() ) ;
			newFile <<  "--- Hash table created by Double hashing ---\n" ;
			for ( int i=0; i < tableSize; i++ ) {
				newFile << "[" << i << "]\t" ;
				if ( table[i].id[0] == '\0' ) {
					newFile << "\n" ;
				} // if
				
				else {
					newFile << table[i].key  <<  ",\t" ;
					newFile << table[i].id   <<  ",\t" ;
					newFile << table[i].name <<  ",   \t" ;
					newFile << table[i].avg  <<  "\n" ;
				} // else
			} // for
			 
			newFile <<  "-------------------------------------------------\n" ;
			newFile.close() ;
		} // void WriteToTxt()
}; // class DoubleHash

class Mission {
	public :
		void Mission1() {
			File file ;
			QuadraticProbing QP ;
			vector<Data> data ; // store binary data
			
			ifstream txtFile ;
			ifstream binFile  ;
			string filename = "\0" ;
			string binFilename = "\0" ;
			string quaFilename = "\0" ;
			
			cout << "\nInput your files ( 301, input301.txt ) : " ;
			cin >> filename ;
			file.Cheak_filename( filename ) ; // modify fileName 
			txtFile.open( filename.c_str() ) ;

			if ( txtFile.is_open() ) {
				binFilename = QP.CreateBinName( filename ) ;
				binFile.open( binFilename.c_str() ) ;
				if ( !binFile.is_open() ) {
					cout << "### " << binFilename << " does not exsit! ###\n" ;
					// convert text to binary
					QP.ConvertToBin( filename, binFilename ) ;
					binFile.open( binFilename.c_str() ) ;
				} // if
				
				// write binary to vec
				QP.WriteToVec( binFilename, data ) ;
				int tableSize = 0 ;
				// count table size
				tableSize = QP.CreateTable( data.size() ) ;
				// declare table
				Table table[tableSize] ;
				// bulid table
				QP.Bulid( table, data, tableSize ) ;
				quaFilename = QP.CreateQuaName( filename ) ;
				// wrire table to txt
				QP.WriteToTxt( table, quaFilename, tableSize ) ;
				
				cout << endl << "Hash table has been successfully created by Quadratic probing" ;
				cout << endl << "unsuccessful search: " << "" << " comparisons on average" ;
				cout << endl << "\nsuccessful search: " << "" << " comparisons on average\n" ;
				
				binFile.close() ;
				txtFile.close();
			} // if

			else
				cout << "\n\n### " << filename << " does not exist! ###\n" ; 
		} // void Mission1

		void Mission2() {
			File file ;
			DoubleHash DH ;
			vector<Data> data ; // store binary data
			
			ifstream txtFile ;
			ifstream binFile  ;
			string filename = "\0" ;
			string binFilename = "\0" ;
			string douFilename = "\0" ;
			
			cout << "\nInput your files ( 301, input301.txt ) : " ;
			cin >> filename ;
			file.Cheak_filename( filename ) ; // modify fileName 
			txtFile.open( filename.c_str() ) ;

			if ( txtFile.is_open() ) {
				binFilename = DH.CreateBinName( filename ) ;
				binFile.open( binFilename.c_str() ) ;
				if ( !binFile.is_open() ) {
					cout << "### " << binFilename << " does not exsit! ###\n" ;
					// convert text to binary
					DH.ConvertToBin( filename, binFilename ) ;
					binFile.open( binFilename.c_str() ) ;
				} // if
				
				// write binary to vec
				DH.WriteToVec( binFilename, data ) ;
				int tableSize = 0 ;
				// count table size
				tableSize = DH.CreateTable( data.size() ) ;
				// declare table
				Table table[tableSize] ;
				// bulid table
				DH.Bulid( table, data, tableSize ) ;
				douFilename = DH.CreateDouName( filename ) ;
				// wrire table to txt
				DH.WriteToTxt( table, douFilename, tableSize ) ;
				
				cout << endl << "Hash table has been successfully created by Double hashing" ;
				cout << endl << "unsuccessful search: " << "" << " comparisons on average" ;
				cout << endl << "\nsuccessful search: " << "" << " comparisons on average\n" ;
				
				binFile.close() ;
				txtFile.close();
			} // if

			else
				cout << "\n\n### " << filename << " does not exist! ###\n" ; 
		} // void Mission2
}; // class Mission

void Start() {
    int command = 0 ;
	Mission mission ;
	do{
	    cout << "\n****** Hash Table ******" ;
        cout << "\n* 0. QUIT              *" ;
        cout << "\n* 1. Quadratic probing *" ;
        cout << "\n* 2. Double hashing    *" ;
        cout << "\n************************" ;
        cout << "\nInput your command ( 0, 1, 2 ) : " ;
        cin >> command ;
        switch ( command ) {
    	    case( 0 ) :
    		    cout << "\nexit" ;
    	    break ;
		    case( 1 ) :
		  	    mission.Mission1() ;
		  	    break ;
		    case( 2 ) :
		  	    mission.Mission2() ;
		  	    break ;
		    default :
		  	    cout << "\n### Command does not exist! ###\n" ;
	    } // switch
	} while ( command > 0 ) ; // do while
} // void start()

int main() { 
	Start() ;
} // int main()
