// 11027205

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

struct Data {
	char id1[10] = {'\0'} ;
	char id2[10] = {'\0'} ;
	float weight ;	
};

struct Receiver {
	char id[10] = {'\0'} ;
	float weight ;	
}; 

struct Sender {
	char id[10] = {'\0'} ;
	vector<Receiver> receiver ;
};

class File {
	public :

        // cheak string is number
		bool IsNumber( string filename ) {
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i]-'0' < 0 || filename[i]-'0' > 9 )
					return false;
			} // for
			return true ;
		} // bool IsNumber
		
		bool IsFloat( string filename ) {
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i] != '.' && ( filename[i]-'0' < 0 || filename[i]-'0' > 9 ) )
					return false;
			} // for
			return true ;
		} // bool IsNumber

		string GetData( string &str, string &temp ) {
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
		} // string GetData()

        // modify filename
		void Cheak_filename( string &filename ) {
			bool hasPoint = false ;
            // cheak filename is or not all int
			if ( IsNumber( filename ) ) 
				filename = "pairs" + filename + ".bin" ;

			else {
				for ( int i = 0; i < filename.length(); i++ ) {
                    // filename has '.'
					if ( filename[i] == '.') {
						hasPoint = true ;
						break ;
					} // if ( hasPoint == true ) 
				} // for

                // filename has not '.'
	  		    if ( !hasPoint )
		  		    filename = filename + ".txt" ;
			} // else
		} // string Cheak_filename
		
		string Create_adjFile( string fileName, string threshold ) {
			fileName = fileName.erase( fileName.size()-4, 4 ) + "_" + threshold + ".adj" ;
			return fileName ;
		} // void Create_adjFile
		
		string Create_adjFile( string fileName ) {
			fileName = fileName.erase( fileName.size()-4, 4 ) + ".cc" ;
			return fileName ;
		} // void Create_adjFile
}; // class File

class Graph  {
	public  :
		int getTotalNode( vector<Sender> sender ) {
			int num  = 0 ;
			for ( Sender s : sender  ) {
				num = num + (int)s.receiver.size() ;
			} // for
			
			return num ;
		} // int getNodeTotal
		
		int getTotalID( vector<Sender> sender ) {
			return (int)sender.size() ;
		} // int getNodeTotal
		
		// @ brief : init temp list struct
		void InitST( Sender &sender, Receiver &receiver ) {
			sender.id[10] = {'\0'} ;
			sender.receiver.clear() ;
			receiver.id[10] = {'\0'} ;
			receiver.weight = 0 ;
		} // void InitST
		
		void Sort( vector<Sender> &sender ) {
			for ( int i=0; i < sender.size(); i++ ) {
				for ( int j=i+1; j < sender.size(); j++ ) {
					if ( strcmp( sender[i].id, sender[j].id ) > 0 )
						swap( sender[i], sender[j] ) ;
				} // for
			} // for
			
			for ( int i=0; i < sender.size(); i++ ) {
				for ( int j=0; j < sender[i].receiver.size(); j++ ) {
					for ( int k=j; k < sender[i].receiver.size(); k++ ) {
						if ( strcmp( sender[i].receiver[j].id, sender[i].receiver[k].id ) > 0 )
							swap(  sender[i].receiver[j],  sender[i].receiver[k] ) ;
					}
				} // for
			} // for
		} // void Sort
		
		void WriteBinToVec( vector<Data> &data, string binFileName, float threshold ) { 
			Data tempData ;
			fstream binFile ;
			int stNo = 0 ;
			
			int count = 0 ;
			
			binFile.open( binFileName.c_str(), fstream::in|fstream::binary) ;
			binFile.seekg( 0, binFile.end ) ;
			stNo = binFile.tellg() / sizeof(tempData) ;
			binFile.seekg( 0, binFile.beg ) ;

			// push binary data to vec
			for ( int i=0 ; i < stNo ; i++ ) {
				binFile.read( (char*)&tempData, sizeof(tempData) ) ;
				if ( tempData.weight <= threshold ) {
					data.push_back(tempData) ;
				}  // if
			} // for

			binFile.close() ;
		} // void WriteBinToVec
		
