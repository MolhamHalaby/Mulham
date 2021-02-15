

#include <math.h>
#include <stdio.h>
#include<stdlib.h>
#define EPSILON 0.00001
#define PI 3.14159265
#define N 100
int solve_quadratic(double a, double b,
                    double c,  
                    double *r1,  double *i1, 
                    double *r2,  double *i2)
{
 double delta, delta_root, xv, qv;

 if ( a == 0)
  if ( b == 0)
   return 0;
  else
   {
    *r1 = -c/b;
    *i1 = 0;
    return 1;
   } /* else */

 xv = -b/(2*a); /* Take care of square quad */
 qv = a*xv*xv + b*xv + c;
 if(fabs(qv) < EPSILON) 
   {
     *r1 = *r2 = xv;
     *i1 = *i2 = 0.0;
     return 2;
   } /* if */


 delta = b*b - 4*a*c;
 if ( delta < 0.0 )
  {
   *r1 = *r2 = -b/(2*a);  /* real part only */
    delta_root = sqrt(-delta);
   *i1 = -  delta_root/(2.0*a); 
   *i2 =  delta_root/(2.0*a); 
   return 0;
  } /* if */
 else
  {
    delta_root = sqrt(delta);
    *r1 = (-b - delta_root)/(2.0*a);
    *r2 = (-b + delta_root)/(2.0*a);
    *i1 = 0;
    *i2 = 0;
    return 2;
  } /* else */

} /* solve_quadratic */


void divide_cubic(double a, double *b,
	     double *c,  double x)
{
  *b = *b + a*x;
  *c = *c + (*b)*x;

} /*  divide_cubic */

void cubic_root(double x, double y, double *r, double *i  )
{
  double radius, theta, temp;

  if ( x == 0.0 && y == 0.0)
   {
    *r = *i = 0.0;
    return;
   } /* if */


  radius = sqrt(x*x + y*y);
  theta = (asin(fabs(y/radius))); 
  
  temp = exp(log(radius)/3.0);
  if ((x < 0)&&(y>=0))
	  theta = 3*PI - theta;
  else
  if ((x<0)&&(y<=0))
	  theta = 3*PI + theta;
  else
  if ((x>=0)&&(y<0))
	  theta=4*PI-theta;

  *r = temp*cos(theta/3.0);
  *i = temp*sin(theta/3.0);
  
} /* cubic_root */

void square_root(double x, double y, double *r, double *i  )
{
  double radius, theta, temp;

  if ( x == 0.0 && y == 0.0)
   {
    *r = *i = 0.0;
    return;
   } /* if */


  radius = sqrt(x*x + y*y);
  theta = (asin(fabs(y/radius))); 
  
  temp = exp(log(radius)/2.0);
  if ((x < 0)&&(y>=0))
	  theta = 3*PI - theta;
  else
  if ((x<0)&&(y<=0))
	  theta = 3*PI + theta;
  else
  if ((x>=0)&&(y<0))
	  theta=4*PI-theta;

  *r = temp*cos(theta/2.0);
  *i = temp*sin(theta/2.0);
  
} /* cubic_root */


