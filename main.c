/*COMPILAR: gcc main.c -o main 
  COMPILAR COM PERFORMACE: gcc main.c -o main -O3

MULTIPLICAÇÃO:
- Comentar o if da linha 150
EXECUTAR 1 VEZ: ./main 200 200 o -n >> 100.txt
EXECUTAR 10 VEZESE: for run in {1..10}; do ./main 200 200 o -n; done >> 200.txt

TRANSPOSTA:
- Mudar o "#define NAME "200t_trans.txt"
EXECUTAR 1 VEZ(TRANSPOSTA): ./main 200 200 t -n >> 200t.txt
EXECUTAR 10 VEZESE: for run in {1..10}; do ./main 200 200 t -n; done >> 200t.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iso646.h>
#include <stdbool.h>

#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

#define NAME "200t_trans.txt" //tempo de transposição

double rand_double();
double rand_double_interval(double a, double b);

FILE *opening_file(FILE *file, char mode);
void close_file(FILE *file);
double rand_matrix(double **mat, double **mat2, int LIN, int COL);
double multiplication_matrix(double **mat, double **mat2, double **mat_result, int LIN, int COL);
double transposed_matrix_m2(double **mat2, double **mat2t, int LIN, int COL);
void print_matrix(double **mat, double **mat2, double **mat_result, int LIN, int COL);
void write_matrix(FILE *file, double **mat, double **mat2, double **mat_result, int LIN, int COL);
void clear_screen(void);

int main(int argc, char *argv[]){
    //Limpa o terminal para a nova execução
    //clear_screen();

    FILE *file;
    bool test_arquive, test_trans = false;

    if(argv[1] and argv[2] and argv[3] and argv[4] == NULL){
        printf("\n\nArgumentos não inseridos\n\n");
        exit(-1);
    }

    //srand serve para aleatorizar os números, usada nas funções rand_double()
    srand(time(NULL));

    //Declaração das variaveis de tempo para o calculo de execução do programa
    float time, time_trans = 0.0;
    clock_t start, end, start_trans, end_trans;

    //Recebe o valor pelo terminal "./main LIN COL"
    int LIN = strtol(argv[1], NULL, 10);
    int COL = strtol(argv[2], NULL, 10);
    
    //Declaração da matriz dinamica usando ponteiro de ponteiro
    double **mat, **mat2;   	//Matrizes bases
    double **mat2t;             //Matriz transposta
    double **mat_result;        //Matriz resultado da multiplicação

    //Define as "colunas" da matriz ou a linha do vetor de vetores
    mat = malloc(LIN * sizeof(double*));
    mat2 = malloc(LIN * sizeof(double*));
    mat2t = malloc(LIN * sizeof(double*));
    mat_result = malloc(LIN * sizeof(double*));

    //Define os "elementos" da matriz ou da linha do vetor de vetores
    for(int i=0; i<LIN; i++){
        mat[i] = malloc(COL * sizeof(double));
        mat2[i] = malloc(COL * sizeof(double));
        mat2t[i] = malloc(COL * sizeof(double));
        mat_result[i] = malloc(COL * sizeof(double));
    }

    //Randomiza as matrizes em double
    rand_matrix(mat, mat2, LIN, COL);

    //Inicia o clock de fato, quando a manipulação sera feita
    start = clock();

    //"o" -> Executa a multiplicação
    //"t" -> Executa a transposição de M2
    if(strcmp(argv[3], "o") == 0){
        //Aplica a multiplicação das matrizes
        multiplication_matrix(mat, mat2, mat_result, LIN, COL);   //MulM1M2
    
    }else if(strcmp(argv[3], "t") == 0){ 
        //Inicia o clock apenas para a transposição
        start_trans = clock();

        //Aplica a transposição da Matriz M2
        transposed_matrix_m2(mat2, mat2t, LIN, COL);

        //Finaliza o clock apenas para a transposição
        end_trans = clock();

        //Aplica a multiplicação das matrizes agora com M2 transposta
        multiplication_matrix(mat, mat2t, mat_result, LIN, COL);

        test_trans = true;
    }

    //Finaliza o clock que foi inicializado no começo da main()
    end = clock();

    //Faz o teste do 3 argumento para verificar qual função deseja dentro do programa

    //"-p" -> Printa as matrizes no console
    //"-e" -> Adiciona as matrizes em um arquivo que é resetado toda vez quando iniciado denovo
    //"-n" -> Apenas mostra o tempo de execução
    if(strcmp(argv[4], "-p") == 0){
        //Chama a função de print das matrizes no console
        print_matrix(mat, mat2, mat_result, LIN, COL);

    }else if(strcmp(argv[4], "-e") == 0){
        //Remove o arquivo criado anteriormente com o mesmo nome para a criação de um novo
        remove(NAME);  
             
        //Adiciona as matrizes em um arquivo criado pelo proprio c com nome de matriz.txt
        file = opening_file(file, 'g');

        //Chama a função para escrever no arquivo as matrizes geradas
        write_matrix(file, mat, mat2, mat_result, LIN, COL);

        //Fecha o arquivo aberto acima    
        close_file(file);

        test_arquive = true;

    }else if(strcmp(argv[4], "-n") == 0){
        goto END;   //Pula o if para  o calculo do time

    }else{
        printf("Argumentos são inválidos\n\n");
        exit(-1);
    }

    //Calcula o tempo de execução com está função
    END: time = (float)(((end - start) + 0.0) / CLOCKS_PER_SEC);
    time_trans = (float)(((end_trans - start_trans) + 0.0) / CLOCKS_PER_SEC);

    //Desaloca todas as matrizes depois da finalização
    //free(mat); free(mat2); free(mat_result);

    //Mostra no terminal o tempo de execução
    printf("%.4f\n", time);

    //Print para colocar no arquivo >> NOME
    /*if(test_trans == true)
        file = opening_file(file, 'a');
        fprintf(file, "%.4f\n", time_trans);
        close_file(file);*/

    //Adiciona o tempo de execução dentro do arquivo
    if(test_arquive == true){
        file = opening_file(file, 'a');
        fprintf(file, "\n\nRuntime = %f s", time);
        close_file(file);
    }
    
    return EXIT_SUCCESS;
}

