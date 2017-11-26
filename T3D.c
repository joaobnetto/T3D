#include <stdio.h>
#include <stdlib.h>

struct mat4x1 {
    double x, y, z, t;
};

struct mat4x4 {
    double ** matriz;
};

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

int main() {
    return 0;
}

void Cria(Mat4x1 * Obj, char * fName) {}
Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ) {}
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ) {}
Mat4x4 Rot(Mat4x4 M, int eixo, double angulo) {}
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2) {}
Mat4x1 MatTransf(Mat4x1 * Obj, Mat4x1 P) {}
void Imprime(Mat4x1 * Obj, char * fName) {}