int solve_cubic(double a1, double a2,
	     double a3, double a4,
	     double *x1, double *y1, 
             double *x2, double *y2,
             double *x3, double *y3)
{

  double p, q;
  double a, b, c;
  double u1, u2, wr,wi;
  double x, t, ur, ui, vr, vi;
  double b2, c2;
  double i1, i2;
  int n;

  if ( a1 == 0.0)
  {
   n = solve_quadratic(a2, a3, a4, x1, &i1, x2, &i2);
   return n;
  } /* if */

  a = a2/a1;
  b = a3/a1;
  c = a4/a1;

  p = b - a*a/3.0;
  q = c + (2.0*a*a*a - 9.0*a*b)/27.0 ;


  if ( ( p==0.0 ) && (q == 0.0))
  {
   *x1 = *x2 = *x3 = -a/3;
   *y1 = *y2 = *y3 = 0;
   return 3;
  } /* if */ 

  if (p == 0.0) /* q != 0 */
  {
    cubic_root(-q,0, &ur, &ui);
    x = ur - (a/3.0);
    *x1 = x; 
    *y1 = 0;

    b2 = a;
    c2 = b;

    divide_cubic(1.0, &b2, &c2,  x);
    n = solve_quadratic(1.0, b2, c2, x2,y2, x3, y3);

    return n+1;

  } /* if */

  solve_quadratic(1.0, -q, -((p*p*p)/27.0), &u1, &i1,  &u2, &i2);

  if (u1 > u2)
  {
   wr = u1;
   wi = i1;
  } /* if */
  else
  {
   wr = u2;
   wi = i2;
  } /* else */

  cubic_root(wr, wi, &ur, &ui);
  cubic_root(-q + wr, wi, &vr, &vi);
  t = vr - ur;
  x = t - (a/3.0);

  *x1 = x;
  *y1 = 0;

  b2 = a;
  c2 = b;

  divide_cubic(1.0, &b2, &c2,  x);
  n = solve_quadratic(1.0, b2, c2, x2,y2, x3, y3);

  return n+1;

} /* solve_cubic */


void solve_biquadratic(double a, double b, double c,
             double *x1, double *y1,
             double *x2, double *y2,
             double *x3, double *y3,
             double *x4, double *y4)
{

double q11, q12, q21, q22;
double sqrt_q11, sqrt_q12, sqrt_q21, sqrt_q22;
double sqrt_q31, sqrt_q32, sqrt_q41, sqrt_q42;


solve_quadratic(a, b, c,
                    &q11,  &q12,
                    &q21,  &q22);

square_root(q11, q12, &sqrt_q11, &sqrt_q12);

sqrt_q21 = -sqrt_q11;
sqrt_q22 = -sqrt_q12;

square_root(q21, q22, &sqrt_q31, &sqrt_q32);

sqrt_q41 = -sqrt_q31;
sqrt_q42 = -sqrt_q32;

*x1 = sqrt_q11;
*y1 = sqrt_q12;

*x2 = sqrt_q21;
*y2 = sqrt_q22;


*x3 = sqrt_q31;
*y3 = sqrt_q32;


*x4 = sqrt_q41;
*y4 = sqrt_q42;


} // solve_biquadratic

