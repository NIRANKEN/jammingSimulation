#ifndef JTCVC_H_
#define JTCVC_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include "jtmessage.h"
#include "jtvgrp.h"

#include "nr.h"
#include "MT.h"


namespace JT
{
  //--------------------//
  //------Eig func------//
  //---(in jteig.cpp)---//
  //--------------------//
  inline int sgn(DP x);  
  inline void innerCMC2(DP &four,DP &four_comp,DP &two,DP sq);
  inline void CMC2calc(DP &CMnum,DP &CMnum1,DP &CMnum2,DP two,DP four,DP four1,DP four2,bool &IPRerror,DP ratTH);
  inline void calcModeQuantity(Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,int Prt1,int Prt2,DP rt,bool &IPRerror,int seednum,DP phi);
  inline void OPcalc(DP sum_C2dtheta,int N, DP &op);
  inline double CumulativeNumber(Vec_I_DP &Eval,int DN,DP EPS,bool &b);
  inline double derive_renomalizeFactor(Mat_IO_DP &Emat,int modenum,int D,int PN,DP m_inv,int Nsmall);
  inline void derive_sqEigvec(Mat_IO_DP &Emat,Vec_IO_DP &v,int modenum,int D,int Pn,DP fact,DP &sq);
  inline void derive_innerIPRandSPR(DP &two,DP &four,DP &four1,DP &four2,DP &spr,int Pn,int Nsmall,DP sq);
  inline void write_modeQ(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP EPS);  
  inline void write_modeQ_CVC(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP OP,int n_c,DP EPS);
  namespace dim2
  {
    inline void ACcalc(int n_cluster,DP &meantheta,DP theta2,DP &sgm2theta);
    inline void innerAC_deriveMEAN(Vec_I_DP &eigvec,int num,int D,DP &meantheta,DP EPS,int &n_cluster,ofstream &ofs);
    inline void innerAC_deriveVAR(Vec_I_DP &eigvec,int num,int D,DP meantheta,DP &theta2,DP EPS);
    inline void calcPerMode(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void calcModeQuantity(Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,int Prt1,int Prt2,DP rt,bool &IPRerror,int seednum,DP phi);
    inline void calcModeQuantity_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,bool &IPRerror,int seednum,DP phi);
    inline void deriveMeanDirection(DP &sumtheta,int N,DP (&md)[2]);
    inline void deriveMeanDirection(DP &sumtheta,int N,DP &x,DP &y);
    inline double C2DTheta(Vec_I_DP &eigvec,int num,int D,DP (&md)[2],DP EPS);
    inline void calcPerMode_V(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void calcPerMode_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void write_modeQ_V(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP meanTheta,DP OP,DP EPS);
    
  }
  
