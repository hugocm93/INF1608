#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

#define TOL 0.5*pow(10,-7)
#define W 1.1

typedef enum metodo
{
    JACOBI,
    GAUSS_SEIDEL,
    SOR_,
    N_METODOS
} Metodo;

int Jacobi(int n, double** A, double* b, double* x, double tol )
{
    //Separa a matriz em duas
    int i, j;
    int contador = 0;
    Matriz _1SobreD = mat_cria(n, n);
    Matriz LU = mat_cria(n, n);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
            {
                _1SobreD[i][j] = 1.0/A[i][j];
            }
            else
            {
                LU[i][j] = A[i][j];
            }
        }
    }

    //Iteração
    double norma2;
    double* aux = (double*)malloc(sizeof(double)*n);
    double* B = (double*)malloc(sizeof(double)*n);
    double* lastX = (double*)malloc(sizeof(double)*n);
    do
    {
        //Guarda o x anterior
        int i;
        for(i = 0; i < n; i++)
        {
            lastX[i] = x[i];
        }
        
        //Primeira multiplicação
        mat_multv(n, n, LU, x, aux);
        
        //Subtração de vetores
        int k;
        for(k = 0; k < n; k++)
        {
            B[k] = b[k] - aux[k];
        }

        //Segunda multiplicação
        mat_multv(n, n, _1SobreD, B, x);

        //Diferença do x para o anterior
        for(i = 0; i < n; i++)
        {
            lastX[i] -= x[i];
        }
        
        //Norma2 da diferença
        norma2 = 0;
        for(k = 0; k < n; k++)
        {
            norma2 += lastX[k]*lastX[k];
        }
        norma2 = sqrt(norma2);

        //Incrementa o número de vezes
        contador++;
    }
    while(norma2 > TOL);

    free(aux);
    free(B);
    mat_libera(n, _1SobreD);
    mat_libera(n, LU);
    
    return contador;
}


int GaussSeidel(int n, double** A, double*b, double*x, double tol)
{
    //Separa a matriz em três 
    int i, j, k;
    int contador = 0;
    Matriz _1SobreD = mat_cria(n, n);
    Matriz L = mat_cria(n, n);
    Matriz U = mat_cria(n, n);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
            {
                _1SobreD[i][j] = 1.0/A[i][j];
            }
            else if(i > j)
            {
                L[i][j] = A[i][j];
            }
            else
            {
                U[i][j] = A[i][j];
            }
        }
    }

    //Iteração
    double norma2;
    double* aux = (double*)malloc(sizeof(double)*n);
    double* aux2 = (double*)malloc(sizeof(double)*n);
    double* B = (double*)malloc(sizeof(double)*n);
    double* lastX = (double*)malloc(sizeof(double)*n);
    do
    {
        //Guarda o x anterior
        for(i = 0; i < n; i++)
        {
            lastX[i] = x[i];
        }
        
        //Primeira multiplicação
        mat_multv(n, n, L, x, aux);
        
        //Segunda multiplicação
        mat_multv(n, n, U, x, aux2);
        
        //Subtração de vetores
        for(k = 0; k < n; k++)
        {
            B[k] = b[k] - aux[k] - aux2[k];
        }

        //Terceira multiplicação
        mat_multv(n, n, _1SobreD, B, x);

        //Quarta multiplicação
        mat_multv(n, n, L, x, aux);
        
        //Subtração de vetores
        for(k = 0; k < n; k++)
        {
            B[k] = b[k] - aux2[k] - aux[k];
        }

        //Quarta multiplicação
        mat_multv(n, n, _1SobreD, B, x);

        //Diferença do x para o anterior
        for(i = 0; i < n; i++)
        {
            lastX[i] -= x[i];
        }
        
        //Norma2 da diferença
        norma2 = 0;
        for(k = 0; k < n; k++)
        {
            norma2 += lastX[k]*lastX[k];
        }
        norma2 = sqrt(norma2);

        //Incrementa o número de vezes
        contador++;
    }
    while(norma2 > TOL);

    free(aux);
    free(aux2);
    free(B);
    mat_libera(n, _1SobreD);
    mat_libera(n, L);
    mat_libera(n, U);
    
    return contador;
}