int solve_quartic(double a4, double a3,
	     double a2, double a1, double a0,
	     double *x1, double *y1, 
             double *x2, double *y2,
             double *x3, double *y3,
             double *x4, double *y4)
{
  double b, c, d, e;
  double p, q, r;
  double b3, b2, b1, b0;
  double alpha1, alpha2, beta1, beta2, gamma1, gamma2;
  double abs_sqrt_alpha, abs_sqrt_beta;
  double sqrt_alpha1, sqrt_alpha2, sqrt_beta1, sqrt_beta2, 
       sqrt_gamma1, sqrt_gamma2;
  double r11, r12,  r21, r22, r31, r32, r41, r42;
  double maybe_q;

  int n;

  /*printf("a4 = %lf, a3 = %lf, a2 = %lf, a1 = %lf, a0 = %lf\n", 
    a4, a3, a2, a1, a0);*/


  b = a3/a4;
  c = a2/a4;
  d = a1/a4;
  e = a0/a4;

 // printf("b = %lf, c = %lf, d = %lf, e = %lf\n", b, c, d, e);


  p = (8.0*c - 3.0*b*b)/8.0;
  q = (b*b*b - 4.0*b*c + 8.0*d)/8.0;
  r = (-3.0*b*b*b*b + 256.0*e - 64.0*b*d + 16*b*b*c)/256.0;

 // printf("p = %lf, q = %lf, r = %lf\n", p, q, r);

  if (fabs(q) < EPSILON)
  {
   solve_biquadratic(1.0, p, r,
             &r11, &r12,
             &r21, &r22,
             &r31, &r32,
             &r41, &r42);
 
   *x1 = r11 - (b/4.0);
   *y1 = r12;
   *x2 = r21 - (b/4.0);
   *y2 = r22;
   *x3 = r31 - (b/4.0);
   *y3 = r32;
   *x4 = r41 - (b/4.0);
   *y4 = r42;
   
   return 1;
  }// if

 

  b3 = 1.0;
  b2 = 2.0*p;
  b1 = p*p - 4*r;
  b0 = -q*q;

  //printf("b3 = %lf, b2 = %lf, b1 = %lf, b0 = %lf\n", b3, b2, b1, b0);


  n = solve_cubic(b3, b2, b1, b0,
	     &alpha1, &alpha2, 
             &beta1, &beta2,
             &gamma1, &gamma2);


 /* printf("alpha1 = %lf, alpha2 = %lf\n", alpha1, alpha2);
  printf("beta1 = %lf, beta2 = %lf\n", beta1, beta2);
  printf("gamma1 = %lf, gamma2 = %lf\n", gamma1, gamma2);*/

  square_root(alpha1, alpha2, &sqrt_alpha1, &sqrt_alpha2);
  square_root(beta1, beta2, &sqrt_beta1, &sqrt_beta2);
  square_root(gamma1, gamma2, &sqrt_gamma1, &sqrt_gamma2);


  abs_sqrt_alpha = sqrt_alpha1*sqrt_alpha1 + sqrt_alpha2*sqrt_alpha2;
  abs_sqrt_beta = sqrt_beta1*sqrt_beta1 + sqrt_beta2*sqrt_beta2;


  sqrt_gamma1 = -q *(sqrt_alpha1*sqrt_beta1 -  
          sqrt_alpha2*sqrt_beta2)/(abs_sqrt_alpha*abs_sqrt_beta);
  sqrt_gamma2 = q *(sqrt_alpha2*sqrt_beta1 +  
      sqrt_alpha1*sqrt_beta2)/(abs_sqrt_alpha*abs_sqrt_beta);


  /*printf("sqrt_alpha1 = %lf, sqrt_alpha2 = %lf\n", sqrt_alpha1, sqrt_alpha2);
  printf("sqrt_beta1 = %lf, sqrt_beta2 = %lf\n", sqrt_beta1, sqrt_beta2);
  printf("sqrt_gamma1 = %lf, sqrt_gamma2 = %lf\n", sqrt_gamma1, sqrt_gamma2);*/

  r11 = (sqrt_alpha1 + sqrt_beta1 + sqrt_gamma1)/2.0;
  r12 = (sqrt_alpha2 + sqrt_beta2 + sqrt_gamma2)/2.0;
  r21 = (sqrt_alpha1 - sqrt_beta1 - sqrt_gamma1)/2.0;
  r22 = (sqrt_alpha2 - sqrt_beta2 - sqrt_gamma2)/2.0;
  r31 = (-sqrt_alpha1 + sqrt_beta1 - sqrt_gamma1)/2.0;
  r32 = (-sqrt_alpha2 + sqrt_beta2 - sqrt_gamma2)/2.0;
  r41 = (-sqrt_alpha1 - sqrt_beta1 + sqrt_gamma1)/2.0;
  r42 = (-sqrt_alpha2 - sqrt_beta2 + sqrt_gamma2)/2.0;

 /*printf("r11 = %lf, r12 = %lf, r21 = %lf,r22 = %lf\n", 
    r11, r12, r21, r22);
 printf("r31 = %lf, r32 = %lf, r41 = %lf,r42 = %lf\n", 
    r31, r32, r41, r42);*/

 
 *x1 = r11 - (b/4.0);
 *y1 = r12;
 *x2 = r21 - (b/4.0);
 *y2 = r22;
 *x3 = r31 - (b/4.0);
 *y3 = r32;
 *x4 = r41 - (b/4.0);
 *y4 = r42;

//printf("b/4.0 = %lf\n", b/4.0);

 return 2;
} // solve_quartic

void complex_mult(double a, double b,
double c, double d, double *x, double *y)
{
*x = a*c - b*d;
*y = a*d + c*b; 
} // complex_mult

