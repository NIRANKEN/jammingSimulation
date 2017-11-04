#ifndef _JTFUNC_H_
#define _JTFUNC_H_

#include "jttool.h"
#include "nr.h"
#include "MT.h"
#include <vector>
#include <limits>

namespace JT
{
  //--------------------//
  //-------JT func------//
  //----(jtfunc.cpp)----//
  //--------------------//
  
  namespace dim2
  {
    DP potential(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps);
    DP potential(Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps);
    DP fastPot2D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    DP fastPot2D(Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    void Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);//alpha =2.0 only...
    void fastHess2D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    void DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D);
    void fastDCod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D,NRVec<vector<int> > &v);
    void noise(Vec_IO_DP& p,DP R,DP Lx,DP Ly,DP n_disp_ratio);
  }

  namespace dim3
  {
    DP potential3D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    DP potential3D(Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    DP fastPot3D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    DP fastPot3D(Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    void Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    void fastHess3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v);
    void DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D);
    void fastDCod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D,NRVec<vector<int> > &v);
    void noise(Vec_IO_DP& p,DP R,DP Lx,DP Ly,DP Lz,DP n_disp_ratio);
  }
  
  inline void distcalc(Vec_IO_DP &dcod,Vec_I_INT num);
  void tappingForUnstable(Vec_IO_DP& EigDispvec,DP eigval,DP EPS,DP R,DP disp_ratio);
  void noise(Vec_IO_DP& p,DP R,DP Len,DP n_disp_ratio);
  inline void HessCalc(Mat_IO_DP &H,int i,int j,DP ijF,DP iiF,DP jjF,DP rr);
  inline void HessCalc(Mat_IO_DP &H,int i1,int i2,int j1,int j2,DP ijF,DP iiF,DP jjF,DP rr);
  DP migrationLengthOnCSpace(Vec_I_DP zahyo,Vec_I_DP zahyotmp);
  //void selectWorkingParticle(int num,vector<int> &v);
}


//---------------------------------------------------
//potential V(2D)を求める関数------------------------
//---------------------------------------------------

DP JT::dim2::potential(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2, int D, DP eps)
{
  if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,x,y,relr,powterm;
    bool m1=false,m2;
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      initializeParticle2(Radj,R,x,y,p[i],p[i+1],m2);
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);
	if(overlapped2D(x,y,p[j],p[j+1],Len,Len,Radi,Radj,sgm,relr)) {
	  powterm = (sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }//j-loop-end
    }//i-loop-end
    return pot;
  }
  else
    return 0.0;
}//End
DP JT::dim2::potential(Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps)
{
 if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relr,powterm,x,y;
    bool m1=false,m2;
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      initializeParticle2(Radj,R,x,y,p[i],p[i+1],m2);
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);
	if(overlapped2D(x,y,p[j],p[j+1],Lx,Ly,Radi,Radj,sgm,relr)) {
	  powterm = (sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }//j-loop-end
    }//i-loop-end
    return pot;
  }
  else
    return 0.0;
}
DP JT::dim3::potential3D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relr,powterm,x,y,z;
    bool m1=false,m2;
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      initializeParticle2(Radj,R,x,y,z,p[i],p[i+1],p[i+2],m2);

      for(int j=0;j<i;j+=D) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);
	if(overlapped3D(x,y,z,p[j],p[j+1],p[j+2],Len,Len,Len,Radi,Radj,sgm,relr)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }//j-loop-end
    }//i-loop-end
    return pot;
  }
  else
    return 0.0;
}//End
DP JT::dim3::potential3D(Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relr,powterm,x,y,z;
    bool m1=false,m2;
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      initializeParticle2(Radj,R,x,y,z,p[i],p[i+1],p[i+2],m2);

      for(int j=0;j<i;j+=D) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);
	if(overlapped3D(x,y,z,p[j],p[j+1],p[j+2],Lx,Ly,Lz,Radi,Radj,sgm,relr)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }//j-loop-end
    }//i-loop-end
    return pot;
  }
  else
    return 0.0;
}//End


