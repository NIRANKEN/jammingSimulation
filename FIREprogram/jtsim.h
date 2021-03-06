#ifndef _JTSIM_H_
#define _JTSIM_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include "nr.h"
#include "jttool.h"

namespace JT
{
  //--------------------------//
  //Parameter Setting Function//
  //-------(jtsim.cpp)--------//
  //--------------------------//
    
  void InitializeSimulationparameter(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP L,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT);
  void InitializeSimulationparameter(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP L,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,int &RT);
  
  void InitializeFIREparameter(DP &T,DP &dmpt,DP &tmax,DP &dphi,DP dphiinit,DP &noise_strength,int &ITERfire);
  void ReRelaxation(int &VVITER,DP &noise_strength,int loop);
  void ReRelaxation(int &VVITER,DP &noise_strength,int loop,const int vviter_times);
  void OutputForQt(Vec_I_DP &z, int dim,int PN,DP phi,DP rt,int Prt1,int Prt2,int snum);
  
  
  namespace dim2
  {
    void InitializeSimulationparameter2D(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP Lx,DP Ly,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT);
    inline void forwardtoPHI2D(Vec_I_DP &z,Vec_IO_DP &ztmp,DP &PHI,DP DPHI,DP &R,DP C,int &loop,int D,int &RT);
    inline void backtoPreviousPHI2D(Vec_IO_DP &z,Vec_I_DP &ztmp,DP &PHI,DP &DPHI,DP &R,DP C,DP &Tmax,int & loop, int D,int &RT);
    void OutputForQt(Vec_I_DP &z, DP Lx,DP Ly,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum);
  }
  namespace dim3
  {
    void InitializeSimulationparameter3D(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP Lx,DP Ly,DP Lz,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT);
    inline void backtoPreviousPHI3D(Vec_IO_DP &z,Vec_I_DP &ztmp,DP &PHI,DP &DPHI,DP &R,DP C,DP &Tmax,int &loop, int D,int &RT);
    inline void forwardtoPHI3D(Vec_I_DP &z,Vec_IO_DP &ztmp,DP &PHI,DP DPHI,DP &R,DP C,int &loop,int D,int &RT);
    void OutputForQt(Vec_I_DP &z, DP Lx,DP Ly,DP Lz,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum);
  }
}


void JT::InitializeSimulationparameter(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP L,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,int &RT) {
  
  phi=phistart;
  meig=true;
  nreig=0;
  loop=0;
  RT=0;
  if(D==2) {
    C=JT::dim2::CtoDerivePHI2D(L,rt,PN,Prt1,Prt2,D);
    R=C*sqrt(phi);
  }
  else if(D==3) {
    C=JT::dim3::CtoDerivePHI3D(L,rt,PN,Prt1,Prt2,D);
    R=C*pow(phi,0.333333333333333);
  }
  else {
    cerr<<"make error."<<endl;
    exit(1);
  }
  return;
}
void JT::InitializeSimulationparameter(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP L,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT) {
  
  phi=phistart;
  meig=true;
  nreig=0;
  loop=0;
  isInit=false;
  RT=0;
  if(D==2) {
    C=JT::dim2::CtoDerivePHI2D(L,rt,PN,Prt1,Prt2,D);
    R=C*sqrt(phi);
  }
  else if(D==3) {
    C=JT::dim3::CtoDerivePHI3D(L,rt,PN,Prt1,Prt2,D);
    R=C*pow(phi,0.333333333333333);
  }
  else {
    cerr<<"make error."<<endl;
    exit(1);
  }
  return;
}
void JT::dim2::InitializeSimulationparameter2D(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP Lx,DP Ly,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT)
{
  phi=phistart;
  meig=true;
  nreig=0;
  loop=0;
  isInit=false;
  RT=0;
  if(D==2) {
    C=JT::dim2::CtoDerivePHI2D(Lx,Ly,rt,PN,Prt1,Prt2,D);
    R=C*sqrt(phi);
  }
  else {
    cerr<<"make error."<<endl;
    exit(1);
  }
  return;
}
void JT::dim3::InitializeSimulationparameter3D(DP &phi,DP phistart,bool &meig,int &nreig,int &loop,DP &C,DP Lx,DP Ly,DP Lz,DP rt,int PN,int Prt1,int Prt2,int D,DP &R,bool &isInit,int &RT)
{
  phi=phistart;
  meig=true;
  nreig=0;
  loop=0;
  isInit=false;
  RT=0;
  if(D==3) {
    C=JT::dim3::CtoDerivePHI3D(Lx,Ly,Lz,rt,PN,Prt1,Prt2,D);
    R=C*pow(phi,0.333333333333333);
  }
  else {
    cerr<<"make error."<<endl;
    exit(1);
  }
  return;
}


