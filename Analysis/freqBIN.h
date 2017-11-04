#ifndef __BIN_H
#define __BIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

namespace binstat
{
  struct iprset
  {
    double sum;
    double sgm;
    double mean;
    double min;
    double max;
    double smallCR_sum;
  };
  void InputStr(string &a,string &b,string &c,string &d) {
    cout<<"本プログラムは,"<<endl;
    cout<<"(2)EigCum0xxxx_\"phi\".txt"<<endl;
    cout<<"の統計平均をテキストにまとめるプログラムです.\n"<<endl;
    cout<<"which \"date\" do you execute the FIRE program??"<<endl;
    cout<<"\"date\" (e.g. 0208)-> ";
    cin>>a;
    cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
    cout<<"->";
    cin>>b;
    cout<<"\nHow many particles?? (e.g. 128)"<<endl;
    cout<<"->";
    cin>>c;
    cout<<"\nwhich dimension?? (2D or 3D)";
    cout<<"->";
    cin>>d;
    return;
  }
  void InputBINrange(double &br);

  void ZeroEigenValprocess(int &freqC);
  void ZeroEigenValWrite(iprset &ipr,iprset &ipr1,iprset &ipr2,int N,double DPHI,double b,double c,double d,double e,double sCR,double &S,double &E,double &M,double &Sln10,double &Mln10,double range,int zeroeig,int &freqC,const int allC,int ifsC,int cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc,bool &zero_searched);


  void innerBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int N,double DPHI,double S,double E,double M,int &freqC,const int allC,int &ifsC,double cum_inv,int &cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc);
  void updateBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double b,double c,double d,double e,double sCR,int N,double DPHI,double &S,double &E,double &M,double &Sln10,double &Mln10,double range,int &freqC,const int allC,int &ifsC,double cum_inv,int &cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc);
  void backToPreIFS(iprset &ipr,iprset &ipr1,iprset &ipr2,int &freqC,int &ifsC,int &cumcnt,int ifsC_tmp,int &freqC_tmp,int cumcnt_tmp,ifstream &ifs,ifstream::pos_type ps_tmp,bool &d_calc);
  void conserveCurrentState(int ifsC,int cumcnt,int &ifsC_tmp,int &cumcnt_tmp,ifstream &ifs,ifstream::pos_type &ps_tmp);
  
    
  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10);
  void updateBINrange(double &S,double &E,double &M,double &Sln10,double &Mln10,double range);

  
  void InitializeIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  void InitializeIPRparameter(iprset &ipr,double c,int &tmpC);
  void ModifyIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  void ModifyIPRparameter(iprset &ipr,double c,int &tmpC);
  void changSampledIPRs(iprset &ipr,iprset &ipr1,iprset& ipr2,bool b);
  


  void InitializeIPRSET(iprset &ipr,double c) {
    ipr.sgm=ipr.min=ipr.max=ipr.sum=c;
    ipr.mean=0.0;
  }

  void ResetIPRSET(iprset &ipr,double T) {
    double c=ipr.sgm;
    ipr.mean=ipr.sum*T;

    //initialize...
    ipr.sgm=pow(log10(c/ipr.mean),2);//ipr.sumが初期のIPR値なので、これを用いる.
    ipr.min=ipr.max=ipr.sum=c; //過去のcで初期化.
  }
  void ModifyIPRSET(iprset &ipr,double c,bool d_calc) {
      ipr.sum+=c;
      if(ipr.min>c)
	ipr.min=c;
      if(ipr.max<c)
	ipr.max=c;
      if(d_calc) {
	ipr.sgm+=pow(log10(c/ipr.mean),2);
      }
  }

  void InitializeBI_IPRs(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int &freqC,bool &d_calc) {
    if(d_calc) {
      freqC=1;
      InitializeIPRSET(ipr,c);
      ipr.smallCR_sum=sCR;
      InitializeIPRSET(ipr1,d);
      InitializeIPRSET(ipr2,e);
      d_calc=false;
    }
    else {
      cerr<<"Cannot initialize why calculating derivation process isn't finished..."<<endl;
      exit(1);
    }
  }
  void ResetBI_IPRs(iprset &ipr,iprset &ipr1,iprset &ipr2,int &freqC,bool d_calc) {
    if(!d_calc) {
      double T=1.0/freqC;
    freqC=1;
    ResetIPRSET(ipr,T);
    ResetIPRSET(ipr1,T);
    ResetIPRSET(ipr2,T);
    }
    else {
      cerr<<"Cannot reset why writing ofs process isn't finished..."<<endl;
      exit(1);
    }
  }
  void ModifyBI_IPRs(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int &freqC,bool d_calc) {
    freqC+=1;
    ModifyIPRSET(ipr,c,d_calc);
    ModifyIPRSET(ipr1,d,d_calc);
    ModifyIPRSET(ipr2,e,d_calc);
    if(d_calc) {
      ipr.smallCR_sum+=sCR;
    }
  }
  
}

#endif