DP JT::dim2::fastPot2D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(checkdim2(D)) {

    int N=v.size(),K,I;
    DP sgm,pot=0.0,Radi=R,Radk,relr,powterm;
    DP x,y;
    bool m1=false,m2;
    if(p.size()!=D*v.size()) {
      cerr<<"接触リストのサイズがおかしいのです!!"<<endl;
      exit(1);
    }
    for(int i=0;i<N;i++) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Radk,R,x,y,p[I],p[I+1],m2);
      
      for(unsigned int j=0;j<v[i].size();j++) {
	K=D*v[i][j];//iばんめの接触リストについて,
	updateRadiusF(K,Radk,rt,Prt1,Prt2,N,D,m2);
	if(overlapped2D(x,y,p[K],p[K+1],Len,Len,Radi,Radk,sgm,relr)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }// j-loop
    }// i-loop
    return pot;
  }
  return 0.0;
}
DP JT::dim2::fastPot2D(Vec_I_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(checkdim2(D)) {

    int N=v.size(),K,I;
    DP sgm,pot=0.0,Radi=R,Radk,relr,powterm;
    DP x,y;
    bool m1=false,m2;
    if(p.size()!=D*v.size()) {
      cerr<<"接触リストのサイズがおかしいのです!!"<<endl;
      exit(1);
    }
    for(int i=0;i<N;i++) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Radk,R,x,y,p[I],p[I+1],m2);
      
      for(unsigned int j=0;j<v[i].size();j++) {
	K=D*v[i][j];//iばんめの接触リストについて,
	updateRadiusF(K,Radk,rt,Prt1,Prt2,N,D,m2);
	if(overlapped2D(x,y,p[K],p[K+1],Lx,Ly,Radi,Radk,sgm,relr)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }// j-loop
    }// i-loop
    return pot;
  }
  return 0.0;
}
DP JT::dim3::fastPot3D(Vec_I_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(checkdim3(D)) {

    int N=v.size(),K,I,cnt=0;
    DP sgm,pot=0.0,Radi=R,Radk,relr,powterm;
    DP x,y,z;
    bool m1=false,m2;
    if(p.size()!=D*v.size()) {
      cerr<<"接触リストのサイズがおかしいのです!!"<<endl;
      exit(1);
    }

    for(int i=0;i<N;i++) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Radk,R,x,y,z,p[I],p[I+1],p[I+2],m2);
      for(unsigned int j=0;j<v[i].size();j++) {
	K=D*v[i][j];//iばんめの接触リストについて,
	updateRadiusF(K,Radk,rt,Prt1,Prt2,N,D,m2);
	if(overlapped3D(x,y,z,p[K],p[K+1],p[K+2],Len,Len,Len,Radi,Radk,sgm,relr)) {
	  cnt++;
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }// j-loop
    }// i-loop
    //    cout<<cnt<<endl;
    return pot;
  }
  return 0.0;
}
DP JT::dim3::fastPot3D(Vec_I_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(checkdim3(D)) {

    int N=v.size(),K,I;
    DP sgm,pot=0.0,Radi=R,Radk,relr,powterm;
    DP x,y,z;
    bool m1=false,m2;
    if(p.size()!=D*v.size()) {
      cerr<<"接触リストのサイズがおかしいのです!!"<<endl;
      exit(1);
    }
    for(int i=0;i<N;i++) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Radk,R,x,y,z,p[I],p[I+1],p[I+2],m2);
      for(unsigned int j=0;j<v[i].size();j++) {
	K=D*v[i][j];//iばんめの接触リストについて,
	updateRadiusF(K,Radk,rt,Prt1,Prt2,N,D,m2);
	if(overlapped3D(x,y,z,p[K],p[K+1],p[K+2],Lx,Ly,Lz,Radi,Radk,sgm,relr)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  pot+=eps*pow(powterm,alp)/alp;
	  //pot_ij = eps*(1-(relr/sgm))^\alpha /\alpha
	}
      }// j-loop
    }// i-loop
    return pot;
  }
  return 0.0;
}


//--------------------------------------------------
//-----------------Hessian Matrix(2D)---------------
//--------------------------------------------------

