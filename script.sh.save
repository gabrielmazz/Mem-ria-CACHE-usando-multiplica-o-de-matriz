#!/bin/bash
for j in 200 400 600 800 1000 1200 1400 1600 1800 2000
do
	echo "Testando Matrizes com $j tamanho (original)"
	for i in $(seq 1 10)
	do
		./main $j $j o -n >> ./resultados/resultadosO$j.txt
	done
	echo "Testando Matrizes com $j tamanho (transposta)"

	for i in $(seq 1 10)
	do
		./main $j $j t -n >> ./resultados/resultadosT$j.txt
	done
done
