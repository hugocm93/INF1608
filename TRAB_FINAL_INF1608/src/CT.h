#ifndef CT_H
#define CT_H

#include <string>

class CT
{
public:

    CT( std::string path, int* indexes );

    ~CT();

    unsigned char getValue( int i, int j, int k );

    void sliceToPGM( std::string path, std::string name, int k );

    double getYLength();

private:

    unsigned char* _values;

    int _indexes[ 3 ];
};

#endif
