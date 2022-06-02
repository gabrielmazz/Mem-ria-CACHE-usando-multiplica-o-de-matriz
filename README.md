# Trabalho 03 - CACHE

##### Organização e Arquitetura de Computadores - Edmar Bellorine

**Gabriel Mazzuco - Heloisa Alves**

---

Este programa foi feito para verificar a cache do computador, primeiro ira alocar matrizes dinamicamente, depois disso, aleatorizara números doubles usando a <time.h>, depois disso fara a multiplicação das duas matrizes, se os argumentos forem certos, ela printara no console ou criara um arquivo txt com os resultados. Neste codigo tambem é utilizado uma flag do próprio gcc para ganharmos performance na execução.

- Para executar o código, precisamos compilar primeiro, usando:

  ```shell
  gcc main.c -o main (Sem performace)

  gcc main.c -o main -O3 (Com performace)
  ```
- Depois disso, usamos o código definindo a sua execução por meio de argumentos

  ```
  Ex (shell): ./main LIN COL Op -Esc
  ```

  - Para usarmos os comandos, serão definidos como:

    - LIN = linha
    - COL = coluna
    - Op = Operação, sendo:
      - "o" -> Multiplicação simples
      - "t" -> Multiplicação com a matriz M2 transposta
    - -Esc = Método de escritura
      - "-p" -> Printa no console os resultados
      - "-e" -> Escreve num arquivo 'matriz_arquivo.txt' os resultados
      - "-n" -> Executa apenas o tempo
      - NULL -> Não ira fazer nenhuma ação
  - ```
    MULTIPLICAÇÃO

    - Comentar o if da linha 155
      EXECUTAR 1 VEZ: ./main 200 200 o -n >> 100.txt
      EXECUTAR 10 VEZESE: for run in {1..10}; do ./main 200 200 o -n; done >> 200.txt

    TRANSPOSTA:

    - Mudar o "#define NAME "200t_trans.txt"
      EXECUTAR 1 VEZ(TRANSPOSTA): ./main 200 200 t -n >> 200t.txt
      EXECUTAR 10 VEZESE: for run in {1..10}; do ./main 200 200 t -n; done >> 200t.txt

    - Na transposta será criado dois arquivos, sendo a execucução do clock da transposta e do aplicativo

    USANDO O SCRIPT

    - Para executar com o script, compila primeiro de depois executa usando:
      ./script.sh

    ```

---

**EXTRA**: Foi feito uma implementação em *C++ usando OpenMP*, para executar é usado:

- COMPILAÇÃO:

  ```g++
     g++ main.c++ -o main.c++ -fopenmp -O3
  ```
- EXECUÇÃO

  ```
    ./scriptc++.sh
  ```

---
