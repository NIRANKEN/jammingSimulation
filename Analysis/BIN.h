#ifndef __BIN_H
#define __BIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

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
    bool meanSampled;
    double smallCR_sum;
  };
  void InputStr(string &a,string &b,string &c,string &d) {
    // cout<<"本プログラムは,"<<endl;
    // cout<<"(2)EigCum0xxxx_\"phi\".txt"<<endl;
    // cout<<"の統計平均をテキストにまとめるプログラムです.\n"<<endl;
    // cout<<"which \"date\" do you execute the FIRE program??"<<endl;
    // cout<<"\"date\" (e.g. 0208)-> ";
    cin>>a;
    // cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
    // cout<<"->";
    cin>>b;
    // cout<<"\nHow many particles?? (e.g. 128)"<<endl;
    // cout<<"->";
    cin>>c;
    // cout<<"\nwhich dimension?? (2D or 3D)";
    // cout<<"->";
    cin>>d;
    return;
  }
  void InputBINrange(double &br);
  void ZeroEigenValprocess(double S,double E,double M,int zeroeig,double allC,ofstream &ofs,int N,double DPHI,ifstream &ifs,ifstream::pos_type &ps);
  void innerBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,double S,double E,double M,int &tmpC,double allC,ofstream &ofs,int &cnt,double cum,int cumcnt,int N,double DPHI,ifstream &ifs,ifstream::pos_type &ps,int &cnt_b);
  void updateBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double b,double c,double d,double e,double sCR,double &S,double &E,double &M,double &Sln10,double &Mln10,int &tmpC,double allC,double range,ofstream &ofs,int &cnt,double cum,int cumcnt,int N,double DPHI,ifstream &ifs,ifstream::pos_type &ps,int &cnt_b);
  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10);
  void updateBINrange(double &S,double &E,double &M,double &Sln10,double &Mln10,double range);
  void InitializeIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  void InitializeIPRparameter(iprset &ipr,double c,int &tmpC);
  void ModifyIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  void ModifyIPRparameter(iprset &ipr,double c,int &tmpC);
  void changSampledIPRs(iprset &ipr,iprset &ipr1,iprset& ipr2,bool b);
  
  void InitializeIPRSET(iprset &ipr) {
    ipr.sgm=ipr.min=ipr.max=ipr.sum=0.0;
    ipr.mean=0.0;
    ipr.smallCR_sum=0.0;
    ipr.meanSampled=false;
  }
  void ResetIPRSET(iprset &ipr,double c) {
    if(ipr.meanSampled==true) {
      ipr.mean=ipr.min=ipr.max=ipr.sum=c;
      ipr.meanSampled=false;
    }
    else {
      ipr.sgm=pow(log10(ipr.sum/ipr.mean),2);//ipr.sumが初期のIPR値なので、これを用いる.
      ipr.meanSampled=true;
    }
  }
  void ResetIPRSET(iprset &ipr,double c,double sCR) {
    if(ipr.meanSampled==true) {
      ipr.mean=ipr.min=ipr.max=ipr.sum=c;
      ipr.smallCR_sum=sCR;
      ipr.meanSampled=false;
    }
    else {
      ipr.sgm=pow(log10(ipr.sum/ipr.mean),2);//ipr.sumが初期のIPR値なので、これを用いる.
      ipr.meanSampled=true;
    }
  }
  void ModifyIPRSET(iprset &ipr,double c) {
    if(ipr.meanSampled==true) {      
      ipr.sum+=c;
      if(ipr.min>c)
	ipr.min=c;
      if(ipr.max<c)
	ipr.max=c;
      ipr.sgm+=pow(log10(c/ipr.mean),2);
    }
    else {
      ipr.mean+=c;
    }
  }
  void ModifyIPRSET(iprset &ipr,double c,double sCR) {
    if(ipr.meanSampled==true) {      
      ipr.sum+=c;
      ipr.smallCR_sum+=sCR;
      if(ipr.min>c)
	ipr.min=c;
      if(ipr.max<c)
	ipr.max=c;
      ipr.sgm+=pow(log10(c/ipr.mean),2);
    }
    else {
      ipr.mean+=c;
    }
  }

  void ResetBI_IPRs(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int &tmpC) {
    tmpC=1;
    ResetIPRSET(ipr,c,sCR);
    ResetIPRSET(ipr1,d);
    ResetIPRSET(ipr2,e);
  }
  void ModifyBI_IPRs(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int &tmpC) {
    tmpC+=1;
    ModifyIPRSET(ipr,c,sCR);
    ModifyIPRSET(ipr1,d);
    ModifyIPRSET(ipr2,e);
  }
  void changeSampledIPRs(iprset &ipr,iprset &ipr1,iprset& ipr2,bool b) {
    ipr.meanSampled = b;
    ipr1.meanSampled = b;
    ipr2.meanSampled = b;
    return;
  }

  
}







#endif
