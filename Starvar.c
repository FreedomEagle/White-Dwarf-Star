/* Declaring Variable for the Differential Equation.
   Identifying al of our equations for Internal Structure of White Dwarf Stars.
*/

#include <math.h>                                   /*Including necessary libraries*/
#include <gsl/gsl_errno.h>

int dwarf_eqs (double r, const double y[], double f[], void*params)
{
    double rho_c=*(double *) params;                /*Central Density*/
    double m = y[0];                                /*Mass*/
    double rho = y[1];                              /*Density*/
   
 if (rho >0)
 {
    double p = pow(rho, 2./3.);                    
    double gamma = p/(3.*sqrt(1.+p));
        
            f[0]= rho*r*r;                          /*First Equation*/
   
     if (r >1.e-6)                                  /*Second Equation*/
        {
            f[1] = -m* rho/(gamma*r*r);             /*mode 1 for when r >0*/
        }
     else
        {
            f[1] = -rho*rho_c/(3.*gamma);           /*mode 2 for when r<0 */
        }
}
else                                                /*Initial Conditions*/
{
    f[0]= 0.;                                                           
    f[1] =0.;
}

return GSL_SUCCESS;
}
