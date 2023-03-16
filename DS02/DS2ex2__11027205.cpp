// 資訊二乙 11027205 蔡宗勳

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Data {
	public :
		int serial ;              // 序號 
		string school_code ; 			// 學校代碼 
		string school_name ; 			// 學校名稱
		string department_code ;  // 科系代碼
		string department_name ;  // 科系名稱
		string day ;  						// 日間
		string education ; 				// 等級別
		int student ; 						// 學生數
		int teacher ; 						// 教師數
		int graduate ; 						// 畢業生數
		string city ; 						// 縣市
		string system ; 					// 體系別 

		void Init() { 						// Init Data
	  		school_code.clear() ;
	  		school_name.clear() ;
	  		department_code.clear() ;
	  		department_name.clear() ;
	  		day.clear() ;
	  		education.clear() ;
	  		student = 0 ;
	 		teacher = 0 ;
	 		graduate = 0 ;
	 		city.clear() ; 
	  		system.clear() ;
  		} // void  Init
} ; // class Data

class InNode {               // Index of node
	public : vector<Data> aNode ;
}; // class InNode

class Node{
	public :
		vector<InNode> node ;
		Node *child[4] ;

		Node() {
			child[0] = NULL ;      // left child
			child[1] = NULL ;      // mid child
			child[2] = NULL ;      // right child
			child[3] = NULL ;      // temp child
		} // Node
}; // class Node

class AvlNode{
	public :
		vector<Data> node ;
		AvlNode *child[2] ;
		AvlNode() {
			child[0] = NULL ;
			child[1] = NULL ;
		} // AvlNode
}; // class AvlNode

class TwoThreeTree {
	public :
		int CountHigh( Node *tree ) {
			int high = 1;
			while ( tree -> child[0] != NULL ) {
				high++ ;
				tree = tree -> child[0] ;
			} // while
			
			return high ;
		} // void CountHigh
		
		void Sort( Node *&tree ) {
			for ( int i = 0; i < tree->node.size(); i++ ) {
				for( int j = i; j < tree->node.size(); j++ ) {
					if ( tree->node[i].aNode[0].school_name > tree->node[j].aNode[0].school_name ) 
						swap( tree->node[i], tree->node[j] ) ;
				} // for ( j = 0 )
			} // for ( i = 0 )
		} // void Sort

