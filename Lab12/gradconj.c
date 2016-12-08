#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

void Cholesky( int n, double** A );
void ConjugateGradient( int n, double** A, double* b, double* x );
double mod( int n, double* v );
double** toMatrix( int n, double* v );
double** toMatrixT( int n, double* v );

int main( void )
{
    Matriz m1 = mat_cria( 3, 3 );
    m1[ 0 ][ 0 ] = 1;
    m1[ 0 ][ 1 ] = -1;
    m1[ 0 ][ 2 ] = 0;
    m1[ 1 ][ 0 ] = -1;
    m1[ 1 ][ 1 ] = 2;
    m1[ 1 ][ 2 ] = 1;
    m1[ 2 ][ 0 ] = 0;
    m1[ 2 ][ 1 ] = 1;
    m1[ 2 ][ 2 ] = 2;

    double b1[ 3 ];
    b1[ 0 ] = 0;
    b1[ 1 ] = 2;
    b1[ 2 ] = 3;

    double b2[ 3 ];
    b2[ 0 ] = 3;
    b2[ 1 ] = -3;
    b2[ 2 ] = 4;

    printf("ConjugateGradient\n"); 
    double x[] = { 0, 0, 0 };
    ConjugateGradient( 3, m1, b1, x );
    vec_imprime("x: ", x, 3 );

    ConjugateGradient( 3, m1, b2, x );
    vec_imprime("x: ", x, 3 );




    printf("Cholesky\n"); 

    mat_imprime( "A: ", 3, 3, m1 );

    Cholesky( 3, m1 );
    mat_imprime( "R:", 3, 3, m1 );

    Matriz RT = mat_cria( 3, 3 );
    mat_transposta( 3, 3, m1, RT );
    mat_imprime( "RT:", 3, 3, RT );

    Matriz A = mat_cria( 3, 3 );
    mat_multm( 3, 3, 3, RT, m1, A );
    mat_imprime( "A:", 3, 3, A );

    mat_libera( 3, RT );
    mat_libera( 3, A );
    mat_libera( 3, m1 );

    return 0;
}


void Cholesky( int n, double** A )
{
    int k;
    for( k = 0; k < n; k++ )
    {
        Matriz U = mat_cria( n - k, 1 );
        Matriz UT = mat_cria( 1, n - k );
        Matriz UUT = mat_cria( n - k, n - k );

        A[ k ][ k ] = sqrt( A[ k ][ k ] );

        int w;
        for( w = k + 1; w < n; w++ )
        {
            A[ k ][ w ] = ( 1 / A[ k ][ k ] ) * A[ k ][ w ];
            UT[ 0 ][ w - ( k + 1 ) ] = A[ k ][ w ];
            A[ w ][ k ] = 0;
        }

        mat_transposta( 1, n - k, UT, U );
        mat_multm( n - k, 1, n - k, U, UT, UUT );

        int j, i;
        for( j = k + 1; j < n; j++ )
        {
            for( i = k + 1; i < n; i++ )
            {
                A[ i ][ j ] = A[ i ][ j ] - UUT[ i - ( k + 1 ) ][ j - ( k + 1 ) ];
            }
        }

        mat_libera( n - k, U );
        mat_libera( 1, UT );
        mat_libera( n - k, UUT );
    }
}


void ConjugateGradient( int n, double** A, double* b, double* x )
{
    double* d = ( double* )malloc( sizeof( double ) * n );
    double* r = ( double* )malloc( sizeof( double ) * n );

    mat_multv( n, n, A, x, d );

    int i;
    for( i = 0; i < n; i++ )
    {
        d[ i ] = b[ i ] - d[ i ];
        r[ i ] = d[ i ];
    }

    int k;
    double tol = 0.5 * pow( 10, -7 );
    for( k = 0; k < n; k++ )
    {
        if( mod( n, r ) < tol )
        {
            return;
        }

        Matriz mR = toMatrix( n, r);
        Matriz mRT = toMatrixT( n, r);
       
        Matriz RTR = mat_cria( 1, 1 );
        mat_multm( 1, n, 1, mRT, mR, RTR );

        Matriz mD = toMatrix( n, d );
        Matriz mDT = toMatrixT( n, d );
        Matriz Ad = mat_cria( n, 1 );
        mat_multm( n, n, 1, A, mD, Ad);

        Matriz dTA = mat_cria( 1, 1 ); 
        mat_multm( 1, n, 1, mDT, Ad, dTA );

        double alpha = RTR[0][0]/dTA[0][0];

        int i;
        for( i = 0; i < n; i++ )
        {
            x[i] += alpha*d[i];
        }

        for( i = 0; i < n; i++ )
        {
            r[i] -= alpha*Ad[i][0];
        }

        
        Matriz mR2 = toMatrix( n, r);
        Matriz mRT2 = toMatrixT( n, r);
       
        Matriz RTR2 = mat_cria( 1, 1 );
        mat_multm( 1, n, 1, mRT2, mR2, RTR2 );

        double beta = RTR2[0][0]/RTR[0][0];

        for( i = 0; i < n; i++ )
        {
            d[i] =  r[i] + beta*d[i];
        }
       
        mat_libera( n, mR );
        mat_libera( 1, mRT );
        mat_libera( 1, RTR );
        mat_libera( n, mD );
        mat_libera( 1, mDT );
        mat_libera( n, Ad );
        mat_libera( 1, dTA );
        mat_libera( n, mR2 );
        mat_libera( 1, mRT2 );
        mat_libera( 1, RTR2 );
    }
    free( d );
    free( r );
}


double mod( int n, double* v )
{
    int i;
    double sum = 0;
    for( i = 0; i < n; i++ )
    {
        sum += v[i] * v[i];
    }
    return sqrt( sum );
}


double** toMatrix( int n, double* v)
{
    Matriz m = mat_cria( n, 1 );

    int i;
    for( i = 0; i < n; i++)
    {
        m[i][0] = v[i];
    }
    return m; 
}


double** toMatrixT( int n, double* v)
{
    Matriz m = mat_cria( 1, n );

    int i;
    for( i = 0; i < n; i++)
    {
        m[0][i] = v[i];
    }
    return m; 
}




