#ifndef _JTFUNC_H_
#define _JTFUNC_H_

#include "jttool.h"
#include "nr.h"
#include "MT.h"


namespace JT
{
  //--------------------//
  //-------JT func------//
  //----(jtfunc.cpp)----//
  //--------------------//
  
  namespace dim2
  {
    DP potential(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt, int D,DP eps);
    DP potential(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps);
    DP potential(Vec_IO_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt, int D,DP eps);
    DP potential(Vec_IO_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps);
    void Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps);//alpha =2.0 only...
    void Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);//alpha =2.0 only...
    void Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt,int D,DP eps);//alpha =2.0 only...
    void Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);//alpha =2.0 only...
    void DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt,int D);
    void DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D);
  }

  namespace dim3
  {
    DP potential3D(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps);
    DP potential3D(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    DP potential3D(Vec_IO_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt,int D,DP eps);
    DP potential3D(Vec_IO_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    void Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps);
    void Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    void Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt,int D,DP eps);
    void Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps);
    void DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt,int D);
    void DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D);
  }
  void DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt,int D);
  void DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt1,int Prt2,int D);
  inline void distcalc(Vec_IO_DP &dcod,Vec_I_INT num,int dim);
  void tappingForUnstable(Vec_IO_DP& EigDispvec,DP eigval,DP EPS,DP R,DP disp_ratio);
  void noise(Vec_IO_DP& p,DP R,DP n_disp_ratio);
}


//---------------------------------------------------
//potential V(2D)を求める関数------------------------
//---------------------------------------------------

