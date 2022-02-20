reset

set style data boxerrorbars
set boxwidth 0.5
unset key


set title "Variation of latency of naive implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'


stats "sample.dat" using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output "naive.png"
plot "sample.dat" using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output "naive.eps"
plot "sample.dat" using 1:3:4:xtic(2)

set title "Variation of latency of multi-threaded custom implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats "sample.dat" using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output "multithreaded.png"
plot "sample.dat" using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output "multithreaded.eps"
plot "sample.dat" using 1:3:4:xtic(2)

set title "Variation of latency of openblas implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats "sample.dat" using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output "openblas.png"
plot "sample.dat" using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output "oepnblas.eps"
plot "sample.dat" using 1:3:4:xtic(2)

set title "Variation of latency of MKL implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats "sample.dat" using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output "mkl.png"
plot "sample.dat" using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output "mkl.eps"
plot "sample.dat" using 1:3:4:xtic(2)