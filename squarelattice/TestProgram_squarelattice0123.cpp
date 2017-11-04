#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include "nr.h"
#include "MT.h"
using namespace std;

//----------------------------------------------------
//global variables-------------------------------------
//----------------------------------------------------

//global変数は使わないように変更.(int main()の中で定義し、引数渡すように変更)

///////////////
//attention!!//
///////////////
//DMPtは速度比例の抵抗定数gammaに(Delta t)をかけたalphaの値(FIRE参照)。
//ここで使われているF,Ftmp,Fnextなどは力の次元ではなく、(力)x(Delta t)/(2m)となっている。

//----------------------------------------------------
//CG法を用いたgranular packingの構築(本体)------------
//----------------------------------------------------

int main()
{

  //-----------------------------------------------------
  //----------Molecular Dynamicsのパラメータ-------------
  //-----------------------------------------------------
  const int PNum=64,Pratio=1,dim=3;//PNumはParticle Number, Pratioは粒子の混合比(Pratio(半径1.0):1(半径1.0*ratio)のBIdisperse),dimは空間次元
  DP Leng =1.0e+2;//Radは粒子径、Lengはセルの一辺の長さ
  const DP alpha =2.0,ratio=1.0;//,eps=1.0,kbT=1.38064852*1.0e-10;//kbT is tekitou

  if((100.0*Pratio)/(Pratio+1)-(int)((100*Pratio)/(Pratio+1)) !=0.0)
    NR::nrerror("your particle ratio is disable for this program...\n\n");
  
  const DP ftol=numeric_limits<double>::epsilon();//粒子数,半径更新のための定数(Rad2=Rad1*ratio); 
  const int DNum=PNum*dim;//Dimension Number
  Vec_DP zahyo(DNum);//zahyotmpはCG法を適用する一個前のzahyo値
  bool minuseig;
  
    /*きちんと半径が計算できているかBUG check
  cout<<sqrt(PNum)<<"\n"<<Rad<<"\n"<<endl;
  DP calc3=2*(Rad-delta)*sqrt(PNum);
  DP calc= (M_PI*Rad*Rad)/(4*(Rad-0.5*delta)*(Rad-0.5*delta));
  DP calc2= 0.25*M_PI;
  cout<<calc<<"   "<<calc2<<"   "<<calc3<<endl;
  */
  int savenum=0,Ntmpi;  
  
  cout<<"テキストのセーブ番号(int)を入れてください.\n -> ";
  cin>>savenum;
  cout<<"\n\n";
  cout<<"正方格子でのシミュレーションを開始します。"<<endl;

  stringstream ss;
  ss.str("");
  ss.clear(stringstream::goodbit);

  ss<<savenum;
  string wrname="MONOPhiEng0125_squarelattice"+ss.str();
  //string kaiseki="MONOPhiEng0125_squarelattice"+ss.str()+"_kaiseki";
  string zz="MONOPhiEng0125_squarelattice"+ss.str()+"_zahyo";
  //string fgname1=wrname+"jam",fgname2=wrname+"jam2",fgname3=wrname+"jam3",fgname4=wrname+"jam4",fgname5=wrname+"jam5",fgnamefin=wrname+"fin";
  string tmpname=wrname+".txt";
  //string kaisekiname=kaiseki+".txt";
  string zahyoname=zz+".txt";
  ofstream kakikoCnfdata(tmpname.data());
  //ofstream kakikokaiseki(kaisekiname.data());
  ofstream kakikozahyo(zahyoname.data());

  
  if(dim==2){
  DP Rad=(100*Leng/(199*sqrt(PNum)));
  DP delta=0.01*Rad;
  
  DP CPHI=((1+pow(ratio,2))*PNum*M_PI)/(2*pow(Leng,2));
  DP PHI=CPHI*Rad*Rad;
  cout<<"充填率は"<<PHI<<"です."<<endl;
  DP plus1=Rad-0.5*delta;
  DP plus2=2*plus1;



    DP Ntmpd=sqrt(PNum);
    Ntmpi=sqrt(PNum);
    //DP theta=M_PI/Ntmpd;
    //DP div=sqrt(delta/(8*Rad*Rad*Rad));
    //DP eig;
    
    if(Ntmpd!=Ntmpi)
      NR::nrerror("your the number of the particle is not valid...");
	    
    for(int i=0;i<Ntmpd;i++){
      zahyo[i*2*Ntmpd]=plus1;
      zahyo[i*2*Ntmpd+1]=plus1+i*plus2;
	  
      for(int j=1;j<Ntmpd;j++){
	zahyo[i*2*Ntmpd+2*j]=zahyo[i*2*Ntmpd+2*j-2]+plus2;
	zahyo[i*2*Ntmpd+2*j+1]=zahyo[i*2*Ntmpd+2*j-1];
      }
    }
    DP tmp4=0.5*delta/Rad;
    DP calc4=PNum*tmp4*tmp4;
    cout<<NR::potential(zahyo,Leng,Rad,ratio,alpha,Pratio,dim)<<"   "<<calc4<<'\n';
    
    
    NR::ModeCalc(zahyo,Leng,Rad,ratio,alpha,Pratio,savenum,PHI,dim,minuseig);
    kakikoCnfdata<<PHI<<NR::potential(zahyo,Leng,Rad,ratio,alpha,Pratio,dim)<<endl;
    /*
    for(int i=0;i<Ntmpd;i++){
      eig=div*sin(i*theta);
      kakikokaiseki<<i<<' '<<eig<<endl;
    }
    */
  }
  else if(dim==3){
    Ntmpi=static_cast<int>(pow(PNum,0.34));
  DP Rad=(100*Leng/(199*Ntmpi));
  DP delta=0.01*Rad;
  DP CPHI=(2*(1+ratio*ratio)*PNum*M_PI)/(3*pow(Leng,3));
  DP PHI=CPHI*Rad*Rad*Rad;
  cout<<"充填率は"<<PHI<<"です."<<endl;
  DP plus1=Rad-0.5*delta;
  DP plus2=2*plus1;
  DP calc1=4*M_PI*Rad*Rad*Rad/(3*pow((2*Rad-delta),3));
  cout<<"**PHIの値checker: "<<PHI<<" <-> "<<calc1<<"\n==============\n"<<endl;
  
    int Ntmpii=Ntmpi*Ntmpi;
    //DP theta=M_PI/Ntmpi;
    //DP div=sqrt(0.5/(4*Rad*Rad));
    //DP eig;
	    
    for(int k=0;k<Ntmpi;k++){//z軸に一番近いとこなので, xとyの値はplus1。zはkにつれて増えてく。
      zahyo[3*k*Ntmpii]=plus1;
      zahyo[3*k*Ntmpii+1]=plus1;
      zahyo[3*k*Ntmpii+2]=plus1+k*plus2;
      kakikozahyo<<3*k*Ntmpii<<' '<<zahyo[3*k*Ntmpii]<<endl;
      kakikozahyo<<3*k*Ntmpii+1<<' '<<zahyo[3*k*Ntmpii+1]<<endl;
      kakikozahyo<<3*k*Ntmpii+2<<' '<<zahyo[3*k*Ntmpii+2]<<endl;
      
      for(int i=0;i<Ntmpi;i++){//y軸に一番近いとこなので、xの値はplus1. yはiにつれて増えてく。zは上と同じxy平面なのでこれでよい。
	if(i!=0){
	zahyo[3*k*Ntmpii+3*i*Ntmpi]=plus1;
	zahyo[3*k*Ntmpii+3*i*Ntmpi+1]=plus1+i*plus2;
	zahyo[3*k*Ntmpii+3*i*Ntmpi+2]=zahyo[3*k*Ntmpii+2];
	kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi]<<endl;
	kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi+1<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi+1]<<endl;
	kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi+2<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi+2]<<endl;
	}
	
	for(int j=1;j<Ntmpi;j++){
	  zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j]=zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j-3]+plus2;
	  zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j+1]=zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j-2];
	  zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j+2]=zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j-1];

	  kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi+3*j<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j]<<endl;
	  kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi+3*j+1<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j+1]<<endl;
	  kakikozahyo<<3*k*Ntmpii+3*i*Ntmpi+3*j+2<<' '<<zahyo[3*k*Ntmpii+3*i*Ntmpi+3*j+2]<<endl;
	}	
      }
    }
    kakikozahyo.close();
    
    NR::ModeCalc3D(zahyo,Leng,Rad,ratio,alpha,Pratio,savenum,PHI,dim,minuseig);
    kakikoCnfdata<<PHI<<NR::potential3D(zahyo,Leng,Rad,ratio,alpha,Pratio,dim)<<endl;
    /*
    for(int i=0;i<Ntmpi;i++){
      eig=div*sin(i*theta);
      kakikokaiseki<<i<<' '<<eig<<endl;
    }
    */
  }	    
  else
    NR::nrerror("Cannot execute this program except for 2D and 3D system...");
	  

  return 0;
}



