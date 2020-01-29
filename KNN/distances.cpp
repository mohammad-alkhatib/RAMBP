#include "distances.hpp"

double euclidianDist(double v1[] , double v2[], int size)
{
  int i ;
  double s = 0.0 ;
   
   for(i=0 ; i<size ; i++)
       s +=(double)(v1[i] - v2[i])*(v1[i] - v2[i]) ;        
	  
return sqrt(s) ; 	      
}	 

double chiDist(double v1[] , double v2[], int size)
{
  int i ;
  double a, s = 0.0 ;
   
   for(i=0 ; i<size ; i++)
     {  a = v1[i] + v2[i] ;
       if (a == 0)
         a = 1.0 ;
       s +=(double)0.5*(v1[i] - v2[i])*(v1[i] - v2[i])/a ;        
     }
return s ; 	      
}	

double JDdiv(double v1[] , double v2[], int size)
{
  int i ;
  double a, b, s = 0.0 ;
   
   for(i=0 ; i<size ; i++)
     {
      a = v1[i] ; b = v2[i] ;
      if( a!=0 && b!=0)
       s += a*log(a/b) + b*log(b/a) ;  
     }

return s ; 
}

double histIntersect(double v1[] , double v2[], int size)
{
int i ;
  double a, b, min, s = 0.0 ;

for(i=0 ; i<size ; i++)
     {
      a = v1[i] ; b = v2[i] ;
       
     if(a<=b)
       min=a;
     else
       min=b;

     s+=min;

     } 

return 1.0/s ; 

}

// segment is a size of one specific feature
// size represent the total size of the features
double mbpDistance(double *vect1, double *vect2, int size, int segment)
{
 
 double dist, min, s ;
 int  l , k , n        ;

 n = (int)size/segment; 
 k=n; l=n;

 double *tmp1, *tmp2;  

 tmp1 = vect1 ; 
 s = 0.0 ;



 for( ; l-- ;  tmp1 +=segment )
   {
        tmp2 = vect2 ; 
        min = DBL_MAX       ;
   
     for( k=n  ; k-- ; tmp2 += segment)
        {
         dist =euclidianDist(tmp1 , tmp2, segment)  ;
    
          if(dist<min)
          min = dist ;
        }

 s += min ;

   }

 return (double)s/n ;

}

