// 資訊二乙 11027205 蔡宗勳

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Data {
	char id[10] ;
	char name[10] ;
	unsigned char score[6] ;
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
		
		string CreateBinName( string filename ) {
			string binFilename = "\0" ;
			binFilename = filename ;
			binFilename = binFilename.erase( binFilename.size()-3, 3 ) + "bin" ;
			return binFilename ;
		} // string CreateBinFile
		
		void ConvertToBin( string filename, string binFilename ) {
			ifstream in  ;
			ofstream newFile ;
			newFile.open( binFilename.c_str() ) ;
			in.open( filename.c_str() ) ;
			
			int score = 0 ;
			float avg  = 0.0 ;
			unsigned char chr ='\0' ;
			string line =  "\0", temp = "\0" ;
			getline(in, line) ; 
			while( line != "\0" ) {
				newFile << CheakDataName( line, temp ) + "\t" ;
				newFile << CheakDataName( line, temp ) + "\t" ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				chr = stoi( CheakDataName( line, temp ) ) ;
				newFile << chr ;
				newFile << "\t" ;
				avg = stof ( CheakDataName( line, temp ) ) ;
				newFile << avg ;
				newFile << "\n" ;

				line = "\0" ;
				getline(in, line) ; 
			} // while
			
			newFile.close() ;
			in.close() ;
		} // void ConvertToBin()
		
}; // class File

class Mission {
	public :
		void Mission1() {
			File file ;
			ifstream in ;
			ifstream in2  ;
			string filename = "\0" ;
			string binFilename = "\0" ;
			
			cout << "\nInput your files ( 301, input301.txt ) : " ;
			cin >> filename ;
			file.Cheak_filename( filename ) ; // modify fileName 
			in.open( filename.c_str() ) ;

			if ( in.is_open() ) {
				binFilename = file.CreateBinName( filename ) ;
				in2.open( binFilename.c_str() ) ;
				if ( !in2.is_open() ) {
					file.ConvertToBin( filename, binFilename ) ;
				} // if
				
				in2.close() ;
				in.close();
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
