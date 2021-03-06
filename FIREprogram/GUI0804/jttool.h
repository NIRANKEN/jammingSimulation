#ifndef _JTTOOL_H_
#define _JTTOOL_H_

#include "nr.h"
#include "MT.h"
#include <vector>
namespace JT
{
  //--------------------------//
  //--Tools for JTsimulation--//
  //-------(jttool.cpp)-------//
  //--------------------------//

  inline void PutZahyoRandomly(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP L,int seednum);
  inline void PeriodicMove(Vec_IO_DP &zahyo,DP L);
  inline void updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified);
  inline void updateParticleF(int I,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified);
  inline void updateRadius(int i,DP &R,DP ratio,int Pratio1,int Pratio2,int N,bool &modified);
  inline void updateRadiusF(int I,DP &R,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified);
  namespace dim2
  {
    inline void PutZahyoRandomly2D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,int seednum);
    inline void PeriodicMove2D(Vec_IO_DP &zahyo,DP Lx,DP Ly);
    inline bool checkdim2(int D);
    inline DP CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt1,int Prt2,int D);
    inline DP CtoDerivePHI2D(DP Lx,DP Ly,DP rt,DP PN, int Prt1,int Prt2,int D);
    inline void updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,bool &modified);
    inline void updateRadiusF_Hessian2D(int I,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified);
    inline void OutofPeriodicboundary2D(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm);
    inline void OutofPeriodicboundary2D_qt(DP &relative_x,DP &relative_y,DP Lx,DP Ly,DP sgm,int &p1,int &p2);

    inline bool overlapped2D(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r);
    inline bool overlapped2D_CL(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP &sgm,DP &r);
    inline bool overlapped2D_F(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r,DP &rx,DP &ry);
    inline bool overlapped2D_H(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r,DP &rx2,DP &ry2,DP &rxy);
    inline void initializeParticle2(DP &R2,DP R,DP &x,DP &y,DP Cx,DP Cy,bool &b);
    inline void initializeParticle2_H(DP &R2,DP R,DP &x,DP &y,DP Cx,DP Cy,bool &b,DP &rtinv2,DP rt);
    void modifyContactList(NRVec<vector<int> > &v,Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,int Prt1,int Prt2,int D);
  }
  namespace dim3
  {
    inline void PeriodicMove3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz);
    inline void PutZahyoRandomly3D(Vec_IO_DP &zahyo,Vec_IO_DP &zahyotmp,DP Lx,DP Ly,DP Lz,int seednum);
    inline bool checkdim3(int D);
    inline DP CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt1,int Prt2,int D);
    inline DP CtoDerivePHI3D(DP Lx,DP Ly,DP Lz,DP rt,DP PN,int Prt1,int Prt2,int D);
    inline void updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,bool &modified);
    inline void updateRadiusF_Hessian3D(int I,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified);
    inline void OutofPeriodicboundary3D(DP &relative_x,DP &relative_y,DP &relative_z,DP Lx,DP Ly,DP Lz,DP sgm);
    
    inline bool overlapped3D(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r);
    inline bool overlapped3D_CL(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP &sgm,DP &r);
    inline bool overlapped3D_F(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r,DP &rx,DP &ry,DP &rz);
    inline bool overlapped3D_H(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r,DP &rx2,DP &ry2,DP &rz2,DP &rxy,DP &ryz,DP &rzx);
    inline void initializeParticle2(DP &R2,DP R,DP &x,DP &y,DP &z,DP Cx,DP Cy,DP Cz,bool &b);
    inline void initializeParticle2_H(DP &R2,DP R,DP &x,DP &y,DP &z,DP Cx,DP Cy,DP Cz,bool &b,DP &rtinv2,DP rt);
    void modifyContactList(NRVec<vector<int> > &v,Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,int Prt1,int Prt2,int D);
  }

  inline void showHESS(Mat_I_DP &H);
  inline void showCL(NRVec<vector<int> > &v,int D);
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

