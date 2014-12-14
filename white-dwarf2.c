/*Problem #3 of the Midterm
 *Integrating dimensionless functions to produce
 *the mass radius distribution function with various central density 
 */

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int dwarf_eqs (double r, const double y[], double f[], void *params);

int main (void)
{
    size_t neqs = 2;                            /* number of equations */
    double eps_abs = 1.e-8, eps_rel = 0.;       /* desired precision */
    double stepsize = 1e-6;                     /* initial integration step */
    double r = 0.;                              /* radius interval */
    double r1 = 1200000000.;
    int np = 100, i;
    double rho_min = 0.08, rho_max = 1000000;   /*Initial and the final central density*/
    double factor = exp (log (rho_max / rho_min) / (np - 1));
    double rho_c = rho_min / factor;        /*Rate at which central density will change*/
    int status;

    for (i = 0; i < np; i++)                /* 100 different central density will be test*/
    {
        rho_c = rho_c * factor;
        r = 0.;                             /*Radius must be set to 0 at every iteration*/
       
        /* 
         * Initial conditions 
         */
        double y[2] = { 0., rho_c };        /* for res1 */


        gsl_odeiv2_step *s = gsl_odeiv2_step_alloc
            (gsl_odeiv2_step_rkf45, neqs);
        gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs,
                                                          eps_rel);
        gsl_odeiv2_evolve *e = gsl_odeiv2_evolve_alloc (neqs);

        gsl_odeiv2_system sys = { dwarf_eqs, NULL, neqs, &rho_c };

        /*
         * Evolution loop 
         */

        while ((r < r1) && (y[1] > 0))                           /*Integrate while the density is greater than 0*/
        {
            status =
                gsl_odeiv2_evolve_apply (e, c, s, &sys, &r, r1, &stepsize, y);

            if (status != GSL_SUCCESS)
            {
                printf ("Troubles: % .5e  % .5e  %.5e\n", r, y[0], y[1]);
                break;
            }
        }
        printf (" % .5e % .5e  % .5e  %.5e\n", r, rho_c, y[0], y[1]);  /* Radius, Central Density, Mass, Density*/


        gsl_odeiv2_evolve_free (e);
        gsl_odeiv2_control_free (c);
        gsl_odeiv2_step_free (s);
    }

    return 0;
}
