#ifndef PGM_H
#define PGM_H

#include <string>
#include <fstream>

class PGM
{
public:

    PGM( std::string path, std::string name, int width, int height, int maxValue );

    void add( int value );

    void newLine();

    void exportPGM();

    ~PGM();

private:

    std::ofstream _file;
};

#endif