void JT::dim2::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relr,fact,x,y,rx2,ry2,rxy,r3,fs,ii,ij,jj;
    bool m1=false,m2;
    H=0.0;
    
    for(int i=0;i<N;i+=D) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt1,Prt2,N,m1);
      initializeParticle2_H(Radj,R,x,y,p[i],p[i+1],m2,rtinv_j,1.0);

      for(int j=0;j<i;j+=D) {
	updateRadius_Hessian2D(j,Radj,rtinv_j,rt,Prt1,Prt2,N,m2);
	
	  if(overlapped2D_H(x,y,p[j],p[j+1],Lx,Ly,Radi,Radj,sgm,relr,rx2,ry2,rxy)) {
	    r3=relr*relr*relr;
	    fact=eps/(sgm*sgm*r3);
	    r3*=fact;
	    fs=fact*sgm;
	    
	    tmpxx=fs*ry2-r3;
	    tmpxy=-fs*(rxy);
	    tmpyy=fs*rx2-r3;

	    ii=rtinv_i*rtinv_i;
	    ij=rtinv_i*rtinv_j;
	    jj=rtinv_j*rtinv_j;

	    HessCalc(H,i,j,ij,ii,jj,tmpxx);
	    HessCalc(H,i,i+1,j,j+1,ij,ii,jj,tmpxy);
	    HessCalc(H,i+1,j+1,ij,ii,jj,tmpyy);
	  }
      }//j-loop-end
    }//i-loop-end
  }//if end
  return;
}
//--------------------------------------------------
//-----------------Hessian Matrix(3D)---------------
//--------------------------------------------------

