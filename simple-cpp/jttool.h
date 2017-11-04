#ifndef _JTTOOL_H_
#define _JTTOOL_H_

#include "nr.h"
#include "MT.h"

namespace JT
{
  //--------------------------//
  //--Tools for JTsimulation--//
  //-------(jttool.cpp)-------//
  //--------------------------//

  inline void PutZahyoRandomly(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP L,int seednum);
  inline void PeriodicMove(Vec_IO_DP &zahyo,DP L);
  
  inline void updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio,int DN,int D);
  inline void updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int DN,int D);
  inline void updateRadius(int i,DP &R,DP ratio,int Pratio,int DN);
  inline void updateRadius(int i,DP &R,DP ratio,int Pratio1,int Pratio2,int DN);
  namespace dim2
  {
    inline void PutZahyoRandomly2D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,int seednum);
    inline void PeriodicMove2D(Vec_IO_DP &zahyo,DP Lx,DP Ly);
    inline bool checkdim2(int D);
    inline DP CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt,int D);
    inline DP CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt1,int Prt2,int D);
    inline DP CtoDerivePHI2D(DP Lx,DP Ly,DP rt,DP PN, int Prt,int D);
    inline DP CtoDerivePHI2D(DP Lx,DP Ly,DP rt,DP PN, int Prt1,int Prt2,int D);
    inline void updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio,int DN);
    inline void updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int DN);
    inline void OutofPeriodicboundary2D(DP &relative_x,DP &relative_y,DP L,DP sgm);
    inline void OutofPeriodicboundary2D(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm);
    inline void OutofPeriodicboundary2D_qt(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm,int &p1,int &p2);
  }
  namespace dim3
  {
    inline void PeriodicMove3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz);
    inline void PutZahyoRandomly3D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,DP Lz,int seednum);
    inline bool checkdim3(int D);
    inline DP CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt,int D);
    inline DP CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt1,int Prt2,int D);
    inline DP CtoDerivePHI3D(DP Lx,DP Ly,DP Lz,DP rt,DP PN,int Prt,int D);
    inline DP CtoDerivePHI3D(DP Lx,DP Ly,DP Lz,DP rt,DP PN,int Prt1,int Prt2,int D);
    inline void updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio,int DN);
    inline void updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int DN);
    inline void OutofPeriodicboundary3D(DP &relative_x,DP &relative_y,DP &relative_z,DP L,DP sgm);
    inline void OutofPeriodicboundary3D(DP &relative_x,DP &relative_y,DP &relative_z,DP Lx,DP Ly,DP Lz,DP sgm);
  }

  inline void showHESS(Mat_I_DP &H);
}


inline void JT::PutZahyoRandomly(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP L,int seednum)
{
  int N=zahyo.size();
  MT::init_genrand(seednum);
  for(int i=0;i<N;i++)
    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*L;
}
inline void JT::dim2::PutZahyoRandomly2D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,int seednum)
{
 int N=zahyo.size();
  MT::init_genrand(seednum);
  for(int i=0;i<N;i+=2) {
    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Lx;
    zahyotmp[i+1]=zahyo[i+1]=MT::genrand_real1()*Ly;
  }
}
inline void JT::dim3::PutZahyoRandomly3D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,DP Lz,int seednum)
{
  int N=zahyo.size();
  MT::init_genrand(seednum);
  for(int i=0;i<N;i+=3) {
    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Lx;
    zahyotmp[i+1]=zahyo[i+1]=MT::genrand_real1()*Ly;
    zahyotmp[i+2]=zahyo[i+2]=MT::genrand_real1()*Lz;
  }
}

inline void JT::PeriodicMove(Vec_IO_DP &zahyo,DP L)
{
  int N=zahyo.size();
  DP tmpL =1.0/L;
  for(int i=0;i<N;i++) {
    if(zahyo[i]<0 || zahyo[i]>L)
      zahyo[i]+=-L*(static_cast<int>(zahyo[i]*tmpL));
    if(zahyo[i]<0)
      zahyo[i]+=L;
  }
}
inline void JT::dim2::PeriodicMove2D(Vec_IO_DP &zahyo,DP Lx,DP Ly)
{
  int N=zahyo.size();
  DP tmpLx =1.0/Lx,tmpLy=1.0/Ly;
  for(int i=0;i<N;i+=2) {
    if(zahyo[i]<0 || zahyo[i]>Lx)
      zahyo[i]+=-Lx*(static_cast<int>(zahyo[i]*tmpLx));
    if(zahyo[i]<0)
      zahyo[i]+=Lx;
    if(zahyo[i+1]<0 || zahyo[i+1]>Ly)
      zahyo[i+1]+=-Ly*(static_cast<int>(zahyo[i+1]*tmpLy));
    if(zahyo[i+1]<0)
      zahyo[i+1]+=Ly;
  }
}
inline void JT::dim3::PeriodicMove3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz)
{
int N=zahyo.size();
 DP tmpLx =1.0/Lx,tmpLy=1.0/Ly,tmpLz=1.0/Lz;
  for(int i=0;i<N;i+=3) {
    if(zahyo[i]<0 || zahyo[i]>Lx)
      zahyo[i]+=-Lx*(static_cast<int>(zahyo[i]*tmpLx));
    if(zahyo[i]<0)
      zahyo[i]+=Lx;
    if(zahyo[i+1]<0 || zahyo[i+1]>Ly)
      zahyo[i+1]+=-Ly*(static_cast<int>(zahyo[i+1]*tmpLy));
    if(zahyo[i+1]<0)
      zahyo[i+1]+=Ly;
    if(zahyo[i+2]<0 || zahyo[i+2]>Lz)
      zahyo[i+2]+=-Lz*(static_cast<int>(zahyo[i+2]*tmpLz));
    if(zahyo[i+2]<0)
      zahyo[i+2]+=Lz;
  }
}