int SOR(int n, double** A, double* b, double* x, double tol, double w)
{
    int i, j, k;

    //Separa a matriz em três 
    int contador = 0;
    Matriz _1SobreD = mat_cria(n, n);
    Matriz L = mat_cria(n, n);
    Matriz U = mat_cria(n, n);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
            {
                _1SobreD[i][j] = 1.0/A[i][j];
            }
            else if(i > j)
            {
                L[i][j] = A[i][j];
            }
            else
            {
                U[i][j] = A[i][j];
            }
        }
    }

    //Iteração
    double norma2;
    double* aux = (double*)malloc(sizeof(double)*n);
    double* aux2 = (double*)malloc(sizeof(double)*n);
    double* B = (double*)malloc(sizeof(double)*n);
    double* a = (double*)malloc(sizeof(double)*n);
    double* lastX = (double*)malloc(sizeof(double)*n);
    do
    {
        //Guarda o x anterior
        for(i = 0; i < n; i++)
        {
            lastX[i] = x[i];
        }
        
        //Primeiro operando
        for(k = 0; k < n; k++)
        {
            a[k] = (1 - w)*x[k];
        }

        //Primeira multiplicação
        mat_multv(n, n, L, x, aux);
        
        //Segunda multiplicação
        mat_multv(n, n, U, x, aux2);
        
        //Subtração de vetores
        for(k = 0; k < n; k++)
        {
            B[k] = b[k] - aux[k] - aux2[k];
        }

        //Terceira multiplicação
        mat_multv(n, n, _1SobreD, B, x);

        //Quarta multiplicação
        mat_multv(n, n, L, x, aux);
        
        //Subtração de vetores
        for(k = 0; k < n; k++)
        {
            B[k] = b[k] - aux2[k] - aux[k];
        }

        //Quinta multiplicação
        mat_multv(n, n, _1SobreD, B, x);

        //Soma
        for(k = 0; k < n; k++)
        {
            x[k] = a[k] + w*x[k];
        }
        
        //Diferença do x para o anterior
        for(i = 0; i < n; i++)
        {
            lastX[i] -= x[i];
        }
        
        //Norma2 da diferença
        norma2 = 0;
        for(k = 0; k < n; k++)
        {
            norma2 += lastX[k]*lastX[k];
        }
        norma2 = sqrt(norma2);

        //Incrementa o número de vezes
        contador++;
    }
    while(norma2 > TOL);

    free(aux);
    free(aux2);
    free(B);
    free(a);
    mat_libera(n, _1SobreD);
    mat_libera(n, L);
    mat_libera(n, U);
    
    return contador;
}


void teste(int n, double** A, double*b)
{
    Metodo m;
    int nVezes;
    char* nome = "Metodo      , res:";

    double* res = (double*)malloc(sizeof(double)*n);

    for(m = JACOBI; m < N_METODOS; m++)
    {
        mat_zerav(n, res); 
        switch(m)
        {
            case JACOBI:
                nVezes = Jacobi(n, A, b, res, TOL); 
                nome = "Jacobi, Res:";
            break;

            case GAUSS_SEIDEL:
                nVezes = GaussSeidel(n, A, b, res, TOL); 
                nome = "GaussSeidel, Res:";
            break;

            case SOR_:
                nVezes = SOR(n, A, b, res, TOL, W); 
                nome = "SOR, Res:";
            break;

            default:
            break;
        }
        vec_imprime(nome, res, n);
        printf("nVezes:%d\n\n\n\n", nVezes);
    }
    free(res);
}


int main(void)
{
    Matriz m1 = mat_cria(2, 2);
    m1[0][0] = 3;
    m1[0][1] = 1;
    m1[1][0] = 1;
    m1[1][1] = 2;

    double b1[2];
    b1[0] = 5;
    b1[1] = 5;


    Matriz m2 = mat_cria(6, 6);
    m2[0][0] = 3;
    m2[0][1] = -1;
    m2[0][2] = 0;
    m2[0][3] = 0;
    m2[0][4] = 0;
    m2[0][5] = 0.5;
    m2[1][0] = -1;
    m2[1][1] = 3;
    m2[1][2] = -1;
    m2[1][3] = 0;
    m2[1][4] = 0.5;
    m2[1][5] = 0;
    m2[2][0] = 0;
    m2[2][1] = -1;
    m2[2][2] = 3;
    m2[2][3] = -1;
    m2[2][4] = 0;
    m2[2][5] = 0;
    m2[3][0] = 0;
    m2[3][1] = 0;
    m2[3][2] = -1;
    m2[3][3] = 3;
    m2[3][4] = -1;
    m2[3][5] = 0;
    m2[4][0] = 0;
    m2[4][1] = 0.5;
    m2[4][2] = 0;
    m2[4][3] = -1;
    m2[4][4] = 3;
    m2[4][5] = -1;
    m2[5][0] = 0.5;
    m2[5][1] = 0;
    m2[5][2] = 0;
    m2[5][3] = 0;
    m2[5][4] = -1;
    m2[5][5] = 3;

    double b2[6];
    b2[0] = 2.5;
    b2[1] = 1.5;
    b2[2] = 1;
    b2[3] = 1;
    b2[4] = 1.5;
    b2[5] = 2.5;

    teste(2, m1, b1);
    teste(6, m2, b2);

    return 0;
}
