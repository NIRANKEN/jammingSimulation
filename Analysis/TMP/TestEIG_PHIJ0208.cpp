#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include "nr.h"

using namespace std;


//sampleのデータを集めるだけ。
int main()
{
  string rdtmp,rdstr,wtstr,wtSAve,phistr,str;
  cout<<"本プログラムは,"<<endl;
  cout<<"EIGのテーブルに対して,欲しい(PHIJ-PHI)の値を入力して"<<endl;
  cout<<"その値でのテーブルを出力するプログラムです."<<endl;
  cout<<"inputするファイル名を入力してください.(e.g. xxx.txtのxxx部分)"<<endl;
  cin>>rdtmp;
  cout<<"\nselectするPHI-PHIJの値を入力してください."<<endl;
  cin>>phistr;
  cout<<"\n-----------\n"<<endl;
  
  rdstr = rdtmp+".txt";
  wtstr = "P-PJeq"+phistr+"_"+rdtmp+".txt";
  //wtSAve ="SampleAverage_PPJeq"+phistr+"_"+rdtmp+".txt";
  ifstream ifs(rdstr.data());
  if(ifs.fail()) {
    cout<<rdstr<<"っていうfile openできなかったよ~."<<endl;
    cout<<"おしまい。"<<endl;
  }
  else {
    string line;
    ofstream ofs(wtstr.data());
    //ofstream ofssam(wtSAve.data());
    istringstream is;
    is.str(phistr);
    double a=0,b=0,c=0,d=0,e=0,f=0,PPJ;
    int cnt=0;
    is>>PPJ;
    while(getline(ifs,line)) {
      sscanf(line.data(),"%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f);
      if(b==PPJ) {
	ofs<<setprecision(10)<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<endl;
	cnt+=1;
      }
    }
    cout<<cnt<<"個のサンプルについて採取しました."<<endl;
    
  }
  cout<<"終了。"<<endl;
}
