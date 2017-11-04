#ifndef JTEIG_H_
#define JTEIG_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include "jttool.h"
#include "jtfunc.h"
#include "jtmessage.h"
#include "jtcvc.h"
#include "nr.h"
#include "MT.h"

namespace JT
{
  //--------------------//
  //------Eig func------//
  //---(in jteig.cpp)---//
  //--------------------//
  
  void WriteEigInfo(Mat_I_DP &EigMat,Vec_I_DP &Eigval,int num,DP phi,int D,int Prt1,int Prt2,bool &IPRerror);
  void WriteEigInfo_test(Mat_I_DP &EigMat,Vec_I_DP &Eigval,int num,DP phi,int D,int Prt1,int Prt2,bool &IPRerror);
  void deriveEigvec(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,Vec_O_DP &out,DP &eigval,int D,int vecnum);
  void outputPEL(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum,DP func(Vec_IO_DP,DP,DP,DP,int,int,int,DP));
  void CollectiveMotionCheck(Mat_I_DP &EigMat,Vec_IO_DP &CMnum,int D);
  void CollectiveMotionCheck2(Mat_I_DP &EigMat,Vec_IO_DP &CMnum,Vec_IO_DP &CMnum1,Vec_IO_DP &CMnum2,int D,int Prt1,int Prt2);
  void RenomalizeEigvec(Mat_IO_DP &EigMat);
  void RenomalizeEigvec_check(Mat_I_DP &EigMat);
  void countEigComponents(Mat_I_DP &EigMat,Vec_IO_DP &cmp_small_ratio,int Prt1,int Prt2);
  void countEigComponents(Mat_I_DP &EigMat,Vec_IO_DP &cmp_small_ratio,Vec_IO_DP &cmp_all,int Prt1,int Prt2);
  
  namespace dim2
  {
    void ModeCalc2D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror);
    void fastMC2D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror,NRVec<vector<int> > &v);
    void deriveEigvec2D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,Vec_O_DP &out,DP &eigval,int D,int vecnum);
    void outputPEL2D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum,DP func(Vec_IO_DP,DP,DP,DP,DP,int,int,int,DP));
  }
  
  namespace dim3
  {
    void ModeCalc3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror);
    void fastMC3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror,NRVec<vector<int> > &v);
    void deriveEigvec3D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,Vec_O_DP &out,DP &eigval,int D,int vecnum);
    void outputPEL3D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum,DP func(Vec_IO_DP,DP,DP,DP,DP,DP,int,int,int,DP));
  }
}


//--------------------------------------------
//Derivation function for DOS, IPR, and so on.
//--------------------------------------------