  namespace dim3
  {
    inline void ACcalc(int n_cluster,DP &meantheta,DP &meanphi,DP theta2,DP phi2,DP &sgm2theta,DP &sgm2phi);
    inline void innerAC_deriveMEAN(Vec_I_DP &eigvec,int num,int D,DP &meantheta,DP &meanphi,DP EPS,int &n_cluster,ofstream &ofs);
    inline void innerAC_deriveVAR(Vec_I_DP &eigvec,int num,int D,DP meantheta,DP meanphi,DP &theta2,DP &phi2,DP EPS);
    inline void calcPerMode(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void calcModeQuantity(Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,int Prt1,int Prt2,DP rt,bool &IPRerror,int seednum,DP phi);
    inline void calcModeQuantity_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP Lz,bool &IPRerror,int seednum,DP phi);
    inline void deriveMeanDirection(DP &sumtheta,DP &sumphi,int N,DP (&md)[3]);
    inline void deriveMeanDirection(DP &sumtheta,DP &sumphi,int N,DP &x,DP &y,DP &z);
    inline double C2DTheta(Vec_I_DP &eigvec,int num,int D,DP (&md)[3],DP EPS);
    inline void calcPerMode_V(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void calcPerMode_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP Lz,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi);
    inline void write_modeQ_V(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP meanTheta,DP meanTheta2,DP OP,DP EPS);
  }
}

//--------------------------------------------
//Derivation function for DOS, IPR, and so on.
//--------------------------------------------
inline int JT::sgn(DP x)
{
  if(x>=0)
    return 1;
  else
    return -1;
}

inline void JT::innerCMC2(DP &four,DP &four_comp,DP &two,DP sq)
{
  DP tmp2=sq*sq;
  four+=tmp2;
  four_comp+=tmp2;
  two+=sq;
}
inline void JT::CMC2calc(DP &CMnum,DP &CMnum1,DP &CMnum2,DP two,DP four,DP four1,DP four2,bool &IPRerror,DP ratTH)
{
  two*=two;
  two=1.0/two;
  CMnum=four*two;
  CMnum1=four1*two;
  CMnum2=four2*two;
  if(CMnum>0.9 && CMnum<ratTH)
    IPRerror=true;
}
inline double JT::CumulativeNumber(Vec_I_DP &Eval,int DN,DP EPS,bool &b)
{
  int cum_num=0;
  for(int i=0;i<DN;i++) {
    if(Eval[i]<-EPS) {
      b=false;
      return 0.0;
    }
    else if(fabs(Eval[i])>EPS) {
      cum_num+=1;
    }
  }
  return 1.0/cum_num;
}
inline void JT::dim2::calcModeQuantity(Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,int Prt1,int Prt2,DP rt,bool &IPRerror,int seednum,DP phi)
{//sortした後の固有値、固有ベクター行列に対して適用.
 //規格化、固有値チェック、IPR,SmallParticleRatio、累積分布、書き込み
  const int DN=Eval.size();
  DP EPS=numeric_limits<double>::epsilon(),cum=1.0,cumfact;
  ofstream wrmode;
  string wrname;
  setOFSeigmethod(seednum,phi,wrname);
  wrmode.open(wrname.data());
  
  cumfact=CumulativeNumber(Eval,DN,EPS,eigplus);
  if(eigplus==false){
    return;
  }
  else {
    for(int i=0;i<DN;i++) {//per modenumber
      calcPerMode(Emat,Eval[i],i,D,Prt1,Prt2,rt,cum,cumfact,IPRerror,wrmode,EPS,seednum,phi);
      if(IPRerror) {
	break;
      }
    }
  }
}
inline void JT::dim2::calcModeQuantity_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,bool &IPRerror,int seednum,DP phi)
{//sortした後の固有値、固有ベクター行列に対して適用.
 //規格化、固有値チェック、IPR,SmallParticleRatio、累積分布、書き込み
  const int DN=Eval.size();
  DP EPS=numeric_limits<double>::epsilon(),cum=1.0,cumfact;
  ofstream wrmode;
  string wrname;
  setOFSeigmethod(seednum,phi,wrname);
  wrmode.open(wrname.data());
  
  cumfact=CumulativeNumber(Eval,DN,EPS,eigplus);
  if(eigplus==false){
    return;
  }
  else {
    for(int i=0;i<DN;i++) {//per modenumber
      calcPerMode_CVC(z,Emat,Eval[i],i,D,R,Prt1,Prt2,rt,Lx,Ly,cum,cumfact,IPRerror,wrmode,EPS,seednum,phi);
      if(IPRerror) {
	break;
      }
    }
  }
}
inline void JT::dim3::calcModeQuantity(Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,int Prt1,int Prt2,DP rt,bool &IPRerror,int seednum,DP phi)
{//sortした後の固有値、固有ベクター行列に対して適用.
 //規格化、固有値チェック、IPR,SmallParticleRatio、累積分布、書き込み
  const int DN=Eval.size();
  DP EPS=numeric_limits<double>::epsilon(),cum=1.0,cumfact;
  ofstream wrmode;
  string wrname;
  setOFSeigmethod(seednum,phi,wrname);
  wrmode.open(wrname.data());

  cumfact=CumulativeNumber(Eval,DN,EPS,eigplus);
  if(eigplus==false){
    return;
  }
  else {
    for(int i=0;i<DN;i++) {//per modenumber
      calcPerMode(Emat,Eval[i],i,D,Prt1,Prt2,rt,cum,cumfact,IPRerror,wrmode,EPS,seednum,phi);
      if(IPRerror) {
	break;
      }
    }
  }
}
inline void JT::dim3::calcModeQuantity_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,Vec_I_DP &Eval,bool &eigplus,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP Lz,bool &IPRerror,int seednum,DP phi)
{//sortした後の固有値、固有ベクター行列に対して適用.
 //規格化、固有値チェック、IPR,SmallParticleRatio、累積分布、書き込み
  const int DN=Eval.size();
  DP EPS=numeric_limits<double>::epsilon(),cum=1.0,cumfact;
  ofstream wrmode;
  string wrname;
  setOFSeigmethod(seednum,phi,wrname);
  wrmode.open(wrname.data());
  
  cumfact=CumulativeNumber(Eval,DN,EPS,eigplus);
  if(eigplus==false){
    return;
  }
  else {
    for(int i=0;i<DN;i++) {//per modenumber
      calcPerMode_CVC(z,Emat,Eval[i],i,D,R,Prt1,Prt2,rt,Lx,Ly,Lz,cum,cumfact,IPRerror,wrmode,EPS,seednum,phi);
      if(IPRerror) {
	break;
      }
    }
  }
}
inline void JT::dim2::calcPerMode(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  if(D==2) {
    m_inv=1.0/rt;
  }
  else {
    cerr<<"seed:"<<seednum<<", PHI:"<<phi<<"でcalcPerMode-Error"<<endl;
    exit(1);
  }
  DP C_inv;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;
  Vec_DP v(DN);

  IPRerror=false;
  
  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);

  //renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
  }
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }
  write_modeQ(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,EPS);
}
inline void JT::dim3::calcPerMode(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  if(D==3) {
    m_inv=1.0/sqrt(rt*rt*rt);
  }
  else {
    cerr<<"seed:"<<seednum<<", PHI:"<<phi<<"でcalcPerMode-Error"<<endl;
    exit(1);
  }
  DP C_inv;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;
  Vec_DP v(DN);
  IPRerror=false;
  
  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);
  
  //renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
  }
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }

  write_modeQ(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,EPS);
}
inline void JT::dim2::calcPerMode_V(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  if(D==2) {
    m_inv=1.0/rt;
  }
  else {
    cerr<<""<<endl;
    exit(1);
  }
  const int dim=2;
  DP C_inv;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;
  DP mtheta=0.0;
  int n_c=0;
  Vec_DP v(DN);
  DP meanDirection[dim],C2=0.0,OP;
  ofstream ofdist;
  string distname;
  setOFSmode(seednum,phi,modenum,distname);
  ofdist.open(distname.data());
  IPRerror=false;

  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);

  //renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
    innerAC_deriveMEAN(v,i,D,mtheta,EPS,n_c,ofdist);
  }
  deriveMeanDirection(mtheta,n_c,meanDirection);
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }
  for(int i=0;i<PN;i++) {
    C2+=C2DTheta(v,i,D,meanDirection,EPS);
  }
  ofdist.close();
  OPcalc(C2,n_c,OP);
  write_modeQ_V(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,mtheta,OP,EPS);
}
inline void JT::dim3::calcPerMode_V(Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,int Prt1,int Prt2,DP rt,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  if(D==3) {
    m_inv=1.0/sqrt(rt*rt*rt);
  }
  else {
    cerr<<""<<endl;
    exit(1);
  }
  const int dim=3;
  DP C_inv;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;
  DP mtheta=0.0;
  DP mtheta2=0.0;
  DP meanDirection[dim],C2=0.0,OP;
  int n_c=0;
  Vec_DP v(DN);
  ofstream ofdist;
  string distname;
  setOFSmode(seednum,phi,modenum,distname);
  ofdist.open(distname.data());
  IPRerror=false;

  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);
  
  //renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
    innerAC_deriveMEAN(v,i,D,mtheta,mtheta2,EPS,n_c,ofdist);
  }

  deriveMeanDirection(mtheta,mtheta2,n_c,meanDirection);
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }

  for(int i=0;i<PN;i++) {
    C2+=C2DTheta(v,i,D,meanDirection,EPS);
  }
  ofdist.close();
  OPcalc(C2,n_c,OP);
  write_modeQ_V(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,mtheta,mtheta2,OP,EPS);
}
inline void JT::dim2::calcPerMode_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  const int dim=2;
  if(D==dim) {
    m_inv=1.0/rt;
  }
  else {
    cerr<<""<<endl;
    exit(1);
  }
  DP C_inv,OPm=0.0;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;
  
  Vec_DP v(DN);
  ofstream ofdist;
  string distname;
  setOFSmode(seednum,phi,modenum,distname);
  ofdist.open(distname.data());
  IPRerror=false;


  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);
  
  //renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
  }
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }

  //~~~//
  Vec_INT att(PN);
  int attmax=0;
  JT::dim2::searchCoCluster(z,Emat,modenum,D,R,rt,Prt1,Prt2,Lx,Ly,att,attmax);
  //Groupingが存在する場合.
  if(attmax>0) {
    int Am=attmax+1,I;
    int n_c[Am];
    DP mtheta[Am];
    DP meanDirection[dim*Am],C2[Am],OP[Am],mDtmp[dim];

    //initialize...
    for(int l=0;l<=attmax;l++) {
      mtheta[l]=meanDirection[dim*l]=meanDirection[dim*l+1]=meanDirection[dim*l+2]=C2[l]=OP[l]=0.0;
      n_c[l]=0;
    }
    for(int i=0;i<PN;i++) {
      I=att[i];
      if(I>0) {
	innerAC_deriveMEAN(v,i,D,mtheta[I],EPS,n_c[I],ofdist);//groupのattributeごとで平均をとる.
      }
    }
    for(int l=1;l<=attmax;l++) {
      deriveMeanDirection(mtheta[l],n_c[l],meanDirection[dim*l],meanDirection[dim*l+1]);
    }
    //groupのattributeごとで平均方位をもとめる.
    for(int i=0;i<PN;i++) {
      I=att[i];
      if(I>0) {
	for(int k=0;k<dim;k++) {
	  mDtmp[k]=meanDirection[dim*I+k];//working var
	}
	C2[I]+=C2DTheta(v,i,D,mDtmp,EPS);
	//groupのattributeごとでcos2の和を求める.
      }
    }
    ofdist.close();
  
    for(int l=1;l<=attmax;l++) {
      OPcalc(C2[l],n_c[l],OP[l]);//groupのattributeごとでorder parameterを求める.
      OPm+=OP[l];
      cout<<OP[l]<<endl;
      //groupのattributeごとの記述をする.
    }
    OPm/=attmax;//Order parameterのグループ平均を求める. <- -nanの原因??
  }
  else {
    OPm=-1.0;
  }
  write_modeQ_CVC(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,OPm,attmax,EPS);
}

