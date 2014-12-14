/*Problem #2 of the Midterm
 *Integrating dimensionless functions to produce
 *the mass radius distribution function while central density remains fixed
 */

#include <stdio.h>                             /*Necessary Libaries*/
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int dwarf_eqs (double r, const double y[], double f[], void *params);

int main (void)
{
    size_t neqs = 2;                            /* number of equations */
    double eps_abs = 1.e-8, eps_rel = 0.;       /* desired precision */
    double stepsize = 1e-6;                     /* Initial integration step */
    double rho_c = 10;                          /* Fixed Central Density  */
    double r = 0., r1 = 1e12;                   /* Radius interval */

    int status;

    double y[2] = { 0., rho_c };                /*Initial Conditions*/


    gsl_odeiv2_step *s = gsl_odeiv2_step_alloc (gsl_odeiv2_step_rkf45, neqs);
    gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs,
                                                      eps_rel);
    gsl_odeiv2_evolve *e = gsl_odeiv2_evolve_alloc (neqs);

    gsl_odeiv2_system sys = { dwarf_eqs, NULL, neqs, &rho_c };

    /*
     * Evolution loop 
     */


    while ((r < r1) && (y[1] > 0))      /*Integrate while the density is greater than 0*/
    {
        status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &r,
                                          r1, &stepsize, y);

        if (status != GSL_SUCCESS)
        {
            printf ("Troubles:  % .5e  % .5e  %.5e\n", r, y[0], y[1]);
            break;
        }

        printf (" % .5e  % .5e  %.5e \n", r, y[0], y[1]);     /*Radius, Mass, Density*/
    }

    gsl_odeiv2_evolve_free (e);
    gsl_odeiv2_control_free (c);
    gsl_odeiv2_step_free (s);

    return 0;
}