inline void JT::dim2::OutofPeriodicboundary2D(DP &relative_x,DP &relative_y,DP L,DP sgm)
{
  if(fabs(relative_x)>L-sgm || fabs(relative_y)>L-sgm) {
    //上記の条件でポテンシャルに寄与するので
    //隣接セルとの評価をおこなう
    // A B C
    // D x E
    // F G H
    //xを自セルとして上記の他セルとの評価を行う。
    if(fabs(relative_x-L)<sgm)//A or D or F
      relative_x-=L;
    else if(fabs(relative_x+L)<sgm)// C or E or H
      relative_x+=L;
    //なにもしない otherwise (B or G)

    if(fabs(relative_y-L)<sgm)//F or G or H
      relative_y-=L;
    else if(fabs(relative_y+L)<sgm)//A or B or C
      relative_y+=L;
    //なにもしない　otherwise (D or E)
  }
  return;
}
inline void JT::dim2::OutofPeriodicboundary2D(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm)
{
if(fabs(relative_x)>Lx-sgm || fabs(relative_y)>Ly-sgm) {
    if(fabs(relative_x-Lx)<sgm)//A or D or F
      relative_x-=Lx;
    else if(fabs(relative_x+Lx)<sgm)// C or E or H
      relative_x+=Lx;
    //なにもしない otherwise (B or G)
    
    if(fabs(relative_y-Ly)<sgm)//F or G or H
      relative_y-=Ly;
    else if(fabs(relative_y+Ly)<sgm)//A or B or C
      relative_y+=Ly;
    //なにもしない　otherwise (D or E)
  }
  return;
}
inline void JT::dim2::OutofPeriodicboundary2D_qt(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm,int &p1,int &p2)
{
  if(fabs(relative_x)>Lx-sgm || fabs(relative_y)>Ly-sgm) {
    if(fabs(relative_x-Lx)<sgm) {//A or D or F
      relative_x-=Lx;
      p1=1;
    }
    else if(fabs(relative_x+Lx)<sgm) {// C or E or H
      relative_x+=Lx;
      p1=-1;
    }
    //なにもしない otherwise (B or G)
    if(fabs(relative_y-Ly)<sgm) {//F or G or H
      relative_y-=Ly;
      p2=1;
    }
    else if(fabs(relative_y+Ly)<sgm) {//A or B or C
      relative_y+=Ly;
      p2=-1;
    }
    //なにもしない　otherwise (D or E)
  }
  return;
}

inline void JT::dim3::OutofPeriodicboundary3D(DP &relative_x,DP &relative_y,DP &relative_z,DP L,DP sgm)
{
  if(fabs(relative_x)>L-sgm || fabs(relative_y)>L-sgm || fabs(relative_z)>L-sgm) {
    if(fabs(relative_x-L)<sgm)
      relative_x-=L;
    else if(fabs(relative_x+L)<sgm)
      relative_x+=L;
    if(fabs(relative_y-L)<sgm)
      relative_y-=L;
    else if(fabs(relative_y+L)<sgm)
      relative_y+=L;
    if(fabs(relative_z-L)<sgm)
      relative_z-=L;
    else if(fabs(relative_z+L)<sgm)
      relative_z+=L;
  }
  return;
}
inline void JT::dim3::OutofPeriodicboundary3D(DP &relative_x,DP &relative_y,DP &relative_z,DP Lx,DP Ly,DP Lz,DP sgm)
{
  if(fabs(relative_x)>Lx-sgm || fabs(relative_y)>Ly-sgm || fabs(relative_z)>Lz-sgm) {
    if(fabs(relative_x-Lx)<sgm)
      relative_x-=Lx;
    else if(fabs(relative_x+Lx)<sgm)
      relative_x+=Lx;
    if(fabs(relative_y-Ly)<sgm)
      relative_y-=Ly;
    else if(fabs(relative_y+Ly)<sgm)
      relative_y+=Ly;
    if(fabs(relative_z-Lz)<sgm)
      relative_z-=Lz;
    else if(fabs(relative_z+Lz)<sgm)
      relative_z+=Lz;
  }
  return;
}

