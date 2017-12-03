#ifndef _VELVER_H_
#define _VELVER_H_

#include "nr.h"
#include "jttool.h"
#include "MT.h"
#include <limits>

namespace JT
{
  //---------------------------//
  //--Velocity Verlet(skiing)--//
  //--------(velver.h)---------//
  //---------------------------//

  void nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Len);
  void nextvel_F(Vec_IO_DP &vel, Vec_I_DP &Fnxt,Vec_I_DP &F);
  void Gen_MBdist(Vec_IO_DP &vel, DP mass, DP kT,DP rt,int Prt1,int Prt2,int D);
  
  namespace dim2
  {
    void nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Lx,DP Ly);
    void VVforce_F(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt, DP mass,DP tstep,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax);
    void fastVVFForce2D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt, DP mass,DP tstep,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax,NRVec<vector<int> > &v);
    void Velocity_Verlet_F(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,int,int,int,DP),const DP ftol,DP Lx,DP Ly,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV);
    void fastVVF2D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,int,int,int,DP,NRVec<vector<int> > &v),const DP ftol,DP Lx,DP Ly,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,NRVec<vector<int> > &v,bool &isInit);
    
  }
  namespace dim3
  {
    void nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Lx,DP Ly,DP Lz);
    void VVforce_F3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt,DP mass,DP tstep, DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax);
    void fastVVFForce3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt,DP mass,DP tstep, DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax,NRVec<vector<int> > &v);
    void Velocity_Verlet_F3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,DP,int,int,int,DP),const DP ftol,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV);
    void fastVVF3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,DP,int,int,int,DP,NRVec<vector<int> > &v),const DP ftol,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,NRVec<vector<int> > &v,bool &isInit);
  }
  void FIRE(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int &ITER);
  void FIRE_localEngine(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int &ITER);
  
}

//---------------------------------------------------
//Velocity Verlet Forceを求める関数(2D)--------------
//---------------------------------------------------