//---------------------------------------------------
//potential V(2D)を求める関数------------------------
//---------------------------------------------------

DP NR::potential(Vec_I_DP &q,DP Len,DP R,DP rt,DP alp,int Prt, int D)
//pは粒子の個数 かける2次元分のベクトル量、Lengは系の大きさである。
{
  if(D!=2)
    nrerror("Cannot caliculate except for 2D system.");
  int N=q.size();
  DP eps=1.0;
  Vec_DP p=q;
  for(int i=0;i<N;i++)
    {
      if(p[i]<0 || p[i]>Len)
	p[i]+=-Len*(((int)p[i])/Len);
      if(p[i]<0)
	p[i]+=Len;
    }

  DP sgm,pot=0.0;//半径等は系のサイズで調節すること。
  //これはd次元のmonodisperseの場合のポテンシャルである。
  DP Radi=R;//初期化

  for(int i=0;i<N;i+=2)
    {
      if((Prt+1)*i==Prt*N)
	Radi=rt*R;

      DP Radj=R;//初期化
      for(int j=i+2;j<N;j+=2)
	{
	  if((Prt+1)*j==Prt*N)
	    Radj=rt*R;

	  sgm=Radi+Radj;
	  DP relrx=p[j]-p[i];
	  DP relry=p[j+1]-p[i+1];
	  if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-Len)<sgm)//A or D or F
		relrx-=Len;
	      else if(fabs(relrx+Len)<sgm)// C or E or H
		relrx+=Len;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-Len)<sgm)//F or G or H
		relry-=Len;
	      else if(fabs(relry+Len)<sgm)//A or B or C
		relry+=Len;
	      //なにもしない　otherwise (D or E)
	    }
	  DP relr=sqrt(relrx*relrx+relry*relry);
	  if(relr<sgm)
	    {
	      DP powterm = (sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	      pot+=eps*pow(powterm,alp)/alp; //2倍はr_ijとr_jiの2種類を足し合わせたという意味である。
	    }

	}//j-loop-end
    }//i-loop-end

  return pot;
}//End


//---------------------------------------------------
//potential V(3D)を求める関数------------------------
//---------------------------------------------------

DP NR::potential3D(Vec_I_DP &q,DP Len,DP R,DP rt,DP alp,int Prt,int D)
//pは粒子の個数 かける3次元分のベクトル量、Lengは系の大きさである。
{
  if(D!=3)
    nrerror("Cannot caliculate except for 3D system.");
  int N=q.size();
  DP eps=1.0;
  Vec_DP p=q;
  for(int i=0;i<N;i++)
    {
      if(p[i]<0 || p[i]>Len)
	p[i]+=-Len*(((int)p[i])/Len);
      if(p[i]<0)
	p[i]+=Len;
    }

  DP sgm,pot=0.0;//半径等は系のサイズで調節すること。
  //これはd次元のmonodisperseの場合のポテンシャルである。
  DP Radi=R;//初期化

  for(int i=0;i<N;i+=3)
    {
      if((Prt+1)*i==Prt*N)
	Radi=rt*R;

      DP Radj=R;//初期化
      for(int j=i+3;j<N;j+=3)
	{
	  if((Prt+1)*j==Prt*N)
	    Radj=rt*R;

	  sgm=Radi+Radj;
	  DP relrx=p[j]-p[i];
	  DP relry=p[j+1]-p[i+1];
	  DP relrz=p[j+2]-p[i+2];
	  if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm || fabs(relrz)>Len-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-Len)<sgm)//A or D or F
		relrx-=Len;
	      else if(fabs(relrx+Len)<sgm)// C or E or H
		relrx+=Len;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-Len)<sgm)//F or G or H
		relry-=Len;
	      else if(fabs(relry+Len)<sgm)//A or B or C
		relry+=Len;
	      //なにもしない　otherwise (D or E)
	      if(fabs(relrz-Len)<sgm)
		relrz-=Len;
	      else if(fabs(relrz+Len)<sgm)
		relrz+=Len;
	      //
	    }
	  DP relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	  if(relr<sgm)
	    {
	      DP powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	      pot+=eps*pow(powterm,alp)/alp; //2倍はr_ijとr_jiの2種類を足し合わせたという意味である。
	    }
	}//j-loop-end
    }//i-loop-end

  return pot;
}//End



//---------------------------------------------------
//Velocity Verlet Forceを求める関数(2D)--------------
//---------------------------------------------------

void NR::VVforce_F(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt, DP mass,DP tstep,DP Len,DP R,DP rt,DP alp,int Prt,int D,bool &relax)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{

  relax=false;
  if(D!=2)
    nrerror("Cannot caliculate except for 2D system.");
  int N=p.size();
  DP eps=1.0;
  DP sgm,tmpx,tmpy,relrx,relry,relr,powterm,Radi=R,Radj,tsum=0.0,Fsum=0.0;//半径等は系のサイズで調節すること。
  //これはd次元のmonodisperseの場合のポテンシャルである。
  Fpot=0.0;
  DP tfact,Ffact,M=mass,Const,EPS=numeric_limits<double>::epsilon(),Fconst;
  Vec_DP veltmp(N),s(N),t(N);


  for(int i=0;i<N;i+=2)
    {
      if((Prt+1)*i==Prt*N)//BIdisperseのときmassとRadを変更する.
	{
	  Radi=rt*R;
	  M=mass*rt;
	}

      Radj=R;//初期化
      for(int j=i+2;j<N;j+=2)
	{
	  if((Prt+1)*j>=Prt*N)//後半はこの値で
	    Radj=rt*R;

	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-Len)<sgm)//A or D or F
		relrx-=Len;
	      else if(fabs(relrx+Len)<sgm)// C or E or H
		relrx+=Len;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-Len)<sgm)//F or G or H
		relry-=Len;
	      else if(fabs(relry+Len)<sgm)//A or B or C
		relry+=Len;
	      //なにもしない　otherwise (D or E)
	    }
	  relr=sqrt(relrx*relrx+relry*relry);
     	  if(relr<sgm)
	    {
	      powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	      tmpx=-1.0*eps*(relrx/(sgm*relr))*pow(powterm,alp-1);
	      tmpy=-1.0*eps*(relry/(sgm*relr))*pow(powterm,alp-1);
	      //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	      Fpot[j]-=tmpx;
	      Fpot[j+1]-=tmpy;
	      Fpot[i]+=tmpx;
	      Fpot[i+1]+=tmpy;
	    }
	}//j-loop-end

      //-----Fpot等を用いて、i番目の粒子に働く力を計算。
      /*
      if(F[i]==0.0 && F[i+1]==0.0)
	for(int k=i;k<i+2;k++)
	  F[k]=Const*tstep*Fpot[k];
      */
      for(int k=i;k<i+2;k++)
	veltmp[k]=vel[k]+F[k];
      for(int k=i;k<i+2;k++)
	{
	  t[k]=2*M*veltmp[k]+tstep*Fpot[k];
	  tsum+=t[k]*t[k];
	}
      Fsum+=Fpot[i]*Fpot[i]+Fpot[i+1]*Fpot[i+1];

      //potential Forceがめちゃくちゃ小さいときに条件分岐したほうが良い??
    }//i-loop-end

  tfact=sqrt(tsum);
  Ffact=sqrt(Fsum);
  Const=1.0/(2*mass+dmpt);
  if(Ffact==0.0)
    for(int k=0;k<N;k++)
      {
	if((Prt+1)*k==Prt*N)//BIdisperseのときmassとRadを変更する.
	  {
	    Const=1.0/(2*mass*rt+dmpt);
	  }

	F[k]=Const*(-dmpt*veltmp[k]);
      }
  else
    {
      Fconst=1.0/Ffact;
      for(int k=0;k<N;k++)
	{
	  if((Prt+1)*k==Prt*N)//BIdisperseのときmassとRadを変更する.
	    {
	      Const=1.0/(2*mass*rt+dmpt);
	    }

	  F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
	}
    }
}//end