		void Split( Node *&tree, Node *&parent, int &numOfNode ) {
			// left child: child[0], mid child: child[1], right child: child[2], temp child: child[3]
			if ( parent == NULL ) {
				numOfNode += 2 ;
		    parent = new Node ;                           // create root node
		    parent -> node.push_back( tree->node[1] ) ;   // set root 
		    parent -> child[0] = tree ;                   // set left child

		    parent -> child[2] = new Node ;							  // create right child
		    parent -> child[2] -> node.push_back( tree->node[2] ) ; // set right child
		  	tree -> node.erase( tree->node.begin()+2 ) ;  // delete node large data
		  	tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data

		  	if ( tree -> child[3] != NULL ) {                     // has temp child
		  	  parent -> child[2] -> child[2] = new Node ;         // create right right child
		  	  parent -> child[2] -> child[2] = tree -> child[3] ; // set right right child
		  	  
		  	  parent -> child[2] -> child[0] = new Node ;         // create right left child
		  	  parent -> child[2] -> child[0] = tree -> child[2] ; // set right left child
		  	  
		  	  tree -> child[2] = tree -> child[1] ;               // set left right child

		  	  tree -> child[1] = NULL ;
		  	  tree -> child[3] = NULL ;
		  	} // if ( tree -> child[3] != NULL )
		  	
		  	tree = parent ;  // update root
			} // if ( parent == NULL )

			else if ( parent -> node.size() == 1 ) { // parent is one Key
				numOfNode += 1 ;
        if ( tree -> node[1].aNode[0].school_name < parent -> node[0].aNode[0].school_name ) { // small side split
        	parent -> node.push_back( tree -> node[1] ) ; // split data to parent
        	Sort( parent ) ;
        	
        	parent -> child[1] = new Node ;               // create mid child
        	parent -> child[1] -> node.push_back( tree -> node[2] ) ; // set mid child
		      tree -> node.erase( tree->node.begin()+2 ) ;  // delete node large data
		  	  tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data
		  	  
		    	if ( tree -> child[3] != NULL ) {             // has temp child
            parent -> child[1] -> child[2] = new Node ; // create mid right child
            parent -> child[1] -> child[2] = tree -> child[3] ; // set mid right child
            
            parent -> child[1] -> child[0] = new Node ; // create mid left child
            parent -> child[1] -> child[0] = tree -> child[2] ; // set mid left child
            
            tree -> child[2] = tree -> child[1] ;  // reset right child 
            
		  	    tree -> child[1] = NULL ;
		  	    tree -> child[3] = NULL ;
		  	  } // if ( tree -> child[3] != NULL )
				} // if ( small side split )
				
				else { // large side split
        	parent -> node.push_back( tree -> node[1] ) ; // split data to parent
        	Sort( parent ) ;
        	
        	parent -> child[1] = new Node ;               // create mid child
        	parent -> child[1] -> node.push_back( tree -> node[0] ) ; // set mid child
		      tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data
		  	  tree -> node.erase( tree->node.begin() ) ;    // delete node small data
		  	  
		    	if ( tree -> child[3] != NULL ) {             // has temp child
            parent -> child[1] -> child[2] = new Node ; // create mid right child
            parent -> child[1] -> child[2] = tree -> child[1] ; // set mid right child
            
            parent -> child[1] -> child[0] = new Node ; // create mid left child
            parent -> child[1] -> child[0] = tree -> child[0] ; // set mid left child
            
            tree -> child[0] = tree -> child[2] ; // reset left child
            tree -> child[2] = tree -> child[3] ; // reset right child
            
		  	    tree -> child[1] = NULL ;
		  	    tree -> child[3] = NULL ;
		  	  } // if ( tree -> child[3] != NULL )
				} // else ( large side split )
			} // else if ( parent = 1 node )

			else if ( parent -> node.size() == 2 ) { // parent is two Key
				numOfNode += 1 ;
			  if ( tree -> node[1].aNode[0].school_name > parent -> node[1].aNode[0].school_name ) { // large side split
        	parent -> node.push_back( tree -> node[1] ) ; // split data to parent
        	Sort( parent ) ;
        	
        	parent -> child[3] =  new Node ;              // create temp child
        	parent -> child[3] -> node.push_back( tree -> node[2] ) ; // set temp child
        	
		      tree -> node.erase( tree->node.begin()+2 ) ;  // delete node large data
		  	  tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data
			  
			  	if ( tree -> child[3] != NULL ) {             // has temp child
			  		parent -> child[3] -> child[2] = new Node ; // create temp right child
			  		parent -> child[3] -> child[2] = tree -> child[3] ; // set temp right child
			  		
            parent -> child[3] -> child[0] = new Node ; // create temp left child
            parent -> child[3] -> child[0] = tree -> child[2] ; // set temp left child
            
            tree -> child[2] = tree -> child[1] ;       // reset right child 
            
		  	    tree -> child[1] = NULL ;
		  	    tree -> child[3] = NULL ;
					} // if ( tree -> child[3] != NULL )
				} // if ( large side split )
				
				else if ( tree -> node[1].aNode[0].school_name < parent -> node[0].aNode[0].school_name ) { // small side split
        	parent -> node.push_back( tree -> node[1] ) ; // split data to parent
        	Sort( parent ) ;
        	
					parent -> child[3] = parent -> child[2] ;     // move childPtr to right side
					parent -> child[2] = parent -> child[1] ;
					
					parent -> child[1] = new Node ;               // create temp child
					parent -> child[1] -> node.push_back( tree -> node[2] ) ; // set temp child
		      tree -> node.erase( tree->node.begin()+2 ) ;  // delete node large data
		  	  tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data
				
					if ( tree -> child[3] != NULL ) {             // has temp child
			  		parent -> child[1] -> child[2] = new Node ; // create temp right child
			  		parent -> child[1] -> child[2] = tree -> child[3] ; // set temp right child
			  		
            parent -> child[1] -> child[0] = new Node ; // create temp left child
            parent -> child[1] -> child[0] = tree -> child[2] ; // set temp left child
            
            tree -> child[2] = tree -> child[1] ;       // reset right child 
            
		  	    tree -> child[1] = NULL ;
		  	    tree -> child[3] = NULL ;
					} // if ( tree -> child[3] != NULL )
				} // else if ( small side split )
				
				else { // mid side split
        	parent -> node.push_back( tree -> node[1] ) ; // split data to parent
        	Sort( parent ) ;
        	
					parent -> child[3] = parent -> child[2] ;     // move childPtr to right side 
					
					parent -> child[2] = new Node ;               // create temp child
					parent -> child[2] -> node.push_back( tree -> node[2] ) ; // set temp child
		      tree -> node.erase( tree->node.begin()+2 ) ;  // delete node large data
		  	  tree -> node.erase( tree->node.begin()+1 ) ;  // delete node mid data
		  	  
					if ( tree -> child[3] != NULL ) {             // has temp child
			  		parent -> child[2] -> child[2] = new Node ; // create temp right child
			  		parent -> child[2] -> child[2] = tree -> child[3] ; // set temp right child
			  		
            parent -> child[2] -> child[0] = new Node ; // create temp left child
            parent -> child[2] -> child[0] = tree -> child[2] ; // set temp left child
            
            tree -> child[2] = tree -> child[1] ;       // reset right child 
            
		  	    tree -> child[1] = NULL ;
		  	    tree -> child[3] = NULL ;
					} // if ( tree -> child[3] != NULL )
				} // else ( mid side split )
			} // else if ( parent = 2 node )
		} // void Split