void JT::InitializeFIREparameter(DP &T,DP &dmpt,DP &tmax,DP &dphi,DP dphiinit,DP &noise_strength,int &ITERfire)
{
  T=1.0e-2;
  dmpt=1.0e-1;
  tmax=T*10;
  dphi=dphiinit;
  noise_strength=0.01;
  ITERfire=5;
  return;
}

void JT::ReRelaxation(int &VVITER,DP &noise_strength,int loop)
{
  VVITER=500000;
  noise_strength=(loop+1)*0.01;
  return;
}
void JT::ReRelaxation(int &VVITER,DP &noise_strength,int loop,const int vviter_times)
{
  VVITER=vviter_times;
  noise_strength=(loop+1)*0.01;
  return;
}

void JT::OutputForQt(Vec_I_DP &z, int dim,int PN,DP phi,DP rt,int Prt1,int Prt2,int snum)
{
  stringstream ss;
  ss<<setprecision(10)<<"QtOutputZahyo"<<snum<<"_"<<phi<<".txt";
  ofstream ofs(ss.str().data());

  ofs<<setprecision(16)<<dim<<' '<<PN<<' '<<phi<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<endl;
  for(int i=0;i<PN;i++) {
    for(int j=0;j<dim-1;j++)
      ofs<<setprecision(16)<<z[dim*i+j]<<' ';
    ofs<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
  }
}
void JT::dim2::OutputForQt(Vec_I_DP &z,DP Lx,DP Ly,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum)
{
  stringstream ss;
  ss<<setprecision(10)<<"QtOutputZahyo"<<snum<<"_"<<phi<<".txt";
  ofstream ofs(ss.str().data());

  ofs<<setprecision(16)<<dim<<' '<<PN<<' '<<R<<' '<<phi<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<' '<<Lx<<' '<<Ly<<endl;
  for(int i=0;i<PN;i++) {
    for(int j=0;j<dim-1;j++)
      ofs<<setprecision(16)<<z[dim*i+j]<<' ';
    ofs<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
  }
}
void JT::dim3::OutputForQt(Vec_I_DP &z,DP Lx,DP Ly,DP Lz,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum)
{
  stringstream ss;
  ss<<setprecision(10)<<"QtOutputZahyo"<<snum<<"_"<<phi<<".txt";
  ofstream ofs(ss.str().data());

  ofs<<setprecision(16)<<dim<<' '<<PN<<' '<<R<<' '<<phi<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<' '<<Lx<<' '<<Ly<<' '<<Lz<<endl;
  for(int i=0;i<PN;i++) {
    for(int j=0;j<dim-1;j++)
      ofs<<setprecision(16)<<z[dim*i+j]<<' ';
    ofs<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
  }
}


inline void JT::dim2::forwardtoPHI2D(Vec_I_DP &z,Vec_IO_DP &ztmp,DP &PHI,DP DPHI,DP &R,DP C,int &loop,int D,int &RT)
{
  if(checkdim2(D)) {
    PHI+=DPHI;
    R=C*sqrt(PHI);
    ztmp=z;
    loop=0;
    RT=0;
  }
}

inline void JT::dim2::backtoPreviousPHI2D(Vec_IO_DP &z,Vec_I_DP &ztmp,DP &PHI,DP &DPHI,DP &R,DP C,DP &Tmax,int & loop, int D,int &RT)
{
  //現在のunjammed stateの座標を棄却,fabs(DeltaPHI)の条件は求めたいPHIJの精度で。
  if(checkdim2(D)) {
    z=ztmp;
    PHI-=DPHI*0.9;
    R=C*sqrt(PHI);
    DPHI*=0.1;
    Tmax*=1.5;
    if(Tmax>1.0)
      Tmax=0.95;
    loop=0;
    RT=0;
  }
}
inline void JT::dim3::forwardtoPHI3D(Vec_I_DP &z,Vec_IO_DP &ztmp,DP &PHI,DP DPHI,DP &R,DP C,int &loop,int D,int &RT)
{
  if(checkdim3(D)) {
    PHI+=DPHI;
    R=C*pow(PHI,0.333333333333333);
    ztmp=z;
    loop=0;
    RT=0;
  }
}
inline void JT::dim3::backtoPreviousPHI3D(Vec_IO_DP &z,Vec_I_DP &ztmp,DP &PHI,DP &DPHI,DP &R,DP C,DP &Tmax,int &loop,int D,int &RT)
{
  if(checkdim3(D)) {
    z=ztmp;
    PHI-=DPHI*0.9;
    R=C*pow(PHI,0.333333333333333);
    DPHI*=0.1;
    Tmax*=1.5;
    if(Tmax>1.0)
      Tmax=0.95;
    loop=0;
    RT=0;
  }
}


#endif