void JT::dim2::ModeCalc2D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror)
{
  if(checkdim2(D)) {
    eigplus=true;
    int N=zahyo.size();
    Mat_DP Hes(N,N),EigMat(N,N);
    Vec_DP Eigval(N),Eigvec(N);
    int cnt=0;
    DP eps=1.0;
    invalidflag=false;
    JT::dim2::Hesspot(zahyo,Hes,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps);
    NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
    if(invalidflag==true) {
      cerr<<"jacobi><"<<endl;
      return;
    }
    NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
    calcModeQuantity(EigMat,Eigval,eigplus,D,Prt1,Prt2,rt,IPRerror,num,phi);
    //calcModeQuantity_CVC(zahyo,EigMat,Eigval,eigplus,D,R,Prt1,Prt2,rt,Lx,Ly,IPRerror,num,phi);
  }
}
void JT::dim2::fastMC2D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus, bool &invalidflag,bool &IPRerror,NRVec<vector<int> > &v)
{
  if(checkdim2(D)) {
    eigplus=true;
    int N=zahyo.size();
    Mat_DP Hes(N,N),EigMat(N,N);
    Vec_DP Eigval(N),Eigvec(N);
    int cnt=0;
    DP eps=1.0;
    invalidflag=false;
    JT::dim2::fastHess2D(zahyo,Hes,Lx,Ly,R,rt,alp,Prt1,Prt2,D,eps,v);
    NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
    if(invalidflag==true) {
      cerr<<"jacobi><"<<endl;
      return;
    }
    NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
    calcModeQuantity(EigMat,Eigval,eigplus,D,Prt1,Prt2,rt,IPRerror,num,phi);
    //calcModeQuantity_CVC(zahyo,EigMat,Eigval,eigplus,D,R,Prt1,Prt2,rt,Lx,Ly,IPRerror,num,phi);
  }
}
void JT::dim3::ModeCalc3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus,bool &invalidflag,bool &IPRerror)
{
  if(checkdim3(D)) {

    eigplus=true;
    int N=zahyo.size();
    Mat_DP Hes(N,N),EigMat(N,N);
    Vec_DP Eigval(N),Eigvec(N);
    int cnt=0;
    DP eps=1.0;
    invalidflag=false;
    JT::dim3::Hesspot3D(zahyo,Hes,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps);
    NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
    if(invalidflag==true) {
      cerr<<"jacobi><"<<endl;
      return;
    }
    NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
    calcModeQuantity(EigMat,Eigval,eigplus,D,Prt1,Prt2,rt,IPRerror,num,phi);
    //calcModeQuantity_CVC(zahyo,EigMat,Eigval,eigplus,D,R,Prt1,Prt2,rt,Lx,Ly,Lz,IPRerror,num,phi);
  }
}
void JT::dim3::fastMC3D(Vec_IO_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,int D,bool &eigplus,bool &invalidflag,bool &IPRerror,NRVec<vector<int> > &v)
{
  if(checkdim3(D)) {
    eigplus=true;
    int N=zahyo.size();
    Mat_DP Hes(N,N),EigMat(N,N);
    Vec_DP Eigval(N),Eigvec(N);
    int cnt=0;
    DP eps=1.0;
    invalidflag=false;
    JT::dim3::fastHess3D(zahyo,Hes,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,eps,v);
    NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
    if(invalidflag==true) {
      cerr<<"jacobi><"<<endl;
      return;
    }
    NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
    calcModeQuantity(EigMat,Eigval,eigplus,D,Prt1,Prt2,rt,IPRerror,num,phi);
    //calcModeQuantity_CVC(zahyo,EigMat,Eigval,eigplus,D,R,Prt1,Prt2,rt,Lx,Ly,Lz,IPRerror,num,phi);
  }
}
void JT::WriteEigInfo(Mat_I_DP &EigMat,Vec_I_DP &Eigval,int num,DP phi,int D,int Prt1,int Prt2,bool &IPRerror)
  //----------------------------------------------------------
  //あるサンプルnumの充填率PHIのときの状態密度の累積をTXT出力.
  //----------------------------------------------------------
{
  IPRerror=false;
  int N=Eigval.size();
  Vec_DP CMnumber(N),CMnumber1(N),CMnumber2(N),er_small(N);//,Eigvec(N);
  string wrname;
  DP cmdist=0.0,cm=1.0,EPS=numeric_limits<double>::epsilon(),eg;
  ofstream wrmode;
  setOFSeigmethod(num,phi,wrname);
  wrmode.open(wrname.data());

  JT::CollectiveMotionCheck2(EigMat,CMnumber,CMnumber1,CMnumber2,D,Prt1,Prt2);// IPR をCMnumberに格納
  JT::countEigComponents(EigMat,er_small,Prt1,Prt2);

  for(int i=0;i<N;i++) {
    if(fabs(Eigval[i])>EPS)
      cmdist+=1;
  }
  cmdist=1.0/cmdist;
  
  for(int i=0;i<N;i++) {
      if(fabs(Eigval[i])>EPS) {
	wrmode<<setprecision(10)<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<CMnumber[i]<<' '<<CMnumber1[i]<<' '<<CMnumber2[i]<<' '<<er_small[i]<<' '<<cm<<endl;
	if(CMnumber[i]>0.9) {
	  IPRerror=true;
	  cout<<"=========================="<<endl;
	  cout<<"seednum: "<<num<<", phi: "<<phi<<endl;
	  cout<<setprecision(10)<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<CMnumber[i]<<' '<<CMnumber1[i]<<' '<<CMnumber2[i]<<' '<<er_small[i]<<' '<<cm<<endl;
	  cout<<"=========================="<<endl;
	}
	cm-=cmdist;
      }
      else {
	eg=fabs(Eigval[i]);
	wrmode<<setprecision(10)<<Eigval[i]<<' '<<sqrt(eg)<<' '<<CMnumber[i]<<' '<<CMnumber1[i]<<' '<<CMnumber2[i]<<' '<<er_small[i]<<" 0"<<endl;
      }
    }
}
void JT::WriteEigInfo_test(Mat_I_DP &EigMat,Vec_I_DP &Eigval,int num,DP phi,int D,int Prt1,int Prt2,bool &IPRerror)
//同一固有値かどうかを見極めるためのmethod.
//同一固有値ならば"*"を先頭に打たない.
{
  IPRerror=false;
  int N=Eigval.size();
  Vec_DP CMnumber(N),CMnumber1(N),CMnumber2(N);//,Eigvec(N);
  string wrname;
  stringstream ss,ss2;
  ofstream wrmode;
  DP cmdist=0.0,cm=1.0,EPS=numeric_limits<double>::epsilon(),eg,eigtmp=Eigval[0];
  
  JT::CollectiveMotionCheck2(EigMat,CMnumber,CMnumber1,CMnumber2,D,Prt1,Prt2);// IPR をCMnumberに格納
  setOFSeigmethod(num,phi,wrname);
  wrmode.open(wrname.data());

  wrmode<<"* "<<Eigval[0]<<' '<<sqrt(Eigval[0])<<' '<<CMnumber[0]<<' '<<cm<<endl;
  cm-=cmdist;
  if(CMnumber[0]>0.7)
    IPRerror=true;
  for(int i=1;i<N;i++) {
      //cout<<Eigval[i]<<' '<<cm<<'\n';
      if(fabs(eigtmp-Eigval[i])>EPS)
	wrmode<<setprecision(10)<<"* "<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<CMnumber[i]<<' '<<cm<<endl;
      else {
	eg=fabs(Eigval[i]);
	wrmode<<setprecision(10)<<Eigval[i]<<' '<<sqrt(eg)<<' '<<CMnumber[i]<<" 0"<<endl;
      }
      eigtmp=Eigval[i];
      cm-=cmdist;
      if(CMnumber[i]>0.7)
	IPRerror=true;
    }
}

