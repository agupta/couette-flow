set title 'Convergence of speed at midpoint of couette flow (Re=100) at different grid levels'
set xlabel 'Time'
# unset xlabel
set ylabel 'Speed at midpoint'
set key bottom
# unset key
# unset xtics
# set xrange [120:135]
# set ytics (0.624999, 0.562499, 0.531249, 0.515624, 0.507812, 0.5)
# set yrange [0.47:0.65]
plot 'final/final5/flow.log' using 1:7 with lines title 'N = 5; 4^{5-3}=16 gridpoints', \
     'final/final6/flow.log' using 1:7 with lines title 'N = 6; 4^{6-3}=64 gridpoints', \
     'final/final7/flow.log' using 1:7 with lines title 'N = 7; 4^{7-3}=256 gridpoints', \
     'final/final8/flow.log' using 1:7 with lines title 'N = 8; 4^{8-3}=1024 gridpoints', \
     'final/final9/flow.log' using 1:7 with lines title 'N = 9; 4^{9-3}=4096 gridpoints'
