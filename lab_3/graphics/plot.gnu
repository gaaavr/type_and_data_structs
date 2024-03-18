set term png
set output 'graphics.png'
set xlabel 'Количество символов в строках'
set ylabel 'Время выполнения алгоритма, мс'
set xrange [0:12]
set yrange [0:0.02]
plot 'lev_std_alg.txt' with lines, 'rec_cache_lev_alg.txt' with lines, 'damerau_alg.txt' with lines
set term png
set output 'recursive_graphics.png'
set xlabel 'Количество символов в строках'
set ylabel 'Время выполнения алгоритма, мс'
set xrange [0:12]
set yrange [0:1000]
plot 'rec_lev_alg.txt' with lines
