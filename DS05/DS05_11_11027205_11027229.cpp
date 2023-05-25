// 11027205

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <stack>
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

        // cheak string is int
		bool IsNumber( string filename ) {
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i]-'0' < 0 || filename[i]-'0' > 9 )
					return false;
			} // for
			return true ;
		} // bool IsNumber
		
		// cheak string is float
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
		void Cheak_FileName( string &filename ) {
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
		
		string Create_FileName( string fileName, string threshold, string lastName ) {
			fileName = fileName.erase( fileName.size()-4, 4 ) + "_" ;
			if ( threshold != "0" )
				fileName = fileName + threshold ;
			fileName = fileName + lastName ;
			return fileName ;
		} // string Create_FileName
}; // class File

class Graph  {
	public  :
		int getTotalNode( vector<Sender> &sender ) {
			int num  = 0 ;
			for ( Sender s : sender  ) {
				num = num + (int)s.receiver.size() ;
			} // for
			
			return num ;
		} // int getNodeTotal
		
		int getTotalID( vector<Sender> &sender ) {
			return (int)sender.size() ;
		} // int getNodeTotal
		
		int FindID( char id[10], vector<Sender> &list, string state ) {
			int position = -1 ;
			// find list 1 dimension ID
			if ( state == "1D" ) {
				for ( int i=0; i < list.size(); i++ )  {
					if ( strcmp( id, list[i].id ) == 0 ) {
						position = i ;
						break ;
					} // if
				} // for
			} // if
			
			// find list 2 dimension ID
			else {
				for ( int i=0; i < list.size(); i++ )  {
					for ( int j=0; j < list[i].receiver.size(); j++ ) {
						if ( strcmp( id, list[i].receiver[j].id ) == 0 ) {
							position = i ;
							break ;
						} // if
					} // for
				} // for
			} // else
			return position ;
		} // int findList
		
		int FindID( string id, vector<Sender> &list, string state ) {
			int position = -1 ;
			// find list 1 dimension ID
			if ( state == "1D" ) {
				for ( int i=0; i < list.size(); i++ )  {
					if ( id == list[i].id ) {
						position = i ;
						break ;
					} // if
				} // for
			} // if
			
			// find list 2 dimension ID
			else {
				for ( int i=0; i < list.size(); i++ )  {
					for ( int j=0; j < list[i].receiver.size(); j++ ) {
						if ( id == list[i].receiver[j].id ) {
							position = i ;
							break ;
						} // if
					} // for
				} // for
			} // else
			return position ;
		} // int findList
		
		int FindID( char id[10], Sender &list ) {
			int position = -1 ;
			for ( int i=0; i < list.receiver.size(); i++ ) {
				if ( strcmp ( id, list.receiver[i].id ) == 0 ) {
					position = i ;
					break ;
				} // if
			} // for
			return position ;
		} // int FindAnsArray

		bool IsVisit( string id, vector<string> &visit ) {
			for ( string v : visit ) {
				if ( id == v ) return true ;
			} //  for
			return false ;
		} // bool IsVisit
		
		bool InStack( string id, vector<string> &stack ) {
			for ( string s : stack ) {
				if ( id == s ) return true ;
			} //  for
			return false ;
		} // bool IsInStack
		
		bool InList( string id, vector<Sender> &list ) {
			for ( Sender l : list ) {
				if ( id == l.id ) return true ;
			} //  for
			return false ;
		} // bool InList
		 
		// @ brief : Init temp list struct
		void InitST( Sender &sender, Receiver &receiver ) {
			sender.id[10] = {'\0'} ;
			sender.receiver.clear() ;
			receiver.id[10] = {'\0'} ;
			receiver.weight = 0 ;
		} // void InitST
		
		void SortMission0( vector<Sender> &sender ) {
			for ( int i=0; i < sender.size(); i++ ) {
				for ( int j=i+1; j < sender.size(); j++ ) {
					if ( strcmp( sender[i].id, sender[j].id ) > 0 )
						swap( sender[i], sender[j] ) ;
				} // for
			} // for
			
			for ( int i=0; i < sender.size(); i++ ) {
				for ( int j=0; j < sender[i].receiver.size(); j++ ) {
					for ( int k=j; k < sender[i].receiver.size(); k++ ) {
						if ( strcmp ( sender[i].receiver[j].id, sender[i].receiver[k].id ) > 0 )
							swap(  sender[i].receiver[j],  sender[i].receiver[k] ) ;
					}
				} // for
			} // for
		} // void SortMission0
		