void JT::dim2::VVforce_F(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt, DP mass,DP tstep,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{
  relax=false;
  if(checkdim2(D)) {
    int N=p.size();
    DP eps=1.0;
    DP sgm,x,y,tmpx,tmpy,relrx,relry,relr,powterm,Radi=R,Radj,tsum=0.0,Fsum=0.0;//半径等は系のサイズで調節すること。
    DP tfact,Ffact,M=mass,Const,Fconst,a=alp-1;
    bool m1=false,m2;
    Vec_DP veltmp(N);
    Fpot=0.0;
    
    for(int i=0;i<N;i+=D) {
      JT::updateParticle(i,Radi,M,rt,Prt1,Prt2,N,D,m1);
      initializeParticle2(Radj,R,x,y,p[i],p[i+1],m2);
      for(int j=i+D;j<N;j+=D) {
	JT::updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);

	if(overlapped2D_F(x,y,p[j],p[j+1],Lx,Ly,Radi,Radj,sgm,relr,relrx,relry)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  Fconst=eps/(sgm*relr);
	  tmpx=-relrx*Fconst*pow(powterm,a);
	  tmpy=-relry*Fconst*pow(powterm,a);
	  //ポテンシャル勾配の対称成分から現れる項も同時に計算する。
	  Fpot[j]-=tmpx;
	  Fpot[j+1]-=tmpy;
	  Fpot[i]+=tmpx;
	  Fpot[i+1]+=tmpy;
	}
      }//j-loop-end

      for(int k=i;k<i+D;k++) {
	veltmp[k]=vel[k]+F[k];
	Fsum+=Fpot[k]*Fpot[k];
	tfact=2*M*veltmp[k]+tstep*Fpot[k];
	tsum+=tfact*tfact;
      }
    }//i-loop-end

    tfact=sqrt(tsum);
    Ffact=sqrt(Fsum);
    Const=1.0/(2*mass+dmpt);
    if(Ffact==0.0)
      for(int k=0;k<N;k++) {
	if((Prt1+Prt2)*k==Prt1*N) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]);
      }
    else {
      Fconst=1.0/Ffact;
      for(int k=0;k<N;k++) {
	if((Prt1+Prt2)*k==Prt1*N) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
      }
    }
  }
}//end
void JT::dim2::fastVVFForce2D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt, DP mass,DP tstep,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax,NRVec<vector<int> > &v)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{
  relax=false;
  if(checkdim2(D)) {
    int N=v.size(),DN=D*N;
    if(D*N!=p.size()) {
      cerr<<"nya"<<endl;
      exit(1);
    }
    DP eps=1.0;
    DP sgm,x,y,tmpx,tmpy,relrx,relry,relr,powterm,Radi=R,Radj,tsum=0.0,Fsum=0.0;//半径等は系のサイズで調節すること。
    DP tfact,Ffact,M=mass,Const,Fconst,a=alp-1;
    int I,J;
    bool m1=false,m2;
    Vec_DP veltmp(DN);
    Fpot=0.0;
    
    for(int i=0;i<N;i++) {
      JT::updateParticle(i,Radi,M,rt,Prt1,Prt2,N,D,m1);
      I=D*i;
      initializeParticle2(Radj,R,x,y,p[I],p[I+1],m2);
      for(unsigned int l=0;l<v[i].size();l++) {
	J=D*v[i][l];
	JT::updateRadiusF(J,Radj,rt,Prt1,Prt2,N,D,m2);
	if(overlapped2D_F(x,y,p[J],p[J+1],Lx,Ly,Radi,Radj,sgm,relr,relrx,relry)) {
	  powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	  Fconst=eps/(sgm*relr);
	  tmpx=-relrx*Fconst*pow(powterm,a);
	  tmpy=-relry*Fconst*pow(powterm,a);
	  //ポテンシャル勾配の対称成分から現れる項も同時に計算する。
	  Fpot[J]-=tmpx;
	  Fpot[J+1]-=tmpy;
	  Fpot[I]+=tmpx;
	  Fpot[I+1]+=tmpy;
	}
      }//j-loop-end

      for(int k=I;k<I+D;k++) {
	Fsum+=Fpot[k]*Fpot[k];
	veltmp[k]=vel[k]+F[k];
	tfact=2*M*veltmp[k]+tstep*Fpot[k];
	tsum+=tfact*tfact;
      }
    }//i-loop-end

    tfact=sqrt(tsum);
    Ffact=sqrt(Fsum);
    Const=1.0/(2*mass+dmpt);
    if(Ffact==0.0)
      for(int k=0;k<DN;k++) {
	if((Prt1+Prt2)*k==Prt1*DN) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]);
      }
    else {
      Fconst=1.0/Ffact;
      for(int k=0;k<DN;k++) {
	if((Prt1+Prt2)*k==Prt1*DN) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
      }
    }
  }
}//end


//---------------------------------------------------
//Velocity Verlet Forceを求める関数(3D)--------------
//---------------------------------------------------

