#/bin/bash

echo "Execução do codigo sequencial"
g++ -o sequential sequential.c
for i in 10 10000 100000; do
  echo "Numero de iterações: $i" >> out_sequencial
  ./sequential $i >> out_sequencial
  echo >> out_sequencial
done

echo "Execução do codigo paralelo"
g++ -o paralelo -fopenmp parallel.c
for i in 2 4 6 8 16; do
    echo "Numero de threads $i" >> out_paralelo
    for j in 10 10000 100000; do
        echo "Numero de iterações $j" >> out_paralelo
        ./paralelo $i $j >> out_paralelo
    done
    echo >> out_paralelo
    echo >> out_paralelo
done



