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

    std::vector< std::vector< double > > matrix( _sceneHeight );
    for( int i = 0; i < _sceneHeight; i++ )
    {
        matrix[i].resize( _sceneWidth );
    }
  
    double L = _ct->getYLength();	
    for( int i = 0; i < _sceneHeight; i++ )
    {
	for( int j = 0; j < _sceneWidth; j++ )
        {
	    Ray ray1( 2*j, 0, i );
	    Ray ray2( 2*j + 1, 0, i );

	    double first = calcIntegral( &ray1, L );	
	    double second = calcIntegral( &ray2, L );	
	    matrix[i][j] = 255*( first + second )/2;
        }
    }

    int maxValue; 
    for( int i = 0; i < _sceneHeight; i++ )
    {
	for( int j = 0; j < _sceneWidth; j++ )
        {
		if( matrix[i][j] > maxValue )
		{
			maxValue = matrix[i][j];
		}
        }
    }

    PGM pgm( pathToFile, fileName, _sceneWidth, _sceneHeight, maxValue );

    for( int i = 0; i < _sceneHeight; i++ )
    {
	for( int j = 0; j < _sceneWidth; j++ )
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
	  return talDt( _ct->getValue( ( double )ray->_x, ( double )value, ( double )ray->_z )/255 );
      };

      double expoent = Integral::simpson( function, 0, L, 1 /*H*/ );

      return exp(-expoent)*Integral::simpson( function, 0, L, 1 /*H*/ ); 
}
