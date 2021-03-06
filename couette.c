#include "navier-stokes/centered.h"

#define MAX_LEVEL 8

int main () {
  init_grid(1 << MAX_LEVEL);
  size(8); // scale the grid up by a factor of 8
  run();
}

event init(t = 0) {
  // set viscosity to 1/Re
  double Re = 100.;
  const face vector muc[] = {1./Re,1./Re};
  mu = muc;

  // flow out of the right -> into the left
  periodic(right);

  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  // cut the top 7/8 out of our domain to obtain a 8:1 rectangle
  mask (y > 1 ? top : none);
  
  // boundary conditions
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);
}

event movie (t += 0.1; t <= 140) {
  // compute the speed
  scalar speed[];
  foreach ()
    speed[] = sqrt(sq(u.x[]) + sq(u.y[])); // L2
  
  output_ppm(speed, box = {{0.,0.},{8.,1.}},linear = true); // output to stdout
}

event logfile (t+= 0.1; t <= 140) {
  // compute the speed
  scalar speed[];
  foreach ()
    speed[] = sqrt(sq(u.x[]) + sq(u.y[])); // l2
  // generate statistics
  stats s = statsf(speed);

  // log to stderr
  Point point = locate(4., 0.5); // midpoint
  double mid = speed[]; // speed at midpoint
  
  fprintf (ferr, "%g %d %g %g %g %g %g\n", t, i, dt, s.sum, s.max, s.min, mid);
}