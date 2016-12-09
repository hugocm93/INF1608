#ifndef VOLUMEVISU_H
#define VOLUMEVISU_H

#include "CT.h"

class Ray;

class VolumeVisualizationScene
{
public:

    VolumeVisualizationScene( CT* ct, int sceneWidth, int sceneHeight );

    ~VolumeVisualizationScene();

    void renderToFile( std::string pathToFile, std::string fileName );

private:

    double talDt( double v );
    double calcIntegral( Ray* ray, double L );

    CT* _ct;
    int _sceneWidth;
    int _sceneHeight;
};
#endif