		void Insert( Node *&tree, Node *&parent, Data data, int &numOfNode ) {
			bool isInsert = false ;

			if ( tree == NULL ) {  // No root
			  numOfNode += 1 ;
				tree = new Node;
				InNode inNode ;
				inNode.aNode.push_back( data ) ;
				tree -> node.push_back( inNode ) ;
			} // if ( tree == NULL )

			else {
				for ( int i=0; i < tree->node.size(); i++ ) { // data school name equal node school name
					if ( data.school_name == tree->node[i].aNode[0].school_name ) {
						tree -> node[i].aNode.push_back( data ) ;
						isInsert = true ;
					} // if
				} // for

				if ( isInsert == false ) {
					if ( tree->child[0] != NULL && data.school_name < tree->node[0].aNode[0].school_name ) {
						Insert ( tree->child[0], tree , data, numOfNode ) ;
					} // if ( has left child )

				  else if ( tree->child[2] != NULL && data.school_name > tree->node[tree->node.size()-1].aNode[0].school_name ) {
				  	Insert ( tree->child[2], tree , data, numOfNode ) ;
					} // else if ( has right child )

					else if ( tree->child[1] != NULL && data.school_name > tree->node[0].aNode[0].school_name &&
					          data.school_name < tree->node[tree->node.size()-1].aNode[0].school_name) {
						Insert ( tree->child[1], tree , data, numOfNode ) ;
					} // else if ( has mid child )

					else { // no child can recursion
						InNode inNode ;
						inNode.aNode.push_back( data ) ;
						tree -> node.push_back( inNode ) ;
						Sort( tree ) ;
					} // else ( child all NULL )

					if ( tree->node.size() > 2 ) {
						Split( tree, parent, numOfNode ) ;
					} // if ( node > 2 )
				} // if ( isInsert == false )
			} // else ( tree != NULL )
		} // void Insert
}; // class TwoThreeTree

class AVLtree {
	public :
		void FindTreehigh( AvlNode *tree, int &max_high, int high ) {
			if ( tree == NULL )
				return ;
			else {
				high++ ;
				if ( max_high < high )
				  max_high = high ;
				if ( tree->child[0] != NULL )
				  FindTreehigh( tree->child[0], max_high, high ) ;
				if ( tree->child[1] != NULL )
				  FindTreehigh( tree->child[1], max_high, high ) ;
			} // else
		} // FindTreehigh()
		