void JT::dim3::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relr,fact,x,y,z,rx2,ry2,rz2,rxy,ryz,rzx,r3,ii,ij,jj,fs;
    bool m1=false,m2;
    H=0.0;
    
    for(int i=0;i<N;i+=D) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt1,Prt2,N,m1);
      initializeParticle2_H(Radj,R,x,y,z,p[i],p[i+1],p[i+2],m2,rtinv_j,1.0);
	for(int j=0;j<i;j+=D) {
	  updateRadius_Hessian3D(j,Radj,rtinv_j,rt,Prt1,Prt2,N,m2);
	  if(overlapped3D_H(x,y,z,p[j],p[j+1],p[j+2],Lx,Ly,Lz,Radi,Radj,sgm,relr,rx2,ry2,rz2,rxy,ryz,rzx)) {
	    r3=relr*relr*relr;
	    fact=eps/(sgm*sgm*r3);
	    r3*=fact;
	    fs=fact*sgm;
		  
	    tmpxx=fs*(ry2+rz2)-r3;
	    tmpxy=-fs*(rxy);
	    tmpyy=fs*(rz2+rx2)-r3;
	    tmpyz=-fs*(ryz);
	    tmpzz=fs*(rx2+ry2)-r3;
	    tmpzx=-fs*(rzx);
	    ii=rtinv_i*rtinv_i;
	    ij=rtinv_i*rtinv_j;
	    jj=rtinv_j*rtinv_j;

	    HessCalc(H,i,j,ij,ii,jj,tmpxx);
	    HessCalc(H,i,i+1,j,j+1,ij,ii,jj,tmpxy);
	    HessCalc(H,i+1,j+1,ij,ii,jj,tmpyy);
	    HessCalc(H,i+1,i+2,j+1,j+2,ij,ii,jj,tmpyz);
	    HessCalc(H,i+2,j+2,ij,ii,jj,tmpzz);
	    HessCalc(H,i+2,i,j+2,j,ij,ii,jj,tmpzx);
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}

void JT::dim2::fastHess2D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {

    int N =v.size(),I,J;
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relr,fact,x,y,rx2,ry2,rxy,r3,ii,ij,jj,fs;
    bool m1=false,m2;
    H=0.0;
    
    for(int i=0;i<N;i++) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2_H(Radj,R,x,y,p[I],p[I+1],m2,rtinv_j,1.0);
	for(unsigned int l=0;l<v[i].size();l++) {
	  J=D*v[i][l];
	  updateRadiusF_Hessian2D(J,Radj,rtinv_j,rt,Prt1,Prt2,N,D,m2);
	  if(overlapped2D_H(x,y,p[J],p[J+1],Lx,Ly,Radi,Radj,sgm,relr,rx2,ry2,rxy)) {
	    r3=relr*relr*relr;
	    fact=eps/(sgm*sgm*r3);
	    r3*=fact;
	    fs=fact*sgm;
	    
	    tmpxx=fs*ry2-r3;
	    tmpxy=-fs*(rxy);
	    tmpyy=fs*rx2-r3;

	    ii=rtinv_i*rtinv_i;
	    ij=rtinv_i*rtinv_j;
	    jj=rtinv_j*rtinv_j;

	    HessCalc(H,I,J,ij,ii,jj,tmpxx);
	    HessCalc(H,I,I+1,J,J+1,ij,ii,jj,tmpxy);
	    HessCalc(H,I+1,J+1,ij,ii,jj,tmpyy);
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}
void JT::dim3::fastHess3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps,NRVec<vector<int> > &v)
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {

    int N =v.size(),J,I;
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relr,fact,x,y,z,rx2,ry2,rz2,rxy,ryz,rzx,r3,ii,ij,jj,fs;
    bool m1=false,m2;
    H=0.0;
    
    for(int i=0;i<N;i++) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2_H(Radj,R,x,y,z,p[I],p[I+1],p[I+2],m2,rtinv_j,1.0);
	for(unsigned int l=0;l<v[i].size();l++) {
	  J=D*v[i][l];
	  updateRadiusF_Hessian3D(J,Radj,rtinv_j,rt,Prt1,Prt2,N,D,m2);
	  if(overlapped3D_H(x,y,z,p[J],p[J+1],p[J+2],Lx,Ly,Lz,Radi,Radj,sgm,relr,rx2,ry2,rz2,rxy,ryz,rzx)) {
	    r3=relr*relr*relr;
	    fact=eps/(sgm*sgm*r3);
	    r3*=fact;
	    fs=fact*sgm;
		  
	    tmpxx=fs*(ry2+rz2)-r3;
	    tmpxy=-fs*(rxy);
	    tmpyy=fs*(rz2+rx2)-r3;
	    tmpyz=-fs*(ryz);
	    tmpzz=fs*(rx2+ry2)-r3;
	    tmpzx=-fs*(rzx);
	    ii=rtinv_i*rtinv_i;
	    ij=rtinv_i*rtinv_j;
	    jj=rtinv_j*rtinv_j;

	    HessCalc(H,I,J,ij,ii,jj,tmpxx);
	    HessCalc(H,I,I+1,J,J+1,ij,ii,jj,tmpxy);
	    HessCalc(H,I+1,J+1,ij,ii,jj,tmpyy);
	    HessCalc(H,I+1,I+2,J+1,J+2,ij,ii,jj,tmpyz);
	    HessCalc(H,I+2,J+2,ij,ii,jj,tmpzz);
	    HessCalc(H,I+2,I,J+2,J,ij,ii,jj,tmpzx);
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}

//--------------------------------------------------
//Distribution of coordination numberを計算func-----
//--------------------------------------------------

inline void JT::distcalc(Vec_IO_DP &Dcod,Vec_I_INT num)
{
  int pN=num.size();
  DP dvd=1.0/pN;
  for(int i=0;i<pN;i++)
    {
      switch(num[i])
	{
	case 0:Dcod[0]+=dvd;
	  break;
	case 1:Dcod[1]+=dvd;
	  break;
	case 2:Dcod[2]+=dvd;
	  break;
	case 3:Dcod[3]+=dvd;
	  break;
	case 4:Dcod[4]+=dvd;
	  break;
	case 5:Dcod[5]+=dvd;
	  break;
	case 6:Dcod[6]+=dvd;
	  break;
	case 7:Dcod[7]+=dvd;
	  break;
	case 8:Dcod[8]+=dvd;
	  break;
	case 9:Dcod[9]+=dvd;
	  break;
	case 10:Dcod[10]+=dvd;
	  break;
	case 11:Dcod[11]+=dvd;
	  break;
	case 12:Dcod[12]+=dvd;
	  break;
	case 13:Dcod[13]+=dvd;
	  break;
  	case 14:Dcod[14]+=dvd;
	  break;
	case 15:Dcod[15]+=dvd;
	  break;
	case 16:Dcod[16]+=dvd;
	  break;
	case 17:Dcod[17]+=dvd;
	  break;
	case 18:Dcod[18]+=dvd;
	  break;
	case 19:Dcod[19]+=dvd;
	  break;
	default:cout<<"-----------------\n接触数が20点以上見つかっちゃいましたぁ〜!!\n--------------------\n";
	  break;
	}
    }
}

void JT::dim2::DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D,dn=Dcod.size();
  Vec_INT tmpnum(pN);
  DP sgm,relr,Ri=R,Rj=R,x,y;
  bool m1=false,m2;
  for(int i=0;i<pN;i++) {
    if(i<dn)
      Dcod[i]=0.0;
    tmpnum[i]=0;//i粒子の接触数.
  }
  if(D==2) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N,m1);
      Rj=R;
      m2=false;
      x=p[i];
      y=p[i+1];
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N,m2);
	if(overlapped2D(x,y,p[j],p[j+1],Lx,Ly,Ri,Rj,sgm,relr)) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum);
}//end void NR::DISTcod
void JT::dim3::DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D,dn=Dcod.size();
  Vec_INT tmpnum(pN);
  DP sgm,relr,Ri=R,Rj=R,x,y,z;
  bool m1=false,m2;
  for(int i=0;i<pN;i++) {
    if(i<dn)
      Dcod[i]=0.0;
    tmpnum[i]=0;//i粒子の接触数.
  }
  if(D==3) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N,m1);
      Rj=R;
      m2=false;
      x=p[i];
      y=p[i+1];
      z=p[i+2];
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N,m2);
	if(overlapped3D(x,y,z,p[j],p[j+1],p[j+2],Lx,Ly,Lz,Ri,Rj,sgm,relr)) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum);
}//end void NR::DISTcod

