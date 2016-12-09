#include <iostream>
#include <vector>
#include <cmath>

#include "VolumeVisualizationScene.h"
#include "PGM.h"
#include "Integral.h"
#include "Ray.h"

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
   
    double L = _ct->getYLength();	
    for( int j = 0; j < _sceneHeight; j++ )
    {
        for( int i = 0; i < _sceneWidth; i++ )
        {
	    Ray ray1( 2*i, 0, j );
	    Ray ray2( 2*i + 1, 0, j );

	    double first = calcIntegral( &ray1, L );	
	    double second = calcIntegral( &ray2, L );	
	    matrix[i][j] = 255*( first + second )/2;
        }
    }


    int maxValue; 
    for( int j = 0; j < _sceneHeight; j++ )
    {
        for( int i = 0; i < _sceneWidth; i++ )
        {
		if( matrix[i][j] > maxValue )
		{
			maxValue = matrix[i][j];
		}
        }
    }

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


double VolumeVisualizationScene::talDt( double v )
{
	if( v <= 0.3 )
	{
		return 0;
	}

	return 0.05*( v - 0.3 );
}


double VolumeVisualizationScene::calcIntegral( Ray* ray, double L )
{
      std::function< double ( double ) > function = [ & ]( double value ) -> double
      {
	  return talDt( _ct->getValue( ray->_x, value, ray->_z )/255 );
      };

      double expoent = Integral::simpson( function, 0, L, 1 /*H*/ );

      return exp(-expoent)*Integral::simpson( function, 0, L, 1 /*H*/ ); 
}