		void LeftRotate( AvlNode *&tree ) {
			AvlNode *y = tree -> child[0] ;
			AvlNode *z = y -> child[1] ;

			y -> child[1] = tree ;
			tree -> child[0] = z ;
			tree = y ;
		} // void BalanceLL

		void RightRotate( AvlNode *&tree ) {
			AvlNode *y = tree -> child[1] ;
			AvlNode *z = y -> child[0] ;

			y -> child[0] = tree ;
			tree -> child[1] = z ;
			tree = y ;
		} // void BalanceRR

		void Balance( AvlNode *&tree ) {
			int lefthigh = 0, righthigh = 0, temphigh = 0 ;
			FindTreehigh( tree->child[0], lefthigh, temphigh ) ;
			FindTreehigh( tree->child[1], righthigh, temphigh ) ;
			
			if ( lefthigh - righthigh == 2 ) {
				lefthigh = 0, righthigh = 0 ;
				FindTreehigh( tree -> child[0] -> child[0], lefthigh, temphigh ) ;
				FindTreehigh( tree -> child[0] -> child[1], righthigh, temphigh ) ;

				if ( lefthigh - righthigh >= 0 ) { // LL Balance
					LeftRotate ( tree ) ;
				} // if
				
				else if ( lefthigh - righthigh < 0 ) { // LR balance
					RightRotate ( tree -> child[0] ) ;
					LeftRotate ( tree ) ;
				} // else if
			} // if ( left heavy )
			
			else if ( lefthigh - righthigh == -2 ) {
				lefthigh = 0, righthigh = 0 ;
				FindTreehigh( tree -> child[1] -> child[0], lefthigh, temphigh ) ;
				FindTreehigh( tree -> child[1] -> child[1], righthigh, temphigh ) ;

				if ( lefthigh - righthigh > 0 ) { // RL Balance
					LeftRotate ( tree -> child[1] ) ;
					RightRotate ( tree ) ;
				} // if
				
				else if ( lefthigh - righthigh <= 0 ) { // RR Balance
					RightRotate ( tree ) ;
				} // else if
			} // else if ( right heavy )
		} // void Balance
		
		void Insert( AvlNode *&tree, Data data, int &numOfNode ) {
			
			if ( tree == NULL ) {
				numOfNode += 1 ;
				tree = new AvlNode ;
				tree -> node.push_back( data ) ;
			} // if ( tree == NULL )

			else if ( data.graduate == tree -> node[0].graduate ) {
				tree -> node.push_back( data ) ;
			} // else if ( data graduate equals node )

			else if ( data.graduate > tree -> node[0].graduate ) {
				Insert( tree -> child[1], data, numOfNode ) ;
			} // else if ( data graduate greater than node )
			
			else if ( data.graduate < tree -> node[0].graduate ) {
				Insert( tree -> child[0], data, numOfNode ) ;
			} // else if ( data graduate small than node )
			
			Balance( tree ) ;
		} // void Insert
}; // class AVLtree

class File {
	public :
		bool IsNumber( string filename ) {											// 確認檔名是否為數字 
			for ( int i = 0; i < filename.length(); i++ ) {
				if ( filename[i]-'0' < 0 || filename[i]-'0' > 9 )
					return false;
			} // for
			return true ;
		} // bool IsNumber

		int Str_to_int( string str ) { // change string to int
			int num = 0 ;
			for( int i=0; i < str.length(); i++ ) {
				if( str[i] >= '0' && str[i] <= '9' )
					num = num * 10 + ( str[i] - '0' ) ;
			} // for

			if(	str[0] == '-' )
				num = -num ;
			return num ;
		} // int Str_to_int

		string CheakDataName( string &str, string &temp ) { // 取出檔案所需的內容 並刪除已取用的 Data 
			temp = "\0" ;
			int i = 0 ;
			int size = str.length() ;
			for( i=0; str[i] != '\t' && str[i] != '\n' && str[i] != '\0'; i++ ) // Marge Data ( include space )
				temp = temp + str[i] ;
			for( int j=i+1; j < size; j++ )    // respell str
			  str[j-i-1] = str[j] ;
			for( int j=size-i-1; j<size; j++ ) // str last word + \0
			  str[j] = '\0' ;
			return temp ;
		} // CheakDataName()

