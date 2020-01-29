#include "distances.hpp"
#include <iostream>
#include <fstream>
#include <new>
#include <cstdio>
#include <cfloat>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

class ImgClass{
public:
char imageName[256] ;
int   imageClass    ;
double   *vect ;
ImgClass(int nbrFeat){
vect = new double[nbrFeat];}
ImgClass(){}
~ImgClass(){ if(vect) delete [] vect ;}
void allocArray(int nbrFeat){
vect = new double[nbrFeat];}
};


class Knn{
ImgClass *tTest, *tTrain;
int nbrNN, nbrOfTests, nbrOfTrains, nbrOfClasses, desSize, segment ;
double *score;
public:
Knn(char *testFile, char *trainFile);
~Knn();
//char *findKnn(imgClass *tTest, imgClass *tTrain);
void rating(int nNN, int distype);
void saveScore(char *resultFile);
double wta(int *Tclass, int classTest);
double *getScore(){return this->score;}
int  getNumberOfClasses(){return this->nbrOfClasses;}
};



