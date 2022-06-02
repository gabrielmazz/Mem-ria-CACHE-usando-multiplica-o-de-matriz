echo "Executando..."

for j in 200 400 600 800 1000 1200 1400 1600 1800 2000

do
    echo "Matriz com $j tamanho (ORIGINAL)"
    for i in $(seq 1 10)
    do
        ./main $j $j $j $j -m n >> ./resultados/resultadosO$j.txt
    done

    echo "Matriz com $j tamanho (TRANSPOSTA)"
    for i in $(seq 1 10)
    do
        ./main $j $j $j $j -t n >> ./resultados/resultadosT$j.txt
    done
done