void complex_add(double a, double b,
double c, double d, double *x, double *y)
{
*x = a + b;
*y = c + d; 
} // complex_mult

void test_solution(double a, double b,
double c, double d, double e,  double x,  double y,
double *result1, double *result2)
{
  double x1,y1, temp11, temp12, temp21, temp22;
  int i;

  temp11 = x;
  temp12 = y;
  temp21 = e;  
  temp22 = 0.0;  

  temp21 += d*temp11;  
  temp22 += d*temp12;;  

  complex_mult(temp11, temp12, x , y, &temp11, &temp12);
  temp21 += c*temp11;  
  temp22 += c*temp12;;  

  complex_mult(temp11, temp12, x , y, &temp11, &temp12);
  temp21 += b*temp11;  
  temp22 += b*temp12;;  

  complex_mult(temp11, temp12, x , y, &temp11, &temp12);
  temp21 += a*temp11;  
  temp22 += a*temp12;;  

 *result1 = temp21;
 *result2 = temp22;

} // test_solution 

void Deriv_calc(double coff[],int deg,double coeffs[])
{
	int i;
	for(i=0;i<deg;i++)
	{
		coff[i]=coeffs[i]*(deg-i);
	}
	
	
}
double check_root_pol( double coeffs[],int deg,double num,double epsilon)
{
     double result=0.0;
	 int i;
	 for(i=0;i<deg;i++)
	 {
	   result+= coeffs[i]*(pow(num,deg-i));
	 }
	 result+=coeffs[deg];
	
	 return result;
}
void devide_pol(double new_coeffs[],double coeffs[],int deg,double num)  //polinom/(x-num)
{
	int i;
	new_coeffs[0]=coeffs[0];
	for(i=1;i<deg;i++)
	{
		new_coeffs[i]=coeffs[i]-(new_coeffs[i-1]*(-num));

	}
	
	
}

double bi_regula_combo(  double (*fun)( double[],int, double ,double),  double a, double b, 
double eps,double coeffs[],int deg, double num)
{
   double x, xmid, f;
   int flag;

  // Calculate initial interval

  
  do {
   // bisection
       x = (a+b)/2.0;
       f = (*fun)(coeffs,deg,x,eps);
       if (fabs(f) < eps)
         return x;
       if ( fun(coeffs,deg,a,eps)*f < 0.0)
         b = x;
       else
         a = x;

  // regula

       x = (a*(*fun)(coeffs,deg,b,eps) - b*(*fun)(coeffs,deg,a,eps))/((*fun)(coeffs,deg,b,eps) 
	   - (*fun)(coeffs,deg,a,eps));
       f = (*fun)(coeffs,deg,x,eps);
       if (fabs(f) < eps)
         return x;
       if ( (*fun)(coeffs,deg,a,eps)*f < 0.0)
          b = x;
       else
         a = x;

   } while( fabs(b-a) > eps);  
  
  return x; 

} /* bi_regula_combo */