void JT::dim2::fastDCod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D,NRVec<vector<int> > &v)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  //cout<<"DCod2D start"<<endl;
  int N=v.size();
  if(p.size()!=D*N) {
    cerr<<"接触リストのサイズが違うにゃあ!!"<<endl;
    exit(1);
  }
  Vec_INT tmpnum(N);
  int j,I,J,dn=Dcod.size();
  DP sgm,relr,Ri=R,Rj=R,x,y;
  bool m1=false,m2;
  for(int i=0;i<N;i++) {
    if(i<dn)
      Dcod[i]=0.0;
    tmpnum[i]=0;//i粒子の接触数.
  }
  if(D==2) {
    for(int i=0;i<N;i++) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Rj,R,x,y,p[I],p[I+1],m2);
      for(unsigned int l=0;l<v[i].size();l++) {
	j=v[i][l];
	J=D*j;
	updateRadiusF(J,Rj,rt,Prt1,Prt2,N,D,m2);
	if(overlapped2D(x,y,p[J],p[J+1],Lx,Ly,Ri,Rj,sgm,relr)) {
	  tmpnum[i]+=1;
	  tmpnum[j]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum);
}//end void NR::DISTcod
void JT::dim3::fastDCod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D,NRVec<vector<int> > &v)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  //cout<<"DCod3D start"<<endl;
  int N=v.size();
  if(p.size()!=D*N) {
    cerr<<"接触リストのサイズが違うにゃあ!!"<<endl;
    exit(1);
  }
  Vec_INT tmpnum(N);
  int I,j,J,dn=Dcod.size();
  DP sgm,relr,Ri=R,Rj=R,x,y,z;
  bool m1=false,m2;
  for(int i=0;i<N;i++) {
    if(i<dn)
      Dcod[i]=0.0;
    tmpnum[i]=0;//i粒子の接触数.
  }
  if(D==3) {
    for(int i=0;i<N;i++) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N,m1);
      I=D*i;
      initializeParticle2(Rj,R,x,y,z,p[I],p[I+1],p[I+2],m2);
      for(unsigned int l=0;l<v[i].size();l++) {
	j=v[i][l];
	J=D*j;
	updateRadiusF(J,Rj,rt,Prt1,Prt2,N,D,m2);
	if(overlapped3D(x,y,z,p[J],p[J+1],p[J+2],Lx,Ly,Lz,Ri,Rj,sgm,relr)) {
	  tmpnum[i]+=1;
	  tmpnum[j]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum);
}//end void NR::DISTcod

