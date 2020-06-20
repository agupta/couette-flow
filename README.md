# couette-flow

A basic Couette flow simulation written in [Basilisk C](http://basilisk.fr/). Plotting in `gnuplot`.

---

## Instructions

1. Modify `MAX_LEVEL` in `couette.c` according to your hardware to find an appropriate balance between accuracy and speed.
2. Ensure ImageMagick and Basilisk is installed on your system.
3. Run 'run.sh' to obtain an animation.

---

## Plots

![Plot of convergence of speed at midpoint of couette flow (Re=100) at different grid levels](plot1.png)
![Detail plot of convergence of speed at midpoint of couette flow (Re=100) at different grid levels](plot2.png)

---

## Animation stills

![t=0.1](1.png)
`t = 0.1`

![t=5.8](2.png)
`t = 5.8`

![t=11.5](3.png)
`t = 11.5`
