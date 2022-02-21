reset

# Directory prefixes for inputs and outputs
DATA_PREFIX = "./"
OUTPUT_PREFIX = "plots/"

# Make the output directory if it doesn't exist
system "mkdir -p " . OUTPUT_PREFIX

# Input files
NAIVE_DATA = DATA_PREFIX."naive.dat"
MULTITHREADED_DATA = DATA_PREFIX."multithreaded.dat"
OPENBLAS_DATA = DATA_PREFIX."openblas.dat"
MKL_DATA = DATA_PREFIX."mkl.dat"

# Set style of plot and other formatting
set style data boxerrorbars
set style fill solid 0.3
set boxwidth 0.5
unset key

# For each implementation, set the titles and labels first
# Then set the xrange so that whole plot is visible
# Finally, plot in two formats, png and eps. Size is set to 1280 x 780.

set title "Variation of latency of naive implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'


stats NAIVE_DATA using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output OUTPUT_PREFIX."naive.png"
plot NAIVE_DATA using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output OUTPUT_PREFIX."naive.eps"
plot NAIVE_DATA using 1:3:4:xtic(2)

set title "Variation of latency of multi-threaded custom implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats MULTITHREADED_DATA using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output OUTPUT_PREFIX."multithreaded.png"
plot MULTITHREADED_DATA using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output OUTPUT_PREFIX."multithreaded.eps"
plot MULTITHREADED_DATA using 1:3:4:xtic(2)

set title "Variation of latency of openblas implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats OPENBLAS_DATA using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output OUTPUT_PREFIX."openblas.png"
plot OPENBLAS_DATA using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output OUTPUT_PREFIX."openblas.eps"
plot OPENBLAS_DATA using 1:3:4:xtic(2)

set title "Variation of latency of MKL implementation with size of the matrix"
set xlabel 'Size of matrix'
set ylabel 'Latency (milliseconds)'

stats MKL_DATA using 1 name 'A' nooutput
set xrange [-1:A_max + 1]


set term png size 1280, 780
set output OUTPUT_PREFIX."mkl.png"
plot MKL_DATA using 1:3:4:xtic(2)

set term epscairo size 1280, 780
set output OUTPUT_PREFIX."mkl.eps"
plot MKL_DATA using 1:3:4:xtic(2)