		void Cheak_filename( string &filename ) {								// 修改檔名 
			bool hasPoint = false ;
			if ( IsNumber( filename ) )														// 檔名都是數字 
				filename = "input" + filename + ".txt" ;

			else { 																								// 檔名包含數字以外的字元 
				for ( int i = 0; i < filename.length(); i++ ) {
					if ( filename[i] == '.') { 												// 檔名包含 '.' 
						hasPoint = true ;
						break ;
					} // if ( hasPoint == true ) 
				} // for

	  		if ( !hasPoint )                        					  // 檔名不包含 '.'
		  		filename = filename + ".txt" ;
			} // else
		} // string Cheak_filename

		void Txt_to_vec( string filename, int mission ) {  // write txt to vector
			Data data ;                   // declare class : Data 
			TwoThreeTree twoThreeTree ;   // declare class : TwoThreeTree 
			AVLtree avlTree ;             // declare class : AVLtree
			
			Node *root = NULL ;
			Node *parent = NULL ; 
			AvlNode *avlroot = NULL ;
			
			int numOfNode = 0 ;           // count node
			int serial = 1 ;
									
			string line = "\0", del = "\0" ; // line : cin to line, del : cin useless data 
			string temp = "\0" ;

			ifstream in ;
			in.open( filename.c_str() ) ;
			for( int i=0 ; i<3 ; i++ )       // delete 1~3 line
				getline(in, del) ; 

			getline(in, line) ; 
			while( line != "\0" ) {
				data.serial = serial ;
				data.school_code = CheakDataName( line, temp ) ;
				data.school_name = CheakDataName( line, temp ) ;
				data.department_code = CheakDataName( line, temp ) ;
				data.department_name = CheakDataName( line, temp ) ;
				data.day = CheakDataName( line, temp ) ;
				data.education = CheakDataName( line, temp ) ;
				data.student = Str_to_int ( CheakDataName( line, temp ) ) ;
				data.teacher = Str_to_int ( CheakDataName( line, temp ) ) ;
				data.graduate = Str_to_int ( CheakDataName( line, temp ) ) ;
				data.city = CheakDataName( line, temp ) ;
				data.system = CheakDataName( line, temp ) ;
				if ( mission == 1 ) {
          twoThreeTree.Insert( root, parent, data, numOfNode ) ;
				} // if ( mission == 1 )
				else if ( mission == 2 ) {
					avlTree.Insert( avlroot, data, numOfNode ) ;
				} // else if ( mission == 2 )

				data.Init() ;
				parent = NULL ;

				serial++ ;
				line = "\0" ;
				getline(in, line) ; 
			} // while
			
			if ( mission == 1 ) {
				PrintData( root, numOfNode ) ;    // print mission 1 data
			} // if ( mission == 1 )
				
			else if ( mission == 2 ) {
				PrintAvlData( avlroot, numOfNode ) ;        // print mission 2 data
			} // else if ( mission == 2 )
				
			in.close() ;
		} // void Txt_to_vec
		
		void PrintData( Node *tree, int numOfNode ) {
			TwoThreeTree twoThreeTree ;              // declare class : TwoThreeTree
			int high = 0 ;
			high = twoThreeTree.CountHigh( tree ) ; // find tree high
			
			cout << "\nTree hight = " << high ;
			cout << "\nNumber of nodes = " << numOfNode << endl ;
			
			if ( tree -> node[0].aNode[0].serial > tree -> node[tree -> node.size()-1].aNode[0].serial )
				swap( tree -> node[0], tree -> node[tree -> node.size()-1] ) ;
			
			int num = 1 ;
			for ( int i=0; i < tree -> node.size(); i++ ) {
				for ( int j=0; j < tree -> node[i].aNode.size(); j++ ) {
					cout << num << ": [" << tree -> node[i].aNode[j].serial << "] " ;
					cout << tree -> node[i].aNode[j].school_name << ", " << tree -> node[i].aNode[j].department_name << ", " ;
					cout << tree -> node[i].aNode[j].day << ", " << tree -> node[i].aNode[j].education << ", " ;
					cout << tree -> node[i].aNode[j].graduate << endl ;
					num++ ;
				} // for
			} // for
		} // void PrintData
		
