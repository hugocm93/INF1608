#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>

#include "PGM.h"
#include "CT.h"

CT::CT( std::string path, int* indexes )
{
    std::ifstream file;
    file.open( path.c_str(), std::ios::in | std::ios::binary );
    if( !file.is_open() )
    {
        std::cout << "File not found" << std::endl;
        exit( 1 );
    }

    file.seekg( 0, std::fstream::end );
    int length = file.tellg();

    file.seekg( 0, std::fstream::beg );
    _values = new unsigned char [ length ];

    file.read( ( char* ) _values, length );

    file.close();

    std::memcpy( _indexes, indexes, 3 * sizeof( int ) );
}


unsigned char CT::getValue( int i, int j, int k )
{
    return _values[ k * _indexes[ 0 ] * _indexes[ 1 ] + j * _indexes[ 0 ] + i ];
}


double CT::getValue( double i, double j, double k )
{
    int previous = ( int )j;
    double percentage = j - previous;

    double first = ( double ) _values[ ( int )k * _indexes[ 0 ] * _indexes[ 1 ] + previous * _indexes[ 0 ] + ( int )i ]*( 1 - percentage );
    double second = ( double ) _values[ ( int )k * _indexes[ 0 ] * _indexes[ 1 ] + ( previous + 1 ) * _indexes[ 0 ] + ( int )i ]*( percentage );

    return first + second;
}


void CT::sliceToPGM( std::string path, std::string name, int k )
{
    int width = _indexes[ 0 ];
    int height = _indexes[ 1 ];
    int maxValue = 0;

    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            if( maxValue < getValue( i, j, k ) )
            {
                maxValue = getValue( i, j, k );
            }
        }
    }

    PGM pgm( path, name, width, height, maxValue );

    for( int j = 0; j < height; j++ )
    {
        for( int i = 0; i < width; i++ )
        {
            pgm.add( ( int )getValue( i, j, k ) );
        }
        pgm.newLine();
    }

    pgm.exportPGM();
}


double CT::getYLength()
{
    return _indexes[ 1 ];
}


CT::~CT()
{
    delete[] _values;
}


