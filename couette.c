#include "navier-stokes/centered.h"
#include "view.h"

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

// event movie (t += 0.1; t <= 300) {
//   // compute the speed
//   scalar speed[];
//   foreach ()
//     speed[] = sqrt(sq(u.x[]) + sq(u.y[])); // L2
  
//   output_ppm(speed, box = {{0.,0.},{8.,1.}}, linear = true); // output to stdout
// }

event animationU (t += 0.05; t <= 5 ){
  view (fov = 100.0, tx = 0.0, ty = 0.0, width = 1600, height = 400, quat = {0, 0, 0.0, 0.0});
  clear();
  squares ("u.x", spread = -1, linear = true, map = cool_warm );
  draw_vof ("f", lc = {0.0,0.0,0.0}, lw=1);
  // box();
  save ("HorizontalVelocity.mp4");
}

event logfile (t+= 0.05; t <= 5) {
  // compute the speed
  scalar speed[];
  foreach ()
    speed[] = norm(u); // l2
  // generate statistics
  stats s = statsf(speed);

  Point point = locate(4., 0.5); // midpoint
  double mid = speed[]; // speed at midpoint
  

  // generate L2 norm of a vertical slice
  double slice_norm = 0.;
  for (int i = 0; i < (1 << (MAX_LEVEL - 3)); i++) {
    double yp = (double)i / (double)(1 << (MAX_LEVEL - 3));
    point = locate(4., yp);
    slice_norm += fabs(speed[]);
  }
  slice_norm /= (double)(1 << (MAX_LEVEL - 3)); // rescale
  
  // log to stderr
  fprintf (ferr, "%g %d %g %g %g %g %g %g\n", t, i, dt, s.sum, s.max, s.min, mid, slice_norm);
}