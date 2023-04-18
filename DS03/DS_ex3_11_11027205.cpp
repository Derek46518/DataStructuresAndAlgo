// ��T�G�A 11027205 ���v��

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

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
				strcpy( data.id , file.CheakDataName( line, temp ).c_str() );
				strcpy( data.name , file.CheakDataName( line, temp ).c_str() );
				for ( int i=0; i < 6; i++ ) {
					data.score[i] = stoi( file.CheakDataName( line, temp ).c_str() ) ;
				} // for
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

			for ( int i=0 ; i < stNo ; i++ ) {
				binFile.read( (char*)&tempData, sizeof(tempData) ) ;
				data.push_back( tempData ) ;
			} // for

			binFile.close() ;
		} // void WriteToVec
		
		int CreateTable( int num ) {
			bool isPrime = false ;
			int count = 0 ;
			num  = num * (1.2) ;
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
			return num ;
		} // void CreateTable
		
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
			int key = 0 ; //���� 
			int quadraticNum = 0 ; // �I����n���誺�� 
			int collisionNum = 0 ; // �I����m 
			for( int i=0; i < data.size(); i++ ) {
				// �Ǹ� ascii �ۭ� 
				chr = data[i].id[0] ;
				for ( int j=1; data[i].id[j] != '\0'; j++ ) {
					chr = chr * ( data[i].id[j] ) ;
					// ��p�Ʀr 
					if ( chr > tableSize ) {
						chr = chr % tableSize ;
					} // if
				} // for

				// �]�w���ȻP�I����m 
				collisionNum = chr ;
				key = chr ;
				
				// table��m�w�Q��mdata 
				while ( table[collisionNum].id[0] != '\0' ) {
					// ��l�I����m 
					// collisionNum = key ; �o�殳�����ѷ|�L�a 
					// ����ƥ[ 1 (  �쥻�� 0 ) 
					quadraticNum++ ;
					collisionNum = collisionNum + ( quadraticNum*quadraticNum ) ;
					// �W�Ltable 
					if ( collisionNum > tableSize ) {
						collisionNum = collisionNum % tableSize ;
					} // if
				} // while
				
				// ��Jtable 
				table[collisionNum].key = key ;
				strcpy( table[collisionNum].id, data[i].id ) ;
				strcpy( table[collisionNum].name, data[i].name ) ;
				table[collisionNum].avg = data[i].avg ;
				
				// ��l�ƸI����m�P����� 
				collisionNum = 0 ;
				quadraticNum = 0 ; 
			} //  for
		} // void Insert
		
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
				
				binFile.close() ;
				txtFile.close();
			} // if

			else
				cout << "\n### " << filename << " does not exist! ###\n" ; 
		} // void Mission1

		void Mission2() {
            cout << "This is mission2\n" ;
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