void JT::dim3::VVforce_F3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt,DP mass,DP tstep, DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{
  relax=false;
  if(checkdim3(D)) {
    int N=p.size();
    DP eps=1.0;
    DP sgm,tmpx,tmpy,tmpz,x,y,z;//半径等は系のサイズで調節すること。
    DP Radi=R,Radj,relrx,relry,relrz,relr,powterm,tsum=0.0,Fsum=0.0;
    bool m1=false,m2;
    Fpot=0.0;
    DP tfact,Ffact,M=mass,Const,Fconst,a=alp-1;
    Vec_DP veltmp(N);

    for(int i=0;i<N;i+=D) {
      JT::updateParticle(i,Radi,M,rt,Prt1,Prt2,N,D,m1);
      initializeParticle2(Radj,R,x,y,z,p[i],p[i+1],p[i+2],m2);

      for(int j=i+D;j<N;j+=D) {
	JT::updateRadius(j,Radj,rt,Prt1,Prt2,N,m2);
	if(overlapped3D_F(x,y,z,p[j],p[j+1],p[j+2],Lx,Ly,Lz,Radi,Radj,sgm,relr,relrx,relry,relrz))
	  {
	    powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	    Fconst=eps/(sgm*relr);
	    tmpx=-1.0*relrx*Fconst*pow(powterm,a);
	    tmpy=-1.0*relry*Fconst*pow(powterm,a);
	    tmpz=-1.0*relrz*Fconst*pow(powterm,a);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。
	    Fpot[j]-=tmpx;
	    Fpot[j+1]-=tmpy;
	    Fpot[j+2]-=tmpz;
	    Fpot[i]+=tmpx;
	    Fpot[i+1]+=tmpy;
	    Fpot[i+2]+=tmpz;
	  }
      }//j-loop-end

      for(int k=i;k<i+D;k++) {
	veltmp[k]=vel[k]+F[k];
	Fsum+=Fpot[k]*Fpot[k];
	tfact=2*M*veltmp[k]+tstep*Fpot[k];
	tsum+=tfact*tfact;
      }
    }//i-loop-end

    tfact=sqrt(tsum);
    Ffact=sqrt(Fsum);
    Const=1.0/(2*mass+dmpt);
    if(Ffact==0.0)
      for(int k=0;k<N;k++) {
	if((Prt1+Prt2)*k==Prt1*N) {
	  //BIdisperseのときmassとRadを変更する
	  Const=1.0/(2*mass*rt*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]);
      }
    else {
      Fconst=1.0/Ffact;
      for(int k=0;k<N;k++) {
	if((Prt1+Prt2)*k==Prt1*N) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
      }
    }
  }
}//end
void JT::dim3::fastVVFForce3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt,DP mass,DP tstep, DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int D,bool &relax,NRVec<vector<int> > &v)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{
  relax=false;
  if(checkdim3(D)) {
    const int N=v.size(),DN=p.size();
    if(D*N!=p.size()) {
      cerr<<"nya"<<endl;
      exit(1);
    }
    DP eps=1.0;
    DP sgm,tmpx,tmpy,tmpz,x,y,z;//半径等は系のサイズで調節すること。
    DP Radi=R,Radj,relrx,relry,relrz,relr,powterm,tsum=0.0,Fsum=0.0;
    bool m1=false,m2;
    Fpot=0.0;
    DP tfact,Ffact,M=mass,Const,Fconst,a=alp-1;
    int I,J;
    Vec_DP veltmp(DN);

    for(int i=0;i<N;i++) {
      JT::updateParticle(i,Radi,M,rt,Prt1,Prt2,N,D,m1);
      I=D*i;
      initializeParticle2(Radj,R,x,y,z,p[I],p[I+1],p[I+2],m2);
      for(unsigned int l=0;l<v[i].size();l++) {
	J=D*v[i][l];
	JT::updateRadiusF(J,Radj,rt,Prt1,Prt2,N,D,m2);
	if(overlapped3D_F(x,y,z,p[J],p[J+1],p[J+2],Lx,Ly,Lz,Radi,Radj,sgm,relr,relrx,relry,relrz))
	  {
	    powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	    Fconst=eps/(sgm*relr);
	    tmpx=-1.0*relrx*Fconst*pow(powterm,a);
	    tmpy=-1.0*relry*Fconst*pow(powterm,a);
	    tmpz=-1.0*relrz*Fconst*pow(powterm,a);
	    //ポテンシャル勾配の対称成分から現れる項も同時に計算する。
	    Fpot[J]-=tmpx;
	    Fpot[J+1]-=tmpy;
	    Fpot[J+2]-=tmpz;
	    Fpot[I]+=tmpx;
	    Fpot[I+1]+=tmpy;
	    Fpot[I+2]+=tmpz;
	  }
      }//j-loop-end

      for(int k=I;k<I+D;k++) {
	veltmp[k]=vel[k]+F[k];
	Fsum+=Fpot[k]*Fpot[k];
	tfact=2*M*veltmp[k]+tstep*Fpot[k];
	tsum+=tfact*tfact;
      }
    }//i-loop-end

    tfact=sqrt(tsum);
    Ffact=sqrt(Fsum);
    Const=1.0/(2*mass+dmpt);
    if(Ffact==0.0)
      for(int k=0;k<DN;k++) {
	if((Prt1+Prt2)*k==Prt1*DN) {
	  //BIdisperseのときmassとRadを変更する
	  Const=1.0/(2*mass*rt*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]);
      }
    else {
      Fconst=1.0/Ffact;
      for(int k=0;k<DN;k++) {
	if((Prt1+Prt2)*k==Prt1*DN) {
	  //BIdisperseのときmassとRadを変更する.
	  Const=1.0/(2*mass*rt*rt*rt+dmpt);
	}
	F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
      }
    }
  }
}//end


//------------------------------------------------
//次の座標値を求める(FIRE ver.)
//------------------------------------------------

