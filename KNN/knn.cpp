#include "knn.hpp"

Knn::Knn(char *testFile, char *trainFile)
{
int k, i;

ifstream intest(testFile); 

if(!intest) {
cout << "in function Knn, failure to open " << testFile << endl ;
exit(1);
}

ifstream intrain(trainFile); 

if(!intrain) {
cout << "in function Knn, failure to open " << trainFile << endl ;
exit(1);
}

intest  >> nbrOfTests  >> nbrOfClasses >> desSize >> segment  ;
intrain >> nbrOfTrains >> nbrOfClasses >> desSize >> segment  ;


try { 
  tTest  = new ImgClass[nbrOfTests]  ;
    } catch (bad_alloc xa) { 
    cout << "In function knn : allocation failure \n"; 
    exit(1); 
  } 

try { 
   tTrain  = new ImgClass[nbrOfTrains]  ;
    } catch (bad_alloc xa) { 
    cout << "In function knn : allocation failure \n"; 
    exit(1); 
  } 

    for(i=0 ; i<nbrOfTests ; i++)
     {     
      intest >> tTest[i].imageName >> tTest[i].imageClass ;
                tTest[i].allocArray(desSize) ;

       for(k=0 ; k < desSize ; k++) 
	    intest >> tTest[i].vect[k] ;
	  
     }


  for(i=0 ; i<nbrOfTrains ; i++)
     {     
      intrain >> tTrain[i].imageName >> tTrain[i].imageClass ;
       
        tTrain[i].allocArray(desSize) ;

      for(k=0 ; k < desSize ; k++) 
	 intrain >> tTrain[i].vect[k] ;  
     }

intest.close();
intrain.close();

score = new double[nbrOfClasses];

}

Knn::~Knn()
{
if(tTest){delete [] tTest ;}
if(tTrain){delete [] tTrain ;}
if(score){delete [] score  ;}
}

void Knn::rating(int nNN, int distype)
{

int   q = 0 , tmp, k, l;
double dist, success, classSucess = 0.0 ,  s = 0.0 ; 


this->nbrNN = nNN;

int *Tclass = new int[nbrNN];
double *Tmin   = new double[nbrNN];


tmp = tTest[0].imageClass ;
int i=0 ;

 while(i<nbrOfTests)
  {
  
   for(k=0 ; k<nbrNN ; k++)
      Tmin[k] = (DBL_MAX); 

  int j = 0 ;

   while(j<nbrOfTrains) 
    {
    
     if (distype == 0)
       dist = chiDist(tTest[i].vect, tTrain[j].vect, desSize) ;
     else if (distype == 1)  
       dist = euclidianDist(tTest[i].vect, tTrain[j].vect, desSize) ;
     else if (distype == 2)
       dist = mbpDistance(tTest[i].vect, tTrain[j].vect, desSize, segment) ;
      
     else 
        dist = histIntersect(tTest[i].vect, tTrain[j].vect, desSize) ;

             for(k=0 ; k<nbrNN ; k++)
                {
                 if(dist<Tmin[k])
                   {
                       for(l=nbrNN-1 ; l>k ; l--)
 		            {	
                               Tmin[l] = Tmin[l-1]  ;
			       Tclass[l] = Tclass[l-1] ;
		            }
                    

                Tmin[k] = dist ; 
		Tclass[k] = tTrain[j].imageClass ; 
                cout << "class: " << Tclass[k] << endl;
		break ;
                   }
                 }
       j++ ;
 
        }//while j
  
/* algorithme winner take all */

success = wta(Tclass,tTest[i].imageClass) ;

 if(tTest[i].imageClass != tmp)
   {
    score[tmp] = 100*classSucess/q ;
    cout << "test class: " << tmp << " ----> sucess: " 
              <<  score[tmp] <<"%"<< endl;
    classSucess = 0.0 ; tmp = tTest[i].imageClass ; q = 0 ;
   }
 classSucess += success ; ++q ; 

 s += success ;
 

  i++ ;

//double rate = (double)100.0*s/i  ;

//cout << "test num: " << i << " ----> sucess: "
//     << success*100.0 <<"%"<< " ----> sucess: "
//     << rate <<endl ;

}//while i
score[tmp] = 100*classSucess/q ;
cout << "test class: " << tmp << " ----> sucess: " 
          <<  score[tmp] << "%" << endl ;
cout << "--------------------------------\n" << "total:\t\t\t    " 
          << 100*s/i << "%" << endl ;

delete [] Tclass;
delete [] Tmin; 

}

void Knn::saveScore(char *resultFile)
{
ofstream outresult(resultFile) ;

if(!outresult) {
cout << "in function Knn, failure to open" << resultFile << endl ;
exit(1);
}

outresult << "\n# Knn classification performances\n"
          << "# number of Knn: " << this->nbrNN << "\n";

int i; double s = 0.0;

for(i=0 ; i<nbrOfClasses ; i++)
  {
   outresult << "test class: " << i << " ----> sucess: " 
           << score[i] <<"%"<< endl;
    s +=score[i] ;
  }

outresult << "--------------------------------\n" << "total:\t\t\t    " 
          << s/nbrOfClasses << "%" << endl ;

outresult.close();
}

double Knn::wta(int *Tclass, int classTest)
{

int j, k, max , cnt, R[nbrOfClasses] ;
double success = 0.0    	     ;

  max = 0	 ;

 for(j=0 ; j<nbrOfClasses ; j++) 
     R[j] = 0 ;

  for(k=0 ; k<nbrNN ; k++)
      R[Tclass[k]]++ ;

  for(j=0 ; j<nbrOfClasses ; j++) 
     if(R[j] > max)
       max = R[j] ;

/*
 cnt = 0 ;
 
 for(j=0 ; j<nbrOfClasses ; j++) 
     if(R[j] == max)
       cnt++ ;

      if(R[classTest] == max)
           success = (double) 1/cnt ;
*/

if(R[classTest] == max) success = 1.0; else success=0.0;

return success ;

}

