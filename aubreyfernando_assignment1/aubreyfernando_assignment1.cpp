/**
Aubrey Fernando 
2271086
ferna190@mail.chapman.edu
CPSC 350-02
Assignment1
**/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
#include <math.h>
using namespace std;
//function declaration
void CheckFile(string fileName);
string GenerateString(double aProb,double tProb, double cProb,double gProb, int mean, double sd);
int BirgramFreq(string line, char x, char y);
double BigramProb(int bifreq, int totalBigrams);
int sumM(string l);
int Mean(int chars);
double StandardDeviation(double Variance); 
double nucleotideProb(int nucCount, int sum);
int numOfBigrams(string line);

//global variable declaration
int countLines; 
ofstream dnaFile;  

int main(int argc, char* argv[])

{
	//variable declaration
	char ans; 
	bool repeat=false; 
	string fileInput; 

	int sum=0;
	int a=0; 
	int t=0; 
	int c=0;
	int g=0;

	int aa=0;
	int at=0; 
	int ac=0;
	int ag=0;

	int ta=0; 
	int tt=0;
	int tc=0;
	int tg=0; 

	int ca=0;
	int ct=0;
	int cc=0;
	int cg=0;

	int ga=0;
	int gt=0;
	int gc=0;
	int gg=0; 

	double aaProb=0; 
	double atProb=0; 
	double acProb=0;
	double agprob=0; 

	double taProb=0; 
	double ttProb=0; 
	double tcProb=0; 
	double tgProb=0; 

	double caProb=0; 
	double ctProb=0; 
	double ccProb=0; 
	double cgProb=0; 

	double gaProb=0; 
	double gtProb=0; 
	double gcProb=0;
	double ggProb=0; 

	double varSum=0;
	double lineLength=0; 
	double variance=0; 
	double sd=0; 

	int numBirgrams=0; 

	//do while loop, completeting this first then checking if while statement is true
	do
	{	
		//if a file was entered in command line
		if(argc>1)
		{
		fileInput=argv[1]; 
		CheckFile(fileInput);

		//if user wants to process another while user is prompted to enter name of file
		//resets fileInput to new file name entered
		if(repeat==true)
		{
			cout<<"Enter the file name you would like to process:"<<endl;
			cin>>fileInput; 
			CheckFile(fileInput);
		}
		//reading in the file
		ifstream infile(fileInput.c_str());
		if(infile.is_open()&&infile.good())
		{
			string line;
			//reading from file line by line
			while(getline(infile,line))
			{
			sum+=sumM(line);
			countLines+=1; 

			//calculating number of bigrams and frequency of each of the 16 bigrams
			numBirgrams+=numOfBigrams(line); 
			aa+=BirgramFreq(line,'A','A'); 
			at+=BirgramFreq(line,'A','T'); 
			ac+=BirgramFreq(line,'A','C');
			ag+=BirgramFreq(line,'A','G'); 

			ta+=BirgramFreq(line,'T','A'); 
			tt+=BirgramFreq(line,'T','T'); 
			tc+=BirgramFreq(line,'T','C');
			tg+=BirgramFreq(line,'T','G');

			ca+=BirgramFreq(line,'C','A');
			ct+=BirgramFreq(line,'C','T');
			cc+=BirgramFreq(line,'C','C');
			cg+=BirgramFreq(line,'C','G'); 

			ga+=BirgramFreq(line,'G','A');
			gt+=BirgramFreq(line,'G','T'); 
			gc+=BirgramFreq(line,'G','C');
			gg+=BirgramFreq(line,'G','G'); 

			//calculating number of times A,T,G,C occur in the file
			for(unsigned int i=0; i<line.length();i++)
				{
				if((line[i]=='A')|(line[i]=='a'))
					a++; 

				else if((line[i]=='T')|(line[i]=='t'))
					t++;

				else if((line[i]=='C')|(line[i]=='c'))
					c++;

				else if((line[i]=='G')|(line[i]=='g'))
					g++;
				}
			}
		}
		infile.close();

		//subtract sum by number lines because line amount gets added to sum
		sum-= countLines; 

		int mean = Mean(sum); 
		
		//calculating frequency individual nucleotides occur
		double aProb = nucleotideProb(a,sum); 
		double tProb = nucleotideProb(t,sum);
		double cProb = nucleotideProb(c,sum); 
		double gProb = nucleotideProb(g,sum); 
		
		//calculating frequency of bigrams
		aaProb = BigramProb(aa,numBirgrams); 
		atProb = BigramProb(at,numBirgrams);
		acProb = BigramProb(ac,numBirgrams);
		agprob = BigramProb(ag,numBirgrams);

		taProb = BigramProb(ta,numBirgrams);
		ttProb = BigramProb(tt,numBirgrams);
		tcProb = BigramProb(tc,numBirgrams);
		tgProb = BigramProb(tg,numBirgrams); 

		caProb = BigramProb(ca,numBirgrams);
		ctProb = BigramProb(ct,numBirgrams);
		ccProb = BigramProb(cc,numBirgrams);
		cgProb = BigramProb(cg,numBirgrams);

		gaProb = BigramProb(ga,numBirgrams);
		gtProb = BigramProb(gt,numBirgrams);
		gcProb = BigramProb(gc,numBirgrams);
		ggProb = BigramProb(gg,numBirgrams); 


		int countLine=0; 
		//open the file again to calc standard deviation and varaince
		//open second time because the mean is necesary but can't calc variance and mean at the same time
		ifstream infile2(fileInput.c_str());
		if(infile2.is_open()&&infile2.good())
		{
			string lines;
			while(getline(infile2,lines))
			{
			//calculate variance
			lineLength = (lines.length()-mean)*(lines.length()-mean);
			varSum+=lineLength;
			countLine++;  
			}
		}
		infile2.close();

		 variance = varSum/countLine; 
		 sd = StandardDeviation(variance); 

		//writing to file
		dnaFile.open("aubreyfernando.out"); 
		dnaFile<<"Aubrey Fernando"<<endl<<"2271086"<<endl<<"CPSC 350-2"<<endl;
		//print stats
		dnaFile<<endl<<"Statistics:"<<endl<<"Sum:"<<sum<<endl<<"Mean:"<<mean<<endl<<"Variance:"<<variance<<endl; 
		dnaFile<<"StandardDeviation:"<<sd<<endl<<endl; 

		//print nucleotide prob
		dnaFile<<"Individual Nucleotide Probability"<<endl;
		dnaFile<<"A:"<<aProb*100<<"% |"<<"T:"<<tProb*100<<"% |"<<"C:"<<cProb*100<<"% |"<<"G:"<<gProb*100<<"%"<<endl; 
		
		//print bigram prob
		dnaFile<<endl<<"Number of bigrams:"<<numBirgrams<<endl;
		dnaFile<<endl<<"Bigram Frequency"<<endl;
		dnaFile<<"AA:"<<aaProb<<"% |AT:"<<atProb<<"% |AC:"<<acProb<<"% |AG:"<<agprob<<"%"<<endl;
		dnaFile<<"TA:"<<taProb<<"% |TT:"<<ttProb<<"% |TC:"<<tcProb<<"% |TG:"<<tgProb<<"%"<<endl;
		dnaFile<<"CA:"<<caProb<<"% |CT:"<<ctProb<<"% |CC:"<<ccProb<<"% |CG:"<<cgProb<<"%"<<endl;
		dnaFile<<"GA:"<<gaProb<<"% |GT:"<<gtProb<<"% |GC:"<<gcProb<<"% |GG:"<<ggProb<<"%"<<endl;

		//print 1000 strings
		dnaFile<<GenerateString(aProb,tProb,cProb,gProb,mean,sd)<<endl; 
		dnaFile.close();

		cout<<"Processing Complete"<<endl; 
		cout<<"Data has been written to aubreyfernando.out"<<endl;
	}	
		//if no file was entered
		else
		{
			cout<<"No file name was entered"<<endl;
			cout<<"Processing Terminated" <<endl; 
			exit(0); 
		}

		//prompt user to process another file
		cout<<"Process another list? (Y/N)"<<endl; 
		cin>>ans;
		if((ans=='y')|(ans=='Y'))
		{
			repeat=true; 
		}
	}

	//repeat do loop is user wants to process another file
	while ((ans=='y')|(ans=='Y'));

	//if not exit
	cout<<"Goodbye"<<endl; 

	return 0;
	 
}