//----------------------------------------------------
//直交行列から,とある番号の固有ベクターを返却。
//----------------------------------------------------

void JT::dim2::deriveEigvec2D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,Vec_O_DP &out,DP &eigval,int D,int vecnum)
{
  int N=zahyo.size();
  if(vecnum>N-1 || vecnum<0) {
    cerr<<"cannot derive Eigenvector..."<<endl;
    exit(1);
  }
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  bool invalidflag;

  JT::dim2::Hesspot(zahyo,Hes,Lx,Ly,R,rt,alp,Prt1,Prt2,D,1.0);
  NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
  if(invalidflag) {
    return;
  }
  if(rt!=1.0) {
    //BIdisperse=>本来の固有ベクターに変換。
    if(D==2) {
      for(int j=(Prt1*N)/(Prt1+Prt2);j<N;j++) {
	for(int i=0;i<N;i++)
	  EigMat[i][j]*=1.0/rt;
      }
    }
  }
  NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
  for(int i=0;i<N;i++) {
      Eigvec[i]=EigMat[i][vecnum];//どこの固有ベクターにするか数値0~DNumで指定。
    }
  eigval=Eigval[vecnum];  
  out=Eigvec;
}
void JT::dim3::deriveEigvec3D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,Vec_O_DP &out,DP &eigval,int D,int vecnum)
{
  int N=zahyo.size();
  if(vecnum>N-1 || vecnum<0) {
    cerr<<"cannot derive Eigenvector..."<<endl;
    exit(1);
  }
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  bool invalidflag;

  JT::dim3::Hesspot3D(zahyo,Hes,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D,1.0);
  NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
  if(invalidflag) {
    return;
  }
    
  if(rt!=1.0) {
    //BIdisperse=>本来の固有ベクターに変換。
    if(D==3) {
      for(int j=(Prt1*N)/(Prt1+Prt2);j<N;j++) {
	for(int i=0;i<N;i++)
	  EigMat[i][j]*=1.0/sqrt(rt*rt*rt);
      }
    }
  }
  NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
  for(int i=0;i<N;i++) {
      Eigvec[i]=EigMat[i][vecnum];//どこの固有ベクターにするか数値0~DNumで指定。
    }
  eigval=Eigval[vecnum];  
  out=Eigvec;
}

