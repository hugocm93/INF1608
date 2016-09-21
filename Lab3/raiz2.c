#include "raiz2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXITERACOES 100

/*Estrutura de matriz*/
typedef double** Matriz;
Matriz mat_cria( int m, int n );
void mat_libera( int m, Matriz A);
double mat_det3( Matriz M );

int NR ( double x0, int p, double ( *f ) ( double x ), double ( *fl ) ( double x ), double* r )
{
  int i = 0;
  double fx = 0, erro = 0.5 * pow( 10, -p );

  while( ( fx = f( x0 ) ) && fabs( fx ) >= erro && ( x0 -= fx/fl( x0 ) ) && ++i && ( i < MAXITERACOES ) );
  *r = x0;

  return i >= MAXITERACOES ? 0 : i;
}

int IQI ( double x0, double x1, double x2, int p, double ( *f ) ( double x ), double* r )
{
  int i = 0;
  double erro = 0.5 * pow( 10, -p ), fx, c = 0;

  do
  {
    Matriz A = mat_cria( 3, 3 );
    A[0][0] = f( x0 )*f( x0 );
    A[0][1] = f( x0 );
    A[0][2] = 1;
    A[1][0] = f( x1 )*f( x1 );
    A[1][1] = f( x1 );
    A[1][2] = 1;
    A[2][0] = f( x2 )*f( x2 );
    A[2][1] = f( x2 );
    A[2][2] = 1;

    Matriz Ac = mat_cria( 3, 3 );
    Ac[0][0] = A[0][0];
    Ac[0][1] = A[0][1];
    Ac[0][2] = x0;
    Ac[1][0] = A[1][0];
    Ac[1][1] = A[1][1];
    Ac[1][2] = x1;
    Ac[2][0] = A[2][0];
    Ac[2][1] = A[2][1];
    Ac[2][2] = x2;

    c = mat_det3( Ac ) / mat_det3( A );

    mat_libera( 3, Ac );
    mat_libera( 3, A );

    double d0 = fabs( c - x0 );
    double d1 = fabs( c - x1 );
    double d2 = fabs( c - x2 );

    if( d0 > d1 && d0 > d2 )
    {
      x0 = c;
    }
    else if( d1 > d0 && d1 > d2 )
    {
      x1 = c;
    }
    else
    {
      x2 = c;
    }

    fx = f(c);
  }while( fabs( fx ) >= erro && ++i && ( i < MAXITERACOES ) );

  *r = c;

  return i >= MAXITERACOES ? 0 : i;
}

/*Implementação da matriz*/
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
