set term png
set output 'graphics.png'
set xlabel 'Количество элементов в матрице, N'
set ylabel 'Время выполнения алгоритма, мс'
set xrange [0:700]
set yrange [0:600]
plot 'Vinograd_alg.txt' with lines, 'std_alg.txt' with lines