int solve_gen_polynom(double solution_points[], double coeffs[], 
int deg, double epsilon)
{
	int flag,i,j,count=0,no_of_solutions=0,number;
	double x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,xstar,result;
	double pd[N],pd_solution_points[N],new_coeffs[N],Q_solution_points[N];
	//////////////////////////////deg=4////////////////////////
	if(deg==4)
	{
	  flag = solve_quartic(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4], &x1, &y1, &x2, &y2, &x3, 
      &y3, &x4, &y4);
	 if(fabs(y1)<1000.0*epsilon)
	 { 
		 solution_points[count]=x1;
		 count++;
	 }
	 if(fabs(y2)<1000.0*epsilon)
	 {
		   solution_points[count]=x2;
		 count++;
	 }
	  if(fabs(y3)<1000.0*epsilon)
	 {
		 solution_points[count]=x3;
		 count++;
	 }
	  if(fabs(y4)<1000.0*epsilon)
	 {
		 solution_points[count]=x4;
		 count++;
	 }
	
	 return count;
	}
	////////////////////////////////////deg=3//////////////////////////////////
	if(deg==3)
	{
		 no_of_solutions = solve_cubic(coeffs[0], coeffs[1], coeffs[2], coeffs[3],  &x1, &y1, &x2, &y2, &x3, &y3);
	     if(no_of_solutions==1)
			 solution_points[0]=x1;
		 if(no_of_solutions==3)	
		 {
			 solution_points[0]=x1;
			 solution_points[1]=x2;
			 solution_points[2]=x3;
		 }
		 return no_of_solutions;
	}
	///////////////////////////////////////deg>4/////////////////////
		
		if(deg%2==1)  
		{	
			xstar=bi_regula_combo(check_root_pol,-10.0, 10.0, epsilon,coeffs,deg,0.0);		
			devide_pol(new_coeffs,coeffs,deg,xstar); //new_coeffs=Q	
			no_of_solutions =solve_gen_polynom(solution_points, new_coeffs, 
            deg-1, epsilon);
			solution_points[no_of_solutions]=xstar;
		  
			return (no_of_solutions+1);
			
		}
		else
		{ 
			Deriv_calc(pd,deg,coeffs);
			no_of_solutions =solve_gen_polynom(pd_solution_points, pd, 
            deg-1, epsilon);	
			flag=0;
	        for(i=0;i<no_of_solutions&&flag==0;i++)
	       {
			   result=check_root_pol(coeffs,deg,pd_solution_points[i],epsilon);
		     if(fabs(result)<1000.0*epsilon) 
		     {
			  devide_pol(new_coeffs,coeffs,deg,pd_solution_points[i]); 
			  
			  flag=1;		
		     }
	       }
	       if(flag==1)
	       {
	         no_of_solutions =solve_gen_polynom(solution_points, new_coeffs, 
             deg-1, epsilon); 
	         solution_points[no_of_solutions]=pd_solution_points[i-1];
	         return no_of_solutions+1;
			}
		   else
		   {
			 
			for(i=0;i<no_of_solutions;i++)
			{
				result=check_root_pol(coeffs,deg,pd_solution_points[i],epsilon);
				
	        		if(result<1000.0*epsilon)
					{
						xstar=bi_regula_combo(check_root_pol,pd_solution_points[i]-10.0,pd_solution_points[i]+ 10.0,
						epsilon,coeffs,deg,pd_solution_points[i]);
						devide_pol(new_coeffs,coeffs,deg,xstar);
					
			            number =solve_gen_polynom(solution_points, new_coeffs, 
                        deg-1, epsilon);
					    
						solution_points[number]=xstar;
					    
						
				      	return number+1;;
					}
				
				
			}
			    
		     	printf("There are no real solutions!!!!!!");
		    	exit(1);
				
				
			
		   }
		}
		
	
	
}

int main()
{
 double r;
 int i1,j1, i;
 double a, b, c, d, e;
 double interval_a, interval_b;
 double x0, x1, x2, x3, x4;
 double y0, y1, y2, y3, y4;
 double min_points[5];
 double min_value, temp_value;
 double coeffs[N];
 double solutions[N];

 double epsilon = 0.00000001;
 int no_of_solutions, degree;
 int flag;
 double result1, result2;

  
 printf("Enter degree\n");
 scanf("%d", &degree);

 printf("Enter %d coeffs, first must be > 0:\n", degree+1);
 for(i=0; i <= degree; i++)
   scanf("%lf", &coeffs[i]);

 printf("The polynom:\n");
 for(i=0; i <= degree; i++)
   printf(" %10.3lf ", coeffs[i]);
 printf("\n");
 no_of_solutions = solve_gen_polynom(solutions, coeffs, 
degree, epsilon);

 printf("no_of_solutions = %d\n", no_of_solutions);
 printf("Solutions:\n");
 for(i=0; i < no_of_solutions; i++)
   printf(" %10.3lf ", solutions[i]);
 printf("\n");
 
 return 0;
} /* main */ 
