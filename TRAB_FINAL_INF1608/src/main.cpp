#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "CT.h"
#include "VolumeVisualizationScene.h"

#define MAX_NUMBER_SIZE 20

void usage( std::string programName );

int main( int argc, char** argv )
{
    if( argc != 6 )
    {
        usage( std::string( argv[ 0 ] ) );
        return 0;
    }

    int indexes[ 3 ], i = 0;
    std::string buff;
    std::string params( argv[ 1 ] );

    std::replace( params.begin(), params.end(), 'X', ' ' );
    std::replace( params.begin(), params.end(), 'x', ' ' );
    std::stringstream ss( params );

    while( ss >> buff )
    {
        if( i > 2 )
        {
            std::cout << "Incorrect parameters" << std::endl;
            exit( 1 );
        }
        indexes[ i++ ] = atoi( buff.c_str() );
    }

    VolumeVisualizationScene volVisuScene( new CT( std::string( argv[ 2 ] ), indexes ), indexes[0]/2, indexes[2] , atof( argv[5] ) );
    volVisuScene.renderToFile( std::string( argv[3] ), std::string( argv[4] ) );

    return 0;
}


void usage( std::string programName )
{
    std::cout << "Usage: " << programName << " [IxJxK] [path to CT file] [path to output pgm file] [pgm file name] [ H ]"
     << std::endl;
}


