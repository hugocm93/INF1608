#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

double** mat_cria( int m, int n )
{
	double** matriz = ( double** )malloc( m*sizeof( double* ) );
	if( !matriz )
	{	
		printf( "Erro na alocação da matriz\n" );
		exit( 1 );
	}

	int i, j;
	for( i = 0; i < m; i++ )
	{
		matriz[ i ] = ( double* )malloc( n*sizeof( double ) );	
		if( !matriz[ i ] )
		{	
			printf( "Erro na alocação da matriz\n" );
			exit( 2 );
		}
	}

	for( i = 0; i < m; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			matriz[ i ][ j ] = 0;
		}
	}

	return matriz;
}

void mat_libera( int m, double** A)
{
	if( !A )
	{
		printf( "Matriz não existe\n" );
		return;
	}

	int i;
	for( i = 0; i < m; i++ )
	{
		free( A[ i ] );
		A[ i ] = NULL;
	}
	
	free( A );
}

void mat_transposta ( int m, int n, double** A, double** T )
{
	if( !A || !T )
	{
		printf( "Matrizes não existem\n" );
		return;
	}
	int i, j;
	for( i = 0; i < m; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			T[ i ][ j ] = A[ j ][ i ];
		}
	}
}

void mat_multv (int m, int n, double** A, double* V, double* W )
{
	if( !A || !V || !W )
	{
		printf( "Dados não existem\n" );
		return;
	}

	int w;
	for( w = 0; w < n ; w++ )
	{
		W[ w ] = 0;
	}

	int i, j;
	for( i = 0; i < m; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			W[ i ] += A[ i ][ j ]*V[ j ];
		}
	}
}

void mat_multm ( int m, int n, int q, double** A, double** B, double** C )
{

}

void mat_imprime( int m, int n, double** A )
{
	if( !A )
	{
		printf( "Matriz não existe\n" );
		return;
	}

	printf( "\n---\n");
	int i, j;
	for( i = 0; i < m; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			printf( "%lf ", A[ i ][ j ] );
		}
		printf( "\n");
	}
	printf( "---\n");
}
