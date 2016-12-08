#ifndef VOLUMEVISU_H
#define VOLUMEVISU_H

#include "CT.h"

class VolumeVisualizationScene
{
public:

    VolumeVisualizationScene( CT* ct, int sceneWidth, int sceneHeight );

    ~VolumeVisualizationScene();

    void renderToFile( std::string pathToFile, std::string fileName );

private:

    CT* _ct;
    int _sceneWidth;
    int _sceneHeight;
};
#endif