//----------------------------------------------------
//固有ベクター方向でのPELをデータ出力。
//----------------------------------------------------

void JT::dim2::outputPEL2D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum,DP func(Vec_IO_DP,DP,DP,DP,DP,int,int,int,DP))
{
  int N=zahyo.size();
  Vec_DP Relrzahyo(N);
  stringstream ss,ss2,ss3;
  string wrname;
  ofstream wrPEL;
  int jmax=1000;//正の方向にjmax plots, 負の方向にjmax plotsの点を取る.
  double tmpfactor;
  
  JT::ssInput(ss,num);
  JT::ssInput(ss2,phi);
  JT::ssInput(ss3,vecnum);
  if(num<10)
    wrname ="PEL_0000"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=10 && num<100)
    wrname ="PEL_000"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=100 && num<1000)
    wrname ="PEL_00"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=1000 && num<10000)
    wrname ="PEL_0"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else
    wrname ="PEL_"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  wrPEL.open(wrname.data());

  for(int j=0;j<2*jmax;j++)//50000はテキトーな区間幅
    {
      tmpfactor=(j-jmax)*0.00000001*Lx*sqrt(D*N);//とりあえずLx(tekitou)
      //0.00000001は適当に設定.
      for(int i=0;i<N;i++)
	Relrzahyo[i]=zahyo[i]+tmpfactor*eigvec[i];
      wrPEL<<0+tmpfactor<<' '<<setprecision(15)<<func(Relrzahyo,Lx,Ly,R,rt,alp,Prt1,Prt2,D)<<endl;
    }
}
void JT::dim3::outputPEL3D(Vec_I_DP &zahyo,DP Lx,DP Ly,DP Lz,DP R,DP rt,DP alp,int Prt1,int Prt2,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum,DP func(Vec_IO_DP,DP,DP,DP,DP,DP,int,int,int,DP))
{
  int N=zahyo.size();
  Vec_DP Relrzahyo(N);
  stringstream ss,ss2,ss3;
  string wrname;
  ofstream wrPEL;
  int jmax=1000;//正の方向にjmax plots, 負の方向にjmax plotsの点を取る.
  double tmpfactor;
  
  JT::ssInput(ss,num);
  JT::ssInput(ss2,phi);
  JT::ssInput(ss3,vecnum);
  if(num<10)
    wrname ="PEL_0000"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=10 && num<100)
    wrname ="PEL_000"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=100 && num<1000)
    wrname ="PEL_00"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else if(num>=1000 && num<10000)
    wrname ="PEL_0"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  else
    wrname ="PEL_"+ss.str()+'_'+ss2.str()+'_'+ss3.str()+".txt";
  wrPEL.open(wrname.data());

  for(int j=0;j<2*jmax;j++)//50000はテキトーな区間幅
    {
      tmpfactor=(j-jmax)*0.00000001*Lx*sqrt(D*N);//とりあえずLx(tekitou)
      //0.00000001は適当に設定.
      for(int i=0;i<N;i++)
	Relrzahyo[i]=zahyo[i]+tmpfactor*eigvec[i];
      wrPEL<<0+tmpfactor<<' '<<setprecision(15)<<func(Relrzahyo,Lx,Ly,Lz,R,rt,alp,Prt1,Prt2,D)<<endl;
    }
}