inline void JT::updateParticle(int i,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*i>=Pratio1*N) {
      R*=ratio;
      BIMASS*=pow(ratio,D);
      modified=true;
    }
  }
  return;
}
inline void JT::updateRadius(int i,DP &R,DP ratio,int Pratio1,int Pratio2,int N,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*i>=Pratio1*N) {
      R*=ratio;
      modified=true;
    }
  }
  return;
}
inline void JT::dim2::updateRadius_Hessian2D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*i>=Pratio1*N) {
      R*=ratio;
      rtinv/=ratio;
      modified=true;
    }
  }
  return;
}
inline void JT::dim3::updateRadius_Hessian3D(int i,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*i>=Pratio1*N) {
      R*=ratio;
      rtinv/=sqrt(ratio*ratio*ratio);
      modified=true;
    }
  }
  return;
}
inline DP JT::dim2::CtoDerivePHI2D(DP L,DP rt,DP PN, int Prt1,int Prt2,int D)
{
  if(checkdim2(D)) {
    DP numer=(Prt1+Prt2)*L*L,denom=(Prt1+Prt2*rt*rt)*PN*M_PI;
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

inline DP JT::dim3::CtoDerivePHI3D(DP L,DP rt,DP PN,int Prt1,int Prt2,int D)
{
  if(checkdim3(D)) {
    DP numer=3*(Prt1+Prt2)*L*L*L,denom=4*(Prt1+Prt2*rt*rt*rt)*PN*M_PI;
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

inline void JT::updateParticleF(int I,DP &R,DP &BIMASS,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*I>=Pratio1*D*N) {
      R*=ratio;
      BIMASS*=pow(ratio,D);
      modified=true;
    }
  }
  return;
}
inline void JT::updateRadiusF(int I,DP &R,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*I>=Pratio1*D*N) {
      R*=ratio;
      modified=true;
    }
  }
  return;
}
inline void JT::dim2::updateRadiusF_Hessian2D(int I,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*I>=Pratio1*D*N) {
      R*=ratio;
      rtinv/=ratio;
      modified=true;
    }
  }
  return;
}
inline void JT::dim3::updateRadiusF_Hessian3D(int I,DP &R,DP &rtinv,DP ratio,int Pratio1,int Pratio2,int N,int D,bool &modified)
{
  if(!modified) {
    if((Pratio1+Pratio2)*I>=Pratio1*D*N) {
      R*=ratio;
      rtinv/=sqrt(ratio*ratio*ratio);
      modified=true;
    }
  }
  return;
}