//checks if the file can open correctly
//if file doesn't exist processing stops
void CheckFile(string fileName)
{

	ifstream read; 
	read.open(fileName.c_str()); 
	if(read.fail())
	{
		cout<<"File Does not exist"<<endl; 
		cout<<"Processing terminated"<<endl;
		exit(0); 
	}
}

//Sum of all chars
int sumM(string l)
{
	int s=0; 
	s+=l.length(); 
	return s; 

}

//mean of chars in lines
int Mean(int chars)
{
	int mean = chars/countLines; 
	return mean; 
}

//calcualtes sd by taking square root of variance
double StandardDeviation(double variance)
{
	double sd = pow(variance,0.5); 
	return sd; 
}

//calc probability of each nucleotide
double nucleotideProb(int nucCount, int sum)
{
	double n = nucCount; 
	double s =sum;
	double probPercent = (n/s); 
	return probPercent; 
}

//calcualte number of bigrams
int numOfBigrams(string line)
{
	int count=0; 
	for(unsigned int i =0;i<line.length();++i)
	{
		count++; 
	}
	if(count>2)
	{
		count-=2; 
	}	
	return count;
}

//calcualting freq of bigrams by inputting 2 chars within the given line
int BirgramFreq(string line, char x, char y)
{
	int count=0; 
	for(unsigned int i=0; i<line.length();i++)
	{
		if(toupper(line[i])==x)
		{
			if(toupper(line[i+1])==y)
			{
				count++; 
			}
		}
	}
	return count;
}

