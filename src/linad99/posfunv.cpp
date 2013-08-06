/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/** \file posfunv.cpp 
  posfun(...) source code for variable arguments.
*/

#include <fvar.hpp>

/**
  Retuns a positive function of the argument \f$x\f$ and sets a penalty for
  \f$x<0\f$. The penalty should be added to the objective function.
  \param x Argument, \f$x\f$.
  \param eps Threshold, \f$\epsilon\f$, 
   a double constant containing the minimum allowed value of \f$x\f$.
  \param  _pen The penalty value \b incremented by \f$ 0.01(x-\epsilon)^2 \f$ 
   if \f$x<\epsilon\f$. 
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
             x\ge\epsilon & x\\
               x<\epsilon & \frac{\epsilon}{2-x/\epsilon}
           \end{array}\right.\f$
  \ingroup misc
 */
dvariable posfun(const dvariable &x, const double eps, const prevariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps)
  {
    return x;
  }
  else
  {
    //dvariable y=1.0-x/eps;
    pen+=.01*square(x-eps);
    return eps/(2-x/eps);
  }
}

/**
  Retuns a positive function of the argument \f$x\f$ and sets a penalty for
  \f$x<0\f$. The penalty should be added to the objective function.
  \param x Argument, \f$x\f$.
  \param eps Threshold, \f$\epsilon\f$, 
   a double constant containing the minimum allowed value of \f$x\f$.
  \param  _pen The penalty value \b incremented by \f$ 0.01(x-\epsilon)^2 \f$ 
   if \f$x<\epsilon\f$. 
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
             x\ge\epsilon & x\\
               x<\epsilon & \frac{\epsilon}{2-x/\epsilon}
           \end{array}\right.\f$
  \ingroup misc
 */
dvariable posfun(const dvariable &x, const double eps, const dvariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps)
  {
    return x;
  }
  else
  {
    //dvariable y=1.0-x/eps;
    pen+=.01*square(x-eps);
    return eps/(2-x/eps);
  }
}

/**
  Retuns a positive function of the argument \f$x\f$ and sets a penalty for
  \f$x<0\f$. The penalty should be added to the objective function. 
   A more coersive version.
  \param x Argument, \f$x\f$.
  \param eps Threshold, \f$\epsilon\f$, 
   a double constant containing the minimum allowed value of \f$x\f$.
  \param  _pen The penalty value \b incremented by \f$ 0.01(x-\epsilon)^3 \f$ 
   if \f$x<\epsilon\f$. 
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
             x\ge\epsilon & x\\
               x<\epsilon & \frac{\epsilon}{1+x/\epsilon
                                             +(x/\epsilon)^2
                                             +(x/\epsilon)^3}
           \end{array}\right.\f$
  \ingroup misc
 */
dvariable posfun2(const dvariable &x, const double eps, const prevariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps)
  {
    return x;
  }
  else
  {
    dvariable y=eps-x;
    dvariable tmp=y/eps;
    dvariable tmp2=tmp*tmp;
    dvariable tmp3=tmp2*tmp;
    pen+=.01*cube(tmp3);
    return eps/(1.0+tmp+tmp2+tmp3);
  }
}

/**
  Adjoint code for posfun; possibly not used.
 */
dvariable dfposfun(const prevariable&x,const double eps)
{
  if (x>=eps)
  {
    return 1;
  }
  else
  {
    //double z=eps/(2-x/eps);
    dvariable dfx=1.0/square(2-x/eps);
    return dfx;
  }
}
