set terminal png size 640,480
set xrange [0:1]
set yrange [0:5]
set ylabel "Y"
set xlabel "X"
set title "Kurs graph"
set key vertical top left
set output "kurs.png"
plot "y.txt" with lp lw 3 title "Y(x)", "int.txt" with lp lw 3 title "P5(x)"