inline void JT::dim3::calcPerMode_CVC(Vec_I_DP &z,Mat_IO_DP &Emat,DP Eval_comp,int modenum,int D,DP R,int Prt1,int Prt2,DP rt,DP Lx,DP Ly,DP Lz,DP &cm,DP cmfact,bool &IPRerror,ofstream &ofs,DP EPS,int seednum,DP phi)
{
  int DN=Emat.ncols(),PN=DN/D,Nsmall=(Prt1*PN)/(Prt1+Prt2);
  DP m_inv;
  if(D==3) {
    m_inv=1.0/sqrt(rt*rt*rt);
  }
  else {
    cerr<<""<<endl;
    exit(1);
  }
  const int dim=3;
  DP C_inv,OPm=0.0;
  DP two=0.0,four=0.0,four1=0.0,four2=0.0,sq,CMnum,CMnum1,CMnum2,rat_threshold=1.0-EPS;
  DP spr=0.0;

  Vec_DP v(DN);
  ofstream ofdist;
  string distname;
  setOFSmode(seednum,phi,modenum,distname);
  ofdist.open(distname.data());
  IPRerror=false;
  
  //1. pre renormalize & times mass factor
  C_inv=derive_renomalizeFactor(Emat,modenum,D,PN,m_inv,Nsmall);
  
  //2. renormalize, IPR, SmallParticleRatio
  for(int i=0;i<PN;i++) {
    derive_sqEigvec(Emat,v,modenum,D,i,C_inv,sq);
    derive_innerIPRandSPR(two,four,four1,four2,spr,i,Nsmall,sq);
  }
  CMC2calc(CMnum,CMnum1,CMnum2,two,four,four1,four2,IPRerror,rat_threshold);
  if(IPRerror) {
    return;
  }
  //~~~//
  Vec_INT att(PN);
  int attmax=0;
  JT::dim3::searchCoCluster(z,Emat,modenum,D,R,rt,Prt1,Prt2,Lx,Ly,Lz,att,attmax);
  if(attmax>0) {
    int Am=attmax+1,I;
    int n_c[Am];
    DP mtheta[Am];
    DP mtheta2[Am];
    DP meanDirection[dim*Am],C2[Am],OP[Am],mDtmp[dim];
    
  
    //initialize...
    for(int l=0;l<=attmax;l++) {
      mtheta[l]=mtheta2[l]=meanDirection[dim*l]=meanDirection[dim*l+1]=meanDirection[dim*l+2]=C2[l]=OP[l]=0.0;
      n_c[l]=0;
    }
    for(int i=0;i<PN;i++) {
      I=att[i];
      if(I>0) {
	innerAC_deriveMEAN(v,i,D,mtheta[I],mtheta2[I],EPS,n_c[I],ofdist);//groupのattributeごとで平均をとる.
      }
    }
    for(int l=1;l<=attmax;l++) {
      deriveMeanDirection(mtheta[l],mtheta2[l],n_c[l],meanDirection[dim*l],meanDirection[dim*l+1],meanDirection[dim*l+2]);
    }
    //groupのattributeごとで平均方位をもとめる.
    for(int i=0;i<PN;i++) {
      I=att[i];
      if(I>0) {
	for(int k=0;k<dim;k++) {
	  mDtmp[k]=meanDirection[dim*I+k];//working var
	}
	C2[I]+=C2DTheta(v,i,D,mDtmp,EPS);
	//groupのattributeごとでcos2の和を求める.
      }
    }
    ofdist.close();
    for(int l=1;l<=attmax;l++) {
      OPcalc(C2[l],n_c[l],OP[l]);//groupのattributeごとでorder parameterを求める.
      OPm+=OP[l];
      cout<<OP[l]<<endl;
      //groupのattributeごとの記述をする.
    }
    OPm/=attmax;//Order parameterのグループ平均を求める.
  }
  else {
    OPm=-1.0;
  }
  
  write_modeQ_CVC(ofs,Eval_comp,CMnum,CMnum1,CMnum2,spr,cm,cmfact,OPm,attmax,EPS);
}
inline void JT::dim2::ACcalc(int n_cluster,DP &meantheta,DP theta2,DP &sgm2theta)
{
  DP n_inv=1.0/n_cluster;
  //  meantheta*=n_inv;
  theta2*=n_inv;
  sgm2theta=theta2-meantheta*meantheta;
  return;
}
inline void JT::dim3::ACcalc(int n_cluster,DP &meantheta,DP &meanphi,DP theta2,DP phi2,DP &sgm2theta,DP &sgm2phi)
{
  DP n_inv=1.0/n_cluster;
  //  meantheta*=n_inv;
  //  meanphi*=n_inv;
  theta2*=n_inv;
  phi2*=n_inv;
  sgm2theta=theta2-meantheta*meantheta;
  sgm2phi=phi2-meanphi*meanphi;
  return;
}
inline void JT::dim2::deriveMeanDirection(DP &sumtheta,int N,DP (&md)[2])
{
  DP Ninv=1.0/N;
  sumtheta*=Ninv;
  DP st=sin(sumtheta),ct=cos(sumtheta);
  md[0]=ct;
  md[1]=st;
  return;
}
inline void JT::dim2::deriveMeanDirection(DP &sumtheta,int N,DP &x,DP &y)
{
  DP Ninv=1.0/N;
  sumtheta*=Ninv;
  DP st=sin(sumtheta),ct=cos(sumtheta);
  x=ct;
  y=st;
  return;
}
inline void JT::dim3::deriveMeanDirection(DP &sumtheta,DP &sumphi,int N,DP (&md)[3])
{
  DP Ninv=1.0/N;
  sumtheta*=Ninv;
  sumphi*=Ninv;
  DP st=sin(sumtheta),ct=cos(sumtheta);
  DP sp=sin(sumphi),cp=cos(sumphi);
  md[0]=st*cp;
  md[1]=st*sp;
  md[2]=ct;
  return;
}
inline void JT::dim3::deriveMeanDirection(DP &sumtheta,DP &sumphi,int N,DP &x,DP &y,DP &z)
{
  DP Ninv=1.0/N;
  sumtheta*=Ninv;
  sumphi*=Ninv;
  DP st=sin(sumtheta),ct=cos(sumtheta);
  DP sp=sin(sumphi),cp=cos(sumphi);
  x=st*cp;
  y=st*sp;
  z=ct;
  return;

}
inline void JT::OPcalc(DP sum_C2dtheta,int N, DP &op)
{
  DP Ninv=1.0/N;
  op=0.5*(3*Ninv*sum_C2dtheta-1.0);
  return;
}
  