//---------------------------------------------------
//Velocity Verlet Forceを求める関数(3D)--------------
//---------------------------------------------------


void NR::VVforce_F3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F, Vec_O_DP &Fpot,DP dmpt,DP mass,DP tstep, DP Len,DP R,DP rt,DP alp,int Prt,int D,bool &relax)
//周期境界条件なのでこれに更に自セル以外の寄与を含めなければならない。
{
  relax=false;
  if(D!=3)
    nrerror("Cannot caliculate except for 3D system.");
  int N=p.size();
  DP eps=1.0;
  DP sgm,tmpx,tmpy,tmpz;//半径等は系のサイズで調節すること。
  DP Radi=R,Radj,relrx,relry,relrz,relr,powterm,tsum=0.0,Fsum=0.0;
  //これはd次元のmonodisperseの場合のポテンシャルである。
  Fpot=0.0;
  DP tfact,Ffact,M=mass,Const,Fconst;
  Vec_DP veltmp(N),t(N);

  for(int i=0;i<N;i+=3)
    {
      if((Prt+1)*i==Prt*N)//BIdisperseのときmassとRadを変更する.
	{
	  Radi=rt*R;
	  M=mass*rt;
	}
      
      Radj=R;//初期化
      for(int j=i+3;j<N;j+=3)
	{
	  if((Prt+1)*j>=Prt*N)//後半はこの値で
	    Radj=rt*R;
	  sgm=Radi+Radj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];
	  relrz=p[j+2]-p[i+2];
	  
	  if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm || fabs(relrz)>Len-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-Len)<sgm)//A or D or F
		relrx-=Len;
	      else if(fabs(relrx+Len)<sgm)// C or E or H
		relrx+=Len;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-Len)<sgm)//F or G or H
		relry-=Len;
	      else if(fabs(relry+Len)<sgm)//A or B or C
		relry+=Len;
	      //なにもしない　otherwise (D or E)
	      if(fabs(relrz-Len)<sgm)
		relrz-=Len;
	      else if(fabs(relrz+Len)<sgm)
		relrz+=Len;
	      //
	    }
	  relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
     	  if(relr<sgm)
	    {
	      powterm=(sgm*sgm-relr*relr)/(sgm*sgm+sgm*relr);
	      tmpx=-1.0*eps*(relrx/(sgm*relr))*pow(powterm,alp-1);
	      tmpy=-1.0*eps*(relry/(sgm*relr))*pow(powterm,alp-1);
	      tmpz=-1.0*eps*(relrz/(sgm*relr))*pow(powterm,alp-1);
	      //ポテンシャル勾配の対称成分から現れる項も同時に計算する。

	      Fpot[j]-=tmpx;
	      Fpot[j+1]-=tmpy;
	      Fpot[j+2]-=tmpz;
	      Fpot[i]+=tmpx;
	      Fpot[i+1]+=tmpy;
     	      Fpot[i+2]+=tmpz;
	    }
	}//j-loop-end

      //-----Fpot等を用いて、i番目の粒子に働く力を計算。
      /*
      if(F[i]==0.0 && F[i+1]==0.0 && F[i+2]==0.0)
	for(int k=i;k<i+3;k++)
	  F[k]=Const*tstep*Fpot[k];
      */
      for(int k=i;k<i+3;k++)
	veltmp[k]=vel[k]+F[k];
      for(int k=i;k<i+3;k++)
	{
	t[k]=2*M*veltmp[k]+tstep*Fpot[k];
	tsum+=t[k]*t[k];
	}
      Fsum+=Fpot[i]*Fpot[i]+Fpot[i+1]*Fpot[i+1]+Fpot[i+2]*Fpot[i+2];

      //potential Forceがめちゃくちゃ小さいときに条件分岐したほうが良い??
    }//i-loop-end

  tfact=sqrt(tsum);
  Ffact=sqrt(Fsum);
  Const=1.0/(2*mass+dmpt);
  if(Ffact==0.0)
    for(int k=0;k<N;k++)
      {
	if((Prt+1)*k==Prt*N)//BIdisperseのときmassとRadを変更する.
	  {
	    Const=1.0/(2*mass*rt+dmpt);
	  }

	F[k]=Const*(-dmpt*veltmp[k]);
      }
  else
    {
      Fconst=1.0/Ffact;
      for(int k=0;k<N;k++)
	{
	  if((Prt+1)*k==Prt*N)//BIdisperseのときmassとRadを変更する.
	    {
	      Const=1.0/(2*mass*rt+dmpt);
	    }

	  F[k]=Const*(-dmpt*veltmp[k]+(Ffact*tstep+dmpt*Const*tfact)*(Fpot[k]*Fconst));
	}
    }
  
}//end


//------------------------------------------------
//次の座標値を求める(FIRE ver.)
//------------------------------------------------

void NR::nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Len)
{
  int N =zahyo.size();
  const DP tmpLeng=1.0/Len;
  for(int i=0;i<N;i++)
    zahyo[i]+=tstep*(vel[i]+F[i]);

  for(int i=0;i<N;i++)//散らばった座標を自セルに描写する。
    {
      if(zahyo[i]<0 || zahyo[i]>Len)//x-coordinate
	{
	  zahyo[i]+=-Len*((int)(zahyo[i]*tmpLeng));
	  if(zahyo[i]<0)
	    zahyo[i]+=Len;
	}
    }
}


//------------------------------------------------
//次の速度を求める(FIRE ver.)
//------------------------------------------------

void NR::nextvel_F(Vec_IO_DP &vel, Vec_I_DP &Fnxt,Vec_I_DP &F)
{
  int N=vel.size();
  for(int i=0;i<N;i++)
    vel[i]+=Fnxt[i]+F[i];
}


//----------------------------------------------------------------------------
//与えられた温度での正規分布に従う速度分布(Maxwell-Boltzmann分布)を求める関数
//----------------------------------------------------------------------------
void NR::Gen_MBdist(Vec_IO_DP &vel, DP mass, DP kT,DP rt,DP Prt)
{
  int N=vel.size();
  DP mfact= 1.0/mass;
  MT::init_genrand((unsigned)time(NULL));

  for(int i=0;i<N;i++)
    {
      if((Prt+1)*i==Prt*N)//後半はこの値で.
	mfact/=rt;
      vel[i]=sqrt(-2.0*kT*mfact*log(MT::genrand_real1()))*cos(2*M_PI*MT::genrand_real2());
    }
}