		void SortMission1( vector<Sender> &connectList ) {
			for ( int i=0; i < connectList.size(); i++ ) {
				for ( int j=i+1; j < connectList.size(); j++ ) {
					if ( connectList[i].receiver.size() > connectList[j].receiver.size() )
						swap( connectList[i], connectList[j] ) ;
				} // for
			} // for
			
			for ( int i=0; i < connectList.size(); i++ ) {
				for ( int j=0; j < connectList[i].receiver.size(); j++ ) {
					for ( int k=j; k < connectList[i].receiver.size(); k++ ) {
						if ( strcmp ( connectList[i].receiver[j].id, connectList[i].receiver[k].id ) > 0 )
							swap( connectList[i].receiver[j], connectList[i].receiver[k] ) ;
					}
				} // for
			} // for
		} // void SortMission1
		
		void SortMission2( Sender &shortArray ) {
			for ( int i=0; i < shortArray.receiver.size(); i++ ) {
				for ( int j=i; j < shortArray.receiver.size(); j++ ) {
					if ( shortArray.receiver[i].weight >= shortArray.receiver[j].weight ) {
						if ( shortArray.receiver[i].weight > shortArray.receiver[j].weight )
							swap ( shortArray.receiver[i], shortArray.receiver[j] ) ;
						else if ( strcmp ( shortArray.receiver[i].id, shortArray.receiver[j].id ) > 0 )
							swap ( shortArray.receiver[i], shortArray.receiver[j] ) ;
					} // if
				} // for
			} // for
		} // void SortMission1
		