DP JT::dim2::potential(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt, int D, DP eps)
{
  if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relr,powterm;
    JT::PeriodicMove(p,Len);
    for(int i=0;i<N;i+=2) {
      updateRadius(i,Radi,rt,Prt,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=2) {
	updateRadius(j,Radj,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	//箱端考慮. relrx relryの更新
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm) {
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
DP JT::dim2::potential(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2, int D, DP eps)
{
  if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relr,powterm;
    JT::PeriodicMove(p,Len);
    for(int i=0;i<N;i+=2) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=2) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	//箱端考慮. relrx relryの更新
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm) {
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
DP JT::dim2::potential(Vec_IO_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt, int D,DP eps)
{
 if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relr,powterm;
    JT::dim2::PeriodicMove2D(p,Lx,Ly);
    for(int i=0;i<N;i+=2) {
      updateRadius(i,Radi,rt,Prt,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=2) {
	updateRadius(j,Radj,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	//箱端考慮. relrx relryの更新
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm) {
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
DP JT::dim2::potential(Vec_IO_DP &p,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2, int D,DP eps)
{
 if(checkdim2(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relr,powterm;
    JT::dim2::PeriodicMove2D(p,Lx,Ly);
    for(int i=0;i<N;i+=2) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=2) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	//箱端考慮. relrx relryの更新
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm) {
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

//---------------------------------------------------
//potential V(3D)を求める関数------------------------
//---------------------------------------------------

DP JT::dim3::potential3D(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relrz,relr,powterm;
    JT::PeriodicMove(p,Len);
    for(int i=0;i<N;i+=3) {
      updateRadius(i,Radi,rt,Prt,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=3) {
	updateRadius(j,Radj,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	//箱端考慮. relrx relryの更新
	OutofPeriodicboundary3D(relrx,relry,relrz,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	if(relr<sgm) {
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
DP JT::dim3::potential3D(Vec_IO_DP &p,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relrz,relr,powterm;
    JT::PeriodicMove(p,Len);
    for(int i=0;i<N;i+=3) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=3) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	//箱端考慮. relrx relryの更新
	OutofPeriodicboundary3D(relrx,relry,relrz,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	if(relr<sgm) {
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
DP JT::dim3::potential3D(Vec_IO_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relrz,relr,powterm;
    JT::dim3::PeriodicMove3D(p,Lx,Ly,Lz);
    for(int i=0;i<N;i+=3) {
      updateRadius(i,Radi,rt,Prt,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=3) {
	updateRadius(j,Radj,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	//箱端考慮. relrx relryの更新
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	if(relr<sgm) {
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
DP JT::dim3::potential3D(Vec_IO_DP &p,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
{
  if(checkdim3(D)) {
    int N=p.size();
    DP sgm,pot=0.0,Radi=R,Radj,relrx,relry,relrz,relr,powterm;
    JT::dim3::PeriodicMove3D(p,Lx,Ly,Lz);
    for(int i=0;i<N;i+=3) {
      updateRadius(i,Radi,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      for(int j=0;j<i;j+=3) {
	updateRadius(j,Radj,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	//箱端考慮. relrx relryの更新
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	if(relr<sgm) {
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


//--------------------------------------------------
//-----------------Hessian Matrix(2D)---------------
//--------------------------------------------------

void JT::dim2::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=2) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt,N);
      Radj=R;//初期化
      rtinv_j=1.0;
      for(int j=0;j<i;j+=2) {
	updateRadius_Hessian2D(j,Radj,rtinv_j,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	OutofPeriodicboundary2D(relrx,relry,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm)
	  {
	    fact=eps/(sgm*sgm*relr*relr*relr);
	    tmpxx=fact*(sgm*relry*relry-pow(relr,3));
	    tmpxy=-fact*sgm*relrx*relry;
	    tmpyy=fact*(sgm*relrx*relrx-pow(relr,3));
		
	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
	  }
      }//j-loop-end
    }//i-loop-end
  }//if end
  return;
}
void JT::dim2::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=2) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      rtinv_j=1.0;
      for(int j=0;j<i;j+=2) {
	updateRadius_Hessian2D(j,Radj,rtinv_j,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	OutofPeriodicboundary2D(relrx,relry,Len,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm)
	  {
	    fact=eps/(sgm*sgm*relr*relr*relr);
	    tmpxx=fact*(sgm*relry*relry-pow(relr,3));
	    tmpxy=-fact*sgm*relrx*relry;
	    tmpyy=fact*(sgm*relrx*relrx-pow(relr,3));
		
	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
	  }
      }//j-loop-end
    }//i-loop-end
  }//if end
  return;
}
void JT::dim2::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt,int D,DP eps)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=2) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt,N);
      Radj=R;//初期化
      rtinv_j=1.0;
      for(int j=0;j<i;j+=2) {
	updateRadius_Hessian2D(j,Radj,rtinv_j,rt,Prt,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm)
	  {
	    fact=eps/(sgm*sgm*relr*relr*relr);
	    tmpxx=fact*(sgm*relry*relry-pow(relr,3));
	    tmpxy=-fact*sgm*relrx*relry;
	    tmpyy=fact*(sgm*relrx*relrx-pow(relr,3));
		
	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
	  }
      }//j-loop-end
    }//i-loop-end
  }//if end
  return;
}
void JT::dim2::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim2(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=2) {
      updateRadius_Hessian2D(i,Radi,rtinv_i,rt,Prt1,Prt2,N);
      Radj=R;//初期化
      rtinv_j=1.0;
      for(int j=0;j<i;j+=2) {
	updateRadius_Hessian2D(j,Radj,rtinv_j,rt,Prt1,Prt2,N);
	sgm=Radi+Radj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(relrx*relrx+relry*relry);
	if(relr<sgm)
	  {
	    fact=eps/(sgm*sgm*relr*relr*relr);
	    tmpxx=fact*(sgm*relry*relry-pow(relr,3));
	    tmpxy=-fact*sgm*relrx*relry;
	    tmpyy=fact*(sgm*relrx*relrx-pow(relr,3));
		
	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
	  }
      }//j-loop-end
    }//i-loop-end
  }//if end
  return;
}

//--------------------------------------------------
//-----------------Hessian Matrix(3D)---------------
//--------------------------------------------------

void JT::dim3::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D,DP eps)
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relrz,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=3) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt,N);
	Radj=R;//初期化
	rtinv_j=1.0;
	for(int j=0;j<i;j+=3) {
	  updateRadius_Hessian3D(j,Radj,rtinv_j,rt,Prt,N);
	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  relrz=p[j+2]-p[i+2];
	  OutofPeriodicboundary3D(relrx,relry,relrz,Len,sgm);
	  relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	  if(relr<sgm) {
	    fact=eps/(sgm*sgm*relr*relr*relr);
		  
	    tmpxx=fact*(sgm*(relry*relry+relrz*relrz)-pow(relr,3));
	    tmpxy=-1.0*fact*sgm*(relrx*relry);
	    tmpyy=fact*(sgm*(relrz*relrz+relrx*relrx)-pow(relr,3));
	    tmpyz=-1.0*fact*sgm*(relry*relrz);
	    tmpzz=fact*(sgm*(relrx*relrx+relry*relry)-pow(relr,3));
	    tmpzx=-1.0*fact*sgm*(relrz*relrx);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分		 
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
		  
	    //---y,z互い違いのHessian成分
	    H[i+1][j+2]=H[i+2][j+1]=H[j+2][i+1]=H[j+1][i+2]=rtinv_i*rtinv_j*tmpyz;
	    H[i+2][i+1]=H[i+1][i+2]-=rtinv_i*rtinv_i*tmpyz;
	    H[j+2][j+1]=H[j+1][j+2]-=rtinv_j*rtinv_j*tmpyz;

	    //---z,z同士のHessian成分
	    H[i+2][j+2]=H[j+2][i+2]=rtinv_i*rtinv_j*tmpzz;
	    H[i+2][i+2]-=rtinv_i*rtinv_i*tmpzz;
	    H[j+2][j+2]-=rtinv_j*rtinv_j*tmpzz;
		  
	    //---z,x互い違いのHessian成分
	    H[i][j+2]=H[i+2][j]=H[j+2][i]=H[j][i+2]=rtinv_i*rtinv_j*tmpzx;
	    H[i+2][i]=H[i][i+2]-=rtinv_i*rtinv_i*tmpzx;
	    H[j+2][j]=H[j][j+2]-=rtinv_j*rtinv_j*tmpzx;
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}
void JT::dim3::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relrz,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=3) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt1,Prt2,N);
	Radj=R;//初期化
	rtinv_j=1.0;
	for(int j=0;j<i;j+=3) {
	  updateRadius_Hessian3D(j,Radj,rtinv_j,rt,Prt1,Prt2,N);
	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  relrz=p[j+2]-p[i+2];
	  OutofPeriodicboundary3D(relrx,relry,relrz,Len,sgm);
	  relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	  if(relr<sgm) {
	    fact=eps/(sgm*sgm*relr*relr*relr);
		  
	    tmpxx=fact*(sgm*(relry*relry+relrz*relrz)-pow(relr,3));
	    tmpxy=-1.0*fact*sgm*(relrx*relry);
	    tmpyy=fact*(sgm*(relrz*relrz+relrx*relrx)-pow(relr,3));
	    tmpyz=-1.0*fact*sgm*(relry*relrz);
	    tmpzz=fact*(sgm*(relrx*relrx+relry*relry)-pow(relr,3));
	    tmpzx=-1.0*fact*sgm*(relrz*relrx);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分		 
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
		  
	    //---y,z互い違いのHessian成分
	    H[i+1][j+2]=H[i+2][j+1]=H[j+2][i+1]=H[j+1][i+2]=rtinv_i*rtinv_j*tmpyz;
	    H[i+2][i+1]=H[i+1][i+2]-=rtinv_i*rtinv_i*tmpyz;
	    H[j+2][j+1]=H[j+1][j+2]-=rtinv_j*rtinv_j*tmpyz;

	    //---z,z同士のHessian成分
	    H[i+2][j+2]=H[j+2][i+2]=rtinv_i*rtinv_j*tmpzz;
	    H[i+2][i+2]-=rtinv_i*rtinv_i*tmpzz;
	    H[j+2][j+2]-=rtinv_j*rtinv_j*tmpzz;
		  
	    //---z,x互い違いのHessian成分
	    H[i][j+2]=H[i+2][j]=H[j+2][i]=H[j][i+2]=rtinv_i*rtinv_j*tmpzx;
	    H[i+2][i]=H[i][i+2]-=rtinv_i*rtinv_i*tmpzx;
	    H[j+2][j]=H[j][j+2]-=rtinv_j*rtinv_j*tmpzx;
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}
void JT::dim3::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt,int D,DP eps)
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relrz,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=3) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt,N);
	Radj=R;//初期化
	rtinv_j=1.0;
	for(int j=0;j<i;j+=3) {
	  updateRadius_Hessian3D(j,Radj,rtinv_j,rt,Prt,N);
	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  relrz=p[j+2]-p[i+2];
	  OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	  relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	  if(relr<sgm) {
	    fact=eps/(sgm*sgm*relr*relr*relr);
		  
	    tmpxx=fact*(sgm*(relry*relry+relrz*relrz)-pow(relr,3));
	    tmpxy=-1.0*fact*sgm*(relrx*relry);
	    tmpyy=fact*(sgm*(relrz*relrz+relrx*relrx)-pow(relr,3));
	    tmpyz=-1.0*fact*sgm*(relry*relrz);
	    tmpzz=fact*(sgm*(relrx*relrx+relry*relry)-pow(relr,3));
	    tmpzx=-1.0*fact*sgm*(relrz*relrx);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分		 
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
		  
	    //---y,z互い違いのHessian成分
	    H[i+1][j+2]=H[i+2][j+1]=H[j+2][i+1]=H[j+1][i+2]=rtinv_i*rtinv_j*tmpyz;
	    H[i+2][i+1]=H[i+1][i+2]-=rtinv_i*rtinv_i*tmpyz;
	    H[j+2][j+1]=H[j+1][j+2]-=rtinv_j*rtinv_j*tmpyz;

	    //---z,z同士のHessian成分
	    H[i+2][j+2]=H[j+2][i+2]=rtinv_i*rtinv_j*tmpzz;
	    H[i+2][i+2]-=rtinv_i*rtinv_i*tmpzz;
	    H[j+2][j+2]-=rtinv_j*rtinv_j*tmpzz;
		  
	    //---z,x互い違いのHessian成分
	    H[i][j+2]=H[i+2][j]=H[j+2][i]=H[j][i+2]=rtinv_i*rtinv_j*tmpzx;
	    H[i+2][i]=H[i][i+2]-=rtinv_i*rtinv_i*tmpzx;
	    H[j+2][j]=H[j][j+2]-=rtinv_j*rtinv_j*tmpzx;
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}
void JT::dim3::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,DP eps)
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
  if(alp!=2.0) {
    cerr<<"invalid potential exponent alpha..."<<endl;
    exit(1);
  }
  if(checkdim3(D)) {
    int N =p.size();
    DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,Radi=R,Radj,rtinv_i=1.0,rtinv_j,relrx,relry,relrz,relr,fact;
    H=0.0;
    
    for(int i=0;i<N;i+=3) {
      updateRadius_Hessian3D(i,Radi,rtinv_i,rt,Prt1,Prt2,N);
	Radj=R;//初期化
	rtinv_j=1.0;
	for(int j=0;j<i;j+=3) {
	  updateRadius_Hessian3D(j,Radj,rtinv_j,rt,Prt1,Prt2,N);
	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  relrz=p[j+2]-p[i+2];
	  OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	  relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	  if(relr<sgm) {
	    fact=eps/(sgm*sgm*relr*relr*relr);
		  
	    tmpxx=fact*(sgm*(relry*relry+relrz*relrz)-pow(relr,3));
	    tmpxy=-1.0*fact*sgm*(relrx*relry);
	    tmpyy=fact*(sgm*(relrz*relrz+relrx*relrx)-pow(relr,3));
	    tmpyz=-1.0*fact*sgm*(relry*relrz);
	    tmpzz=fact*(sgm*(relrx*relrx+relry*relry)-pow(relr,3));
	    tmpzx=-1.0*fact*sgm*(relrz*relrx);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	    //---x,x同士のHessian成分
	    H[i][j]=H[j][i]=rtinv_i*rtinv_j*tmpxx;
	    H[i][i]-=rtinv_i*rtinv_i*tmpxx;
	    H[j][j]-=rtinv_j*rtinv_j*tmpxx;

	    //---x,y互い違いのHessian成分
	    H[i][j+1]=H[i+1][j]=H[j+1][i]=H[j][i+1]=rtinv_i*rtinv_j*tmpxy;
	    H[i+1][i]=H[i][i+1]-=rtinv_i*rtinv_i*tmpxy;
	    H[j+1][j]=H[j][j+1]-=rtinv_j*rtinv_j*tmpxy;

	    //---y,y同士のHessian成分		 
	    H[i+1][j+1]=H[j+1][i+1]=rtinv_i*rtinv_j*tmpyy;
	    H[i+1][i+1]-=rtinv_i*rtinv_i*tmpyy;
	    H[j+1][j+1]-=rtinv_j*rtinv_j*tmpyy;
		  
	    //---y,z互い違いのHessian成分
	    H[i+1][j+2]=H[i+2][j+1]=H[j+2][i+1]=H[j+1][i+2]=rtinv_i*rtinv_j*tmpyz;
	    H[i+2][i+1]=H[i+1][i+2]-=rtinv_i*rtinv_i*tmpyz;
	    H[j+2][j+1]=H[j+1][j+2]-=rtinv_j*rtinv_j*tmpyz;

	    //---z,z同士のHessian成分
	    H[i+2][j+2]=H[j+2][i+2]=rtinv_i*rtinv_j*tmpzz;
	    H[i+2][i+2]-=rtinv_i*rtinv_i*tmpzz;
	    H[j+2][j+2]-=rtinv_j*rtinv_j*tmpzz;
		  
	    //---z,x互い違いのHessian成分
	    H[i][j+2]=H[i+2][j]=H[j+2][i]=H[j][i+2]=rtinv_i*rtinv_j*tmpzx;
	    H[i+2][i]=H[i][i+2]-=rtinv_i*rtinv_i*tmpzx;
	    H[j+2][j]=H[j][j+2]-=rtinv_j*rtinv_j*tmpzx;
	  }
	}//j-loop-end
      }//i-loop-end
  }
  return;
}


//--------------------------------------------------
//Distribution of coordination numberを計算func-----
//--------------------------------------------------

inline void JT::distcalc(Vec_IO_DP &Dcod,Vec_I_INT num,int dim)
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

void JT::DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relrz,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.

  if(D==2) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,L,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  else if(D==3) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,L,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2)+pow(relrz,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
}//end void NR::DISTcod
void JT::DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt1,int Prt2,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relrz,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.

  if(D==2) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,L,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  else if(D==3) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,L,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2)+pow(relrz,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
}//end void NR::DISTcod


void JT::dim2::DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.

  if(D==2) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
}//end void NR::DISTcod
void JT::dim2::DISTcod2D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP rt,int Prt1,int Prt2,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.

  if(D==2) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	JT::dim2::OutofPeriodicboundary2D(relrx,relry,Lx,Ly,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
}//end void NR::DISTcod
void JT::dim3::DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relrz,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.
  if(D==3) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2)+pow(relrz,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
}//end void NR::DISTcod
void JT::dim3::DISTcod3D(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP Lx,DP Ly,DP Lz,DP rt,int Prt1,int Prt2,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  DP sgm,relrx,relry,relrz,relr,Ri=R,Rj=R;
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;//i粒子の接触数.
  if(D==3) {
    for(int i=0;i<N;i+=D) {
      updateRadius(i,Ri,rt,Prt1,Prt2,N);
      Rj=R;
      for(int j=0;j<i;j+=D) {
	updateRadius(j,Rj,rt,Prt1,Prt2,N);
	sgm=Ri+Rj;
	relrx=p[j]-p[i];
	relry=p[j+1]-p[i+1];
	relrz=p[j+2]-p[i+2];
	JT::dim3::OutofPeriodicboundary3D(relrx,relry,relrz,Lx,Ly,Lz,sgm);
	relr=sqrt(pow(relrx,2)+pow(relry,2)+pow(relrz,2));
	if(relr<sgm) {
	  tmpnum[i/D]+=1;
	  tmpnum[j/D]+=1;
	}
      }//for-j-end
    }//for-i-end
  }
  distcalc(Dcod,tmpnum,D);
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

void JT::noise(Vec_IO_DP& p,DP R,DP n_disp_ratio)
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
}

#endif