void JT::nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Len)
{
  int N =zahyo.size();
  for(int i=0;i<N;i++)
    zahyo[i]+=tstep*(vel[i]+F[i]);
  JT::PeriodicMove(zahyo,Len);  
}
void JT::dim2::nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Lx,DP Ly)
{
  int N =zahyo.size();
  for(int i=0;i<N;i++)
    zahyo[i]+=tstep*(vel[i]+F[i]);
  JT::dim2::PeriodicMove2D(zahyo,Lx,Ly);  
}
void JT::dim3::nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Lx,DP Ly,DP Lz)
{
  int N =zahyo.size();
  for(int i=0;i<N;i++)
    zahyo[i]+=tstep*(vel[i]+F[i]);
  JT::dim3::PeriodicMove3D(zahyo,Lx,Ly,Lz);  
}

//------------------------------------------------
//次の速度を求める(FIRE ver.)
//------------------------------------------------

void JT::nextvel_F(Vec_IO_DP &vel, Vec_I_DP &Fnxt,Vec_I_DP &F)
{
  int N=vel.size();
  for(int i=0;i<N;i++)
    vel[i]+=Fnxt[i]+F[i];
}


//----------------------------------------------------------------------------
//与えられた温度での正規分布に従う速度分布(Maxwell-Boltzmann分布)を求める関数
//----------------------------------------------------------------------------
void JT::Gen_MBdist(Vec_IO_DP &vel, DP mass, DP kT,DP rt,int Prt1,int Prt2 ,int D)
{
  int N=vel.size();
  DP mfact= 1.0/mass;
  MT::init_genrand((unsigned)time(NULL));

  for(int i=0;i<N;i++) {
    if((Prt1+Prt2)*i==Prt1*N)//後半はこの値で.
      mfact/=pow(rt,D);
    vel[i]=sqrt(-2.0*kT*mfact*log(MT::genrand_real1()))*cos(2*M_PI*MT::genrand_real2());
  }
}

