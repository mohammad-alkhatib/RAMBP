#include "knn.hpp"


class Option{
public:
char testfile[128], trainfile[128], resultfile[128];
int dist, numNN; 
Option(){ 
dist = 0; numNN = 3;
}
};



/*---------*/
void knn_help()
/*---------*/
{
  cout << "<executable> <arguments>\n";
  cout << "\trequires:\n";
  cout << "\t-ts <test file> containing descriptors\n"   ;
  cout << "\t-tr <train file> containing\n"  ;
  cout << "\t\tthe train and test files should be in the following format:\n"
	  "\t\t1: \"number of images in the file (integer)\" \n"
	  "\t\t2: \"number of classes (integer)\"\n"
          "\t\t3: \"size of descriptor vector (integer)\"\n"
	  "\t\t4: \"image name (char*)\"  \"class of image (integer)\"  \"[des1 des2....](double)\" \n"
	  "\t\t5: \"image name (char*)\"  \"class of image (integer)\"  \"[des1 des2....](double)\" \n"
	  "\t\t6: ....\n";
  cout << "\toptions:\n";
  cout << "\t-rs <result file> save the rate classification\n" ;
  cout << "\t-d <distance type> : 0 chi (default), 1 euclidean, 2 JD divergence\n" ;
  cout << "\t-k <number of k nearest neighbors> by default is 3\n" ;
  cout << "\t-help the current help\n";
}


/*-----------------------------------------------------*/
void parseArgs(int theArgc, char **theArgv, Option *opt)
/*-----------------------------------------------------*/
{

if(theArgc < 5)
 {knn_help(); exit(1);}


while(theArgc)
    {
      if(*(*theArgv)=='-') //  option
        {
 
         if(!strcmp((*theArgv),"-help"))
           {
            knn_help(); exit(1); 
           }

         if(!strcmp((*theArgv),"-ts"))
           {
            theArgc-- ; theArgv++ ; 
            strcpy(opt->testfile,*theArgv); 
           }

	if(!strcmp((*theArgv),"-tr"))
           {
            theArgc-- ; theArgv++ ; 
            strcpy(opt->trainfile,*theArgv); 
           }

	if(!strcmp((*theArgv),"-rs"))
           {
            theArgc-- ; theArgv++ ; 
            strcpy(opt->resultfile,*theArgv); 
           }
          
         else if(!strcmp((*theArgv),"-k"))
           {
            theArgc-- ; theArgv++ ; 
            opt->numNN=atoi(*theArgv); 
           }

         else if(!strcmp((*theArgv),"-d"))
           {
            theArgc-- ; theArgv++ ; 
            opt->dist = atoi(*theArgv); 
           }           
        }
    
    else
        {
         theArgc-- ; theArgv++ ; 
        }
    }
}

int main(int argc, char **argv)
{
Option opt;
parseArgs(argc, argv, &opt);

Knn eval(opt.testfile, opt.trainfile) ;
eval.rating(opt.numNN, opt.dist);

double *score=eval.getScore();

string  s1 = opt.testfile ;
	size_t pos = s1.rfind('/') ;
	s1=s1.substr(pos+1) ;
	pos = s1.find('.')  ;
	s1  = s1.substr(0,pos)  ;
	stringstream st1    ;
        s1+="-k" ;
	st1 << opt.numNN ;
	s1+=st1.str()+".score" ;
        //s1.insert(0,"score/")  ;

        ofstream resultFile(s1.c_str());
	resultFile << opt.testfile << endl
		   << opt.trainfile << endl 
                   << "k-nn= " << opt.numNN << "  dist: " << opt.dist << endl;	

        double som = 0.0;
	for (int i=0 ; i<eval.getNumberOfClasses()  ; i++)
	{ 
	    resultFile << "classe: " << i <<"  "<< score[i] << endl;
	    som += score[i]; 
	}

	resultFile << "mean: " << som/eval.getNumberOfClasses() << endl;

 resultFile.close() ;	
	
 return 0 ;
}