void JT::CollectiveMotionCheck(Mat_I_DP &EigMat,Vec_IO_DP &CMnum,int D)//IPRのこと.
{
  //DP eps=numeric_limits<double>::epsilon();
  int N=CMnum.size();
  for(int i=0;i<N;i++)
    {
      DP four=0;
      DP two=0;
      DP tmp;
      
      for(int j=0;j<N;j+=D) {
	tmp=0;
	for(int k=0;k<D;k++)
	  tmp+=EigMat[j+k][i]*EigMat[j+k][i];
	four+=tmp*tmp;
	two+=tmp;
	}
      two*=two;
      CMnum[i]=four/two;
    }
}
void JT::CollectiveMotionCheck2(Mat_I_DP &EigMat,Vec_IO_DP &CMnum,Vec_IO_DP &CMnum1,Vec_IO_DP &CMnum2,int D,int Prt1,int Prt2)//IPRのこと.
{
  //DP eps=numeric_limits<double>::epsilon();
  int N=CMnum.size();
  
  for(int i=0;i<N;i++)
    {
      DP four=0,four1=0,four2=0;
      DP two=0;
      DP tmp;
      bool particle1=true;
      
      for(int j=0;j<N;j+=D) {
	tmp=0;
	if((Prt1+Prt2)*j==Prt1*N)
	  particle1=false;
	for(int k=0;k<D;k++)
	  tmp+=pow(EigMat[j+k][i],2);
	four+=tmp*tmp;
	if(particle1)
	  four1+=tmp*tmp;
	else
	  four2+=tmp*tmp;
	two+=tmp;
	}
      two*=two;
      tmp=1.0/two;
      CMnum[i]=four*tmp;
      CMnum1[i]=four1*tmp;
      CMnum2[i]=four2*tmp;
    }
}

//------------------------------
//Jacobi method//
//------------------------------
namespace
{
  inline void rot(Mat_IO_DP &a, const DP s, const DP tau, const int i,const int j, const int k, const int l)
  {
    //matrix:a (今取り扱っている実対称行列)
    //double(const):s sin(phi)の値.
    //double(const):tau tau(phi)の値.
    //int:i i行目の値.
    //int:j j列目の値.
    DP g,h;

    g=a[i][j];
    h=a[k][l];

    a[i][j]=g-s*(h+g*tau);
    a[k][l]=h+s*(g-h*tau);

  }//非対角成分を更新するalgorithm
}