		void WriteBinToVec( vector<Data> &data, string binFileName, float threshold ) { 
			Data tempData ;
			fstream binFile ;
			int stNo = 0 ;
			
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
		
		void WriteListToAdj( string &adjFileName, string tempThreshold, vector<Sender> &list ) {
			File  file ;
			adjFileName = file.Create_FileName( adjFileName, tempThreshold, ".adj" ) ;
			
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
		
		void WriteListToCc( string ccFileName, vector<Sender> &connectList )  {
			File  file ;
			ccFileName = file.Create_FileName( ccFileName, "0", ".cc" ) ;
			int count = 0 ;
			int receiverSize = 0 ;

			ofstream ccFile ;
			ccFile.open( ccFileName.c_str() ) ;
			ccFile << "<<< There are " << connectList.size() << "  connected components in total. >>>\n" ;
			
			for( int i=connectList.size()-1; i >= 0; i-- ) {
				receiverSize = connectList[i].receiver.size() ;
				ccFile << "{" << connectList.size()-i << "} " << "Connected Component: size = " << receiverSize << "\n" ;
				for ( int j=0; j < connectList[i].receiver.size(); j++ )  {
					count++ ;
					ccFile << "\t(" << j+1 << ") " << connectList[i].receiver[j].id  ;
					if  ( count == 8 ) {
						ccFile <<  "\n" ;
						count = 0 ;
					}
				} // for
				ccFile << "\n" ;
				count = 0 ;
			} // for

			ccFile.close() ;
		} //  void WriteListToCc
		
		void WriteListToDs( string id, string dsFileName, Sender &shortArray ) {
			ofstream dsFile ;
			int count = 0 ;
			
			dsFile.open( dsFileName.c_str(), std::ofstream::out | std::ofstream::app ) ;
			dsFile << "\norigin: " << id << "\n" ;
			for ( int i=0; i < shortArray.receiver.size(); i++ ) {
				count++ ;
				dsFile << "(" << i+1 << ") \t" << shortArray.receiver[i].id << ", " << shortArray.receiver[i].weight << "\t"   ;
				if ( count == 8 ) {
					dsFile << "\n" ;
					count = 0 ;
				} // if
			}  // for
			 
			dsFile << "\n" ;
			dsFile.close() ;
		} // void WriteListToDs
		
		// @ brief : build list
		void BuildList( vector<Sender> &list, vector<Data> data ) {
			int position = -1 ;
			Sender tempSender ;
			Receiver tempReceiver ;
			
            for(Data d : data) {
				if ( list.size() == 0 ) { // list is null
					SetList( list, d.id1, d.id2, d.weight, "null" ) ;
					// Because it is an undirected graph, so do reverse again
					SetList( list, d.id2, d.id1, d.weight, "null" ) ;
				} // if 
				
				else { // list isn't null
					SetList( list, d.id1, d.id2, d.weight, "unNull" ) ;
					SetList( list, d.id2, d.id1, d.weight, "unNull" ) ;
				} // else
            } // for
            
            SortMission0( list ) ;
		}  // void  BuildList
		
		// @ brief : build connect list
		void BuildConnectList( vector<Sender> &list, vector<Sender> &connectList ) {
			Sender tempSender ;
			vector<string> stack ;
			vector<string> visit ;
			
			for ( int i=0; i < list.size(); i++ ) {
				if ( IsVisit( list[i].id, visit ) == false ) {
					stack.push_back( list[i].id ) ;
					visit.push_back( list[i].id ) ;
					traveler( list[i].id, stack, visit, list, tempSender ) ;
					connectList.push_back(tempSender) ; // put the friend circle to list
					// Init
					tempSender.receiver.clear() ;
					stack.clear() ;
				} // if
			} // for
			
			SortMission1( connectList ) ;
		} // void BuildConnectList
		
		void  BuildGraph( string id, vector<Sender> &graph, vector<Sender> &list, vector<Sender> &connectList ) {
			Sender tempSender ;
			int position = -1 ;
			
			/* find ID, if ID in connectList receiver have the same ID
			 * connectList 1-D is empty
			 * so find ID need go to 2D list to search
			*/
			position = FindID( id, connectList, "2D" ) ;

			// set graph data
			for ( int i=0; i < connectList[position].receiver.size(); i++ ) {
				// set 1D graph
				strcpy ( tempSender.id, connectList[position].receiver[i].id ) ;
				// set 2D graph
				for ( int j=0 ; j < connectList[position].receiver.size(); j++ ) {
					tempSender.receiver.push_back( connectList[position].receiver[j] ) ;
				} //  for
				
				// Init
				graph.push_back(tempSender) ;
				tempSender.id[10] = {'\0'} ;
				tempSender.receiver.clear() ;
			} // for
			
			position = -1 ;
			// set weight
			for ( int i=0; i < graph.size(); i++ ) {
				// find ID in list
				position = FindID( graph[i].id, list, "1D" ) ;
				
				// get weight from mission 0's list
				for ( int j=0 ; j < list[position].receiver.size(); j++ ) {
					// set weight to graph
					for ( int k=0 ; k < graph[i].receiver.size(); k++ ) {
						// if ID is same, set weight
						if ( strcmp ( list[position].receiver[j].id, graph[i].receiver[k].id ) == 0 ) {
							graph[i].receiver[k].weight =  list[position].receiver[j].weight ;
							break ;
						} // if
					} //  for
				} // for
			} // for
			
		} // void BuildGraph
		
		void SetList( vector<Sender> &list, char id1[10], char id2[10], float weight, string state ) {
			Sender tempSender ;
			Receiver tempReceiver ;
			int position = -1 ;

			// list is null
			if ( state == "null" ) {
				strcpy( tempSender.id, id1 ) ;   // set sender
				strcpy( tempReceiver.id, id2 ) ; // set receiver
				tempReceiver.weight = weight ;
				tempSender.receiver.push_back(tempReceiver) ;
				list.push_back(tempSender) ; 	// push to list
				InitST( tempSender, tempReceiver ) ; // Init
			} // if
			
			// list isn't null
			else {
				strcpy( tempReceiver.id, id2 ) ; // set receiver
				tempReceiver.weight = weight ;
				
				// Find ID, If list have the same sender
				position = FindID( id1, list, "1D" ) ;
				
				// find the same sender
				if ( position != -1 ) {
					list[position].receiver.push_back(tempReceiver) ;
				}  // if
					
				// not find the same sender
				else {
					// push new sender in graph
					strcpy( tempSender.id, id1 ) ;
					tempSender.receiver.push_back(tempReceiver) ;
					list.push_back(tempSender) ;
				}  // else
					
				// Init
				position  = -1 ;
				InitST( tempSender, tempReceiver ) ;
			} // else
		} // void SetList
		
		void SetSmallWeight( Sender &graph, vector<string> &visit, float &minWeight, char (&preID )[10] ) {
			char tempID[10] = {'\0'} ;
			float tempWeight = 0.0 ;

			for ( int i=0; i < graph.receiver.size(); i++ ) {
			   	strcpy ( tempID, graph.receiver[i].id ) ;
			    tempWeight = graph.receiver[i].weight ;
			    if ( IsVisit( tempID, visit ) == false && tempWeight != 0 && tempWeight < minWeight ) {
			    	preID[10] = {'\0'}  ;
			    	strcpy( preID, tempID ) ;
			    	minWeight = tempWeight ;
				} // if
			} // for
		} // void SetSmallWeight
		
		void traveler( string id, vector<string> &stack, vector<string> &visit, vector<Sender> list, Sender &tempSender ) {
			int position = -1 ;
			int tempStack = stack.size() ;
			Receiver tempReceiver ;
			
			// Find ID in list
			position = FindID( id, list, "1D" ) ;
			// put ID's receiver in stack
			Add( stack, visit, list[position] ) ;
			
			// stack last point isn't visit
			if ( IsVisit( stack[stack.size()-1], visit ) == false ) {
				visit.push_back( stack[stack.size()-1] ) ;
				while ( !stack.empty() ) {
					traveler( stack[stack.size()-1], stack, visit, list, tempSender ) ;
				} // while
			} // if

			// stack last point is visit
			else {
				stack.pop_back() ;
				// copy ID to tempReceiver ( char[10] <- string )
	            for( int i=0; i < id.length(); i++ ) {
	            	tempReceiver.id[i] = id[i] ;
				} // for
				
				// push back to friend circle
				tempSender.receiver.push_back(tempReceiver) ;
			} // else
		} // void traver
		
		void Add( vector<string> &stack, vector<string> &visit, Sender sender ) {
			for ( int i=0; i < sender.receiver.size(); i++ ) {
				if ( InStack( sender.receiver[i].id, stack ) == false && IsVisit( sender.receiver[i].id, visit ) == false  )
					stack.push_back( sender.receiver[i].id ) ;
			} // for
		} // void AddToStack
						
		void ShortPath( string fileName, vector<Sender> list, vector<Sender> connectList ) {
			File file ;
			string tempID = "\0" ;
			Sender shortArray ;
			vector<Sender> graph ;
			
			fileName = file.Create_FileName( fileName, "0", ".ds" ) ;
			
			do {
				Mission2_Print( list ) ;
				cout << "\nInput a student ID [0: exit] : " ;
				cin >> tempID ;
				if ( tempID == "0" ) return ;
				
				if ( InList( tempID, list ) == true ) {
					BuildGraph( tempID, graph, list, connectList ) ;
					Dijkstra( tempID, shortArray, graph ) ;
					SortMission2( shortArray ) ;
					WriteListToDs( tempID, fileName, shortArray ) ;
					shortArray.id[10] = {'\0'} ; // Init
					shortArray.receiver.clear() ;
				} // if
				
				else {
					cout << "\n### the student id does not exist! ###\n" ;
				} // else
			} while ( tempID != "0" ) ;
		} // void ShortPath
		
		void Dijkstra( string id, Sender &shortArray, vector<Sender> &graph ) {
			vector<string> visit ;
			int position = -1 ;
			int tempPos = -1 ;
			float tempWeight = 0.0 ;
			float minWeight = 999 ;
			char tempID[10] = {'\0'} ;
			char preID[10] = {'\0'} ; // store previously path(ID)
						
			// find ID in graph
			position = FindID( id, graph, "1D" ) ;
		
			//  set shortArray ID and weight
			for ( int i=0; i < graph[position].receiver.size(); i++  ) {
				if ( id != graph[position].receiver[i].id ) 
					shortArray.receiver.push_back( graph[position].receiver[i] ) ;
			} // for
			
			// set smallest weight & previously path(ID)
			SetSmallWeight( shortArray, visit, minWeight, preID ) ;

			position = -1 ; // Init position
			
			// push id to visit
			visit.push_back( id ) ;
			visit.push_back( preID ) ;
			
			for ( int count=0; count < shortArray.receiver.size()-1; count++  ) {
				// find ID in graph
				position = FindID( preID, graph, "1D" ) ;
				tempID[10] = {'\0'} ;
				tempWeight = 0.0 ;
				
				// update short path 
			    for ( int i=0; i < graph[position].receiver.size(); i++ ) {
			    	strcpy ( tempID, graph[position].receiver[i].id ) ;
			    	tempWeight = graph[position].receiver[i].weight ;
			    	
			    	if ( IsVisit( tempID, visit ) == false && tempWeight != 0 ) {						
						tempWeight = tempWeight + minWeight ;
						// find ID in shortArray
			    		tempPos = FindID( tempID, shortArray ) ; 
			    		// sum weight < short path weight or short path weight = 0
			    		if ( tempWeight < shortArray.receiver[tempPos].weight || shortArray.receiver[tempPos].weight == 0 )
			    			shortArray.receiver[tempPos].weight = tempWeight ;
					} // if
				} // for
				

				minWeight = 999 ; // reset min weight
				// set small weight & previously path(ID)
			    SetSmallWeight( shortArray, visit, minWeight, preID ) ;				
				visit.push_back( preID ) ;

				// Init 
				position = -1 ;
				tempID[10] = {'\0'} ;
				tempWeight = 0.0 ;
				tempPos = -1 ;
			} // for
		} // void dijkstra
		
		void Mission0_Print( vector<Sender> list ) {
			int node = getTotalNode(list) ;
			int id = getTotalID(list) ;
			cout << "\n<<< There are " << id << " IDs in total. >>>\n" ;
			cout << "\n<<< There are " << node << " nodes in total. >>>\n" ;
		} // void Mission0_Print
		
		void Mission1_Print( vector<Sender> connectList ) {
			int ccSize = connectList.size() ;
			cout << "\n<<< There are " << ccSize << " connected components in total. >>>\n" ;
			for ( int i=ccSize-1; i >= 0; i-- ) {
				cout << "{ " << ccSize-i << "} Connected Component: size = "  << connectList[i].receiver.size() << endl ;
			} // for
		} // void Mission1_Print
		
		void Mission2_Print( vector<Sender> list ) {
			int count = 0 ;
			cout << endl ;
			for( Sender s : list ) {
				cout << "   " << s.id ;
				count++ ;
				if ( count == 8 ) {
					cout << "\n" ;
					count = 0  ;
				} // if
			} // for
		} // void Mission2_Print
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
			file.Cheak_FileName(fileName) ;
			
			binFile.open( fileName.c_str() ) ;
			if ( binFile.is_open() ) {
				vector<Data> data ;
				graph.WriteBinToVec( data , fileName, threshold ) ;
				if ( data.size() == 0 ) // any data's weight < threshold
					return ;
				graph.BuildList( list, data ) ;
				graph.WriteListToAdj( fileName, tempThreshold, list )  ;
				graph.Mission0_Print(list) ;
				data.clear() ;
				binFile.close() ;
			} // if
			
			else 
				cout << "### "  <<  fileName << " does not exist! ###\n" ;
		} // void Mission0
		
		void Mission1( string fileName, vector<Sender> list, vector<Sender> &connectList ) {
			Graph graph ;
			connectList.clear() ;
			
			if ( list.size() == 0 ) {
				cout << "\n### There is no graph and choose 0 first. ###\n" ;
			} // if
			
			else {
				graph.BuildConnectList( list, connectList ) ;
				graph.WriteListToCc( fileName, connectList ) ;
				graph.Mission1_Print(connectList) ;
			} // else 
		} // void Mission1

		void Mission2( string fileName, vector<Sender> list, vector<Sender> connectList ) {
			Graph graph ;
			
			if ( list.size() == 0 ) {
				cout << "\n### There is no graph and choose 0 first. ###\n" ;
			} // if
			
			else if ( connectList.size() == 0 )  {
				cout << "\n### Choose 1 to find connected components. ###\n" ;
			} // else if
			
			else  {
				graph.ShortPath( fileName, list, connectList ) ;
			} // else
		} // void Mission2
}; // class Mission

void Start() {
	int command = 0 ;
    string temp = "\0" ;
    string fileName = "\0" ;
    /* @parem : list, mission 0 build graph will store in this vector
     * @parem : connectList, mission 1 build graph will store in this vector
     */
    vector<Sender> list ;
    vector<Sender> connectList ;
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
		  	    	mission.Mission1( fileName, list, connectList ) ;
		  	    	break ;
		    	case( 2 ) :
		  	    	mission.Mission2( fileName, list,  connectList ) ;
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