void NR::Velocity_Verlet_F(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV)
{

  if(D!=2)
    nrerror("Cannot calculate except for 3D system!\n\n");
  
  int N=p.size();
  int M=vel.size();
  Vec_DP Force(N),Forcetmp(N),PotForce(N);
  if(N!=M)
    nrerror("COD is different size to vel");

  int ITMAX=iterVV,ITER=0,itbrk=0;
  iterVV=0;
  bool relax=false;
  //ofstream test01("test01.txt");
  //ofstream testMBdist("MBdist.txt"),kakikozahyo("testkakikozahyo01.txt"),kakikoforce("testkakikoforce001.txt");
  //  ofstream codfin("codfin.txt");
  //  stringstream hel;
  const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
  DP fret,fp,DMPt=dmpt;
  fret=func(p,Len,R,rt,alp,Prt,D);
  fp=fret;

  for(int i=0;i<N;i++)
    Force[i]=vel[i]=0.0;
  NR::VVforce_F(p,vel,Force,PotForce,DMPt,mass,tstep,Len,R,rt,alp,Prt,D,relax);
  Forcetmp=Force;
  for(int it=0;it<ITMAX;it++)
    {
      NR::nextcod_F(p,vel,Force,tstep,Len);
      NR::VVforce_F(p,vel,Force,PotForce,DMPt,mass,tstep,Len,R,rt,alp,Prt,D,relax);
      /*
	if(relax==true) 
	return; //鞍点でbreakする原因か??
      */
      NR::nextvel_F(vel,Force,Forcetmp);
      NR::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      
      Forcetmp=Force;
      fret=func(p,Len,R,rt,alp,Prt,D);
      
      /*
	cout<<iter<<"step me de, Energy:";
	printf("%.15e ->",fp);
	printf("%.15e ni henka shimashita\n",fret);
      */
      iterVV+=1;

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS))//相対誤差(真値に対する絶対誤差の割合)の評価である。
	//スケールに依存せずに評価するために絶対誤差ではなく相対誤差を用いる。<-2016/12/22,固有値マイナス原因の可能性
	{
	  if(itbrk<100)//連続で10回以上相対誤差評価に成功しなければ抜けない。
	    itbrk+=1;
	  else
	    {
	      DP sumpot=0.0;
	      stringstream ss;
	      ss.clear();
	      ss<<num;
	      ss<<'_';
	      ss<<phi;
	      string Fpotstr;
	      if(num<10)
		Fpotstr = "Fpot_test_0000"+ss.str()+".txt";
	      else if(num>=10 && num<100)
		Fpotstr = "Fpot_test_000"+ss.str()+".txt";
	      else if(num>=100 && num<1000)
		Fpotstr = "Fpot_test_00"+ss.str()+".txt";
	      else if(num>=1000 && num<10000)
		Fpotstr = "Fpot_test_0"+ss.str()+".txt";
	      else
		Fpotstr = "Fpot_test_"+ss.str()+".txt";

	      ofstream Fpotofs(Fpotstr.data());
	      for(int i=0;i<N;i+=2)
		{
		  Fpotofs<<PotForce[i]<<' '<<PotForce[i+1]<<'\n';// '<<PotForce[i+2]<<'\n';
		  sumpot+=PotForce[i]*PotForce[i]+PotForce[i+1]*PotForce[i+1];
		}
	      Fpotofs<<'\n'<<"------------\n"<<setprecision(15)<<sumpot<<'\n';
	      return;
	    }
	}
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fabs(fret)==0.0)//unjammed stateに落ちた。
	return;
      fp=fret;
      
    }// i-loop-end
  //cout<<"\n\n=================================\nVValgorithm cannot converge...\n=================================\n\n\n";
  //nrerror("VValgorithm cannot converge...\n\n");
}//1.14同期


void NR::Velocity_Verlet_F3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV)
{
  
  if(D!=3)
    nrerror("Cannot calculate except for 3D system!\n\n");
  
  int N=p.size();
  int M=vel.size();
  Vec_DP Force(N),Forcetmp(N),PotForce(N);

  
  if(N!=M)
    nrerror("COD is different size to vel");

  int ITMAX=iterVV,ITER=0,itbrk=0;
  iterVV=0;
  bool relax=false;
  //ofstream test01("test01.txt");
  //ofstream testMBdist("MBdist.txt"),kakikozahyo("testkakikozahyo01.txt"),kakikoforce("testkakikoforce001.txt");
  //  ofstream codfin("codfin.txt");
  //  stringstream hel;
  const DP EPS=1.0e-18; //関数値が正確にゼロに収束する特別な場合を訂正する最小の数
  DP fret,fp,DMPt=dmpt;
  fret=func(p,Len,R,rt,alp,Prt,D);
  fp=fret;

  for(int i=0;i<N;i++)
    Force[i]=vel[i]=0.0;
  NR::VVforce_F3D(p,vel,Force,PotForce,DMPt,mass,tstep,Len,R,rt,alp,Prt,D,relax);
  Forcetmp=Force;
  for(int it=0;it<ITMAX;it++)
    {
      NR::nextcod_F(p,vel,Force,tstep,Len);
      NR::VVforce_F3D(p,vel,Force,PotForce,DMPt,mass,tstep,Len,R,rt,alp,Prt,D,relax);
      /*
	if(relax==true) 
	return; //鞍点でbreakする原因か??
      */
      NR::nextvel_F(vel,Force,Forcetmp);
      NR::FIRE(vel,PotForce,DMPt,tstep,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,ITER);
      iterVV+=1;
      
      Forcetmp=Force;
      fret=func(p,Len,R,rt,alp,Prt,D);
      
      /*
	cout<<iter<<"step me de, Energy:";
	printf("%.15e ->",fp);
	printf("%.15e ni henka shimashita\n",fret);
      */

      if (2.0*fabs(fret-fp) <=ftol*(fabs(fret)+fabs(fp)+EPS))//相対誤差(真値に対する絶対誤差の割合)の評価である。
	//スケールに依存せずに評価するために絶対誤差ではなく相対誤差を用いる。<-2016/12/22,固有値マイナス原因の可能性
	{
	  if(itbrk<100)//連続で10回以上相対誤差評価に成功しなければ抜けない。
	    itbrk+=1;
	  else
	    {
	      DP sumpot=0.0;//single run専用の書き込み。
	      stringstream ss;
	      ss.clear();
	      ss<<num;
	      ss<<'_';
	      ss<<phi;
	      string Fpotstr;
	      if(num<10)
		Fpotstr = "Fpot_test_0000"+ss.str()+".txt";
	      else if(num>=10 && num<100)
		Fpotstr = "Fpot_test_000"+ss.str()+".txt";
	      else if(num>=100 && num<1000)
		Fpotstr = "Fpot_test_00"+ss.str()+".txt";
	      else if(num>=1000 && num<10000)
		Fpotstr = "Fpot_test_0"+ss.str()+".txt";
	      else
		Fpotstr = "Fpot_test_"+ss.str()+".txt";

	      ofstream Fpotofs(Fpotstr.data());
	      for(int i=0;i<N;i+=3)
		{
		  Fpotofs<<PotForce[i]<<' '<<PotForce[i+1]<<' '<<PotForce[i+2]<<'\n';
		  //cout<<PotForce[i]<<' '<<PotForce[i+1]<<' '<<PotForce[i+2]<<'\n';
		  sumpot+=PotForce[i]*PotForce[i]+PotForce[i+1]*PotForce[i+1]+PotForce[i+2]*PotForce[i+2];
		  //cout<<sumpot<<'\n';
		}
	      Fpotofs<<'\n'<<"------------\n"<<setprecision(15)<<sumpot<<'\n';
	      return;
	    }
	}
      else//相対誤差の評価に当てはまらない.
	itbrk=0;//連続評価失敗により初期化。
      if(fabs(fret)==0.0)//unjammed stateに落ちた。
	return;
      fp=fret;
      
    }// i-loop-end
  //cout<<"\n\n=================================\nVValgorithm cannot converge...\n=================================\n\n\n";
  //nrerror("VValgorithm cannot converge...\n\n");
}


//------------------------------------------
//FIRE algorithm (the FIRE-step part) の関数
//------------------------------------------
void NR::FIRE(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int &ITER)
{
  DP P=0.0,EPS=numeric_limits<double>::epsilon();
  int N=vel.size();
  for(int i=0;i<N;i++)
    P+=vel[i]*Fpot[i];
  if(P>0 && ITER>=ITFIRE)
    {
      ITER+=1;
      if(tstep*fra_inc-tstep_max<0)
	tstep*=fra_inc;
      else
	tstep=tstep_max;
      dmpt*=fra_alp;
    }	
  else if(P<=0)
    {
      ITER=0;
      tstep*=fra_dec;
      for(int i=0;i<N;i++)
	vel[i]=0.0;
      //これが鞍点に止まる原因か?? noiseなしのときジャミング点近傍では=EPSにしても鞍点に行くっぽい.
      dmpt=dmpt_init;
    }
  else//(P>0 && ITER<ITFIRE)の場合!!
    {
      ITER+=1;
    }
}



