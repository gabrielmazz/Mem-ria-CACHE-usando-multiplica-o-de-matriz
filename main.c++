//g++ main.c++ -o main -fopenmp -/- g++ main.c++ -o main.c++ -fopenmp -O3
//./main LIN_MAT1 COL_MAT1 LIN_MAT2 COL_MA2 -m/-t p/n

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

using namespace std;

double rand(double MIN, double MAX);
vector<vector<double>> rand_matriz(vector<vector<double>> matriz, int LIN_MAT, int COL_MAT);

void print_matriz(vector<vector<double>> matriz1, vector<vector<double>> matriz2, vector<vector<double>> matriz_resultado,
                  int LIN_MAT1, int COL_MAT1, int LIN_MAT2, int COL_MAT2);

bool verifica_matriz(vector<vector<double>> matriz1, vector<vector<double>> matriz2);

vector<vector<double>> multiplication(vector<vector<double>> matriz1, vector<vector<double>> matriz2, vector<vector<double>> matriz_resultado, 
                                      int LIN_MAT1, int COL_MAT1, int LIN_MAT2, int COL_MAT2);

vector<vector<double>> transposta(vector<vector<double>> matriz2, vector<vector<double>> matriz_transposta,
                                  int LIN_MAT2, int COL_MAT2);

int main(int argc, char *argv[]){
    srand(time(NULL));

    int LIN_MAT1 = strtol(argv[1], NULL, 10);
    int COL_MAT1 = strtol(argv[2], NULL, 10);
    int LIN_MAT2 = strtol(argv[3], NULL, 10);
    int COL_MAT2 = strtol(argv[4], NULL, 10);

    float time, time_trans = 0.0;
    clock_t start, end, start_trans, end_trans;

    vector<vector<double>> matriz1(LIN_MAT1, vector<double> (COL_MAT1, 0));
    vector<vector<double>> matriz2(LIN_MAT2, vector<double> (COL_MAT2, 0));

    /*if(verifica_matriz(matriz1, matriz2) != true){
        cout << "As matrizes estão vazias!" << endl;
        EXIT_SUCCESS;
    }*/

    matriz1 = rand_matriz(matriz1, LIN_MAT1, COL_MAT1);
    matriz2 = rand_matriz(matriz2, LIN_MAT2, COL_MAT2);

    vector<vector<double>> matriz_resultado(LIN_MAT1, vector<double> (COL_MAT2, 0));
    vector<vector<double>> matriz_transposta(LIN_MAT2, vector<double> (COL_MAT2, 0));

    start = clock();

    if(strcmp(argv[5], "-m") == 0){
        matriz_resultado = multiplication(matriz1, matriz2, matriz_resultado, LIN_MAT1, COL_MAT1, LIN_MAT2, COL_MAT2);   
    }else if(strcmp(argv[5], "-t") == 0){
        matriz_transposta = transposta(matriz2, matriz_transposta, LIN_MAT2, COL_MAT2);
        matriz_resultado = multiplication(matriz1, matriz_transposta, matriz_resultado, LIN_MAT1, COL_MAT1, LIN_MAT2, COL_MAT2);
    }

    end = clock();

    if(strcmp(argv[6], "p") == 0){
        print_matriz(matriz1, matriz2, matriz_resultado, LIN_MAT1, COL_MAT1, LIN_MAT2, COL_MAT2);
    }else if(strcmp(argv[6], "n") == 0){
        goto END;
    }else{
        cout << "Não foi passado o argumento de print" << endl;
        EXIT_SUCCESS;
    }

    END: time = (float)(((end - start) + 0.0) / CLOCKS_PER_SEC);
    time_trans = (float)(((end_trans - start_trans) + 0.0) / CLOCKS_PER_SEC);

    cout << "TIME = " << time << endl;
    return EXIT_SUCCESS;
}

bool verifica_matriz(vector<vector<double>> matriz1, vector<vector<double>> matriz2){
    if(matriz1.empty() || matriz2.empty() != 0)
        return true;
    else
        return false;
}

double rand(double MIN, double MAX){
    double aux = (double)rand() / RAND_MAX;
    return MIN + aux * (MAX - MIN);
}

vector<vector<double>> rand_matriz(vector<vector<double>> matriz, int LIN_MAT, int COL_MAT){
    #pragma omp parallel num_threads(4) shared(matriz)
    {
        for(int i=0; i<LIN_MAT; i++)
            for(int j=0; j<COL_MAT; j++){
                matriz[i][j] = rand(10, 100);
        }
    }
    
    return matriz;
}

void print_matriz(vector<vector<double>> matriz1, vector<vector<double>> matriz2, vector<vector<double>> matriz_resultado,
                  int LIN_MAT1, int COL_MAT1, int LIN_MAT2, int COL_MAT2){
            
    cout << "Matriz A:" << endl;
    for(int i=0; i<LIN_MAT1; i++){
        for(int j=0; j<COL_MAT1; j++){
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatriz B:" << endl;
    for(int i=0; i<LIN_MAT2; i++){
        for(int j=0; j<COL_MAT2; j++){
            cout << matriz2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatriz Resultado:" << endl;
    for(int i=0; i<LIN_MAT1; i++){
        for(int j=0; j<COL_MAT2; j++){
            cout << matriz_resultado[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> multiplication(vector<vector<double>> matriz1, vector<vector<double>> matriz2, vector<vector<double>> matriz_resultado, 
                       int LIN_MAT1, int COL_MAT1, int LIN_MAT2, int COL_MAT2){

    if(COL_MAT1 != LIN_MAT2)
        EXIT_SUCCESS;
    
    for(int i=0; i<LIN_MAT1; i++){
        for(int j=0; j<COL_MAT2; j++){
            for(int k=0; k<COL_MAT1; k++){
                matriz_resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    return matriz_resultado;
}

vector<vector<double>> transposta(vector<vector<double>> matriz2, vector<vector<double>> matriz_transposta,
                                  int LIN_MAT2, int COL_MAT2){
    
    for(int i=0; i<LIN_MAT2; i++){
        for(int j=0; j<COL_MAT2; j++){
            matriz_transposta[i][j] = matriz2[j][i];
        }
    }

    return matriz_transposta;
}
