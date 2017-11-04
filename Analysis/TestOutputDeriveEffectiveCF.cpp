#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <limits>
#include "BIN.h"

using namespace std;

int main(int argc, char** argv)
{
if(argc!=3) {
    cerr<<"宣言ミス\n1. 最小二乗法適用DPHI個数, 2.DPHIのシフト定数"<<endl;
    exit(1);
  }
  int n=atoi(argv[1]);
  double shift=atof(argv[2]);
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,wt_ecf,rd,str;
  ifstream ifs;
  ofstream ofs,ofs_ecf;
  int N;
  const int Nd=2; //dataの列数(DPHI, Characteristiv Frequency)
  double x,y,sum_x=0.0,sum_y=0.0,sum_xx=0.0,sum_xy=0.0,y_intercept,slope,denom,numer,EPS=numeric_limits<double>::epsilon();
  string line;
  int cnt=0;
  double data[Nd];
  vector<double> omega,dos;
  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  cout<<"入力する \"CFreq-DPHI\" のTEXT名を入れて下さい.(e.g. SM_cfreq2.txt)"<<endl;
  cout<<"-> ";
  cin>>rd;
  cout<<endl;
  
  ifs.open(rd.data());
  if(ifs.fail()) {
    cerr<<"catnot open your file: "<<rd<<endl;
    return 1;
  }
  else {
    wt="ECF_"+rd;
    wt_ecf="ECF.txt";
    ofs.open(wt.data());
    ofs_ecf.open(wt_ecf.data());
    N=atoi(Pnum.data());
    cout<<"\n\n\""<<n<<"\"個のDPHIと"<<endl;
    cout<<"\""<<shift<<"\"のSHIFT定数を用いてEffectiveでCriticalなomega*の値を導出"<<endl;

    while(getline(ifs,line)) {
      if(cnt<n) {
	stringstream ss(line);
	for(int i=0;i<Nd;i++) {
	  ss>>setprecision(10)>>data[i];
	}
	x=log10(data[0]);
	y=log10(data[1]);
	if(data[0]<EPS && data[1]<EPS) {
	  cnt--;
	}
	else {
	sum_x+=x;
	sum_y+=y;
	sum_xx+=x*x;
	sum_xy+=x*y;
	omega.push_back(data[0]);
	dos.push_back(data[1]);
	}
      }
      else {
	break;
      }
      cnt++;
    }
    ifs.close();
    
    denom=n*(sum_xx)-sum_x*sum_x;
    numer=sum_xx*sum_y-sum_xy*sum_x;
    y_intercept=numer/denom;
    numer=n*(sum_xy)-sum_x*sum_y;
    slope=numer/denom;
    x=pow(shift,slope);
    ofs_ecf<<N<<" "<<x<<endl;
    for(unsigned int i=0;i<omega.size();i++) {
      y=pow(omega[i],slope)*pow(10,y_intercept);
      ofs<<omega[i]<<" "<<y<<" "<<y_intercept<<" "<<slope<<" "<<N<<" "<<x<<endl;
    }
    ofs.close();
    ofs_ecf.close();
    
  }
}
