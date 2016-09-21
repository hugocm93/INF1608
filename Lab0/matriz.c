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

	mat_zeram( n, m, T );

	int i, j;
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < m; j++ )
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

	mat_zerav( n, W );

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
	if( !A || !B || !C )
	{
		printf( "Dados não existem\n" );
		return;
	}

	mat_zeram( m, q, C );

	int i, j, k;
	for( k = 0; k < q; k++ )
	{
		for( i = 0; i < m; i++ )
		{
			for( j = 0; j < n; j++ )
			{
				C[ i ][ k ] += A[ i ][ j ]*B[ j ][ k ];
			}
		}
	}
}

void mat_imprime( char* title, int m, int n, double** A )
{
	if( !A )
	{
		printf( "Matriz não existe\n" );
		return;
	}

	printf( "%s\n", title );
	int i, j;
	for( i = 0; i < m; i++ )
	{
		printf( " |");
		for( j = 0; j < n; j++ )
		{
			printf( A[ i ][ j ] >= 0 ? " %.2lf " : "%.2lf " , A[ i ][ j ] );
		}
		printf( "|\n");
	}
	printf( "\n");
}

void mat_zeram( int m, int n, double** A )
{
	if( !A || !m || !n )
	{
		printf( "Dados não existem\n" );
		return;
	}

	int i, j;
	for( i = 0; i < m; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			A[ i ][ j ] = 0;
		}
	}
}

void mat_zerav( int m, double* V )
{
	if( !V || !m )
	{
		printf( "Dados não existem\n" );
		return;
	}

	int v;
	for( v = 0; v < m ; v++ )
	{
		V[ v ] = 0;
	}
}

double mat_det3( double** M )
{
	if( !M )
	{
		printf( "Dados não existem\n" );
		return -1;
	}

	return
	  M[0][0]*( M[1][1]*M[2][2] - M[1][2]*M[2][1] )
	- M[0][1]*( M[1][0]*M[2][2] - M[2][0]*M[1][2] )
	+ M[0][2]*( M[1][0]*M[2][1] - M[2][0]*M[1][1] );
}