inline void JT::dim2::innerAC_deriveMEAN(Vec_I_DP &eigvec,int num,int D,DP &meantheta,DP EPS,int &n_cluster,ofstream &ofs)
{
  DP r=0.0,r_inv,theta;
  DP x[D],x2[D];
    for(int j=0;j<D;j++) {
      x[j]=eigvec[D*num+j];
      x2[j]=x[j]*x[j];
      r+=x2[j];
    }
    r_inv=1.0/sqrt(r);
    if(r<EPS) {
      //EPSはもっと大きいthresholdでよい.
      //eigvec
      theta=0.0;//zeroで埋めとく.
    }
    else {
	  if(x2[0]<x2[1]) {
	    theta=asin(r_inv*x[1]);
	    if(x[0]<0)
	      theta=sgn(x[1])*(M_PI-theta);
	    meantheta+=theta;
	  }
	  else {
	    theta=sgn(x[1])*acos(r_inv*x[0]);// 0 ~ pi
	    meantheta+=theta;
	  }
      n_cluster++;
    }//r>=EPS
    ofs<<num<<" "<<theta<<endl;
}
inline void JT::dim2::innerAC_deriveVAR(Vec_I_DP &eigvec,int num,int D,DP meantheta,DP &theta2,DP EPS)
{ 
  DP r=0.0,r_inv,theta;
  DP x[D],x2[D],pi=M_PI,dtheta;
  int shift;
    for(int j=0;j<D;j++) {
      x[j]=eigvec[D*num+j];
      x2[j]=x[j]*x[j];
      r+=x2[j];
    }
    r_inv=1.0/sqrt(r);
    if(r<EPS) {
      //EPSはもっと大きいthresholdでよい.
      //eigvec
      theta=0.0;//zeroで埋めとく.
    }
    else {
	  if(x2[0]<x2[1]) {
	    theta=asin(r_inv*x[1]);//-pi/2 ~ pi/2 -> 
	    if(x[0]<0)
	      theta=sgn(x[1])*(M_PI-theta);// -> -pi ~ pi
	    dtheta=theta-meantheta;//平均値からの距離がpiより小さくなるようにシフト
	    shift=(dtheta<-pi) - (dtheta>pi);
	    if(shift)
	      theta+=shift*pi;
	    theta2+=theta*theta;
	  }
	  else {
	    theta=sgn(x[1])*acos(r_inv*x[0]);// 0 ~ pi -> -pi ~ pi
	    dtheta=theta-meantheta;//平均値からの距離がpiより小さくなるようにシフト
	    shift=(dtheta<-pi) - (dtheta>pi);
	    if(shift)
	      theta+=shift*pi;
	    theta2+=theta*theta;
	  }
    }//r>=EPS
}
inline void JT::dim3::innerAC_deriveMEAN(Vec_I_DP &eigvec,int num,int D,DP &meantheta,DP &meanphi,DP EPS,int &n_cluster,ofstream &ofs)
{
  DP r=0.0,r_inv,sth_inv,theta,phi,pi=M_PI;
  DP x[D],x2[D];
    for(int j=0;j<D;j++) {
      x[j]=eigvec[D*num+j];
      x2[j]=x[j]*x[j];
      r+=x2[j];
    }
    r_inv=1.0/sqrt(r);
    if(r<EPS) {
      //EPSはもっと大きいthresholdでよい.
      //eigvec
      theta=0.0;//zeroで埋めとく.
      phi=0.0;
    }
    else {
      if(fabs(r_inv*x[2])>=1.0) {
	theta=0.0;
	phi=0.0;
	//x-y平面のみを使って(射影して)phiを求めるmethod.
      }
      else {
	theta=acos(r_inv*x[2]);
	meantheta+=theta;
	sth_inv=1.0/sin(theta);

	if(x2[0]+x2[1]<EPS) {
	  phi=0.0;
	}
	else {
	  if(x2[0]<x2[1]) {
	    phi=asin(r_inv*sth_inv*x[1]);//-pi/2 ~ pi/2 -> 
	    if(x[0]<0)
	      phi=sgn(x[1])*(pi-phi);// -> -pi ~ pi
	    meanphi+=phi;
	  }
	  else {
	    phi=sgn(x[1])*acos(r_inv*sth_inv*x[0]);// 0 ~ pi -> -pi ~ pi
	    meanphi+=phi;
	  }
	}
      }//x2(z)>=EPS
      n_cluster++;
    }//r>=EPS
    ofs<<num<<" "<<theta<<" "<<phi<<endl;
}
inline void JT::dim3::innerAC_deriveVAR(Vec_I_DP &eigvec,int num,int D,DP meantheta,DP meanphi,DP &theta2,DP &phi2,DP EPS)
{
  DP r=0.0,r_inv,sth_inv,theta,phi,dtheta,dphi,pi=M_PI;
  DP x[D],x2[D];
  int shift;
    for(int j=0;j<D;j++) {
      x[j]=eigvec[D*num+j];
      x2[j]=x[j]*x[j];
      r+=x2[j];
    }
    r_inv=1.0/sqrt(r);
    if(r<EPS) {
      //EPSはもっと大きいthresholdでよい.
      //eigvec
      theta=0.0;//zeroで埋めとく.
      phi=0.0;
    }
    else {
      if(fabs(r_inv*x[2])>=1.0) {
	theta=0.0;
	phi=0.0;
      }
      else {
	theta=acos(r_inv*x[2]);
	dtheta=theta-meantheta;//平均値からの距離がpiより小さくなるようにシフト
	shift=(dtheta<-pi) - (dtheta>pi);
	if(shift)
	  theta+=shift*pi;
	theta2+=theta*theta;
	sth_inv=1.0/sin(theta);

	if(x2[0]+x2[1]<EPS) {
	  phi=0.0;
	}
	else {
	  if(x2[0]<x2[1]) {
	    phi=asin(r_inv*sth_inv*x[1]);//-pi/2 ~ pi/2 -> 
	    if(x[0]<0)
	      phi=sgn(x[1])*(M_PI-phi);// -> -pi ~ pi
	    dphi=phi-meanphi;//平均値からの距離がpiより小さくなるようにシフト
	    shift=(dphi<-pi) - (dphi>pi);
	    if(shift)
	      phi+=shift*pi;	    
	    phi2+=phi*phi;
	  }
	  else {
	    phi=sgn(x[1])*acos(r_inv*sth_inv*x[0]);// 0 ~ pi -> -pi ~ pi
	    dphi=phi-meanphi;//平均値からの距離がpiより小さくなるようにシフト
	    shift=(dphi<-pi) - (dphi>pi);
	    if(shift)
	      phi+=shift*pi;
	    phi2+=phi*phi;
	  }
	}
      }//x2(z)>=EPS
    }//r>=EPS
}
inline double JT::dim2::C2DTheta(Vec_I_DP &eigvec,int num,int D,DP (&md)[2],DP EPS)
{
  DP r=0.0,r_inv,ip=0.0;
  DP x;
  for(int j=0;j<D;j++) {
    x=eigvec[D*num+j];
    ip+=x*md[j];
    r+=x*x;
  }
  if(r<EPS) {
    return 0.0;
  }
  else {
    r_inv=1.0/sqrt(r);
    ip=r_inv*ip;
    return ip*ip;
  }
}
inline double JT::dim3::C2DTheta(Vec_I_DP &eigvec,int num,int D,DP (&md)[3],DP EPS)
{
  DP r=0.0,r_inv,ip=0.0;
  DP x;
  for(int j=0;j<D;j++) {
    x=eigvec[D*num+j];
    ip+=x*md[j];
    r+=x*x;
  }
  if(r<EPS) {
    return 0.0;
  }
  else {
    r_inv=1.0/sqrt(r);
    ip=r_inv*ip;
    return ip*ip;
  }
}
inline double JT::derive_renomalizeFactor(Mat_IO_DP &Emat,int modenum,int D,int PN,DP m_inv,int Nsmall)
{
  DP Ecomp,C_rn;
//1. pre renormalize & times mass factor
  for(int i=0;i<PN;i++) {
    if(i<Nsmall) {
      for(int j=0;j<D;j++) {
	Ecomp=Emat[D*i+j][modenum];
	C_rn+=Ecomp*Ecomp;
      }
    }
    else {
      for(int j=0;j<D;j++) {
	Ecomp=Emat[D*i+j][modenum]=m_inv*Emat[D*i+j][modenum];
	C_rn+=Ecomp*Ecomp;
      }
    }
    //eig 負ならばreturnのメソッド,
    //累積分布求めるためのカウント.
  }
  //renormalize factor
  return 1.0/sqrt(C_rn);
}
inline void JT::derive_sqEigvec(Mat_IO_DP &Emat,Vec_IO_DP &v,int modenum,int D,int Pn,DP fact,DP &sq)
{
  sq=0.0;
  for(int j=0;j<D;j++) {
    v[D*Pn+j]=Emat[D*Pn+j][modenum]=fact*Emat[D*Pn+j][modenum];
    sq+=v[D*Pn+j]*v[D*Pn+j];
  }
  return;
}
inline void JT::derive_innerIPRandSPR(DP &two,DP &four,DP &four1,DP &four2,DP &spr,int Pn,int Nsmall,DP sq)
{
  if(Pn>=Nsmall) {//large components
    innerCMC2(four,four2,two,sq);
  }
  else {//small components
    innerCMC2(four,four1,two,sq);
    spr+=sq;
  }
}
inline void JT::write_modeQ(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP EPS)
{
  if(fabs(Eval_comp)>EPS) {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<cum<<endl;
    cum-=cumfact;
  }
  else {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<0.0<<endl;
  }
}
inline void JT::dim2::write_modeQ_V(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP meanTheta,DP OP,DP EPS)
{
  if(fabs(Eval_comp)>EPS) {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<cum<<' '<<meanTheta<<' '<<OP<<endl;
    cum-=cumfact;
  }
  else {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<0.0<<' '<<meanTheta<<' '<<OP<<endl;
  }
}
inline void JT::dim3::write_modeQ_V(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP meanTheta,DP meanTheta2,DP OP,DP EPS)
{
  if(fabs(Eval_comp)>EPS) {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<cum<<' '<<meanTheta<<' '<<meanTheta2<<' '<<OP<<endl;
    cum-=cumfact;
  }
  else {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<0.0<<' '<<meanTheta<<' '<<meanTheta2<<' '<<OP<<endl;
  }
}
inline void JT::write_modeQ_CVC(ofstream &ofs,DP Eval_comp,DP CMnum,DP CMnum1,DP CMnum2,DP SPR,DP &cum,DP cumfact,DP OP,int n_c,DP EPS)
{
  if(fabs(Eval_comp)>EPS) {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<cum<<' '<<OP<<' '<<n_c<<endl;
    cum-=cumfact;
  }
  else {
    ofs<<setprecision(10)<<Eval_comp<<' '<<sqrt(Eval_comp)<<' '<<CMnum<<' '<<CMnum1<<' '<<CMnum2<<' '<<SPR<<' '<<0.0<<' '<<OP<<' '<<n_c<<endl;
  }
}
#endif
