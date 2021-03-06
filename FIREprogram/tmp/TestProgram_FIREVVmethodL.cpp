#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include "MT.h"
#include "jt.h"

using namespace std;

///////////////
//attention!!//
///////////////
//DMPtは速度比例の抵抗定数gammaに(Delta t)をかけたalphaの値(FIRE参照)。
//ここで使われているF,Ftmp,Fnextなどは力の次元ではなく、(力)x(Delta t)/(2m)となっている。

//----------------------------------------------------
//CG法を用いたgranular packingの構築(本体)------------
//----------------------------------------------------

int main(int argc,char* argv[])
{
  if(JT::errArguments(argc))
    return 1;

  //----------------------------------------------------
  //---Simulation of the Jamming Systemのパラメータ-----
  //----------------------------------------------------
  
  int sd_s=atoi(argv[1]);//sd_sは乱数seedのスタート値
  int sd_e=atoi(argv[2]);//sd_eは乱数seedループのend値
  DP PHIstart =atof(argv[3]);//初期PHI
  DP TargetPHI =atof(argv[4]);//目的地PHI
  //!!下げの場合はunjammedで結局breakするので十分に低ければok
  DP DeltaPHIinit=atof(argv[5]);//PHIの上げ下げ刻み幅
  const int PNum=atoi(argv[6]);//粒子数
  const int dim=atoi(argv[7]);//次元
  const DP ratio=atof(argv[8]);//粒子のサイズ比1.0(要素1):ratio(要素2)
  const int Pratio1=atoi(argv[9]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  const int Pratio2=atoi(argv[10]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  
  //-------------------------------------------//
  //-----------Box size 可変スタイル-----------//
  double Lr;//Leng ratio (N128 as standard size)
  if(dim==2) {
    Lr=(1.0e+2)*sqrt(PNum/128.0); // Leng変更してシミュレーション.
  }
  else if(dim==3) {
    Lr=(1.0e+2)*pow(PNum/128.0,0.3333333333333333); // Leng変更してシミュレーション.
  }
  else {
    cerr<<"invalid dimension case...(must be 2 or 3) yours:"<<dim<<endl;
    exit(1);
  }
  const DP Leng=Lr;//立方体の一辺の長さ
  //-------------------------------------------//
  
  DP pot;//potential energy
  const DP alpha =2.0;//potential exponent
  Vec_DP distcod(20);//接触数分布
  stringstream ss,ss2,ss3,sserr,ss_simerr;
  ofstream kakikoPHIJ,kakikoSingle,kakikoCODDIST,kakikoJCBERR,kakikoSIMERR;
  int cnter=0;//sample-counter
  string strdate="0524"; //DATE
  const DP eps=1.0; //potentialのオーダー
  if(JT::errPN(PNum) || JT::errDim(dim) || JT::errPratio(Pratio1,Pratio2,PNum))
    return 1;
  JT::startingMessage(sd_s,sd_e,PHIstart,TargetPHI,DeltaPHIinit);
  ss2<<"VV"<<strdate<<"_R"<<sd_s<<"to"<<sd_e<<"_PNum"<<PNum<<"_alpha"<<alpha<<'_'<<PHIstart<<".txt";
  kakikoPHIJ.open(ss2.str().data());
  
  

  //-------------------------------------------
  //----------------MDパラメータ---------------
  //-------------------------------------------
  //!(ratio)が異なる場合,2番目のmassは(MASS*ratio)になる.
  //!同じ球形でmassが異なる構成要素については,この場で考えてない.
  //!BIdisperseの場合のmassは各々のroutineでmass処理している.
  //!ここを変える場合はHessian matrixやMDfuncも変えねばならない.
  //kb=1.38064852*1.0e-23;
  DP Tstep=1.0e-2,PHI,CRadBI;
  const DP MASS=1.0,ftol=numeric_limits<double>::epsilon(),fftol=ftol*1.0e-3;
  const int DNum=PNum*dim;//Configurational Dimension Number
  Vec_DP zahyo(DNum),zahyotmp(DNum),sokudo(DNum);
  bool pluseig=true,invalidflag,iprerror;//scheduling var
  int notrelaxeig=0,VViter,loopcnt=0;//scheduling var

  //CRadBIは半径更新のための定数
  //fftolはunjammed stateを評価するための値(pot~0と見なす.)
  //

  //-------------------------------------------
  //--------------FIREパラメータ---------------
  //-------------------------------------------
  const DP fra_inc=1.1,fra_dec=0.5,fra_alp=0.99,dmpt_init=1.0e-1;
  DP DMPt,tstep_max,DeltaPHI,Rad,n_strength;
  int ITFIRE;
  const int iter_times=500000;//MDのステップ回数
  //DMPt = (damping factor)*(delta t) 

  //
  //////////////////////////////////////////////
  ///////////////     本体     /////////////////
  //////////////////////////////////////////////
  if(dim==2)//2D method
    {
      for(int l=sd_s;l<sd_e;l++)//sample loop
	{
	  //Initialize FIRE parameter
	  JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad);
	  JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	  JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	  MT::init_genrand(l);
	  for(int i=0;i<DNum;i++)
	    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
      
	  for(int i=0;i<99999;i++)//PHI loop
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      JT::noise(zahyo,Rad,Leng,n_strength);
	      JT::dim2::Velocity_Verlet_F(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim2::potential,ftol,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter);//
	      pot=JT::dim2::potential(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps);//
	      if(loopcnt>0)
	        JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,VViter,n_strength);
	      
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-6)
		//一個前の座標とPHIに戻す
		JT::dim2::backtoPreviousPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim);
	      else
		{
		  JT::PeriodicMove(zahyo,Leng);//?
		  if(pot<fftol) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim2::DISTcod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<VViter<<' '<<(int)pluseig<<endl;
		    JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    
		    break;
		  }
		  JT::dim2::ModeCalc2D(zahyo,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror);//
		  /*
		  if(invalidflag==true) {
		    JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,VViter);
		    break;
		  }
		  */
		  if(pluseig==true && iprerror==false && invalidflag==false) { //modify!
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim2::DISTcod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<VViter<<' '<<(int)pluseig<<endl;
		    JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    if(DeltaPHI==0.0)
		      break;
		    JT::dim2::forwardtoPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim);
		  }
		  else {
		    //負の固有値が出てきたのでノイズかけてもういっかい.
		    /*
		    if(pluseig==true && iprerror==true)
		      JT::OutputForQt(zahyo,dim,PNum,PHI,ratio,Pratio,l);
		    */
		    if(invalidflag==true) {
		      JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,VViter);
		    }
		    if(loopcnt>=25 && loopcnt<30) {
		      JT::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,dim,PNum,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,VViter,pluseig,iprerror,invalidflag);
		    }
		    if(loopcnt==30) {
		      break;
		    }
		    if(i%2==0)
		      loopcnt+=1;
		  }
		}
	    }//PHI-loop-end
	  kakikoSingle.close();
	  kakikoPHIJ<<setprecision(10)<<l<<' '<<PHI<<' '<<notrelaxeig<<endl;
	  cnter+=1;
	  cout<<cnter<<"回目のRAND"<<l<<"の反復操作が終了しました\n"<<endl;
	}
      kakikoPHIJ.close();
    }
  else if(dim==3)//3D method
    {
      for(int l=sd_s;l<sd_e;l++)
	{
	  //Initialize parameter
	  JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad);
	  JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	  JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	  
	  MT::init_genrand(l);
	  for(int i=0;i<DNum;i++)
	    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
	  
	  for(int i=0;i<99999;i++)//99999はテキトー.
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      JT::noise(zahyo,Rad,Leng,n_strength);
	      JT::dim3::Velocity_Verlet_F3D(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim3::potential3D,ftol,Leng,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter);//
	      pot=JT::dim3::potential3D(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps);//
	      if(loopcnt>0)
		JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,VViter,n_strength);
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-6)
		//一個前の座標とPHIに戻す
		JT::dim3::backtoPreviousPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim);
	      else
		{
		  JT::PeriodicMove(zahyo,Leng);//?
		  if(pot<fftol) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim3::DISTcod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<VViter<<' '<<(int)pluseig<<endl;
		    JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    break;
		  }
		  JT::dim3::ModeCalc3D(zahyo,Leng,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror);//

		  if(pluseig==true && iprerror==false && invalidflag==false) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim3::DISTcod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim);
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<VViter<<' '<<(int)pluseig<<endl;
		    JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    if(DeltaPHI==0.0)
		      break;
		    JT::dim3::forwardtoPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim);
		  }
		  else {
		    if(invalidflag==true) {
		      JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,VViter);
		    }
		    if(loopcnt>=25 && loopcnt<30) {
		      JT::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,dim,PNum,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,VViter,pluseig,iprerror,invalidflag);
		    }
		    if(loopcnt==30) {
		      break;
		    }
		    if(i%2==0)
		      loopcnt+=1;
		  }
		}
	    }//phi-loop-end
	  kakikoSingle.close();
	  kakikoPHIJ<<setprecision(10)<<l<<' '<<PHI<<' '<<notrelaxeig<<endl;
	  cnter+=1;
	  cout<<cnter<<"回目のRAND"<<l<<"の反復操作が終了しました\n"<<endl;
      	}
      kakikoPHIJ.close();
    }
  else {
    cerr<<"Cannot calculate except for 2D and 3D systems!!\n\n"<<endl;
    exit(1);
  }
  return 0;
}
