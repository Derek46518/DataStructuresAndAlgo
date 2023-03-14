# include <cstdio>
using namespace std ;

int main( int argc, char** argv ) {

  // printf( "Number of parameters : %d\n", argc ) ;

  for ( int i = 0 ; i < argc ; i++ )
    printf( "Para %d >>%s<<\n", i, argv[i] ) ;

} // main()