//calcualting probability of each birgram
double BigramProb(int bifreq, int totalBigrams)
{
	double bigramNum = bifreq;
	double total = totalBigrams; 

	double prob = (bigramNum/total);
	return prob*100 ; 
}

//print out 1000 strings
string GenerateString(double aProb,double tProb, double cProb,double gProb, int mean, double sd)
{
	//stringstream is return and is able to be written to file when called
	stringstream write; 
	write<<endl<<"1000 Nucleotide Strings"<<endl; 

	//probs were in decimal form before
	int a1 = aProb*100; 
	int t1 = tProb*100; 
	int c1 = cProb*100; 
	int g1 = gProb*100; 

	int total = a1+t1+c1+g1; 

	//when rand num is made what nucletide it will be is based on nucletide prob
	int aNucProb = a1;
	int tNucProb = a1+t1; 
	int cNucProb = a1+t1+c1;
	int gNucProb = a1+t1+c1+g1; 
	
	//begin printing 1000 strings/lines
	for(int i=0; i<1000; ++i)
	{
		//generating random num between [0,1)  to calculte c
		double a = ((double)rand() / (RAND_MAX)) ;
		double b = ((double)rand()/ (RAND_MAX)); 
		
		//gaussian calculation
		double c = ((pow((-2*log(a)),0.5))*cos(2*M_PI*b));

		//calcualte d, lenght of string
		double d = ((sd*c)+mean); 

		string nucleotide=""; 
		
		//printing nucleotides lenght of d
		for(int j=0; j<d; ++j)
			{

			// generate random number between nucleotide probabilities total
			int num  = rand()%total+1; 

			//Char is added to string line based on rand num
			if(num<=aNucProb)
			{
			nucleotide+= 'A'; 
			}
			else if(num>aNucProb && num<=tNucProb)
			{
			nucleotide+= 'T'; 
			}
			else if(num>tNucProb && num<=cNucProb)
			{
			nucleotide+= 'C'; 
			}

			else if(num>cNucProb && num<=gNucProb)
			{
			nucleotide+= 'G';
			}
			else
			{
			nucleotide+= 'N';
			}
		}
	//print out string line to file using stringstream
	write<<nucleotide<<endl; 
	}
	return write.str(); 
}