//----------------------------------------------------------------
//Fast Inertial Relaxation Engine (Velocity Verlet ver.)
//----------------------------------------------------------------
void JT::dim2::Velocity_Verlet_F(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,int,int,int,DP),const DP ftol,DP Lx,DP Ly,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV)
{
  if(checkdim2(D)) {
    int N=p.size();
    Vec_DP Force(N),Forcetmp(N),PotForce(N);
    const int ITMAX=iterVV;
    int ITER=0,itbrk=0;
    bool relax=false;
    const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
    DP fret,fp,DMPt=dmpt;
    iterVV=0;
    fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps);
    fp=fret;
    for(int i=0;i<N;i++)
      Force[i]=vel[i]=0.0;
    JT::dim2::VVforce_F(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax);
    Forcetmp=Force;
    for(int it=0;it<ITMAX;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly);
      VVforce_F(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      Forcetmp=Force;
      fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps);
      iterVV+=1;

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50)
	  itbrk+=1;
	else {
	  cout<<"ENG-relative-error-min break."<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fabs(fret)==0.0) {//unjammed stateに落ちた。
	cout<<"ENG-zero break."<<endl;
	return;
      }
      fp=fret;
      
    }// i-loop-end
  }
}
void JT::dim2::fastVVF2D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,int,int,int,DP,NRVec<vector<int> > &v),const DP ftol,DP Lx,DP Ly,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,NRVec<vector<int> > &v,bool &isInit)
{
  if(checkdim2(D)) {
    //cout<<"start velver2D!"<<endl;
    int N=p.size();
    Vec_DP Force(N),Forcetmp(N),PotForce(N);
    int fI;
    if(N<=384) {
      fI=1;
    }
    else if(N>384 && N<=3*pow(2.0,19)) {
      fI=N/384;
    }
    else {
      fI=pow(2.0,12);
    }
    int fInit=1;
    if(!isInit) {
      fInit=10;
    }
    const int ITMAX=iterVV,first=5,second=150,third=50000*fInit,ITsecond=1500*fI; //default: 5000
    int ITfirst=100*fI; // ITfirst =O(2N)=300*factI default: 1000
    int ITER=0,itbrk=0;
    bool relax=false;
    const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
    DP fret,fp,DMPt=dmpt;
    iterVV=0;
    fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
    fp=fret;
    for(int i=0;i<N;i++)
      Force[i]=vel[i]=0.0;
    modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
    fastVVFForce2D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax,v);
    Forcetmp=Force;
    if(isInit) {
      for(int it=0;it<ITfirst;it++) {
	nextcod_F(p,vel,Force,tstep,Lx,Ly);
	fastVVFForce2D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax,v);
	JT::nextvel_F(vel,Force,Forcetmp);
	JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
	Forcetmp=Force;
	fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
	iterVV+=1;
	if((it+1)%first==0) {
	  modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
	}
	fp=fret;
      }
      isInit=true;
    }
    for(int it=ITfirst;it<ITsecond;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly);
      fastVVFForce2D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax,v);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      Forcetmp=Force;
      fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
      iterVV+=1;

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50) {
	  if(itbrk%10==1)
	    modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
	  itbrk+=1;
	}
	else {
	  cout<<"ENG-relative-error-min. break(2nd)"<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fret==0.0) {//unjammed stateに落ちた。
	modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
	fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
	if(fret==0.0) {
	  cout<<"ENG-zero. break(2nd)"<<endl;
	  return;
	}
      }
      if((it+1)%second==0) {
	modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
      }
      fp=fret;
    }// i-loop-end
    for(int it=ITsecond;it<ITMAX;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly);
      fastVVFForce2D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,R,rt,alp,Prt1,Prt2,D,relax,v);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      Forcetmp=Force;
      fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
      iterVV+=1;

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50) {
	  if(itbrk%10==1)
	    modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
	  itbrk+=1;
	}
	else {
	  cout<<"ENG-relative-error-min. break(3rd)"<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fret==0.0) {//unjammed stateに落ちた。
	modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
	fret=func(p,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
	if(fret==0.0) {
	  cout<<"ENG-zero. break(3rd)"<<endl;
	  return;
	}
      }
      if((it+1)%third==0) {
	modifyContactList(v,p,Lx,Ly,R,rt,Prt1,Prt2,D);
      }
      fp=fret;
    }// i-loop-end
  }
}
void JT::dim3::Velocity_Verlet_F3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,DP,int,int,int,DP),const DP ftol,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV)
{
  if(checkdim3(D)) {
    int N=p.size();
    Vec_DP Force(N),Forcetmp(N),PotForce(N);
    const int ITMAX=iterVV;
    int ITER=0,itbrk=0;
    iterVV=0;
    bool relax=false;
    const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
    DP fret,fp,DMPt=dmpt;
    fp=fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps);

    for(int i=0;i<N;i++)
      Force[i]=vel[i]=0.0;
    JT::dim3::VVforce_F3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax);
    Forcetmp=Force;
    for(int it=0;it<ITMAX;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly,Lz);
      VVforce_F3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      iterVV+=1;
      Forcetmp=Force;
      fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps);

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50)
	  itbrk+=1;
	else {
	  cout<<"ENG-relative-error-min break."<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fabs(fret)==0.0) {//unjammed stateに落ちた。
	cout<<"ENG-zero. break"<<endl;
	return;
      }
      fp=fret;
    }// i-loop-end
  }
}
void JT::dim3::fastVVF3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,DP,DP,int,int,int,DP,NRVec<vector<int> > &v),const DP ftol,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,DP eps,int Prt1,int Prt2,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,NRVec<vector<int> > &v,bool &isInit)
{
  if(checkdim3(D)) {
    //cout<<"start velver3D!"<<endl;
    int N=p.size();
    Vec_DP Force(N),Forcetmp(N),PotForce(N);
    int fI;
    if(N<=384) {
      fI=1;
    }
    else if(N>384 && N<=3*pow(2.0,19)) {
      fI=N/384;
    }
    else {
      fI=pow(2.0,12);
    }
    int fInit=1;
    if(!isInit) {
      fInit=10;
    }
    const int ITMAX=iterVV,first=5,second=150,third=50000*fInit,ITsecond=1500*fI; //default: 5000
    int ITfirst=100*fI; // ITfirst =O(3N)=300*factI default: 1000
    int ITER=0,itbrk=0;
    iterVV=0;
    bool relax=false;
    const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
    DP fret,fp,DMPt=dmpt;
    modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
    fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
    fp=fret;
    for(int i=0;i<N;i++)
      Force[i]=vel[i]=0.0;
    fastVVFForce3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax,v);
    Forcetmp=Force;
    if(isInit) {
      for(int it=0;it<ITfirst;it++) {
	nextcod_F(p,vel,Force,tstep,Lx,Ly,Lz);
	fastVVFForce3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax,v);
	JT::nextvel_F(vel,Force,Forcetmp);
	JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
	iterVV+=1;
	Forcetmp=Force;
	fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
	if((it+1)%first==0) {
	  modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
	}
	fp=fret;
      }// i-loop-end
      isInit=true;
    }
    else {
      ITfirst=0;
    }
    for(int it=ITfirst;it<ITsecond;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly,Lz);
      fastVVFForce3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax,v);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      iterVV+=1;
      Forcetmp=Force;
      fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50) {
	  if(itbrk%10==1)
	    modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
	  itbrk+=1;
	}
	else {
	  cout<<"ENG-relative-error-min. break(2nd)"<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fret==0.0) {//unjammed stateに落ちた。
	modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
	fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
	if(fret==0.0) {
	  cout<<"ENG-zero. break(2nd)"<<endl;
	  return;
	}
      }
      if((it+1)%second==0) {
	modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
      }
      fp=fret;
    }// i-loop-end
    for(int it=ITsecond;it<ITMAX;it++) {
      nextcod_F(p,vel,Force,tstep,Lx,Ly,Lz);
      fastVVFForce3D(p,vel,Force,PotForce,DMPt,mass,tstep,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,relax,v);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      iterVV+=1;
      Forcetmp=Force;
      fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS)) {
	if(itbrk<50) {
	  if(itbrk%10==1)
	    modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);	    
	  itbrk+=1;
	}
	else {
	  cout<<"ENG-relative-error-min. break(3rd)"<<endl;
	  return;
	}
      }
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fret==0.0) {//unjammed stateに落ちた。
	modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
	fret=func(p,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
	if(fret==0.0) {
	  cout<<"ENG-zero. break(3rd)"<<endl;
	  return;
	}
      }
      if((it+1)%third==0) {
	modifyContactList(v,p,Lx,Ly,Lz,R,rt,Prt1,Prt2,D);
      }

      fp=fret;
    }// i-loop-end
  }
}