//deriveEigVecとペアで組み合わせて用いる。
void JT::tappingForUnstable(Vec_IO_DP& EigDispvec,DP eigval,DP EPS,DP R,DP disp_ratio)
{
  int N=EigDispvec.size();
  DP DISP;
  if(disp_ratio<0.0 || disp_ratio>1.0)
    disp_ratio=0.01; //default値は半径の1%ランダム変位させる.
  DISP=R*disp_ratio;
  srand((unsigned)time(NULL));
  if(eigval>-EPS) {
    cerr<<"ERROR for tapping method..."<<endl;
    exit(1);
  }
  if(rand()%2==1)
    DISP*=-1.0;
  for(int i=0;i<N;i++)
    EigDispvec[i]*=DISP;
}

void JT::noise(Vec_IO_DP& p,DP R,DP Len,DP n_disp_ratio)
{
  int N=p.size();
  DP DISP;
  MT::init_genrand((unsigned)time(NULL));
  if(n_disp_ratio<0.0 || n_disp_ratio>1.0)
    n_disp_ratio=0.01; //default値は半径の1%ランダム変位させる.
  DISP=R*n_disp_ratio;
  for(int i=0;i<N;i++) {
      if(MT::genrand_real2()<0.5)
	p[i]+=DISP;
      else
	p[i]-=DISP;
  }
  PeriodicMove(p,Len);
}
void JT::dim2::noise(Vec_IO_DP& p,DP R,DP Lx,DP Ly,DP n_disp_ratio)
{
  int N=p.size();
  DP DISP;
  MT::init_genrand((unsigned)time(NULL));
  if(n_disp_ratio<0.0 || n_disp_ratio>1.0)
    n_disp_ratio=0.01; //default値は半径の1%ランダム変位させる.
  DISP=R*n_disp_ratio;
  for(int i=0;i<N;i++) {
      if(MT::genrand_real2()<0.5)
	p[i]+=DISP;
      else
	p[i]-=DISP;
  }
  PeriodicMove2D(p,Lx,Ly);
}
void JT::dim3::noise(Vec_IO_DP& p,DP R,DP Lx,DP Ly,DP Lz,DP n_disp_ratio)
{
  int N=p.size();
  DP DISP;
  MT::init_genrand((unsigned)time(NULL));
  if(n_disp_ratio<0.0 || n_disp_ratio>1.0)
    n_disp_ratio=0.01; //default値は半径の1%ランダム変位させる.
  DISP=R*n_disp_ratio;
  for(int i=0;i<N;i++) {
      if(MT::genrand_real2()<0.5)
	p[i]+=DISP;
      else
	p[i]-=DISP;
  }
  PeriodicMove3D(p,Lx,Ly,Lz);
}
inline void JT::HessCalc(Mat_IO_DP &H,int i,int j,DP ijF,DP iiF,DP jjF,DP rr)
{
  //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=ijF*rr;
	    H[i][i]-=iiF*rr;
	    H[j][j]-=jjF*rr;
}
inline void JT::HessCalc(Mat_IO_DP &H,int i1,int i2,int j1,int j2,DP ijF,DP iiF,DP jjF,DP rr)
{
	    H[i1][j2]=H[i2][j1]=H[j1][i2]=H[j2][i1]=ijF*rr;
	    H[i1][i2]=H[i2][i1]-=iiF*rr;
	    H[j1][j2]=H[j2][j1]-=jjF*rr;
}


DP migrationLengthOnCSpace(Vec_I_DP zahyo,Vec_I_DP zahyotmp)
{
  const int N1=zahyo.size(),N2=zahyotmp.size();
  DP z,sum=0.0,root;

  if(N1!=N2) {
    cerr<<"cannot calculate migration length for different dimensional vectors"<<endl;
    exit(1);
  }
  else {
    for(int i=0;i<N1;i++) {
      z=zahyo[i]-zahyotmp[i];
      sum+=z*z;
    }
    root=sqrt(sum);
    return root;
  }
  return 0.0;
}

#endif