		void WriteListToAdj( string &adjFileName, string tempThreshold, vector<Sender> list ) {
			File  file ;
			adjFileName = file.Create_adjFile( adjFileName, tempThreshold ) ;
			
			int count = 0 ;
			int node = getTotalNode(list) ;
			int id = getTotalID(list) ;
			
			ofstream adjFile ;
			adjFile.open( adjFileName.c_str() ) ;
			adjFile << "<<< There are " << id << " IDs in total. >>>\n" ;
			
			for( int i=0; i < list.size(); i++ ) {
				adjFile << "[" << i+1 << "] " << list[i].id << " : \n" ;
				for ( int j=0; j < list[i].receiver.size(); j++ )  {
					count++ ;
					adjFile << "\t(" << j+1 << ") " << list[i].receiver[j].id << ",  " << list[i].receiver[j].weight ;
					if  ( count == 10 ) {
						adjFile <<  "\n" ;
						count = 0 ;
					}
				} // for
				adjFile << "\n" ;
				count = 0 ;
			} // for
			adjFile << "<<< There are " << node << " nodes in total. >>>\n" ;
			adjFile.close() ;
		} // void WriteListToAdj
		
		// @ brief :  build graph
		void BuildList( vector<Sender> &list, vector<Data> data ) {
			int position = -1 ;
			Sender tempSender ;
			Receiver tempReceiver ;
            for(Data d : data){
            	// list is null
				if ( list.size() == 0 )  {
					// set sender
					strcpy( tempSender.id, d.id1 ) ;
					// set receiver
					strcpy( tempReceiver.id, d.id2 ) ;
					tempReceiver.weight = d.weight ;
					tempSender.receiver.push_back(tempReceiver) ;
					// push to graph
					list.push_back(tempSender) ;
					
                    InitST( tempSender, tempReceiver ) ;
					
					/* Because it is an undirected graph
					 * So do it in reverse again 
					*/
					strcpy( tempSender.id, d.id2 ) ;
					strcpy( tempReceiver.id, d.id1 ) ;
					tempReceiver.weight = d.weight ;
					tempSender.receiver.push_back(tempReceiver) ;
					list.push_back(tempSender) ;
				} // if 
				
				// list isn't null
				else {
					// set receiver
					strcpy( tempReceiver.id, d.id2 ) ;
					tempReceiver.weight = d.weight ;
					
					// Find if graphs have the same sender
					for( int i=0; i < list.size();  i++ )  {
						if( strcmp( d.id1, list[i].id ) == 0 ) {
							position = i ;
							break ;
						} // if
					} // for
					
					// find the same sender
					if ( position != -1 ) {
						list[position].receiver.push_back(tempReceiver) ;
					}  // if
					
					// no find the same sender
					else {
						// push new sender in graph
						strcpy( tempSender.id, d.id1 ) ;
						tempSender.receiver.push_back(tempReceiver) ;
						list.push_back(tempSender) ;
					}  // else
					
					// init
					position  = -1 ;
					InitST( tempSender, tempReceiver ) ;
					
					// do it in reverse again
					strcpy( tempReceiver.id, d.id1 ) ;
					tempReceiver.weight = d.weight ;
					
					for( int i=0; i < list.size();  i++ )  {
						if( strcmp( d.id2, list[i].id ) == 0 ) {
							position = i ;
							break ;
						} // if
					} // for
					
					if ( position != -1 ) {
						list[position].receiver.push_back(tempReceiver) ;
					}  // if
					
					else {
						strcpy( tempSender.id, d.id2 ) ;
						tempSender.receiver.push_back(tempReceiver) ;
						list.push_back(tempSender) ;
					}  // else
				} // else
				
				position  = -1 ;
				InitST( tempSender, tempReceiver ) ;
            } // for
            
            Sort( list ) ;
		}  // void  BuildList
		
		void Print( vector<Sender> &list ) {
//			int count  = 0 ;
//			for( int i=0; i < list.size(); i++ ) {
//				count = 0 ;
//				cout << "\n\n(" << i+1 << ") " << list[i].id << " : " << endl ;
//				for ( int j=0; j < list[i].receiver.size(); j++ )  {
//					cout << "\t" << list[i].receiver[j].id ;
//					count++ ;
//					if( count == 5 )  {
//						cout << "\n" ;
//					count = 0 ;
//					}
//				} // for
//			} // for
			
			int node = getTotalNode(list) ;
			int id = getTotalID(list) ;
			cout << "\n<<< There are " << id << " IDs in total. >>>\n" ;
			cout << "\n<<< There are " << node << " nodes in total. >>>\n" ;
		} // void testPrint
		
}; // class Graph

