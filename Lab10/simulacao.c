#include <stdio.h>

#define T 15 // s
#define M 20 // Kg
#define K 20 // N/m
#define X0 1 // m
#define V0 0 // m/s
#define H 0.1  // passo

typedef struct estado
{
    double posicao;
    double velocidade;    
} Estado;

typedef struct estadoDiff
{
    double velocidade;
    double aceleracao;   
} EstadoDiff;


void teste(double c);
void imprimeEstado(Estado e);
void rungeKutta(double c, Estado* inicial, Estado* final);

int main(void)
{
    double c = 0; // coeficiente
    
    c = 5; // subamortecido
    teste(c);   
    
    c = 40; // criticamente amortecido
    teste(c);   
    
    c = 200; // superamortecido
    teste(c);   

    return 0;
}


void teste(double c)
{
    Estado inicial;
    inicial.posicao = X0;
    inicial.velocidade = V0;

    printf("Teste:%.1f h:%.1f \n", c, H);
    double t;
    for(t = 0; t < T; t += H)
    {
        Estado final;
        rungeKutta(c, &inicial, &final);
        imprimeEstado(final);
    }           
    printf("\n");
}


void rungeKutta(double c, Estado* inicial, Estado* final)
{
    EstadoDiff s1, s2, s3, s4;

    s1.velocidade = H*inicial->velocidade;
    s1.aceleracao = H*(-K*inicial->posicao - c*inicial->velocidade)/M;

    s2.velocidade = H*(inicial->velocidade + s1.aceleracao/2);
    s2.aceleracao = H*(-K*(inicial->posicao + s1.velocidade/2) 
                        - c*(inicial->velocidade + s1.aceleracao/2) )/M;
    
    s3.velocidade = H*(inicial->velocidade + s2.aceleracao/2);
    s3.aceleracao = H*(-K*(inicial->posicao + s2.velocidade/2) 
                    - c*(inicial->velocidade + s2.aceleracao/2) )/M;

    s4.velocidade = H*(inicial->velocidade + s3.aceleracao);
    s4.aceleracao = H*(-K*(inicial->posicao + s3.velocidade) 
                        - c*(inicial->velocidade + s3.aceleracao) )/M;

    final->posicao = inicial->posicao + (1/6.)*(s1.velocidade +
                                                2*s2.velocidade +
                                                2*s3.velocidade +
                                                s4.velocidade);
 
    final->velocidade = inicial->velocidade + (1/6.)*(s1.aceleracao +
                                                      2*s2.aceleracao +
                                                      2*s3.aceleracao +
                                                      s4.aceleracao);    
    inicial->posicao = final->posicao;
    inicial->velocidade = final->velocidade;
}


void imprimeEstado(Estado e)
{
    //printf("Posição:%f  Velocidade:%f\n", e.posicao, e.velocidade);    
    //printf("%f %f\n", e.posicao, e.velocidade);    
    printf("%f\n", e.posicao);    
}
