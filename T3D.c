#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef T3T_H
#define T3D_H
#define to_degrees(angulo) (angulo*M_PI) / 180.0

struct mat4x1 {
    // respectivamente x, y, z, t
    double coordenadas[4];
    struct mat4x1 * next;
};

struct mat4x4 {
    double matriz[4][4];
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
Mat4x4 Rot(Mat4x4 M, char eixo, double angulo);


/* Multiplica duas matrizes 4x4, para composição de transformações */
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2);


/* Multiplica uma matriz 4x4 por um vetor de coordenad as, efetuando a transformação */
Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P);


/* Imprime as coordenadas de um objeto no arquivo de nome fName */
void Imprime(Mat4x1 * Obj, char * fName);

/* Cria cabeça da lista */
Mat4x1 * cria_lista(void);

// Pulo o arquivo ate onde começa as operações
FILE * pula_coordenadas(char * file_name);

/* Adiciona nó no fim da lista */
void add_node(Mat4x1 * head, Mat4x1 dados);

#endif

int main() {
    char nome_arquivo_entrada[] = "entrada.txt";
    char nome_arquivo_saida[] = "saida.txt", comando, eixo, op;
  	double graus, x, y, z;
    FILE * arquivo_entrada, * arquivo_saida;
    Mat4x1 * coordenadas = NULL;
  	Mat4x4 M;
    coordenadas = cria_lista();
    Cria(coordenadas, nome_arquivo_entrada);
    arquivo_entrada = pula_coordenadas(nome_arquivo_entrada);
    while(!feof(arquivo_entrada)) {
        fscanf(arquivo_entrada, " %c", &comando);
     	if(comando == 'T') {
      		fscanf(arquivo_entrada, "%lf %lf %lf", &x, &y, &z);
          	Trans(M, x, y, z);
    	}
        else if (comando == 'R') {
        	fscanf(arquivo_entrada, " %c %lf", &eixo, &graus);
          	Rot(M, eixo, graus);
        }
        else if (comando == 'S') {
            fscanf(arquivo_entrada, "%lf %lf %lf", &x, &y, &z);
          	Escala(M, x, y, z);
        }
    }

    return 0;
}



void Cria(Mat4x1 * Obj, char * fName) {
  	int quantidade;
  	Mat4x1 leitura;
  	FILE * entrada;
  	entrada = fopen(fName, "r");
  	if(entrada == NULL) {
      	printf("Erro na abertura do arquivo!");
      	exit(1);
  	}
  	fscanf(entrada, " %d", &quantidade);
  	while(quantidade) {
      	fscanf(entrada, " %lf %lf %lf",
               &leitura.coordenadas[0],
               &leitura.coordenadas[1],
               &leitura.coordenadas[2]);
      	leitura.coordenadas[3] = 1;
      	quantidade--;
  	}
  	add_node(Obj, leitura);
  	fclose(entrada);
}

Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ) {
  	// Uso o memset para definir todos os valores da matriz como 0.
	Mat4x4 tmp;
  	memset(tmp.matriz, 0, sizeof(tmp.matriz));
  	// Dou os valores corretos para cada ponto da matriz.
  	tmp.matriz[0][0] = tmp.matriz[1][1] = tmp.matriz[2][2] = tmp.matriz[3][3] = 1;
  	tmp.matriz[0][3] = deltaX;
  	tmp.matriz[1][3] = deltaY;
  	tmp.matriz[2][3] = deltaZ;
  	// Faco a conta com a matriz recebida por argumento e a nova matriz, armazenando a em tmp.
  	tmp = MatComp(M, tmp);
  	// Retorno a nova matriz com os valores.
  	return tmp;
}
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ) {
	// memset: O(n)
	Mat4x4 tmp;
  	// Limpo os valores da matriz para 0.
  	memset(tmp.matriz, 0, sizeof(tmp.matriz));
  	// Colo os valores nos lugares certos.
  	tmp.matriz[0][0] = FX;
  	tmp.matriz[1][1] = FY;
  	tmp.matriz[2][2] = FZ;
  	tmp.matriz[3][3] = 1;
  	// Faco a multiplicacao das matrizes e retorno tmp.
  	tmp = MatComp(M, tmp);
  	return tmp;
}
Mat4x4 Rot(Mat4x4 M, char eixo, double angulo) {
  	Mat4x4 tmp;
  	memset(tmp.matriz, 0, sizeof(tmp.matriz));
  	// Faço as operacões necessarias em cada eixo.
  	if(eixo == 'x' || eixo == 'X'){
          tmp.matriz[0][0] = tmp.matriz[3][3] = 1;
          tmp.matriz[1][1] = tmp.matriz[2][2] = cos(to_degrees(angulo));
          tmp.matriz[2][1] = tmp.matriz[1][2] = sin(to_degrees(angulo));
          tmp.matriz[1][2] *= -1;
    }
  	else if(eixo == 'y' || eixo == 'Y'){
          tmp.matriz[1][1] = tmp.matriz[3][3] = 1;
          tmp.matriz[0][0] = tmp.matriz[2][2] = cos(to_degrees(angulo));
          tmp.matriz[2][0] = tmp.matriz[0][2] = sin(to_degrees(angulo));
          tmp.matriz[0][2] *= -1;
  	}
  	else{
          tmp.matriz[2][2] = tmp.matriz[3][3] = 1;
          tmp.matriz[0][0] = tmp.matriz[1][1] = cos(to_degrees(angulo));
          tmp.matriz[0][1] = tmp.matriz[1][0] = sin(to_degrees(angulo));
          tmp.matriz[0][1] *= -1;
   }
   // Faco a multiplicacao e retorno.
   tmp = MatComp(M, tmp);
   return tmp;
}


Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2) {
    Mat4x4 MF;
  	// Multiplicação basica de matrizes
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


Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P) {
  	int i, j;
  	Mat4x1 temp;
  	for(i = 0; i < 4; i++) {
      	temp.coordenadas[i] = 0;
      	for(j = 0; j < 4; j++) {
          	temp.coordenadas[i] += M.matriz[i][j] * P.coordenadas[j];
        }
    }
	return temp;
}
void Imprime(Mat4x1 * Obj, char * fName) {}

Mat4x1 * cria_lista(void) {
    Mat4x1 * temp;
    temp = (Mat4x1 *) malloc(sizeof(Mat4x1));
    if(temp == NULL) {
        printf("Memory error\n");
        exit(1);
    }
    temp->next = NULL;
    return temp;
}

FILE * pula_coordenadas(char * file_name) {
    int quantidade, total;
    double lixo;
    FILE * arquivo = fopen(file_name, "r");
    fscanf(arquivo, " %d", &quantidade);
    total = quantidade * 3;
    while(total) {
        fscanf(arquivo, "%lf", &lixo);
      	total--;
    }
    return arquivo;

}

void add_node(Mat4x1 * head, Mat4x1 dados) {
	Mat4x1 * temp = head;
  	if(head == NULL) {
  		printf("cabeça vazia");
      	return;
    }
  	while(temp->next != NULL) {
    	temp = temp->next;
    }
  	temp->next = (Mat4x1 *) malloc(sizeof(Mat4x1));
  	temp = temp->next;
  	(*temp) = dados;
  	temp->next = NULL;
}