inline bool JT::dim2::overlapped2D(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r)
{
  DP rx=x2-x1;
  DP ry=y2-y1;
  sgm=R1+R2;
  JT::dim2::OutofPeriodicboundary2D(rx,ry,Lx,Ly,sgm);
  r=sqrt(rx*rx+ry*ry);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim2::overlapped2D_CL(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP &sgm,DP &r)
{
  DP rx=x2-x1;
  DP ry=y2-y1;
  sgm=2*R1;
  JT::dim2::OutofPeriodicboundary2D(rx,ry,Lx,Ly,sgm);
  r=sqrt(rx*rx+ry*ry);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim2::overlapped2D_F(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r,DP &rx,DP &ry)
{
  rx=x2-x1;
  ry=y2-y1;
  sgm=R1+R2;
  JT::dim2::OutofPeriodicboundary2D(rx,ry,Lx,Ly,sgm);
  r=sqrt(rx*rx+ry*ry);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim2::overlapped2D_H(DP x1,DP y1,DP x2,DP y2,DP Lx,DP Ly,DP R1,DP R2,DP &sgm,DP &r,DP &rx2,DP &ry2,DP &rxy)
{
  DP rx=x2-x1;
  DP ry=y2-y1;
  sgm=R1+R2;
  JT::dim2::OutofPeriodicboundary2D(rx,ry,Lx,Ly,sgm);
  rx2=rx*rx;
  ry2=ry*ry;
  rxy=rx*ry;
  r=sqrt(rx2+ry2);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim3::overlapped3D(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r)
{
  DP rx=x2-x1;
  DP ry=y2-y1;
  DP rz=z2-z1;
  sgm=R1+R2;
  JT::dim3::OutofPeriodicboundary3D(rx,ry,rz,Lx,Ly,Lz,sgm);
  r=sqrt(rx*rx+ry*ry+rz*rz);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim3::overlapped3D_CL(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP &sgm,DP &r)
{
  DP rx=x2-x1;
  DP ry=y2-y1;
  DP rz=z2-z1;
  sgm=2*R1;
  JT::dim3::OutofPeriodicboundary3D(rx,ry,rz,Lx,Ly,Lz,sgm);
  r=sqrt(rx*rx+ry*ry+rz*rz);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim3::overlapped3D_F(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r,DP &rx,DP &ry,DP &rz)
{
  rx=x2-x1;
  ry=y2-y1;
  rz=z2-z1;
  sgm=R1+R2;
  JT::dim3::OutofPeriodicboundary3D(rx,ry,rz,Lx,Ly,Lz,sgm);
  r=sqrt(rx*rx+ry*ry+rz*rz);
  if(r<sgm)
    return true;
  else
    return false;
}
inline bool JT::dim3::overlapped3D_H(DP x1,DP y1,DP z1,DP x2,DP y2,DP z2,DP Lx,DP Ly,DP Lz,DP R1,DP R2,DP &sgm,DP &r,DP &rx2,DP &ry2,DP &rz2,DP &rxy,DP &ryz,DP &rzx)
{
  
  DP rx=x2-x1;
  DP ry=y2-y1;
  DP rz=z2-z1;
  sgm=R1+R2;
  JT::dim3::OutofPeriodicboundary3D(rx,ry,rz,Lx,Ly,Lz,sgm);
  rx2=rx*rx;
  ry2=ry*ry;
  rxy=rx*ry;
  rz2=rz*rz;
  ryz=ry*rz;
  rzx=rz*rx;
  r=sqrt(rx2+ry2+rz2);
  if(r<sgm)
    return true;
  else
    return false;
}
inline void JT::dim2::initializeParticle2(DP &R2,DP R,DP &x,DP &y,DP Cx,DP Cy,bool &b) {
  R2=R;
  x=Cx;
  y=Cy;
  b=false;
}
inline void JT::dim3::initializeParticle2(DP &R2,DP R,DP &x,DP &y,DP &z,DP Cx,DP Cy,DP Cz,bool &b) {
  R2=R;
  x=Cx;
  y=Cy;
  z=Cz;
  b=false;
}
inline void JT::dim2::initializeParticle2_H(DP &R2,DP R,DP &x,DP &y,DP Cx,DP Cy,bool &b,DP &rtinv2,DP rt) {
  R2=R;
  x=Cx;
  y=Cy;
  b=false;
  rtinv2=rt;
}
inline void JT::dim3::initializeParticle2_H(DP &R2,DP R,DP &x,DP &y,DP &z,DP Cx,DP Cy,DP Cz,bool &b,DP &rtinv2,DP rt) {
  R2=R;
  x=Cx;
  y=Cy;
  z=Cz;
  b=false;
  rtinv2=rt;
}

void JT::dim2::modifyContactList(NRVec<vector<int> > &v,Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,int Prt1,int Prt2,int D)
{
  int N=v.size();
  int N1=Prt1*N/(Prt1+Prt2);
  //int N2=N-N1;
  if(D*v.size()!=p.size()) {
    cerr<<"接触リストのサイズがおかしいよ~"<<endl;
    exit(1);
  }
  int I,J;
  DP R1=2.25*R;
  DP sgm,relr;

  for(int i=0;i<N;i++) {
    v[i]=vector<int>();
    I=D*i;
    if(i==N1) {
      R1*=rt;
    }
    for(int j=i+1;j<N;j++) {
      J=D*j;
      if(overlapped2D_CL(p[I],p[I+1],p[J],p[J+1],Lx,Ly,R1,sgm,relr)) {
	v[i].push_back(j);
      }
    }//for-j-end
  }//for-i-end
}
void JT::dim3::modifyContactList(NRVec<vector<int> > &v,Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,int Prt1,int Prt2,int D)
{
  //cout<<"MODIFY ContactList"<<endl;
  int N=v.size();
  int N1=Prt1*N/(Prt1+Prt2);
  if(D*v.size()!=p.size()) {
    cerr<<"接触リストのサイズがおかしいよ~"<<endl;
    exit(1);
  }
  int I,J;
  DP R1=2.25*R,sgm,relr;
  for(int i=0;i<N;i++) {
    v[i]=vector<int>();
    I=D*i;
    if(i==N1) {
      R1*=rt;
    }
    for(int j=i+1;j<N;j++) {
      J=D*j;
      if(overlapped3D_CL(p[I],p[I+1],p[I+2],p[J],p[J+1],p[J+2],Lx,Ly,Lz,R1,sgm,relr)) {
	v[i].push_back(j);
      }
    }//for-j-end
  }//for-i-end
}
inline void JT::showCL(NRVec<vector<int> > &v,int D)
{
  int N=v.size(),K;
  ofstream ofs("test.txt");
  for(int i=0;i<N;i++) {
    ofs<<i<<": ";
    for(unsigned int j=0;j<v[i].size();j++) {
      K=D*v[i][j];
      if(j==0)
	ofs<<K<<","<<K+1<<","<<K+2;
      else
	ofs<<" "<<K<<","<<K+1<<","<<K+2;
    }
    ofs<<endl;
  }
  ofs.close();
}

#endif
