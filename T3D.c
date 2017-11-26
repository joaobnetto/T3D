#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef T3T_H
#define T3D_H

typedef struct mat4x1 Mat4x1;
typedef struct mat4x4 Mat4x4;

/* Cria o objeto a transformar: lê o arquivo de entrada e preenche o vetor de coordenadas.
 * O espaço de memória necessário para o vetor deverá ser alocado dinamicamente por
 * esta função.
 */
void Cria(Mat4x1 * Obj, char * fName);


/* Preenche uma matriz 4x4 com os parâmetros de translação */
Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ);


/* Preenche uma matriz 4x4 com os parâmetros de mudança de escala */
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ);


/* Preenche uma matriz 4x4 com os parâmetros de rotação */
Mat4x4 Rot(Mat4x4 M, int eixo, double angulo);


/* Multiplica duas matrizes 4x4, para composição de transformações */
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2);


/* Multiplica uma matriz 4x4 por um vetor de coordenad as, efetuando a transformação */
Mat4x1 MatTransf(Mat4x1 * Obj, Mat4x1 P);


/* Imprime as coordenadas de um objeto no arquivo de nome fName */
void Imprime(Mat4x1 * Obj, char * fName);

#endif

int main() {
    return 0;
}

struct mat4x1 {
    double x, y, z, t;
};

struct mat4x4 {
    double matriz[4][4];
};
void Cria(Mat4x1 * Obj, char * fName) {
    int quantidade;
    FILE * arquivo = fopen(fName, "r");
    if(arquivo == NULL) exit(1);
    fscanf(arquivo, "%d", &quantidade);
    Obj = (Mat4x1 *) malloc(sizeof(Mat4x1) * quantidade);
}
Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ) {}
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ) {}
Mat4x4 Rot(Mat4x4 M, int eixo, double angulo) {}


Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2) {
    Mat4x4 MF;
    int i, j, k;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            MF.matriz[i][j] = 0;
            for(k = 0; k < 4; k++) {
                MF.matriz[i][j] += M1.matriz[i][k] * M2.matriz[k][j];
            }
        }
    }
    return MF;

}


Mat4x1 MatTransf(Mat4x1 * Obj, Mat4x1 P) {}
void Imprime(Mat4x1 * Obj, char * fName) {}