//Abre o arquivo testando-o se foi possivel tal feito
FILE *opening_file(FILE *file, char mode){
    switch(mode){
        case('g'):  //modo gravação
            file = fopen(NAME,"wt"); 
            break;

        case('l'):  //modo leitura
            file = fopen(NAME,"rt"); 
            break;

        case('a'):  //modo append
            file = fopen(NAME,"a"); 
            break;
    }
    
    if(file == NULL){    //Se ouver algum erro, o ponterio apontará para NULL
        printf("Não foi possivel abrir o arquivo\n");
        exit(0);
    }
}

//Fecha o arquivo
void close_file(FILE *file){
    fclose(file);
}

//Função recursiva para aleatorização de numeros em double
double rand_double(){
    return ((double)rand()) / ((double)RAND_MAX);
}

//Aleatoria os numeros na chama da função rand_double()
double rand_double_interval(double a, double b){
    return rand_double() * (b - a) + a;
}

//Adiciona os elementos aleatorizados na matriz
double rand_matrix(double **mat, double **mat2, int LIN, int COL){
    //Define os elementos que entraram na matriz dinamica como se fosse uma matriz normal
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            //Chama a função de aleatorização de numeros doubles
            mat[i][j] = rand_double_interval(100, 10);
            mat2[i][j] = rand_double_interval(100, 10);
        }
    }
}

double multiplication_matrix(double **mat, double **mat2, double **mat_result, int LIN, int COL){
    double mat_aux = 0;

    for(int i=0; i<LIN; i++){
        for(int j=0; j<LIN; j++){
            for(int k=0; k<COL; k++){
                mat_aux = mat_aux + (mat[i][k] * mat2[k][j]);
            }
            mat_result[i][j] = mat_aux;
            mat_aux = 0;
        }
    }
    return **mat_result;
}

double transposed_matrix_m2(double **mat2, double **mat2t, int LIN, int COL){
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            mat2t[j][i] = mat2[i][j];
        }
    }

    return **mat2t;
}

void print_matrix(double **mat, double **mat2, double **mat_result, int LIN, int COL){
    printf("\nMatriz A\n");
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            printf("%lf ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n\nMatriz B\n");

    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            printf("%lf ", mat2[i][j]);
        }
        printf("\n");
    }

    printf("\n\nMatriz resultante\n");

    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            printf("%lf ", mat_result[i][j]);
        }
        printf("\n");
    }
}

void write_matrix(FILE *file, double **mat, double **mat2, double **mat_result, int LIN, int COL){
    //Retorna o ponteiro do arquivo para o começo, apenas como um extra
    fseek(file, 0, SEEK_SET);

    //Escreve a primeira matriz que foi alocada
    fputs("Matriz A:\n", file);
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            fprintf(file, "%lf ", mat[i][j]);
        }
        fprintf(file, "\n");
    }

    //Escreve a segunda matriz que foi alocada
    fputs("\n\nMatriz B:\n", file);
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            fprintf(file, "%lf ", mat2[i][j]);
        }
        fprintf(file, "\n");
    }

    //Escreve a matriz resultante
    fputs("\n\nMatriz Resultante:\n", file);
    for(int i=0; i<LIN; i++){
        for(int j=0; j<COL; j++){
            fprintf(file, "%lf ", mat_result[i][j]);
        }
        fprintf(file, "\n");
    }
}

void clear_screen(void){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}
