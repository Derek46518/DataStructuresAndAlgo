// 資訊二乙 11027205 蔡宗勳

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

        // 確認檔名是否為數字 
		bool IsNumber( string filename ) {
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i]-'0' < 0 || filename[i]-'0' > 9 )
					return false;
			} // for
			return true ;
		} // bool IsNumber

        // 取出檔案所需的內容 並刪除已取用的 Data 
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

        // 修改檔名 
		void Cheak_filename( string &filename ) {
			bool hasPoint = false ;
            // 檔名都是數字
			if ( IsNumber( filename ) ) 
				filename = "input" + filename + ".txt" ;

            // 檔名包含數字以外的字元 
			else {
				for ( int i = 0; i < filename.length(); i++ ) {
                    // 檔名包含 '.'
					if ( filename[i] == '.') {
						hasPoint = true ;
						break ;
					} // if ( hasPoint == true ) 
				} // for

                // 檔名不包含 '.'
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
			
			num = num * (1.2) ;
			tableSize  = tableSize * (1.2) ;
			// 整數乘 1.2 如有小數點 需進位 
			if ( tableSize - (int)tableSize != 0 ) num = num + 1 ;
			
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
			/* @parem key : 雜湊值
			   @parem h2key : h2 function 計算碰撞用 
			   @parem quadraticNum : 碰撞後要平方的值
			   @parem insertPos : insert position
			*/
			int key = 0, temp = 0 ;
			int quadraticNum = 0, insertPos = 0 ; 
			for( int i=0; i < data.size(); i++ ) {
				// 學號 ascii 相乘 
				key = data[i].id[0] ;
				for ( int j=1; data[i].id[j] != '\0'; j++ ) {
					temp = data[i].id[j] ;
					key = key * temp ;
					// 減小數字 
					if ( key >= tableSize ) {
						key = key % tableSize ;
					} // if
				} // for
				
				if ( key >= tableSize ) {
					key = key % tableSize ;
				} // if

				// set insert position
				insertPos = key ;
				
				// table位置已被放置data 
				while ( table[insertPos].id[0] != '\0' ) {
					// init insert position 
					insertPos = key ;
					// 平方數加 1 (  原本為 0 ) 
					quadraticNum++ ;
					insertPos = insertPos + ( quadraticNum*quadraticNum ) ;
					// 超過table 
					if ( insertPos >= tableSize ) {
						insertPos = insertPos % tableSize ;
					} // if
				} // while
				
				// 放入table 
				table[insertPos].key = key ;
				strcpy( table[insertPos].id, data[i].id ) ;
				strcpy( table[insertPos].name, data[i].name ) ;
				table[insertPos].avg = data[i].avg ;
				
				// 初始化碰撞位置與平方值 
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
			
			num = num / 3 ;
			tableSize  = tableSize / 3 ;
			// 整數除 3 如有小數點 需進位 
			if ( tableSize - (int)tableSize != 0 ) num = num + 1 ;
			
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
			return num ;
		} // int HighStep
		
		void Bulid( Table table[], vector<Data> &data, int tableSize ) {
			char chr = '\0' ; 
			/* @parem key : 雜湊值
			   @parem h2key : h2 function 計算碰撞用
			*/
			long long key = 0, h2key = 0 ;
			int  temp = 0,  insertPos = 0, highStep = 0 ;
			highStep = HighStep( data.size() ) ;
			
			for ( int i=0; i < data.size(); i++ ) {
				// 學號 ascii 相乘 
				key = data[i].id[0] ;
				for ( int j=1; data[i].id[j] != '\0'; j++ ) {
					temp = data[i].id[j] ;
					key = key * temp ;
				} // for
				
				h2key = key ;
				if ( key >= tableSize ) {
					key = key % tableSize ;
				} // if
				
				// 設定碰撞位置 
				insertPos = key ;
				cout << "name : " << data[i].name << " key : " << key << endl ;
				
				// table位置已被放置data 
				if ( table[key].id[0] != '\0' ) {
					h2key = highStep - ( h2key % highStep ) ;
					insertPos = h2key ;
					cout << "insertPos : " << insertPos << endl ; 
				} // if
				
				// 放入table 
				table[insertPos].key = key ;
				strcpy( table[insertPos].id, data[i].id ) ;
				strcpy( table[insertPos].name, data[i].name ) ;
				table[insertPos].avg = data[i].avg ;
				
			} // for

		} // void Bulid
		
		void WriteToTxt( Table table[], string douFilename, int tableSize ) {
			ofstream newFile ;
			newFile.open( douFilename.c_str() ) ;
			newFile <<  "--- Hash table created by Double hash ---\n" ;
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