		void PrintAvlData( AvlNode *tree, int numOfNode ) {
			AVLtree avlTree ;                              // declare class : AVLtree
			int tempHigh = 0, high = 0 ;
			avlTree.FindTreehigh( tree, high, tempHigh ) ; // find tree high
			
			cout << "\nTree hight = " << high ;
			cout << "\nNumber of nodes = " << numOfNode << endl ;
			
			int num = 1 ;
			for ( int i=0; i < tree -> node.size(); i++ ) {
				cout << num << ": [" << tree -> node[i].serial << "] " ;
				cout << tree -> node[i].school_name << ", " << tree -> node[i].department_name << ", " ;
				cout << tree -> node[i].day << ", " << tree -> node[i].education << ", " ;
				cout << tree -> node[i].graduate << endl ;
				num++ ;
			} // for
		} // void PrintAvlData
		
		/*
		
		void printCurrentLevel( AvlNode* root, int level) {  // print level data ( debug )
    	if (root == NULL)
        return;
        
      if (level == 1) {
          cout << root -> node[0].graduate  ;
          cout << "   " ;
      } // if ( level == 1 )
      
      else if (level > 1) {
        printCurrentLevel(root->child[0], level - 1);
        printCurrentLevel(root->child[1], level - 1);
      } // else if ( level >= 1 )
    } // void printCurrentLevel

    void printLevelOrder(AvlNode* root) {  // print tree
    	AVLtree avlTree ;
    	int tempHigh = 0, high = 0 ;
			avlTree.FindTreehigh(root, high, tempHigh);
      for ( int i = 1; i <= high; i++){
        printCurrentLevel(root, i);
        cout << endl ;
      } // for
    } // void printLevelOrder
    
    */
    
}; // class File

class Mission {
	public :
		void Mission1( string &filename ) {
			File file ; // declare class : File
			ifstream in ;
			filename = "\0" ;
			cout << "\nInput your files ( 201, input201.txt ) : " ;
			cin >> filename ;
			file.Cheak_filename( filename ) ; // modify fileName 
			in.open( filename.c_str() ) ;

			if ( in.is_open() ) {
				file.Txt_to_vec( filename, 1 ) ; // write text to vector and Insert to 2-3 tree
				in.close();
			} // if

			else
				cout << "\n### " << filename << " does not exist! ###\n" ; 
		} // void Mission1

		void Mission2( string filename ) {
			File file ;
			ifstream in ;
			in.open( filename.c_str() ) ;

			if ( in.is_open() ) {
				file.Txt_to_vec( filename, 2 ) ; // write text to vector and Insert to AVL tree
				in.close();
			} // if

			else
				cout << "\n### Choose 1 first. ###\n" ; 
		} // void Mission2
}; // class Mission

void Start() {
	int command = 0 ;
	string filename = "\0" ; 
	Mission mission ;
	do{
		cout << "\n*** Search Tree Utilities **" ;
    cout << "\n* 0. QUIT                  *" ;
    cout << "\n* 1. Build 2-3 tree        *" ;
    cout << "\n* 2. Build AVL tree        *" ;
    cout << "\n****************************" ;
    cout << "\nInput your command ( 0, 1, 2 ) : " ;
    cin >> command ;
    switch ( command ) {
    	case( 0 ) :
    		cout << "\nexit" ;
    	  break ;
		  case( 1 ) :
		  	mission.Mission1( filename ) ;
		  	break ;
		  case( 2 ) :
		  	mission.Mission2( filename ) ;
		  	break ;
		  default :
		  	cout << "\n### Command does not exist! ###\n" ;
	  } // switch
	} while ( command > 0 ) ; // do while
} // void start()

int main() { 
	Start() ;
} // int main()