class Mission {
	public :
		void Mission0( string &fileName, vector<Sender> &list ) {
			list.clear() ;
			
			File file ;
			Graph graph ;
			float threshold = 0.0 ;
			string tempThreshold = "\0" ;
			ifstream binFile ;
			
			do {
				cout << "\nInput a real number in (0,1] :  " ;
				cin >> tempThreshold ;

				while ( file.IsFloat(tempThreshold) == false ) {
					cout  << "\nInput a real number in (0,1] : " ;
					cin >> tempThreshold ;
				}  // while
				
				threshold = stof( tempThreshold ) ;
				if ( threshold <= 0 || threshold > 1  ) 
					threshold = -1 ;
			} while(  threshold <= 0 || threshold > 1  ) ;
			
			cout << "\nInput a file number ( 501, pairs501 ) : " ;
			cin >> fileName ;
			file.Cheak_filename(fileName) ;
			
			binFile.open( fileName.c_str() ) ;
			if ( binFile.is_open() ) {
				vector<Data> data ;
				graph.WriteBinToVec( data , fileName, threshold ) ;
				if ( data.size() == 0 )
					return ;
				graph.BuildList( list, data ) ;
				graph.WriteListToAdj( fileName, tempThreshold, list )  ;
				graph.Print(list) ;
				data.clear() ;
				binFile.close() ;
			} // if
			
			else 
				cout << "### "  <<  fileName << " does not exist! ###\n" ;
		} // void Mission0
		
		void Mission1( string fileName, vector<Sender> list ) {
			Graph graph ;
			
			if ( list.size() == 0 ) {
				cout << "\n### There is no graph and choose 0 first. ###\n" ;
			} // if
			
			else {
				int node = graph.getTotalNode(list) ;
				int id = graph.getTotalID(list) ;
				cout << endl << fileName << endl ;
				cout << "\n<<< There are " << id << " IDs in total. >>>\n" ;
				cout << "\n<<< There are " << node << " nodes in total. >>>\n" ;
			}
		} // void Mission1

		void Mission2( string fileName, vector<Sender> list ) {
			Graph graph ;
			
			if ( list.size() == 0 ) {
				cout << "\n### There is no graph and choose 0 first. ###\n" ;
			} // if
			
			else  {
				int node = graph.getTotalNode(list) ;
				int id = graph.getTotalID(list) ;
				cout << endl << fileName << endl ;
				cout << "\n<<< There are " << id << " IDs in total. >>>\n" ;
				cout << "\n<<< There are " << node << " nodes in total. >>>\n" ;
			}
		} // void Mission2
}; // class Mission

void Start() {
	int command = 0 ;
    string temp = "\0" ;
    string fileName = "\0" ;
    vector<Sender> list ;
	Mission mission ;
	File file  ;
	
	
	do{
	    cout << "\n******* Graph data applications ******" ;
        cout << "\n* [Any other key: QUIT]              *" ;
        cout << "\n* 0. Create adjacency lists          *" ;
        cout << "\n* 1. Build connected components      *" ;
        cout << "\n* 2. Find shortest paths by Dijkstra *" ;
        cout << "\n**************************************" ;
        cout << "\nInput a choice(0, 1, 2) [Any other key: QUIT] :" ;
        cin >> temp ;

        if ( file.IsNumber( temp ) ) {
        	command = stoi(temp) ;
        	switch ( command ) {
    	    	case( 0 ) :
		  	    	mission.Mission0( fileName, list ) ;
		  	    	break ;
		   		case( 1 ) :
		  	    	mission.Mission1( fileName, list ) ;
		  	    	break ;
		    	case( 2 ) :
		  	    	mission.Mission2( fileName, list ) ;
		  	    	break ;
		    	default :
		  	    	cout << "\nexit" ;
		  	    	return ;
	    	} // switch
		} // if
		
		else command = -1 ;
	} while ( command >= 0 && command < 3 ) ; // do while
} // void start()

int main() { 
	Start() ;
} // int main()