void NR::jacobi(Mat_IO_DP &a, Vec_O_DP &d, Mat_O_DP &v, int &nrot,bool &invalidflag)
//matrix:a(実対象行列)の固有値と固有ベクターを求めるルーチン.
//matrix:vは縦行が固有ベクターに対応するような行列.
//vector:dは降順でソートされた固有値の集まりのベクター.
//int:nrotはヤコビローテーションをした回数の情報を返す.
{
  int i,j,ip,iq;
  DP tresh,theta,tau,t,sm,s,h,g,c;
  const DP EPS=numeric_limits<double>::epsilon();
  invalidflag=false;
  int n=d.size();
  const int ITER=10*n; //場合によってはiterationが足りないかもしれない...><
  Vec_DP b(n),z(n);
  for (ip=0;ip<n;ip++)
    {
      for (iq=0;iq<n;iq++) v[ip][iq]=0.0;
      v[ip][ip]=1.0;
    }//単位行列の作成.
  for (ip=0;ip<n;ip++)
    {
      b[ip]=d[ip]=a[ip][ip];//a行列の対角成分で初期化.(bとdを用意する有り難みがあんまりわからない...)
      z[ip]=0.0;//a_{pq}*tan(phi)を累積で保存しておく.(zero-vectorで初期化)
    }
  nrot=0;
  for (i=1;i<=ITER;i++)
    {
      sm=0.0;
      for (ip=0;ip<n-1;ip++)
	{
	  for (iq=ip+1;iq<n;iq++)
	    sm += fabs(a[ip][iq]);//非対角成分(半分)の和をとる.
	}
      if (sm == 0.0)//非対角成分の総和がzeroならば現在の状態を返却.
	return;
      if (i < 4)
	tresh=0.2*sm/(n*n);//最初の3回のsweepに用いる.
      else
	tresh=0.0;// after 3 sweeps...
      for (ip=0;ip<n-1;ip++)
	{
	  for (iq=ip+1;iq<n;iq++)//反復はn(n-1)/2回である.
	    {
	      g=100.0*fabs(a[ip][iq]);
	      if (i>4 && g<=EPS*fabs(d[ip]) && g<=EPS*fabs(d[iq]))//(i > 4 && (fabs(d[ip])+g) == fabs(d[ip])// after 4 sweeps && 非対角成分が微小
		  //(対角成分+非対角成分=対角成分ppパターンとqqパターン)
		  //&& (fabs(d[iq])+g) == fabs(d[iq]))//=>a_{pq}=0にsetする.
		a[ip][iq]=0.0;
	      else if (fabs(a[ip][iq]) > tresh)
		{
		  h=(d[iq]*d[iq]-d[ip]*d[ip])/(d[iq]+d[ip]);//a_{qq}-a_{pp}を誤差少ないように評価
		  if (g<=EPS*fabs(h))//((fabs(h)+g) == fabs(h))//引き算の値めっちゃ小さくなっちゃった.(theta微小)
		    t=(a[ip][iq])/h;//=1/(2*(theta))
		  else
		    {
		      theta=0.5*h/(a[ip][iq]);
		      t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));//tan(phi)
		      if (theta < 0.0) t = -t;//thetaの値で選ぶ解を変更.
		    }
		  c=1.0/sqrt(1+t*t);//cos(phi)
		  s=t*c;//sin(phi)
		  tau=s/(1.0+c);//tau(phi)
		  h=t*a[ip][iq];//NEXTのa_{pp}やa_{qq}を計算する上で用いる.
		  z[ip] -= h;//a-matrixの対角成分ppに施された足し引きの保存.(あとでつかう)
		  z[iq] += h;//a-matrixの対角成分qqに施された足し引きの保存.(あとでつかう)
		  d[ip] -= h;//a_{pp}の更新.
		  d[iq] += h;//a_{qq}の更新.
		  a[ip][iq]=0.0;//NEXTのa_{pq}とa_{qp}はzeroです.(そうなるように相似変換するalgorithmなので.)
		  for (j=0;j<ip;j++)//NEXTのa_{jp}とa_{jq}を求める.(0<=j<pのrotation)
		    rot(a,s,tau,j,ip,j,iq);
		  for (j=ip+1;j<iq;j++)//NEXTのa_{pj}とa_{jq}を求める.(p+1<=j<qのrotation)
		    rot(a,s,tau,ip,j,j,iq);
		  for (j=iq+1;j<n;j++)//NEXTのa_{pj}とa_{qj}を求める.(q+1<=j<nのrotation),上三角で作業しているため3通りの場合分け.
		    rot(a,s,tau,ip,j,iq,j);
		  for (j=0;j<n;j++)//matrix:vについて, pとqの列vectorをそれぞれ操作.(元は単位行列)
		    rot(v,s,tau,j,ip,j,iq);//単位行列に右から直交行列(x_0,x_1,...,x_(N-1))(の一部P_i)をかけていることに対応.
		  ++nrot;
		}//(else if)-end
	    }//iq-loop-end
	}//ip-loop-end
      for (ip=0;ip<n;ip++)
	{
	  b[ip] += z[ip];
	  d[ip]=b[ip];//dの更新.
	  z[ip]=0.0;//zをもっかい初期化.
	}
    }
  cerr<<"Too many iterations in routine jacobi"<<endl;
  invalidflag=true;
  return;
}