//--------------------------
//    sorting function
//--------------------------

void NR::sort(Vec_IO_DP &arr)
//arrを昇順になるようにソートする、そのときクイックソートのアルゴリズムを用いる。ソート後の配列をarrとして返却する。
{
  const int M=7,NSTACK=50;//Mはstraight insertionによってソートされるsubarrayのサイズ、NSTACKは必要とされる予備の記憶量?である。
  int i,ir,j,k,jstack=-1,l=0;
  DP a;
  Vec_INT istack(NSTACK);

  int n=arr.size();
  ir=n-1;
  for(;;)
    {
      if(ir-l<M)//subarrayが十分に小さいときinsertion sortを行う。
	{
	  for(j=l+1;j<=ir;j++)
	    {
	      a=arr[j];
	      for(i=j-1;i>=l;i--)
		{
		  if(arr[i]<=a)
		    break;
		  arr[i+1]=arr[i];
		}
	    
	      arr[i+1]=a;
	    }
	  if(jstack<0)
	    break;
	  ir=istack[jstack--];
	  l=istack[jstack--];
	}
      else
	{
	  k=(l+ir)>>1;//1bit-shift 要素aを分割するような中央値(left,center,rightの要素の)を選ぶ
	  SWAP(arr[k],arr[l+1]);//a[l]<=a[l+1]<=a[ir]になるようにrearrangeする。
	  if(arr[l]>arr[ir])
	    {
	      SWAP(arr[l],arr[ir]);
	    }
	  if(arr[l+1]>arr[ir])
	    {
	      SWAP(arr[l+1],arr[ir]);
	    }
	  if(arr[l]>arr[l+1])	 
	    {			
	      SWAP(arr[l],arr[l+1]);
	    }
	  i=l+1;
	  j=ir;
	  a=arr[l+1];
	  for(;;)
	    {
	      do i++;
	      while(arr[i]<a);
	      do j--;
	      while(arr[j]>a);
	      if(j<i)
		break;
	      SWAP(arr[i],arr[j]);
	    }
	  arr[l+1]=arr[j];
	  arr[j]=a;
	  jstack+=2;

	  if(jstack>=NSTACK)
	    {
	      nrerror("NSTACK too small in sort.");
	    }
	  if(ir-i+1>=j-l)
	    {
	      istack[jstack]=ir;
	      istack[jstack-1]=i;
	      ir=j-1;
	    }
	  else
	    {
	      istack[jstack]=j-1;
	      istack[jstack-1]=l;
	      l=i;
	    }
	}
    }
}

//--------------------------------------------------
//-----------------Hessian Matrix(2D)---------------
//--------------------------------------------------

