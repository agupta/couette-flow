#include "navier-stokes/centered.h"
#define MAX_LEVEL 7

int main () {
  init_grid(1 << MAX_LEVEL);
  // key for stderr log
  fprintf(ferr, "t, i, dt, s.sum, s.max, s.min\n");
  run();
}

event init(t = 0) {
  mu = fm; // set viscosity to unity

  // flow out of the right -> into the left
  periodic(right);

  // funky initial condition for demo purposes
  // change to 0 everywhere and add boundary condition

  foreach () {
    u.x[] = (y>0.5) ? 1. : 0.;
    u.y[] = 0.;
  }
}

event movie (t += 0.01; t<=0.25) {
  scalar speed[];
  foreach ()
    speed[] = sqrt(sq(u.x[]) + sq(u.y[])); // L2
  output_ppm(speed, linear = true); // output to stdout
}

event logfile(t <= 0.25; t+= 0.01) {
  scalar speed[];
  foreach ()
    speed[] = sqrt(sq(u.x[]) + sq(u.y[])); // L2
  stats s = statsf(speed);
  fprintf (ferr, "%g %d %g %g %g %g\n", t, i, dt, s.sum, s.max, s.min);
}