void NR::eigsrt(Vec_IO_DP &d, Mat_IO_DP &v)
{
  int i,j,k;
  DP p;

  int n=d.size();
  for (i=0;i<n-1;i++)
    {
      p=d[k=i];
      for (j=i;j<n;j++)
	if (d[j] >= p) p=d[k=j];
      if (k != i)
	{
	  d[k]=d[i];
	  d[i]=p;
	  for (j=0;j<n;j++)
	    {
	      p=v[j][i];
	      v[j][i]=v[j][k];
	      v[j][k]=p;
	    }
	}
    }
}

void JT::RenomalizeEigvec(Mat_IO_DP &EigMat)
{
  const int N=EigMat.ncols(),M=EigMat.nrows();
  if(N!=M) {
    cerr<<"EigMatERR!!"<<endl;
    exit(1);
  }
  Vec_DP C_rn(N);//各固有ベクターの大きさ
  double Cinv;//(1/固有ベクターの大きさ)

  for(int i=0;i<N;i++) {
    C_rn[i]=0.0;//initialize
    for(int j=0;j<M;j++) {
      C_rn[i]+=EigMat[j][i]*EigMat[j][i];
    }
    Cinv=1.0/sqrt(C_rn[i]);
    C_rn[i]=0.0;
    for(int j=0;j<M;j++) {
      EigMat[j][i]*=Cinv;
      C_rn[i]+=EigMat[j][i]*EigMat[j][i];
    }
    //cout<<"固有ベクトル"<<i<<"番目の大きさ: "<<C_rn[i]<<endl;
  }
  
  return;
}

void JT::RenomalizeEigvec_check(Mat_I_DP &EigMat)
{
  const int N=EigMat.ncols(),M=EigMat.nrows();
  Vec_DP C_rn(N);//各固有ベクターの大きさ

  for(int i=0;i<N;i++) {
    C_rn[i]=0.0;//initialize
    for(int j=0;j<M;j++) {
      C_rn[i]+=EigMat[j][i]*EigMat[j][i];
    }
    cout<<"固有ベクトル"<<i<<"番目の大きさ: "<<C_rn[i]<<endl;
  }
  
  return;
}

void JT::countEigComponents(Mat_I_DP &EigMat,Vec_IO_DP &cmp_small_ratio,int Prt1,int Prt2) {
  const int N=cmp_small_ratio.size();
  int NSmall=(Prt1*N)/(Prt1+Prt2);
  for(int i=0;i<N;i++) {
    cmp_small_ratio[i]=0.0;
    for(int j=0;j<N;j++) {
      if(j<NSmall) {
        cmp_small_ratio[i]+=EigMat[j][i]*EigMat[j][i];
      }
    }
  }
  return;
}

void JT::countEigComponents(Mat_I_DP &EigMat,Vec_IO_DP &cmp_small_ratio,Vec_IO_DP &cmp_all, int Prt1,int Prt2) {
  const int N=cmp_small_ratio.size();
  Vec_DP eigvec_max(N);

  for(int i=0;i<N;i++) {
    eigvec_max[i]=0.0;
    for(int j=0;j<N;j++) {
      if(fabs(EigMat[j][i])>eigvec_max[i])
	eigvec_max[i]=fabs(EigMat[j][i]);
    }
  }
  for(int i=0;i<N;i++) {
    cmp_all[i]=0;
    cmp_small_ratio[i]=0;
    int changeParticle=(Prt1*N)/(Prt1+Prt2);
    for(int j=0;j<N;j++) {
      if(fabs(EigMat[j][i])>=0.1*eigvec_max[i]) {//0.01 ha shikiichi
	cmp_all[i]+=1;
	if(j<changeParticle)
	  cmp_small_ratio[i]+=1;
      }
    }
    cmp_small_ratio[i]/=cmp_all[i];
  }
  return;
}

#endif