//------------------------------------------
//FIRE algorithm (the FIRE-step part) の関数
//------------------------------------------
void JT::FIRE(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int &ITER)
{
  DP P=0.0;//,EPS=numeric_limits<double>::epsilon();
  int N=vel.size();
  for(int i=0;i<N;i++)
    P+=vel[i]*Fpot[i];
  if(P>0.0 && ITER>=ITFIRE) {
    ITER+=1;
    if(tstep*fra_inc-tstep_max<0)
      tstep*=fra_inc;
    else
      tstep=tstep_max;
    dmpt*=fra_alp;
  }	
  else if(P<=0.0) {
    ITER=0;
    tstep*=fra_dec;
    for(int i=0;i<N;i++)
      vel[i]=0.0;
    //これが鞍点に止まる原因か??
    //noiseなしのときジャミング点近傍では=EPSにしても鞍点に行くっぽい.
    dmpt=dmpt_init;
  }
  else {
    //(P>0 && ITER<ITFIRE)の場合!!
    ITER+=1;
  }
}

//------------------------------------------
//FIRE algorithm local Engine(the FIRE-step part) の関数
//つかってみたけどゴミだった
//------------------------------------------
void JT::FIRE_localEngine(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int &ITER)
{
  DP Pl,Pg=0.0,EPS=numeric_limits<double>::epsilon();
  int N=vel.size();
  for(int i=0;i<N;i++) {
    Pl=vel[i]*Fpot[i];
    Pg+=Pl;
    if(Pl<=EPS)
      vel[i]=0;
  }
  if(Pg>0.0 && ITER>=ITFIRE) {
    ITER+=1;
    if(tstep*fra_inc-tstep_max<0)
      tstep*=fra_inc;
    else
      tstep=tstep_max;
    dmpt*=fra_alp;
  }	
  else if(Pg<=0.0) {
    ITER=0;
    tstep*=fra_dec;
    dmpt=dmpt_init;
  }
  else {
    //(P>0 && ITER<ITFIRE)の場合!!
    ITER+=1;
  }
}
#endif