void NR::Hesspot(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
    if(D!=2)
      nrerror("Cannot calculate except for 2D system!\n\n");

    int N =p.size();

    DP sgm,tmpxx,tmpxy,tmpyy,eps=1.0;//半径等は系のサイズで調節すること。
    //これは2次元のmonodisperseの場合のポテンシャルである。

    for(int i=0;i<N;i++)//zeroで初期化
      for(int j=0;j<N;j++)
	H[i][j]=0.0;

    if(alp!=2.0)
      return;

    DP Radi=R;//初期化
    DP rtinv_i=1.0;//MASS=1.0だと勝手に仮定.
    for(int i=0;i<N;i+=2)
      {
	if((Prt+1)*i==Prt*N)//後半はこの値で。
	  {
	    Radi=rt*R;
	    rtinv_i=1.0/sqrt(rt);
	  }

	DP Radj=R;//初期化
	DP rtinv_j=1.0;
	for(int j=0;j<i;j+=2)
	  {
	    if((Prt+1)*j==Prt*N)//後半はこの値で
	      {
		Radj=rt*R;
		rtinv_j=1.0/sqrt(rt);
	      }

	    sgm=Radi+Radj;
	    DP relrx=p[j]-p[i];
	    DP relry=p[j+1]-p[i+1];

	    if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm)
	      //上記の条件でポテンシャルに寄与するので
	      //隣接セルとの評価をおこなう
	      // A B C
	      // D x E
	      // F G H
	      //xを自セルとして上記の他セルとの評価を行う。
	      {
		//x方向評価
		if(fabs(relrx-Len)<sgm)//A or D or F
		  relrx-=Len;
		else if(fabs(relrx+Len)<sgm)// C or E or H
		  relrx+=Len;
		//なにもしない otherwise (B or G)

		//y方向評価
		if(fabs(relry-Len)<sgm)//F or G or H
		  relry-=Len;
		else if(fabs(relry+Len)<sgm)//A or B or C
		  relry+=Len;
		//なにもしない　otherwise (D or E)
	      }
	    // otherwiseで自セル内評価に移行
	    DP relr=sqrt(relrx*relrx+relry*relry);
	    if(relr<sgm)
	      {
		DP fact=eps/(sgm*relr*relr*relr);
		tmpxx=fact*(sgm*sgm*pow(relry,4)-pow(relr,6))/(sgm*(sgm*relry*relry+relr*relr*relr));
		tmpxy=-fact*(relrx*relry);
		tmpyy=fact*(sgm*sgm*pow(relrx,4)-pow(relr,6))/(sgm*(sgm*relrx*relrx+relr*relr*relr));

		/*桁落ちを考慮して2乗の引き算に変更。
		tmpxx=(eps*(sgm*pow(relry,2)-pow(relr,3)))/(pow(sgm,2)*pow(relr,3));
		tmpxy=(-1.0*eps*(relrx*relry))/(sgm*pow(relr,3));
		tmpyy=(eps*(sgm*pow(relrx,2)-pow(relr,3)))/(pow(sgm,2)*pow(relr,3));
		//ポテンシャル勾配の対称成分から現れる項も同時に計算する。
		*/

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
    return;
}

//--------------------------------------------------
//-----------------Hessian Matrix(3D)---------------
//--------------------------------------------------

void NR::Hesspot3D(Vec_I_DP &p, Mat_IO_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D)//alpha =2.0 only...
//BIdisperse を計算する場合,実際の系の固有ベクター{\bm e}_{sys}をM^{-1/2}{\bm e}_{this}で求めねばならない.
{
    if(D!=3)
    nrerror("Cannot calculate except for 3D system!\n\n");

  int N =p.size();

  DP sgm,tmpxx,tmpxy,tmpyy,tmpyz,tmpzz,tmpzx,eps=1.0;//,hyokamax,hyokamin;//半径等は系のサイズで調節すること。

  for(int i=0;i<N;i++)//zeroで初期化
    for(int j=0;j<N;j++)
      H[i][j]=0.0;

  if(alp!=2.0)
      return;

  DP Radi=R;//初期化
  DP rtinv_i=1.0;
  for(int i=3;i<N;i+=3)
    {
      if((Prt+1)*i==Prt*N)//後半はこの値で。
	{
	  Radi=rt*R;
	  rtinv_i=1.0/sqrt(rt);
	}

      DP Radj=R;//初期化
      DP rtinv_j=1.0;
      for(int j=0;j<i;j+=3)
	{
	  if((Prt+1)*j==Prt*N)//後半はこの値で
	    {
	      Radj=rt*R;
	      rtinv_j=1.0/sqrt(rt);
	    }

	  sgm=Radi+Radj;
	  DP relrx=p[j]-p[i];
	  DP relry=p[j+1]-p[i+1];
	  DP relrz=p[j+2]-p[i+2];

	      if(fabs(relrx)>Len-sgm || fabs(relry)>Len-sgm || fabs(relrz)>Len-sgm)
		//上記の条件でポテンシャルに寄与するので
		//隣接セルとの評価をおこなう
		// A B C
		// D x E
		// F G H
		//xを自セルとして上記の他セルとの評価を行う。
		{
		  //x方向評価
		  if(fabs(relrx-Len)<sgm)//A or D or F
		    relrx-=Len;
		  else if(fabs(relrx+Len)<sgm)// C or E or H
		    relrx+=Len;
		  //なにもしない otherwise (B or G)

		  //y方向評価
		  if(fabs(relry-Len)<sgm)//F or G or H
		    relry-=Len;
		  else if(fabs(relry+Len)<sgm)//A or B or C
		    relry+=Len;
		  //なにもしない　otherwise (D or E)
		  //z方向評価
		  if(fabs(relrz-Len)<sgm)//F or G or H
		    relrz-=Len;
		  else if(fabs(relrz+Len)<sgm)//A or B or C
		    relrz+=Len;
		  //なにもしない　otherwise (D or E)
		}
	      // otherwiseで自セル内評価に移行
	      DP relr=sqrt(relrx*relrx+relry*relry+relrz*relrz);
	      if(relr<sgm)
		{
		  //符号はH[k][l]成分が異なる(k!=l)パターン(+)に合わせているので、異ならないパターンは以下の計算で引き算
		  /*
		  DP Numx= sgm*(relry*relry+relrz*relrz);
		  DP Numy= sgm*(relrz*relrz+relrx*relrx);
		  DP Numz= sgm*(relrx*relrx+relry*relry);
		  DP Divxyz= sgm*relr*relr*relr;
		  DP fact=eps/(sgm*relr*relr*relr);
		  
		  tmpxx=eps*(Numx*Numx-pow(relr,6))/(sgm*Numx+Divxyz);
		  tmpyy=eps*(Numy*Numy-pow(relr,6))/(sgm*Numy+Divxyz);
		  tmpzz=eps*(Numz*Numz-pow(relr,6))/(sgm*Numz+Divxyz);
		  tmpxy=-fact*(relrx*relry);
		  tmpyz=-fact*(relry*relrz);
		  tmpzx=-fact*(relrz*relrx);
		  */

		  DP fact=eps/(sgm*sgm*relr*relr*relr);//,hyokatmpmax,hyokatmpmin;
		  tmpxx=fact*(sgm*(relry*relry+relrz*relrz)-relr*relr*relr);
		  tmpxy=-1.0*fact*sgm*(relrx*relry);
		  tmpyy=fact*(sgm*(relrz*relrz+relrx*relrx)-relr*relr*relr);
		  tmpyz=-1.0*fact*sgm*(relry*relrz);
		  tmpzz=fact*(sgm*(relrx*relrx+relry*relry)-relr*relr*relr);
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
  return;
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

void NR::jacobi(Mat_IO_DP &a, Vec_O_DP &d, Mat_O_DP &v, int &nrot)
//matrix:a(実対象行列)の固有値と固有ベクターを求めるルーチン.
//matrix:vは縦行が固有ベクターに対応するような行列.
//vector:dは降順でソートされた固有値の集まりのベクター.
//int:nrotはヤコビローテーションをした回数の情報を返す.
{
  int i,j,ip,iq;
  DP tresh,theta,tau,t,sm,s,h,g,c;
  const DP EPS=numeric_limits<double>::epsilon();

  int n=d.size();
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
  for (i=1;i<=50;i++)
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
  nrerror("Too many iterations in routine jacobi");
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

//--------------------------------------------
//Derivation function for DOS, IPR, and so on.
//--------------------------------------------

void NR::ModeCalc(Vec_IO_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,int D,bool &minus)
{
  if(D!=2)
    nrerror("Cannot calculate except for 3D system!\n\n");
  minus=true;
  int N=zahyo.size();
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  DP EPS=numeric_limits<double>::epsilon();
  
  NR::Hesspot(zahyo,Hes,Len,R,rt,alp,Prt,D);
  for(int i=0;i<3;i++)
    {
  cout<<Hes[0+4*i][0+4*i]<<' '<<Hes[0+4*i][1+4*i]<<' '<<Hes[0+4*i][2+4*i]<<' '<<Hes[0+4*i][3+4*i]<<endl;
  cout<<Hes[1+4*i][0+4*i]<<' '<<Hes[1+4*i][1+4*i]<<' '<<Hes[1+4*i][2+4*i]<<' '<<Hes[1+4*i][3+4*i]<<endl;
  cout<<Hes[2+4*i][0+4*i]<<' '<<Hes[2+4*i][1+4*i]<<' '<<Hes[2+4*i][2+4*i]<<' '<<Hes[2+4*i][3+4*i]<<endl;
  cout<<Hes[3+4*i][0+4*i]<<' '<<Hes[3+4*i][1+4*i]<<' '<<Hes[3+4*i][2+4*i]<<' '<<Hes[3+4*i][3+4*i]<<endl;
  cout<<'\n';
    }

  cout<<" taikaku:"<<0.5/(R*R)-1.0/(398*R*R)<<" yoko:"<<-0.25/(R*R)<<" tate:"<<1.0/(796*R*R)<<endl;
  
  /*
x軸上に[0,1]粒子と[2,3]粒子が隣り合わせのとき、
Hessian成分は、
taikaku: [0][0],[1][1],[2][2],[3][3] = 2*1.0/sgm*sgm - delta/sgm*sgm*(sgm-delta) = 0.5/(R*R) - 1.0/(398*R*R)
tatenami: [0][2],[2][0] = -1.0/sgm*sgm = -0.25/(R*R)
yokonami: [1][3],[3][1] = delta/sgm*sgm*(sgm-delta) = 1.0/(796*R*R)
となる。
さいごのイコールはdelta=(1/100)*R = 0.01*Rのときのものである。
   */
  
  //NR::tred2(Hes,Eigval,tmpvec);
  //NR::tqli(Eigval,tmpvec,Hes);
  
  NR::jacobi(Hes,Eigval,EigMat,cnt);

  
  
  if(rt!=1.0)//BIdisperseのときは本来の固有ベクターに変換しなければならない。
    {
      for(int j=(Prt*N)/(Prt+1);j<N;j++)
	{
	  for(int i=0;i<N;i++)
	    EigMat[i][j]*=1.0/sqrt(rt);
	}
    }
  NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.

  
  for(int j=0;j<N;j++)//固有値がすげえ負ならばそのときのPELを描いてもらう。
    {
      if(Eigval[j]<-EPS)
	{
	  for(int i=0;i<N;i++)
	    {
	      Eigvec[i]=EigMat[i][j];//どこの固有ベクターにするか数値0~DNumで指定。
	      //......そのどこの固有ベクターにするかってのもパラメータにすればよくない?
	    }
	  //	  NR::outputPEL3D(zahyo,Len,R,rt,alp,Prt,num,phi,Eigvec,D,j);
	  /*
	  tapping(Eigvec,Eigval[j],NR::potential(zahyo,Len,R,rt,alp,Prt,D),EPS);//この関数で固有ベクターの方向の微小(?)変位ベクトルを作成。(もしかしたら変位の大きさやばいかも)
	  for(int i=0;i<N;i++)
	    zahyo[i]+=Eigvec[i];
	  */
	  minus=false;
	}
    }

  NR::WriteEigInfo(EigMat,Eigval,num,phi);

  //累積の状態密度を導出しているが,ふつーのやつも矩形で区切って出してみるか...?
}

//--------------------------------------------
//Derivation function for DOS, IPR, and so on.(3D)
//--------------------------------------------

void NR::ModeCalc3D(Vec_IO_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,int D,bool &minus)
{

  if(D!=3)
    nrerror("Cannot calculate except for 3D system!\n\n");
  minus=true;
  int N=zahyo.size();
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  DP EPS=numeric_limits<double>::epsilon();
  
  NR::Hesspot3D(zahyo,Hes,Len,R,rt,alp,Prt,D);

  int nn=2*D;
  for(int i=0;i<3;i++)
    {
      for(int j=0;j<nn;j++)
	{
	for(int k=0;k<nn;k++)
	  {
	    if(k==nn-1)
	      cout<<Hes[j+nn*i][k+nn*i]<<endl;
	    else
	      cout<<Hes[j+nn*i][k+nn*i]<<' ';
	  }
	}
      cout<<"\n-----------------------\n"<<endl;
    }

  cout<<" taikaku:"<<0.5/(R*R)-1.0/(398*R*R)<<" yoko:"<<-0.25/(R*R)<<" tate:"<<1.0/(796*R*R)<<endl;
  
  /*
x軸上に[0,1]粒子と[2,3]粒子が隣り合わせのとき、
Hessian成分は、
taikaku: [0][0],[1][1],[2][2],[3][3] = 2*1.0/sgm*sgm - delta/sgm*sgm*(sgm-delta) = 0.5/(R*R) - 1.0/(398*R*R)
tatenami: [0][2],[2][0] = -1.0/sgm*sgm = -0.25/(R*R)
yokonami: [1][3],[3][1] = delta/sgm*sgm*(sgm-delta) = 1.0/(796*R*R)
となる。
さいごのイコールはdelta=(1/100)*R = 0.01*Rのときのものである。
   */
    
  //NR::tred2(Hes,Eigval,tmpvec);
  //NR::tqli(Eigval,tmpvec,Hes);
  NR::jacobi(Hes,Eigval,EigMat,cnt);

  if(rt!=1.0)//BIdisperseのときは本来の固有ベクターに変換しなければならない。
    {
      for(int j=(Prt*N)/(Prt+1);j<N;j++)
	{
	  for(int i=0;i<N;i++)
	    EigMat[i][j]*=1.0/sqrt(rt);
	}
    }
  NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.

  
  for(int j=0;j<N;j++)//固有値がすげえ負ならばそのときのPELを描いてもらう。
    {
      if(Eigval[j]<-EPS)
	{
	  for(int i=0;i<N;i++)
	    {
	      Eigvec[i]=EigMat[i][j];//どこの固有ベクターにするか数値0~DNumで指定。
	      //......そのどこの固有ベクターにするかってのもパラメータにすればよくない?
	    }
	  //	  NR::outputPEL3D(zahyo,Len,R,rt,alp,Prt,num,phi,Eigvec,D,j);
	  /*
	  tapping(Eigvec,Eigval[j],NR::potential3D(zahyo,Len,R,rt,alp,Prt,D),EPS);//この関数で固有ベクターの方向の微小(?)変位ベクトルを作成。(もしかしたら変位の大きさやばいかも)
	  for(int i=0;i<N;i++)
	    zahyo[i]+=Eigvec[i];
	  */
	  minus=false;
	}
    }

  NR::WriteEigInfo(EigMat,Eigval,num,phi);

}

void NR::WriteEigInfo(Mat_I_DP &EigMat,Vec_I_DP &Eigval,int num,DP phi)
{
  
  int N=Eigval.size();
  
  Vec_DP CMnumber(N);//,Eigvec(N);
  NR::CollectiveMotionCheck(EigMat,CMnumber);// IPR をCMnumberに格納
  
  //----------------------------------------------------------
  //あるサンプルnumの充填率PHIのときの状態密度の累積をTXT出力.
  //----------------------------------------------------------
  stringstream ss,ss2;
  ss.str("");
  ss2.str("");
  ss.clear(stringstream::goodbit);
  ss2.clear(stringstream::goodbit);
  ss<<num;
  ss2<<phi;

  string wrname;
  if(num<10)
    wrname ="EigCum0000"+ss.str()+'_'+ss2.str()+".txt";
  else if(num>=10 && num<100)
    wrname ="EigCum000"+ss.str()+'_'+ss2.str()+".txt";
  else if(num>=100 && num<1000)
    wrname ="EigCum00"+ss.str()+'_'+ss2.str()+".txt";
  else if(num>=1000 && num<10000)
    wrname ="EigCum0"+ss.str()+'_'+ss2.str()+".txt";
  else
    wrname ="EigCum"+ss.str()+'_'+ss2.str()+".txt";
  ofstream wrmode(wrname.data());
  /*
  for(int i=0;i<N;i++)
    Eigvec[i]=EigMat[i][0];
  */
  DP cmdist=1.0/N,cm=1.0;
  for(int i=0;i<N;i++)
    {
      //cout<<Eigval[i]<<' '<<cm<<'\n';
      wrmode<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<CMnumber[i]<<' '<<cm<<'\n';
      cm-=cmdist;
    }

  //累積の状態密度を導出しているが,ふつーのやつも矩形で区切って出してみるか...?
}



//----------------------------------------------------
//直交行列から,とある番号の固有ベクターを返却。
//----------------------------------------------------


void NR::deriveEigvec(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,Vec_O_DP &out,int D,int vecnum)
{
  
  int N=zahyo.size();
  if(vecnum>N-1 || vecnum<0)
    nrerror("your eigvecnum is inappropreate for deriving eigvec...");
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N);
  int cnt=0;
  NR::Hesspot(zahyo,Hes,Len,R,rt,alp,Prt,D);
  NR::jacobi(Hes,Eigval,EigMat,cnt);
  NR::eigsrt(Eigval,EigMat);
  Vec_DP Eigvec(N);
  for(int i=0;i<N;i++)
    {
      Eigvec[i]=EigMat[i][vecnum];//どこの固有ベクターにするか数値0~DNumで指定。
      //......そのどこの固有ベクターにするかってのもパラメータにすればよくない?
    }
  
  out=Eigvec;

}

//----------------------------------------------------
//直交行列から,とある番号の固有ベクターを返却。(3D)
//----------------------------------------------------


void NR::deriveEigvec3D(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,Vec_O_DP &out,int D,int vecnum)
{
  int N=zahyo.size();
  if(vecnum>N-1 || vecnum<0)
    nrerror("your eigvecnum is inappropreate for deriving eigvec...");
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N);
  int cnt=0;
  NR::Hesspot3D(zahyo,Hes,Len,R,rt,alp,Prt,D);
  NR::jacobi(Hes,Eigval,EigMat,cnt);
  NR::eigsrt(Eigval,EigMat);
  Vec_DP Eigvec(N);
  for(int i=0;i<N;i++)
    {
      Eigvec[i]=EigMat[i][vecnum];//どこの固有ベクターにするか数値0~DNumで指定。<- 引数与えてその位置の固有ベクターを吐き出すように改善すべき。
      //......そのどこの固有ベクターにするかってのもパラメータにすればよくない?
    }
  
  out=Eigvec;

}


//----------------------------------------------------
//固有ベクター方向でのPELをデータ出力。
//----------------------------------------------------

void NR::outputPEL(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum)
{
 int N=zahyo.size();
  Vec_DP Relrzahyo(N);

  stringstream ss,ss2,ss3;
  ss.str("");
  ss2.str("");
  ss3.str("");
  ss.clear(stringstream::goodbit);
  ss2.clear(stringstream::goodbit);
  ss3.clear(stringstream::goodbit);
  ss<<num;
  ss2<<phi;
  ss3<<vecnum;
  string wrname;//sample数5桁(0~99999サンプルまで)分のPELを取れるようにしておいた。
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
  ofstream wrPEL(wrname.data());

  int jmax=1000;//正の方向にjmax plots, 負の方向にjmax plotsの点を取る.
  for(int j=0;j<2*jmax;j++)//50000はテキトーな区間幅
    {
      double tmpfactor=(j-jmax)*0.00000001*Len*sqrt(D*N);//0.0000025は適当に設定.
      
      for(int i=0;i<N;i++)
	{
	  Relrzahyo[i]=zahyo[i]+tmpfactor*eigvec[i];
	}
      wrPEL<<0+tmpfactor<<' '<<setprecision(15)<<potential(Relrzahyo,Len,R,rt,alp,Prt,D)<<'\n';
    }
}

//----------------------------------------------------
//固有ベクター方向でのPELをデータ出力。(3D)
//----------------------------------------------------

void NR::outputPEL3D(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum)
{
  
 int N=zahyo.size();
  Vec_DP Relrzahyo(N);

  stringstream ss,ss2,ss3;
  ss.str("");
  ss2.str("");
  ss3.str("");
  ss.clear(stringstream::goodbit);
  ss2.clear(stringstream::goodbit);
  ss3.clear(stringstream::goodbit);
  ss<<num;
  ss2<<phi;
  ss3<<vecnum;
  string wrname;//sample数5桁(0~99999サンプルまで)分のPELを取れるようにしておいた。
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
  ofstream wrPEL(wrname.data());

  int jmax=1000;//正の方向にjmax plots, 負の方向にjmax plotsの点を取る.
  for(int j=0;j<2*jmax;j++)//jmax=50000はテキトーな区間幅
    {
      double tmpfactor=(j-jmax)*0.00000001*Len*sqrt(D*N);//0.0000025は適当に設定.
      
      for(int i=0;i<N;i++)
	{
	  Relrzahyo[i]=zahyo[i]+tmpfactor*eigvec[i];
	}
      wrPEL<<0+tmpfactor<<' '<<setprecision(15)<<potential3D(Relrzahyo,Len,R,rt,alp,Prt,D)<<'\n';
    }
}


void NR::CollectiveMotionCheck(Mat_I_DP &EigMat,Vec_IO_DP &CMnum)//IPRのこと.
{
  //DP eps=numeric_limits<double>::epsilon();
  int N=CMnum.size();
  for(int i=0;i<N;i++)
    {
      DP four=0;
      DP two=0;
      
      for(int j=0;j<N;j++)
	{
	  four+=pow(EigMat[j][i],4);
       	  two+=pow(EigMat[j][i],2);
	}
      two*=two;
      CMnum[i]=four/two;
    }
}


//--------------------------------------------------
//Distribution of coordination numberを計算func-----
//--------------------------------------------------

void NR::DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt,int D)
//座標値と半径、セル長さを受け取って次数i(粒子の接触数)の分布Dcod[i]を返却する関数である。(0~6までのベクトル型,sizeを7で宣言すべし)
{
  int N=p.size();
  int pN=N/D;
  Vec_INT tmpnum(pN);
  for(int i=0;i<Dcod.size();i++)
    Dcod=0.0;
  for(int i=0;i<pN;i++)
    tmpnum[i]=0;
  if(D==2)
    {
      DP sgm,relrx,relry,relr,Ri=R,Rj=R;
      for(int i=0;i<N;i+=D)
	{
	  if((Prt+1)*i==Prt*N)
	    Ri=rt*R;
	  Rj=R;
	  for(int j=0;j<i;j+=D)
	    {
	      if((Prt+1)*j==Prt*N)
		Rj=rt*R;
	      sgm=Ri+Rj;
	      relrx=p[j]-p[i];
	      relry=p[j+1]-p[i+1];

	      if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm)
		//上記の条件でポテンシャルに寄与するので
		//隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
		// A B C
		// D x E
		// F G H
		//xを自セルとして上記の他セルとの評価を行う。
		{
		  if(fabs(relrx-L)<sgm)//A or D or F
		    relrx-=L;
		  else if(fabs(relrx+L)<sgm)// C or E or H
		    relrx+=L;
		  //なにもしない otherwise (B or G)

		  if(fabs(relry-L)<sgm)//F or G or H
		    relry-=L;

		  else if(fabs(relry+L)<sgm)//A or B or C
		    relry+=L;

		  //なにもしない　otherwise (D or E)
		}//if-隣接セルend

	      relr=sqrt(pow(relrx,2)+pow(relry,2));
	      if(relr<sgm)
		{
		  tmpnum[i/D]+=1;
		  tmpnum[j/D]+=1;
		}
	    }//for-j-end
	}//for-i-end

    }
  else if(D==3)
    {
      DP sgm,relrx,relry,relrz,relr,Ri=R,Rj=R;
      for(int i=0;i<N;i+=D)
	{
	  if((Prt+1)*i==Prt*N)
	    Ri=rt*R;
	  Rj=R;
	  for(int j=0;j<i;j+=D)
	    {
	      if((Prt+1)*j==Prt*N)
		Rj=rt*R;
	      sgm=Ri+Rj;
	      relrx=p[j]-p[i];
	      relry=p[j+1]-p[i+1];
	      relrz=p[j+2]-p[i+2];

	      if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm || fabs(relrz)>L-sgm)
		//上記の条件でポテンシャルに寄与するので
		//隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
		// A B C
		// D x E
		// F G H
		//xを自セルとして上記の他セルとの評価を行う。
		{
		  if(fabs(relrx-L)<sgm)//A or D or F
		    relrx-=L;
		  else if(fabs(relrx+L)<sgm)// C or E or H
		    relrx+=L;
		  //なにもしない otherwise (B or G)

		  if(fabs(relry-L)<sgm)//F or G or H
		    relry-=L;
		  else if(fabs(relry+L)<sgm)//A or B or C
		    relry+=L;
		  //なにもしない　otherwise (D or E)
		  
  		  if(fabs(relrz-L)<sgm)
		    relrz-=L;
		  else if(fabs(relrz+L)<sgm)
		    relrz+=L;
		  //なにもしない　

		}//if-隣接セルend
	      relr=sqrt(pow(relrx,2)+pow(relry,2)+pow(relrz,2));
	      if(relr<sgm)
		{
		  tmpnum[i/D]+=1;
		  tmpnum[j/D]+=1;
		}
	    }//for-j-end
	}//for-i-end

    }
  else
    nrerror("space dimension D!=2 or 3...\n\n");
  
  
  DP dvd=1.0/pN;
  for(int i=0;i<pN;i++)
    {
      switch(tmpnum[i])
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

}//end void NR::DISTcod

//要変更。
void NR::tapping(Vec_IO_DP& EigDispvec,DP eigval, DP eng,DP EPS)
//エネルギーの値わかると嬉しい。
{
  int N=EigDispvec.size();
  DP norm=0.0,div;
  srand((unsigned)time(NULL));
  
  if(eigval>-EPS)
    nrerror("ERROR for tapping method");
  for(int i=0;i<N;i++)
    {
      norm+=EigDispvec[i]*EigDispvec[i];
    }      
  div=9*eng/(norm*10*eigval);//今、Potential Energyが1/10に下がるような変位について考えている。(2次近似ポテンシャルにおいて。)
  div=sqrt(div);
  if(rand()%2==1)
    div*=-1.0;
  for(int i=0;i<N;i++)
    EigDispvec[i]*=div;
}

void NR::noise(Vec_IO_DP& p,Vec_IO_DP& vel,DP &dmpt,DP mass, DP& tstep,DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,DP CRadBI)
{
  int N=p.size();
  Vec_DP ptmp(N);
  DP DeltaPHI=1.0e-8,phitmp=phi+DeltaPHI;
  //充填率が1.0e-8増える際の粒子変位の平均をノイズとしている。
  DP Radtmp,meandisp=0.0;
  srand((unsigned)time(NULL));
  ptmp=p;
  if(D==2)
    {
      Radtmp = CRadBI*sqrt(phi+DeltaPHI);
      NR::Velocity_Verlet_F(ptmp,vel,dmpt,mass,tstep,func,ftol,Len,Radtmp,rt,alp,Prt,num,phitmp,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,D,iterVV);
    }
  else if(D==3)
    {
      Radtmp = CRadBI*pow(phi+DeltaPHI,0.3333333333333333);
      NR::Velocity_Verlet_F3D(ptmp,vel,dmpt,mass,tstep,func,ftol,Len,Radtmp,rt,alp,Prt,num,phitmp,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,D,iterVV);
    }
  else
    nrerror("Noise-function is for 2 or 3D...\n\n");

  for(int i=0;i<N;i++)
    {
      meandisp+=fabs(ptmp[i]-p[i]);

    }
  meandisp*=(1.0/N);
  /*
  if(meandisp<numeric_limits<double>::epsilon()*1.0e-3)
    nrerror("noise is too infinitesimally small...\n");
  */
  //else
  //{
      for(int i=0;i<N;i++)//-1 or +1 というような摂動のかけ方をする。(-1~+1というかけ方でもイイ気がするけど、それか1粒子について半径1の球面のどこかに移動とか??)
	{
	  if(rand()%2==0)
	    p[i]-=meandisp;
	  else
	    p[i]+=meandisp;
	}
      //}
}
