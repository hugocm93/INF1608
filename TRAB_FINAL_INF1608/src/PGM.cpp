#include <iostream>
#include <cstdlib>

#include "PGM.h"


PGM::PGM( std::string path, std::string name, int width, int height, int maxValue )
{
    path = path + name + ".pgm";
    _file.open( path.c_str(), std::ios::out );
    if( !_file.is_open() )
    {
        std::cout << "It was not possible to export the PGM to a file" << std::endl;
        exit( 1 );
    }

    _file << "P2\n";
    _file << "# " << name << ".pgm\n";
    _file << width << " " << height << "\n";
    _file << maxValue << "\n";
}


void PGM::add( int value )
{
    _file << value << " ";
}


void PGM::newLine()
{
    _file << "\n";
}


void PGM::exportPGM()
{
    _file.close();
}


PGM::~PGM()
{
}