inline void JT::updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio,int DN,int D)
{
  if((Pratio+1)*i==Pratio*DN) {
    R*=ratio;
    BIMASS*=pow(ratio,D);
  }
  return;
}
inline void JT::updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int DN,int D)
{
  if((Pratio1+Pratio2)*i==Pratio1*DN) {
    R*=ratio;
    BIMASS*=pow(ratio,D);
  }
  return;
}

inline void JT::updateRadius(int i,DP &R,DP ratio,int Pratio,int DN)
{
  if((Pratio+1)*i==Pratio*DN)
    R*=ratio;
  return;
}
inline void JT::updateRadius(int i,DP &R,DP ratio,int Pratio1,int Pratio2,int DN)
{
  if((Pratio1+Pratio2)*i==Pratio1*DN)
    R*=ratio;
  return;
}

inline void JT::dim2::updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio,int DN)
{
  if((Pratio+1)*i==Pratio*DN) {
    R*=ratio;
    rtinv/=ratio;
  }
  return;
}
inline void JT::dim2::updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int DN)
{
  if((Pratio1+Pratio2)*i==Pratio1*DN) {
    R*=ratio;
    rtinv/=ratio;
  }
  return;
}

inline void JT::dim3::updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio,int DN)
{
  if((Pratio+1)*i==Pratio*DN) {
    R*=ratio;
    rtinv/=sqrt(ratio*ratio*ratio);
  }
  return;
}
inline void JT::dim3::updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int DN)
{
  if((Pratio1+Pratio2)*i==Pratio1*DN) {
    R*=ratio;
    rtinv/=sqrt(ratio*ratio*ratio);
  }
  return;
}

inline DP JT::dim2::CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt,int D)
{
  if(checkdim2(D)) {
    DP numer=(Prt+1)*L*L,denom=(Prt+rt*rt)*PN*M_PI;
    return sqrt(numer/denom);
  }
  return 0.0;
}
inline DP JT::dim2::CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt1,int Prt2,int D)
{
  if(checkdim2(D)) {
    DP numer=(Prt1+Prt2)*L*L,denom=(Prt1+Prt2*rt*rt)*PN*M_PI;
    return sqrt(numer/denom);
  }
  return 0.0;
}
inline DP JT::dim2::CtoDerivePHI2D(DP Lx,DP Ly,DP rt,DP PN, int Prt,int D)
{
  if(checkdim2(D)) {
    DP numer=(Prt+1)*Lx*Ly,denom=(Prt+rt*rt)*PN*M_PI;
    return sqrt(numer/denom);
  }
  return 0.0;
}
inline DP JT::dim2::CtoDerivePHI2D(DP Lx,DP Ly,DP rt,DP PN, int Prt1,int Prt2,int D)
{
  if(checkdim2(D)) {
    DP numer=(Prt1+Prt2)*Lx*Ly,denom=(Prt1+Prt2*rt*rt)*PN*M_PI;
    return sqrt(numer/denom);
  }
  return 0.0;
}

inline DP JT::dim3::CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt,int D)
{
  if(checkdim3(D)) {
    DP numer=3*(Prt+1)*L*L*L,denom=4*(Prt+rt*rt*rt)*PN*M_PI;
    return pow(numer/denom,0.333333333333333);
  }
  return 0.0;
}
inline DP JT::dim3::CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt1,int Prt2,int D)
{
  if(checkdim3(D)) {
    DP numer=3*(Prt1+Prt2)*L*L*L,denom=4*(Prt1+Prt2*rt*rt*rt)*PN*M_PI;
    return pow(numer/denom,0.333333333333333);
  }
  return 0.0;
}
inline DP JT::dim3::CtoDerivePHI3D(DP Lx,DP Ly,DP Lz,DP rt,DP PN,int Prt,int D)
{
  if(checkdim3(D)) {
    DP numer=3*(Prt+1)*Lx*Ly*Lz,denom=4*(Prt+rt*rt*rt)*PN*M_PI;
    return pow(numer/denom,0.333333333333333);
  }
  return 0.0;
}
inline DP JT::dim3::CtoDerivePHI3D(DP Lx,DP Ly,DP Lz,DP rt,DP PN,int Prt1,int Prt2,int D)
{
  if(checkdim3(D)) {
    DP numer=3*(Prt1+Prt2)*Lx*Ly*Lz,denom=4*(Prt1+Prt2*rt*rt*rt)*PN*M_PI;
    return pow(numer/denom,0.333333333333333);
  }
  return 0.0;
}

inline bool JT::dim2::checkdim2(int D)
{
  if(D==2)
    return true;
  else {
    cerr<<"Your system dimension is "<<D<<". Must simulate for 2D!!"<<endl;
    exit(1);
  }
  return false;
}

inline bool JT::dim3::checkdim3(int D)
{
  if(D==3)
    return true;
  else {
    cerr<<"Your system dimension is "<<D<<". Must simulate for 3D!!"<<endl;
    exit(1);
  }
  return false;
}

inline void JT::showHESS(Mat_I_DP &H)
{
  int N=H.ncols(),M=H.nrows();
  for(int i=0;i<M;i++) {
    for(int j=0;j<N;j++)
      cout<<H[i][j]<<' ';
    cout<<endl;
  }
}


#endif
