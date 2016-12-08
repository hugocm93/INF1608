#include <iostream>

#include "VolumeVisualizationScene.h"
#include "PGM.h"
#include "Integral.h"

VolumeVisualizationScene::VolumeVisualizationScene( CT* ct, int sceneWidth, int sceneHeight ) :
    _ct( ct ),
    _sceneWidth( sceneWidth ),
    _sceneHeight( sceneHeight )
{
}


VolumeVisualizationScene::~VolumeVisualizationScene()
{
    delete _ct;
}


void VolumeVisualizationScene::renderToFile( std::string pathToFile, std::string fileName )
{
    std::cout << "Rendering to file " << pathToFile << fileName << ".pgm" << std::endl;

    std::vector< std::vector< double > > matrix( _sceneWidth );
    for( int i = 0; i < _sceneHeight; i++ )
    {
        matrix[i].resize( _sceneHeight );
    }
   

    //Populate matrix
    int maxValue; 
    //Update maxValue

    PGM pgm( pathToFile, fileName, _sceneWidth, _sceneHeight, maxValue );

    for( int j = 0; j < _sceneHeight; j++ )
    {
        for( int i = 0; i < _sceneWidth; i++ )
        {
            pgm.add( matrix[i][j] );
        }
        pgm.newLine();
    }

    pgm.exportPGM();
}
