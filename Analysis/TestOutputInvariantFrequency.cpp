#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <cmath>
#include <vector>
#include "BIN.h"
#include "l_approx.h"

using namespace std;

int main(int argc,char** argv)
{

  if(argc!=2) {
    cerr<<"生DOS=> \"0\", 平滑化DOS=> \"1\"を引数に入力して下さい."<<endl;
    exit(1);
  }
  string rdtmp;
  switch(atoi(argv[1])) {
  case 0: rdtmp="EIGEnsAve_"; break;
  case 1: rdtmp="SM_EIGEnsAve_"; break;
  default: cerr<<"ERROR!!"<<endl; exit(1); break;
  }
  
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string rd1,rd2,dir1,dir2;
  //stringstream ss;
  ifstream ifs1,ifs2;
  

  binstat::InputStr(dt,disperse,Pnum,dim);
  cout<<"読み込み先のディレクトリを2つ指定してください."<<endl;
  cout<<"-> ";
  cin>>dir1;
  cout<<"\n-> ";
  cin>>dir2;
  cout<<endl;
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  rd1="./"+dir1+"/"+rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  rd2="./"+dir2+"/"+rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs1.open(rd1.data());
  if(ifs1.fail()) {
    cerr<<"catnot open your file: "<<rd1<<endl;
    return 1;
  }
  else {
    ifs2.open(rd2.data());
    if(ifs2.fail()) {
      cerr<<"catnot open your file: "<<rd2<<endl;
      return 1;
    }
    else {
      string line1,line2,wt="InvariantFreq_"+dir1+"_"+dir2+"_"+rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
      int cnt=0,cnttmp=0;
      const int Nd=15;
      double iData1[Nd],iData2[Nd],DOS1,DOS2,omega1,omega2,domega,dos_tmp,dDOS,omega_ans,dos_ans,denom,numer;
      bool written=false;
      ofstream ofs(wt.data());
      cout<<"処理を開始します...\n"<<endl;
      
      while(getline(ifs1,line1)) {
	if(!getline(ifs2,line2))
	  break;
	stringstream ss1(line1);
	for(int i=0;i<Nd;i++) {
	  ss1>>iData1[i];
	  //cout<<iData1[i]<<' '; //stringstream test
	}
	//cout<<endl;
	stringstream ss2(line2);
	for(int i=0;i<Nd;i++) {
	  ss2>>iData2[i];
	  //cout<<iData2[i]<<' '; //stringstream test
	}
	//cout<<endl;
	
	if(cnt==0) {
	  omega1=iData1[0];
	  dos_tmp=iData1[10];
	  DOS1=iData2[10]-iData1[10];
	}
	else {
	  omega2=iData1[0];
	  DOS2=iData2[10]-iData1[10];

	  while(iData1[0]!=iData2[0]) {
	    cnttmp=0;
	    if(iData1[0]<iData2[0]) {
	      //cout<<"entered roop1: "<<endl;
	      //cout<<"increment omega of 1st TEXT"<<endl;
	      getline(ifs1,line1);
	      stringstream ss1_tmp(line1);
	      for(int i=0;i<Nd;i++) {
		ss1_tmp>>iData1[i];
		//cout<<iData1[i]<<' '; //stringstream test
	      }
	      //cout<<endl;
	      cnttmp+=1;
	   
	      omega2=iData1[0];
	      DOS2=iData2[10]-iData1[10];
	    }
	    else if(iData1[0]>iData2[0]) {
	      //cout<<"entered roop2: "<<endl;
	      //cout<<"increment omega of 2nd TEXT"<<endl;
	      getline(ifs2,line2);
	      stringstream ss2_tmp(line2);
	      for(int i=0;i<Nd;i++) {
		ss2_tmp>>iData2[i];
		//cout<<iData2[i]<<' '; //stringstream test
	      }
	      //cout<<endl;
	      DOS2=iData2[10]-iData1[10];
	    }
	    cnttmp+=1;
	    if(cnttmp==200) {
	      cerr<<"cannot calculate omeaga dividing intermediate|high frequency regime!"<<endl;
	      exit(1);
	    }
	  }

	  //処理
	  if(DOS1*DOS2<0 && cnt>3) {//cnt>3は適当.
	    denom=DOS2-DOS1;
	    numer=DOS2*omega1-DOS1*omega2;
	    omega_ans=numer/denom;
	    cout<<omega1<<' '<<omega_ans<<' '<<omega2<<endl;
	    domega=omega2-omega1;
	    numer=(iData1[10]-dos_tmp)*(omega_ans-omega1);
	    denom=domega;
	    dos_ans=dos_tmp+numer/denom;
	    written=true;
	  }
	  omega1=omega2;
	  dos_tmp=iData1[10];
	  DOS1=DOS2;
	}
	cnt+=1;
      }//while - end
      if(written) {
	ofs<<omega_ans<<' '<<dos_ans<<endl;
	cout<<"書き込み成功."<<endl;
      }
      else {
	cout<<"書き込み失敗"<<endl;
      }
    }//ifs2
  }//ifs1

}//int main
